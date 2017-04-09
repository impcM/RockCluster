#pragma once
#ifndef _ROCK_
#define _ROCK
#include <string>
#include <vector>
#include "AlertData.h"
//class AlertData;

class rock
{
public:
	rock(std::vector<AlertData> point, int k, double th);
	~rock();
	void fit();
private:
	int _k;     //聚类数目
	double _th;     //邻接阈值
	std::vector<AlertData> _point;   //数据点
	double **_similarityMatrix;  //相似度矩阵
	int **_linkMatrix;         //链接矩阵
	int **_adjacency;           //共同邻居矩阵
	int _dataSize;             //数据大小
	std::vector<std::vector<int> > cluster;
	double _powcount = 0.0;
	void calculateMatrix();
	void findBestMerge(int &clusteri, int &clusterj);
	double calculateGoodnessMeasure(std::vector<int> &clusteri, std::vector<int> &clusterj);
};

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



#endif