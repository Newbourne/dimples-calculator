#include <QCoreApplication>
#include <boost/regex.hpp>
#include <string>
#include <iostream>

/*
    Given a string representation of a math problem.
    Recursively parse the string and calculate the answer.
    Must be able to work with the following operators:
    +       Addtion
    -       Subtraction
    x or *  Multiplication
    /       Division (Obelus)
    ^       Exponents
            Square Root
    ()      Parenthesis

    Must follow the order of operations.
 */

using namespace std;

static const boost::regex operandRegex("^(\\-?)(\\d+)?(\\d|\\.)?(\\d)+");
static const boost::regex operatorRegex("(\\+|\\-|\\(|\\)|\\/|\\*|\\^)");

const std::string parsedOperand = "";
const std::string parsedOperator = "";

bool operandCheck(const string check){
    if(boost::regex_match(check, operandRegex)){
        return true;
    }
    else{
        return false;
    }
}

bool operatorCheck(const string check){
    if(boost::regex_match(check, operatorRegex)){
        return true;
    }
    else{
        return false;
    }
}

void calculate(int startIndex, int endIndex, string equation){
    if(startIndex == endIndex)
        return;

    for(int i=startIndex; i<endIndex; i++){
        string target;
        target.push_back(equation[i]);

        parsedOperand.append(target);

        cout << tempOperand << endl;

        if(operandCheck(tempOperand)){
            // Is a valid number. Move on.
            parsedOperand = tempOperand;
            cout << "Operand" << parsedOperand << endl;
        }
        else if(operatorCheck(target)){
            // operator found
            parsedOperator = equation[i];
            cout << "Operator" << parsedOperator << endl;
        }
        else{
            throw "WTF!";
            // unsupported charater found.
            // Probably a letter or some shit.
            // Can't do Algebra yet.
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string test = "(1+2)";

    cout << "Parsing: " << test << endl;

    calculate(0, test.length(), test);

    return a.exec();
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
