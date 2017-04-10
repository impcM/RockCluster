// RockCluster.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "rock.h"


int loadFile(std::string filename, std::vector<AlertData> &data){
	std::ifstream input(filename, std::ios::in);
	char buffer[256];
	int buffersize = 256;
	int i = 3;
	while (--i > 0)
	{
		input.getline(buffer, buffersize);
		std::cout << buffer << std::endl;
	}
	while (!input.eof())
	{
		input.getline(buffer, buffersize);
		int count = strlen(buffer);
		std::string temp[8];
		int k = 0;

		for (int j = 0; j < count; j++)
		{
			if (buffer[j] == ',')
			{
				k++;
			}
			else
			{
				temp[k] += buffer[j];
			}
		}
		AlertData alert(temp[0], atoi(temp[1].data()), temp[2], atoi(temp[3].c_str()), temp[4], atoi(temp[5].c_str()), temp[6], atoi(temp[7].c_str()));
		data.push_back(alert);
	}
	input.close();
	return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<AlertData> data;
	loadFile("alertData.txt", data);
	rock myrock(data, 10, 0.75);
	myrock.fit();
	system("pause");
	return 0;
}

