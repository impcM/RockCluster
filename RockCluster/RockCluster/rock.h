#pragma once
#ifndef _ROCK_
#define _ROCK
#include <string>
#include <vector>
#include "AlertData.h"

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




#endif