#include <string>
#include <iostream>
#include "Situation.h"

using namespace std;

int main(int argc, char *argv[])
{
    try{
        Situation* sit = new Situation("default-generator");
        int iterations = 0;
        while(iterations < 100){
            sit->generate(5, 2, 2, "+-");
            cout << "Problem: " 
                 << sit->getEquation() 
                 << " Solution: " 
                 << sit->getSolution()
                 << endl;
                 
            iterations++;
        }
        return 0;
    }
    catch(exception ex){
        cout << "Exception: " <<  ex.what() << endl;
    }
}

/*
    Integer Check
    0				Pass
    9				Pass
    123             Pass
    123123123       Pass
    ABC             Fail
    !@#$%@#%		Fail
    x*-+			Fail

    Decimal Check
    .123			Pass
    123.123         Pass
    .123.123		Fail
    ...123...       Fail

    Negative Check
    -1              Pass
    -1234.34		Pass
    -.3         	Pass
    -.023			Pass
    -34.344.34      Fail
    -				Fail
    --323--23       Fail

    Complex Check
    -123.443		Pass
    -.343			Pass
    1123.43         Pass

    Starting Regex
    ^(\-?)(\d+)?(\d|\.)?(\d)+
*/
