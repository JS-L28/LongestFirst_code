#include "CRCgenerator.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <bitset>
#include "header.h"

using namespace std;
CRCgenerator::CRCgenerator()
{
    //CRC_Row = bitset<32>("01011101111101011100010100110111");
    CRC_Row = bitset<64>("0101110111110101110001010011011101110010101110010111000010110010");
    //CRC_mem.resize(PrefixLength);
}

bitset<64> CRCgenerator::CRC(bitset<PrefixLength> A_reg, int length)
{
    bitset<64> CRC;
    bitset<64> CRC_reg;
    CRC_reg = bitset<64>("0101110111110101110001010011011101110010101110010111000010110010");
    int count = 0;
    while (count != length)
    {
        CRC[0] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[63];
        CRC[1] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[0];
        CRC[2] = CRC_reg[1];
        CRC[3] = CRC_reg[2];
        CRC[4] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[3];
        CRC[5] = CRC_reg[4];
        CRC[6] = CRC_reg[5];
        CRC[7] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[6];
        CRC[8] = CRC_reg[7];
        CRC[9] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[8];
        CRC[10] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[9];
        CRC[11] = CRC_reg[10];
        CRC[12] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[11];
        CRC[13] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[12];
        CRC[14] = CRC_reg[13];
        CRC[15] = CRC_reg[14];
        CRC[16] = CRC_reg[15];
        CRC[17] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[16];
        CRC[18] = CRC_reg[17];
        CRC[19] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[18];
        CRC[20] = CRC_reg[19];
        CRC[21] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[20];
        CRC[22] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[21];
        CRC[23] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[22];
        CRC[24] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[23];
        CRC[25] = CRC_reg[24];
        CRC[26] = CRC_reg[25];
        CRC[27] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[26];
        CRC[28] = CRC_reg[27];
        CRC[29] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[28];
        CRC[30] = CRC_reg[29];
        CRC[31] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[30];

        CRC[32] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[31];
        CRC[33] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[32];
        CRC[34] = CRC_reg[33];
        CRC[35] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[34];
        CRC[36] = CRC_reg[35];
        CRC[37] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[36];
        CRC[38] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[37];
        CRC[39] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[38];
        CRC[40] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[39];
        CRC[41] = CRC_reg[40];
        CRC[42] = CRC_reg[41];
        CRC[43] = CRC_reg[42];
        CRC[44] = CRC_reg[43];
        CRC[45] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[44];
        CRC[46] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[45];
        CRC[47] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[46];
        CRC[48] = CRC_reg[47];
        CRC[49] = CRC_reg[48];
        CRC[50] = CRC_reg[49];
        CRC[51] = CRC_reg[50];
        CRC[52] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[51];
        CRC[53] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[52];
        CRC[54] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[53];
        CRC[55] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[54];
        CRC[56] = CRC_reg[55];
        CRC[57] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[56];
        CRC[58] = CRC_reg[57];
        CRC[59] = CRC_reg[58];
        CRC[60] = CRC_reg[59];
        CRC[61] = CRC_reg[60];
        CRC[62] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[61];
        CRC[63] = CRC_reg[62];
        count += 1;
        CRC_reg = CRC;

    }

    CRC_Row = CRC_reg;
    return CRC_Row;
}

/*bitset<32> CRCgenerator::CRC(bitset<PrefixLength> A_reg, int length)
{
    bitset<32> CRC;
    bitset<32> CRC_reg;
    CRC_reg = bitset<32>("01011101111101011100010100110111");
    int count = 0;
    while (count != length)
    {
        CRC[0] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[31];
        CRC[1] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[0];
        CRC[2] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[1];
        CRC[3] = CRC_reg[2];
        CRC[4] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[3];
        CRC[5] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[4];
        CRC[6] = CRC_reg[5];
        CRC[7] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[6];
        CRC[8] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[7];
        CRC[9] = CRC_reg[8];
        CRC[10] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[9];
        CRC[11] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[10];
        CRC[12] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[11];
        CRC[13] = CRC_reg[12];
        CRC[14] = CRC_reg[13];
        CRC[15] = CRC_reg[14];
        CRC[16] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[15];
        CRC[17] = CRC_reg[16];
        CRC[18] = CRC_reg[17];
        CRC[19] = CRC_reg[18];
        CRC[20] = CRC_reg[19];
        CRC[21] = CRC_reg[20];
        CRC[22] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[21];
        CRC[23] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[22];
        CRC[24] = CRC_reg[23];
        CRC[25] = CRC_reg[24];
        CRC[26] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[25];
        CRC[27] = CRC_reg[26];
        CRC[28] = CRC_reg[27];
        CRC[29] = CRC_reg[28];
        CRC[30] = CRC_reg[29];
        CRC[31] = CRC_reg[30];
        count += 1;
        CRC_reg = CRC;

    }

    CRC_Row = CRC_reg;
    return CRC_Row;
}
*/

/*
vector<bitset<32>> CRCgenerator::readyCRC(bitset<PrefixLength> A_reg) //½ÇÆÐ. Æó±â!!
{
    bitset<32> CRC;
    bitset<32> CRC_reg;
    CRC_reg = bitset<32>("01011101111101011100010100110111");
    vector<bitset<32>> CRC_mem(PrefixLength);
    int count = 0;
    while (count != PrefixLength)
    {
        CRC[0] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[31];
        CRC[1] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[0];
        CRC[2] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[1];
        CRC[3] = CRC_reg[2];
        CRC[4] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[3];
        CRC[5] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[4];
        CRC[6] = CRC_reg[5];
        CRC[7] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[6];
        CRC[8] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[7];
        CRC[9] = CRC_reg[8];
        CRC[10] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[9];
        CRC[11] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[10];
        CRC[12] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[11];
        CRC[13] = CRC_reg[12];
        CRC[14] = CRC_reg[13];
        CRC[15] = CRC_reg[14];
        CRC[16] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[15];
        CRC[17] = CRC_reg[16];
        CRC[18] = CRC_reg[17];
        CRC[19] = CRC_reg[18];
        CRC[20] = CRC_reg[19];
        CRC[21] = CRC_reg[20];
        CRC[22] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[21];
        CRC[23] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[22];
        CRC[24] = CRC_reg[23];
        CRC[25] = CRC_reg[24];
        CRC[26] = A_reg[PrefixLength - static_cast<size_t>(count) - 1] ^ CRC_reg[25];
        CRC[27] = CRC_reg[26];
        CRC[28] = CRC_reg[27];
        CRC[29] = CRC_reg[28];
        CRC[30] = CRC_reg[29];
        CRC[31] = CRC_reg[30];
        CRC_mem[count] = CRC_reg;

        CRC_reg = CRC;
        count += 1;

    }
    return CRC_mem;

}
*/
CRCgenerator::~CRCgenerator()
{

}
