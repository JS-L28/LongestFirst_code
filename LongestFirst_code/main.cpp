#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <bitset>
#include "header.h"
#include "CRCgenerator.h"
#include <cstdint>
using namespace std;
int No_of_BF_Access = 0;
int No_of_hash_Access = 0;
std::ofstream fin5;

void processPrefixes(int lastPosLevel, std::string& currenIP, std::string& Hash_h1_prefix)
{

    std::bitset<32> cmpIPAddr(currenIP);
    std::bitset<32> cmp_h1_Prefix(Hash_h1_prefix);
    //std::bitset<32> cmp_h2_Prefix(Hash_h2_prefix); 

    if (lastPosLevel <= 32 && lastPosLevel > 0) {
        std::bitset<32> mask = (~0u << (32 - lastPosLevel)) & 0xFFFFFFFF;

        cmpIPAddr = cmpIPAddr & mask;
        cmp_h1_Prefix = cmp_h1_Prefix & mask;
        //cmp_h2_Prefix = cmp_h2_Prefix & mask;
    }

    currenIP = cmpIPAddr.to_string();
    Hash_h1_prefix = cmp_h1_Prefix.to_string();
    //Hash_h2_prefix = cmp_h2_Prefix.to_string(); // Update data 
}

void BFQuery(std::bitset<BF_size> BF, std::bitset<32> curIP, int Length, std::vector<std::string>& HASH, CRCgenerator* crc0)
{

    while (Length > 0) {
        No_of_BF_Access += 1;
    //cout << "bf" << No_of_BF_Access << endl;

    //int lastPosLevel = PrefixLength - 1;

    int ranges[k_num][2] = { // ************************************
        {A, M},  // Start at bit 0, length m 
        {B, M},
        {C, M},
        //{D, M},
        //{E, M},
        //{F, M},

        //{G, M},
        //{H, M},
        //{I, M},
        //{J, M},
        //{K, M}
    };

    /*
    int ranges[6][2] = { // ************************************
        {0, M},  // Start at bit 0, length m
        {3, M},
        {6, M},
        {9, M},
        {12, M},
        {16, M}
    };
    */

    std::vector<unsigned long long> index(k_num);

    for (int k = 0; k < k_num; k++) //BF index generation
    {
        int start = ranges[k][0];
        int ilength = ranges[k][1];
        std::bitset<cbit> mask((1ull << ilength) - 1);
        std::bitset<cbit> range = (crc0->CRC(curIP, Length) >> start) & mask;
        std::bitset<M> Bitset(range.to_ullong());
        index[k] = Bitset.to_ullong();

        //cout << "index"<< index[k] << endl;
        //index[k] = (range.to_ulong());

    }

    //bool BFQueryPos = (BF[index[0]] && BF[index[1]] && BF[index[2]] && BF[index[3]] && BF[index[4]] && BF[index[5]] && BF[index[6]] && BF[index[7]] && BF[index[8]] && BF[index[9]] && BF[index[10]]);
    //bool BFQueryNeg = (!BF[index[0]] || !BF[index[1]] || !BF[index[2]] || !BF[index[3]] || !BF[index[4]] || !BF[index[5]] || !BF[index[6]] || !BF[index[7]] || !BF[index[8]] || !BF[index[9]] || !BF[index[10]]);


    //bool BFQueryPos = (BF[index[0]] && BF[index[1]] && BF[index[2]] && BF[index[3]] && BF[index[4]] && BF[index[5]]);
    //bool BFQueryNeg = (!BF[index[0]] || !BF[index[1]] || !BF[index[2]] || !BF[index[3]] || !BF[index[4]] || !BF[index[5]]);


    bool BFQueryPos = (BF[index[0]] && BF[index[1]] && BF[index[2]]);
    bool BFQueryNeg = (!BF[index[0]] || !BF[index[1]] || !BF[index[2]]);

    if (BFQueryPos) //HashAccess
    {
        //cout << "BFQueryPos" << " , length: " << Length << endl;

        std::bitset<cbit> hmask_upper = ((1ull << N) - 1) << Ha; // mask for upper 16 bits
        std::bitset<cbit> hmask_lower = (1ull << N) - 1;         // mask for lower 16 bits

        std::bitset<cbit> hrange1 = ((crc0->CRC(curIP, Length)) & hmask_upper) >> Ha;
        std::bitset<cbit> hrange2 = (crc0->CRC(curIP, Length)) & hmask_lower;
        std::bitset<N> hashindex1(hrange1.to_ullong());
        std::bitset<N> hashindex2(hrange2.to_ullong());
        int attempts = 0; // number of hash attempts made

        bool found = false;
        string currenIP = curIP.to_string();


        //cout << currenIP;

        No_of_hash_Access += 1;
        while (attempts < HashTableSize) {
            // Calculate the new hash index using double hashing
            std::bitset<N> newIndex((hashindex1.to_ullong() + attempts * hashindex2.to_ullong()) % HashTableSize);

            string currentRow = HASH[newIndex.to_ullong()];

            if (currentRow == "1111111111111111111111111111111111111111111111111111111111") {
                // Empty slot found, end the search
                break;
            }

            string currentPreLen = currentRow.substr(0, 6);
            string currentPrefix = currentRow.substr(6, 32);
            string currentBMP = currentRow.substr(38, BMP_LEN);

            bitset<6> l(Length);
            bitset<BMP_LEN> bmpBits(currentBMP);

            string tempCurrenIP = currenIP;
            string tempCurrentPrefix = currentPrefix;

            if (Length >= 1)
                processPrefixes(Length, tempCurrenIP, tempCurrentPrefix);
            else {
                found = false;
                break;
            }

            if (l.to_string() == currentPreLen && tempCurrenIP == tempCurrentPrefix) {
                int bmp = 0;
                for (int j = 0; j < BMP_LEN; j++) {
                    bmp += (bmpBits[j]) * pow(2, j);
                }
                //cout << "BMP = " << bmp << endl;
                fin5 << "IP_Addr = " << curIP << ", BMP = " << bmp
                    << ", No_of_hash_Access = " << No_of_hash_Access
                    << ", No_of_BF_Access = " << No_of_BF_Access << std::endl;
                found = true;
                break;
            }

            attempts++;
        }

        if (found) {
            return; 
        }

        Length -= 1;
        continue;
    }
    else if (BFQueryNeg) {
        Length -= 1; 
        continue;
    }
    }

    fin5 << "IP_Addr = " << curIP << ", BMP = " << "z"
        << " No_of_hash_Access = " << No_of_hash_Access
        << ", No_of_BF_Access = " << No_of_BF_Access << std::endl;
    No_of_hash_Access -= 1;


}



int main()
{
    string BMP;
    bool TruePos = 0;


    
    ifstream fin;
    fin.open("..\\binary.txt");
    if (!fin) {
        cout << "Failed to open the prefix file" << endl;
        return -1;
    }

    std::vector<std::vector<std::string>> myArray(No_BFnodes, std::vector<std::string>(3));

    for (int i = 0; i < No_BFnodes; i++) {
        for (int j = 0; j < 3; j++) {

            fin >> myArray[i][j];
        }
    }

    std::vector<std::string> prefix(No_BFnodes);
    std::bitset<BF_size> BF;

    for (int i = 0; i < No_BFnodes; i++)
    {
        CRCgenerator* crc = new CRCgenerator();
        //cout << i << endl;
        prefix[i] = myArray[i][1].substr(0, stoi(myArray[i][0]));
        std::bitset<32> preval(myArray[i][1]);
        std::bitset<32> bitsetVal(prefix[i]);
        int length = stoi(myArray[i][0]);

        crc->CRC(preval, length);

        std::bitset<cbit> CRC_reg = crc->CRC_Row;

        // ************************************
        int ranges[k_num][2] = {
            {A, M},
            {B, M},
            {C, M},
            //{D, M},
            //{E, M},
            //{F, M},

           //{G, M},
           //{H, M},
           //{I, M},
           //{J, M},
           //{K, M}
        };

        /*
        int ranges[6][2] = { // ************************************
            {0, M},  // Start at bit 0, length m
            {3, M},
            {6, M},
            {9, M},
            {12, M},
            {16, M}

        };
        */
        for (int k = 0; k < k_num; ++k) {
            int start = ranges[k][0];
            int length = ranges[k][1];
            std::bitset<cbit> mask((1ull << length) - 1);
            std::bitset<cbit> range = (CRC_reg >> start) & mask;

            std::size_t index = range.to_ullong();
            //cout << index << endl;
            BF[index] = 1;

        }
        //cout << BF << endl;
        delete crc;

    }

    std::ofstream fo2;
    fo2.open("BF.txt", std::ios::out);
    if (!fo2) {
        std::cerr << "Failed to open file for writing" << std::endl;
        return -1;
    }

    fo2 << BF;
    fo2.close();



    // "HashTable"

    std::vector<std::vector<std::string>> myHash(No_hashnodes, std::vector<std::string>(3));
    ifstream fin2;
    ifstream fin3;

    fin2.open("..\\forhash.txt"); //hashtable에 넣을거
    if (!fin2) {
        cout << "Failed to open file" << endl;
        return -1;
    }

    fin3.open("..\\binary.txt");
    if (!fin3) {
        cout << "Failed to open file" << endl;
        return -1;
    }


    std::vector<std::string> HashArray(No_hashnodes);

    for (int i = 0; i < No_hashnodes; i++) {
        for (int j = 0; j < 3; j++) {

            fin3 >> myHash[i][j];
        }
    }

    for (int i = 0; i < No_hashnodes; i++) {
        fin2 >> HashArray[i];
    }
    ///


    std::vector<std::string> prefix2(No_hashnodes);
    CRCgenerator* cn = new CRCgenerator();
    std::vector<std::bitset<TableWidth>> HashTable(HashTableSize, std::bitset<TableWidth>("1111111111111111111111111111111111111111111111111111111111"));

    for (int i = 0; i < No_hashnodes; i++)
    {
        prefix2[i] = myHash[i][1].substr(0, stoi(myHash[i][0]));

        int length = stoi(myHash[i][0]);
        std::bitset<32> bitsetVal(prefix2[i]);
        //cout << bitsetVal << endl;
        std::bitset<32> preval(myHash[i][1]);

        //std::bitset<32> CRC_reg = cn->CRC(bitsetVal, length);

        std::bitset<cbit> CRC_reg = cn->CRC(preval, length);

        //cout << "CRC" << CRC_reg << endl;
     // ************************************
        std::bitset<cbit> mask1 = ((1ull << N) - 1) << Ha;
        std::bitset<cbit> mask2 = ((1ull << N) - 1);

        std::bitset<cbit> range1 = ((CRC_reg)&mask1) >> Ha;
        std::bitset<cbit> range2 = (CRC_reg)&mask2;


        std::bitset<32> hash(myHash[i][1]);

        bitset<TableWidth> hashline(HashArray[i]);

        std::bitset<N> index1(range1.to_ullong());
        std::bitset<N> index2(range2.to_ullong());

        /*
        //std::cout << "index1"<<index1.to_ullong() << " " << index2.to_ullong();
        if (HashTable[index1.to_ullong()] == 0b1111111111111111111111111111111111111111111111111111111111)
            HashTable[index1.to_ullong()] = hashline;
            //HashTable[index1] = HashArray[i];
        else if (HashTable[index2.to_ullong()] == 0b1111111111111111111111111111111111111111111111111111111111)
            HashTable[index2.to_ullong()] = hashline;
        else
            cout << "Overflow occured" << endl;
        //cout << "Processing node: " << i << endl;
        */
        bool inserted = false;

        for (std::size_t j = 0; j < HashTableSize; ++j) {
            std::size_t index = (index1.to_ullong() + j * index2.to_ullong()) % HashTableSize;

            if (HashTable[index] == 0b1111111111111111111111111111111111111111111111111111111111) {
                HashTable[index] = hashline;
                inserted = true;
                break;
            }
        }

        if (!inserted) {
            cout << "Overflow occurred" << endl;
        }
    }
    delete cn;

    std::ofstream fin4;
    fin4.open("Hash.txt", std::ios::out);

    if (!fin4) {
        std::cout << "Failed to open file for writing" << std::endl;
        return -1;
    }

    for (const auto& bs : HashTable) {
        fin4 << bs << std::endl;
    }
    fin4.close();




    ////////Searching//////


    bool backTrack = 0;

    fin5.open("result.txt", std::ios::out);

    if (!fin5) {
        std::cout << "Failed to open file for writing" << std::endl;
        return -1;
    }
    std::vector<std::string> HASH(HashTableSize);

    ifstream fhash;

    fhash.open("Hash.txt");
    if (!fhash) {
        cout << "Failed to open the Hash file" << endl;
        return -1;
    }

    for (int i = 0; i < HashTableSize; i++) {

        fhash >> HASH[i];

    }
    std::vector<std::bitset<32>> curIP(Testset);
    ifstream addr;
    addr.open("..\\IPAddr.txt");



    if (!addr) {
        cout << "Failed to open the IPAddr file" << endl;
        return -1;
    }

    for (int i = 0; i < Testset; i++) {

        addr >> curIP[i];

    }
    for (int i = 0; i < Testset; i++) {
        CRCgenerator* crc0 = new CRCgenerator();

        BFQuery(BF, curIP[i], 32, HASH, crc0);
        //BFQuery(BF, 0b11001010001101011111100010101011, 32, HASH, crc0);
        No_of_hash_Access = 0;
        No_of_BF_Access = 0;
        delete crc0;
    }
    fin5.close();






}
