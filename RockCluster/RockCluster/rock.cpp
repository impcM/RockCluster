#include "stdafx.h"
#include "rock.h"
#include <cmath>
#include <fstream>

rock::rock(std::vector<AlertData> point, int k, double th)
{
	this->_point = point;
	this->_k = k;
	this->_th = th;
	this->_dataSize = _point.size();
	this->_powcount = 1.0 + 2.0 * (1 - th) / (1 + th);
	//二维数组动态开辟空间
	_similarityMatrix = new double*[_dataSize];
	_linkMatrix = new int*[_dataSize];
	_adjacency = new int*[_dataSize];
	for (int i = 0; i < _dataSize; i++)
	{
		_similarityMatrix[i] = new double[_dataSize];
		_linkMatrix[i] = new int[_dataSize];
		_adjacency[i] = new int[_dataSize];
	}
	//初始化
	for (int i = 0; i < _dataSize; i++)
	{
		for (int j = 0; j < _dataSize; j++)
		{
			_similarityMatrix[i][j] = 0;
			_linkMatrix[i][j] = 0;
			_adjacency[i][j] = 0;
		}
	}
}

rock::~rock()
{
	for (int i = 0; i < _dataSize; i++)
	{
		delete[] _similarityMatrix[i];
		delete[] _linkMatrix[i];
		delete[] _adjacency[i];
	}
	delete[] _similarityMatrix;
	delete[] _linkMatrix;
	delete[] _adjacency;
	//	delete similarityMatrix;
	//	delete linkMatrix;
	//	delete clusterResult;
}


void rock::calculateMatrix(){
	for (int i = 0; i < _dataSize; i++)
	{
		_linkMatrix[i][i] = 1;
	}
	for (int i = 0; i < _dataSize; i++)
	{
		for (int j = i + 1; j < _dataSize; j++)
		{
			_similarityMatrix[i][j] = _point[i].calculateSimilary(_point[j]);
			if (_similarityMatrix[i][j] > _th)
			{
				_linkMatrix[i][j] = _linkMatrix[j][i] = 1;
			}
		}
	}
	for (int i = 0; i < _dataSize; i++)
	{
		for (int j = i; j < _dataSize; j++)   //三角阵，只需要计算一半
		{
			_adjacency[i][j] = 0;
			for (int k = 0; k < _dataSize; k++)
			{
				_adjacency[i][j] += _linkMatrix[i][k] * _linkMatrix[k][j];
			}
			_adjacency[j][i] = _adjacency[i][j];
		}
	}

}
//计算goodnessMeasure
double rock::calculateGoodnessMeasure(std::vector<int> &clusteri, std::vector<int> &clusterj)
{
	int leni = clusteri.size();
	int lenj = clusterj.size();
	double link = 0.0;
	double goodnessMeasure = 0.0;
	for (int i = 0; i < leni; i++)
	{
		for (int j = 0; j < lenj; j++)
		{
			link += _adjacency[clusteri[i]][clusterj[j]];
		}
	}
	goodnessMeasure = link / (pow(leni + lenj, _powcount) - pow(leni, _powcount) - pow(lenj, _powcount));
	return goodnessMeasure;
}
//寻找当前最好聚类
void rock::findBestMerge(int &clusteri, int &clusterj)
{
	clusteri = -1;
	clusterj = -1;
	double maxGoodnessMeasure = 0.0;
	double goodnessMeasure = 0.0;
	int len = cluster.size();
	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			goodnessMeasure = calculateGoodnessMeasure(cluster[i], cluster[j]);
			if (goodnessMeasure > maxGoodnessMeasure)
			{
				maxGoodnessMeasure = goodnessMeasure;
				clusteri = i;
				clusterj = j;
			}
		}
	}
}


void rock::fit(){

	calculateMatrix();     //计算相似度矩阵和邻居矩阵
	//建立初始聚类
	for (int i = 0; i < _dataSize; i++)
	{
		std::vector<int> temp;
		temp.push_back(i);
		cluster.push_back(temp);
	}
	int current_cluster = _dataSize;
	int clusteri = 0;
	int clusterj = 0;
	while (current_cluster > _k)
	{
		findBestMerge(clusteri, clusterj);
		if (clusteri == -1 || clusterj == -1)     //没有具有合并关系的类
			break;
		int lenj = cluster[clusterj].size();
		for (int i = 0; i < lenj; i++)
		{
			cluster[clusteri].push_back(cluster[clusterj][i]);
		}
		auto it = cluster.begin();
		for (it = cluster.begin(); it != cluster.end() && clusterj > 0; it++, clusterj--)
		{
		}
		cluster.erase(it);
		current_cluster--;
		printf("\rcurrent process: %lf%%", (_dataSize - current_cluster) * 100.0 / (_dataSize - _k));
		fflush(stdout);
	}
	printf("\rcurrent process: 100%");
	fflush(stdout);
	std::ofstream outfile;
	outfile.open("cluster_result.txt", std::ios::out | std::ios::trunc);
	if (outfile.fail())
	{
		printf("file open fail!\n");
	}
	else
	{
		int len = cluster.size();
		for (int i = 0; i < len; i++)
		{
			outfile << "the " << i << " cluster: ";
			for (int j = 0; j < cluster[i].size(); j++)
				outfile << cluster[i][j] << " ";
			outfile << "\n";
		}
	}
	outfile.close();
	
}