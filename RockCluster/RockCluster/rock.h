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




#endif