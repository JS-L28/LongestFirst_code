#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <bitset>

#include "header.h"

using namespace std;


class CRCgenerator
{
public:
	CRCgenerator();

	//bitset<32> CRC(bitset<PrefixLength> A_reg, int cou);
	//vector<bitset<32>> readyCRC(bitset<PrefixLength> A_reg);

	//bitset<32> CRC_Row;

	bitset<64> CRC_Row;

	bitset<64> CRC(bitset<PrefixLength> A_reg, int length);

	~CRCgenerator();

};

