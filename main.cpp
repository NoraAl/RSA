
#include <iostream>
#include <time.h> 
#include "BigIntegerLibrary.hpp"
#include "RSA.hpp"

int main() {
	try {
        std::cout<<"Generating RSA keys...\n";
        
        std::clock_t start;
        double duration;
        start = std::clock();
        
        RSA obj =  RSA();
        
        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        
        std::cout<<"Total time: "<< duration <<"seconds\n\n";
    
    } catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}
	return 0;
}