#include <QCoreApplication>
#include <string>
#include <iostream>
#include "nodebuilder.h"

using namespace std;

int main(int argc, char *argv[])
{
    try{
        QCoreApplication a(argc, argv);
        NodeBuilder* builder = new NodeBuilder();
        builder->parse("123-456+789-333");
        builder->print("      ");

        cout << endl << endl << "Done." << endl;

        double answer = builder->solve();
        cout << "Answer: " << answer << endl;
        return a.exec();
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
