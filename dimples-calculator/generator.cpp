#include <time.h>
#include <math.h>
#include <string>
#include <stdlib.h>
#include "Generator.h"

std::string Generator::operand(int operandMin, int operandMax){
    int length = rand() % operandMax + operandMin;
    char* operand = new char[length];

    for(int i=0; i<length;i++){
        operand[i] = (char)(((int)'0')+(rand() % 9));
    }
    return std::string(operand);
}
