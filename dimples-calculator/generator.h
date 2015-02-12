#include <time.h>
#include <math.h>
#include <string>

using namespace std;

class Generator {
public:
    static string operand(int operandMin, int operandMax){
        srand (time(NULL));

        int length = rand() % operandMax + operandMin;

        char* operand = new char[length];

        for(int i=0; i<length;i++){
            operand[i] = rand() % 9;
        }

        return string(operand);
    }
};
