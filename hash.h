#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <array>

typedef std::size_t HASH_INDEX_T;
using namespace std;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

				
        unsigned long long k_conv[30] = {0};

        for(size_t i = 0; i < k.length(); i++){
            k_conv[30 - k.length() + i] = letterDigitToNumber(k[i]);
        }
				unsigned long long w[5]; 

        size_t ct = 0; 
        for(int i = 0; i < 5; i++){   
            w[i] = ((((k_conv[0+ct]*36 + k_conv[1+ct])*36 + k_conv[2+ct])*36 + k_conv[3+ct])*36 + k_conv[4+ct])*36 + k_conv[5+ct];
            ct+=6;
        }

        unsigned long long hashVal = 0;
        hashVal = rValues[0]*w[0] + rValues[1]*w[1] + rValues[2]*w[2] + rValues[3]*w[3] + rValues[4]*w[4];

        return hashVal;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
				HASH_INDEX_T retVal;
        // Add code here or delete this helper function if you do not want it
				if(isalpha(letter)){
					letter = tolower(letter); //convert to lowercase
					retVal = int(letter) - 97; 
				}
				else{
					retVal = int(letter) - 22;
				}

				return retVal;

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
