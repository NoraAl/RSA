//
//  RSA.hpp
//
//  Created by Nora on 1/31/16.
//  Copyright © 2016 Nora. All rights reserved.
//

#ifndef RSA_hpp
#define RSA_hpp

#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */ 
#include <string>
#include <fstream>
#include <iostream>
#include "BigIntegerLibrary.hpp"


class RSA{
private:
    BigInteger p, q, n, φ, e, d;
    int sizeInBits;
public:
    RSA();
    RSA(int primeLeastSizeInBits);
    ~RSA();
    
    void assignValues(bool firstTime);
    BigInteger generateRandomPrime(int primeLeastSizeInBits);
    BigInteger bigIntegerWithSize();
    bool isPrime(BigInteger p);
    BigInteger nextRandom(BigInteger b);
    BigInteger generateRandomLessThan(BigInteger p);
    void evaluateAll();
    bool generate_e_d();

    std::string towBigIntegersToString(BigInteger& first, BigInteger& second);
    void writeToFile(std::string fileName, std::string content);
    
    
};


#endif /* RSA_hpp */
