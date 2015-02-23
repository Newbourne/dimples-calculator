#include <time.h>
#include <math.h>
#include <string>
#include "Generator.h"

std::string Generator::operand(int operandMin, int operandMax){
    int length = rand() % operandMax + operandMin;
    std::string result = "";

    for(int i=0; i<length-1; i++){
        result += ((char)(((int)'0')+(rand() % 9)));
    }
    return result;
}