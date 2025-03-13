# Project Overview

## 1. Code Description
- header.h  
- CRCgenerator.h, CRCgenerator.cpp
  - Implements a class for obtaining CRC to generate hash indices.  
- main.cpp

## 2. How to Run the Code

### Required Input Files
- IPAddr.txt
- binary.txt
- forhash.txt

### Parameters to Modify When Changing Alpha
#### header.h
- M value
- k_num
- BF_size
  
// When modifying the input: No_hashnodes = No_BFnodes, Testset

#### main.cpp
- BFPos
- BFNeg
- int ranges

## Execution
Run the main.cpp file.

## Output Files
- BF.txt
- Hash.txt
- result.txt
