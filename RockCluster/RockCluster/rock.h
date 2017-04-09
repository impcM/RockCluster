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
	int _k;     //������Ŀ
	double _th;     //�ڽ���ֵ
	std::vector<AlertData> _point;   //���ݵ�
	double **_similarityMatrix;  //���ƶȾ���
	int **_linkMatrix;         //���Ӿ���
	int **_adjacency;           //��ͬ�ھӾ���
	int _dataSize;             //���ݴ�С
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
	//��ά���鶯̬���ٿռ�
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