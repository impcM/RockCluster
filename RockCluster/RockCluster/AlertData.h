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

AlertData::AlertData(std::string srcip = nullptr, int srcport = 0, std::string dstip = nullptr, int dstport = 0, std::string proto = nullptr, time_t timestamp = 0, std::string alertType = nullptr, int risk = 1) :
_srcip(srcip), _srcport(srcport), _dstip(dstip), _dstport(dstport), _proto(proto), _timestamp(timestamp), _alertType(alertType), _risk(risk)
{
}
AlertData::AlertData(const AlertData &temp){
	this->_alertType = temp._alertType;
	this->_dstip = temp._dstip;
	this->_dstport = temp._dstport;
	this->_proto = temp._proto;
	this->_risk = temp._risk;
	this->_srcip = temp._srcip;
	this->_srcport = temp._srcport;
	this->_timestamp = temp._timestamp;
}

int ip2num(std::string ip)
{
	int ret = 0;
	int len = ip.size();
	int k = 0;
	int i = 0;
	for (i = 0; i < len; i++)
	{
		if (ip[i] == '.')
		{
			ret = ret << 8 + atoi(ip.substr(k, i).c_str());
			k = i + 1;
		}
	}
	ret = ret << 8 + atoi(ip.substr(k, i).c_str());
	return ret;
}

double ipSimilar(std::string ip1, std::string ip2)
{
	if (ip1 == ip2)
		return 1.0;
	int i_ip1 = ip2num(ip1);
	int i_ip2 = ip2num(ip2);
	int result = i_ip1 ^ i_ip2;
	int i = 0;
	for (i = 0; i < 32; i++)
	{
		if (result == 0)
			break;
		result >>= 1;
	}
	return (double)((32.0 - i) / 32.0);
}

double AlertData::calculateSimilary(const AlertData &data)
{
	double similar = 0.0;
	double alpha[8] = { 0.2, 0.0, 0.8, 0.0, 0.0, 0.0, 0.0, 0.0 };
	similar = similar + alpha[0] * ipSimilar(this->_srcip, data._srcip);
	similar = similar + alpha[2] * ipSimilar(this->_dstip, data._dstip);
	return similar;
}

AlertData::~AlertData()
{
}

#endif