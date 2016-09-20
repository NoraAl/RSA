//
//  RSA.cpp
//  
//
//  Created by Nora on 1/31/16.
//  Copyright © 2016 Nora. All rights reserved.
//

#include "RSA.hpp"

RSA::RSA()
{ RSA(512);}

RSA::RSA(int primeLeastSizeInBits){
    sizeInBits = primeLeastSizeInBits;
    assignValues(true);
}

RSA::~RSA(){}


/**************************************************
 This function returns assignes values to the 
 class members. If it the first time, i.e. coming
 from the constructor, it generates p with the 
 specified "sizeInBits" and then generates q basd on
 the length of p. Otherwise, it change only the value 
 of q, based on the length of the previous value of 
 q.
 **************************************************/
void RSA::assignValues(bool firstTime){
    if (firstTime) {
        p = generateRandomPrime(sizeInBits);
        q = generateRandomPrime(p.getMagnitude().bitLength() +1);
    } else {
        q = generateRandomPrime(q.getMagnitude().bitLength());
    }
    n.multiply(p, q);
    φ.multiply((p-1), (q-1));
    evaluateAll();
}


/**************************************************
 This function returns a bigInteger random less than 
 p. That is, generateRandomLessThan(p) returns {1,....,p-1}
 rand() cannot generate a value that is equal to p,
 so it gurantees returning from 1 not zero.
 **************************************************/
BigInteger RSA::generateRandomLessThan(BigInteger p){
    srand( static_cast<unsigned int>(time(NULL)));
    BigInteger x;
    x.add(p, BigInteger(rand()));
    x = x % p;
    return x;
}


/**************************************************
 This function implements Fermat's little theorem to 
 test the primality of p. The names of the used 
 functions are modified to be easily read and to 
 match the naming convention of my project
 **************************************************/
bool RSA::isPrime(BigInteger p){
    
    int iterations = 5;
    for (int i = 0; i < iterations; i++){
        BigInteger a = generateRandomLessThan(p);
        
        if (modExponent(a.getMagnitude(), (p-1).getMagnitude(), p.getMagnitude()) != 1) {
            return false;
        }
    }
    return true;
}


/**************************************************
 This function uses a customized construcore that 
 is added to the library for RSA project
 Then I am using random() to move the value up
 Testing the resulting value
 If not prime
 Generate the next one, and so on.
 **************************************************/
BigInteger RSA::generateRandomPrime(int primeLeastSizeInBits){
    srand( static_cast<unsigned int>(time(NULL)));
    BigInteger x = BigInteger(primeLeastSizeInBits,BigInteger::positive,true);
    x += (rand()*2);
    
    while(!isPrime(x)){
        x += (rand()*2);
    }
    return x;
}


/**************************************************
 This function evaluate all the values and does 
 not proceed to file reading and writing until it 
 reachs proper values
 **************************************************/
void RSA::evaluateAll(){
    while(!generate_e_d()){
        assignValues(false);
        return;//this function is indirectly recursive
    }
    
    writeToFile("p_q.txt",towBigIntegersToString(p,q));
    writeToFile("e_n.txt",towBigIntegersToString(e,n));
    writeToFile("d_n.txt",towBigIntegersToString(d,n));
    std::cout<<"RSA keys are generated, writing to files is done.\n";
    
}


/**************************************************
 Like in "isPrime(BigInteger p)" function, this 
 function generates randomly a value for e that
 is less than φ. testing the resulting value, 
 returning false if it cannot find e (coprime for φ).
 if it does find an e, try to find a proper p through
 a while loop.
 **************************************************/
bool RSA::generate_e_d(){
    srand( static_cast<unsigned int>(time(NULL)));
    
    do{//exit  the outer loop when d!=e and return true
        e = (φ + rand()) % φ;
        while (e > 1){//exit the inner loop once e reaches 1 and return false
            e--;
            if (gcd(e.getMagnitude(), (φ).getMagnitude())==1)
            {
                break;//found a proper value for e, break the inner loop
            }
        }
        if (e==1) {
            return false;//one of the primes should be changed
        }
        d = modInverse(e.getMagnitude(), φ.getMagnitude());
    }
    while (d == e);

    return true;
}

/**************************************************
 These two functions are used to save rsa values into
 files for later use.
 **************************************************/
std::string RSA::towBigIntegersToString(BigInteger& first, BigInteger& second){
    std::string oneString;
    oneString.append(bigIntegerToString(first));
    oneString.append(1u,'$');
    oneString.append(bigIntegerToString(second));
    oneString.append(1u,'$');
    return oneString;
}

void RSA::writeToFile(std::string fileName, std::string content){
    std::ofstream myfile;
    myfile.open(fileName,std::ios::out );
    
    if (myfile.is_open())
    {
        myfile << content;
        myfile.close();
    }
    else
        throw "FileReadingWriting: Unable to open file for writing";
}