#pragma once
/* To change

1. header.h
 -M value
 -k_num
 -BF_size
 -When changing the input: No_hashnodes = No_BFnodes, Testset

2. main.cpp
 -BFPos, BFNeg
 -2 parts of { }

*/


const int cbit = 64; //crcbits

const int N = 20; //hash table addr* 고정

const int M = 20; //BF addr*
const int k_num = 3; //hash index num
const int BF_size = 1048576;

const int HashTableSize = 1048576; //* 고정


//2^20 = 1048576, 2^21 = 2097152, 2^22 = 4194304, 2^23 = 8388608;
const int No_hashnodes = 203093; //for hash* 
const int No_BFnodes = 203093; //programmed in BF*

//port80 145267, Group 203093, Telstra 285741
const int IP_LEN = 32; //length of IP addr
const int PrefixLength = 32; //length of prefix

const int PrefixSize = 6; //number of digits indicating length(size) of prefix. CRCgen에서 COUNT와 같음.
const int BMP_LEN = 20; //num of digits indicating BMP

const int TableWidth = 58; //width of the hash table

const int Testset = 511803; //num of IPs to be tested*

const int Ha = 10; //Hash Table만드는 hash 미는정도
/*
const int A = 0;
const int B = 4;
const int C = 8; //3
const int D = 12;
const int E = 16;

const int F = 20; //6
const int G = 24;
const int H = 28;
const int I = 32;
const int J = 36;

const int K = 40;
*/
const int A = 0;
const int B = 3;
const int C = 7; //3
const int D = 12;
const int E = 15;

const int F = 19; //6
const int G = 24;
const int H = 27;
const int I = 31;
const int J = 36;

const int K = 39; //11
// const int HashTableSize = 1048576; //* 고


//const int Testset = 336930; //port80
//const int Testset = 511803; //Groupltcom
//const int Testset = 681669; //Telstra



        /*
        int ranges[6][2] = { // ************************************
           a {0, M},  // Start at bit 0, length m
           b {3, M},
          c  {6, M},
          d  {9, M},
          e  {12, M},
          f  {16, M}
        };
        */#pragma once
