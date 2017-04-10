#pragma once
#ifndef _ALERTDATA_
#define _ALERTDATA_
#include <string>
class AlertData
{
public:
	AlertData(std::string srcip = nullptr, int srcport = 0, std::string dstip = nullptr, int dstport = 0, std::string proto = nullptr, time_t timestamp = 0, std::string alertType = nullptr, int risk = 1);
	AlertData(const AlertData &temp);
	~AlertData();
	double calculateSimilary(const AlertData &data);
private:
	std::string _srcip;
	int _srcport;
	std::string _dstip;
	int _dstport;
	std::string _proto;
	time_t _timestamp;
	std::string _alertType;
	int _risk;
};



#endif