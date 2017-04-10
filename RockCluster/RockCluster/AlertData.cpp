#include "stdafx.h"
#include "AlertData.h"

AlertData::AlertData(std::string srcip, int srcport, std::string dstip, int dstport, std::string proto, time_t timestamp, std::string alertType, int risk) :
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
			ret = (ret << 8) + atoi(ip.substr(k, i).c_str());
			k = i + 1;
		}
	}
	ret = (ret << 8) + atoi(ip.substr(k, i).c_str());
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