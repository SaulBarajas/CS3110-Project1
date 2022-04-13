//CS3110.02
//Project 1
//Saul Barajas && Changu Kang

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <typeinfo>
#include <math.h>
#include <cstring>
using namespace std;


//Logic for conversion from string to float
float stringConversionFloat(string& input) {
    int decPlaces = 0;
    float dec = 0;
    float wholeNum = 0;
    float result, denominator, temp;

    for (int i = 0; input[i] != '\0'; i++) {
        //skips first character if negative and will convert at end
        if (input[i] == '-') {
            continue;
        }
        
        //Checks for all digits going past the decimal in the the string
        if (input[i] == '.' && input[i + 1] != '\0') {
            for (int j = i + 1; input[j] != '\0'; j++) {
                //checks decimal places to the right
                dec = (dec * 10) + (input[j] - '0');
                //keeps track of decimal places
                decPlaces = j - i;
            }
            break;
        }
        else {
            wholeNum = (wholeNum * 10) + (input[i] - '0');
        }
    }

    //sets up division for decimal places(example: input "2.34" will be seen as 234/100 which is 2.34 )
    if (decPlaces != 0) {
        denominator = pow(10, decPlaces);
        temp = wholeNum * denominator;
        temp = temp + dec;
        result = temp / denominator;
    }
    else {
        result = wholeNum;
    }
    //Incase the string started as a negative
    if (input[0] == '-') {
        result *= -1;
    }
    return result;
}

//Logic for conversion from string to Int
int stringConversionInt(string& input) {
    int wholeNum = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        //skips first character if negative and will convert at end
        if (input[i] == '-') {
            continue;
        }
        wholeNum = (wholeNum * 10) + (input[i] - '0');
    }
    if (input[0] == '-') {
        wholeNum *= -1;
    }
    return wholeNum;
}

//function for float output (check_ and position_ not currently being used)
float fLiteral(string& input, bool checkF, bool checkE, int positionF, int positionE, bool check_, int position_) {
    string temp = "";
    int exponent;
    int exponentCalc = 1;
    float charToFloat;
    float exponentCalcNeg = 1;
    int strLen = input.length();
    string exponentStr = "";


    //Logic for string only containing a float literal
    if (checkF == true && checkE == false) {
        //For loop iterates through input and turns string into float by dropping the f literal
        for (int i = 0; i < strLen; i++) {
            //skips seperators (_'s)
            if (input[i] == '_') {
                continue;
            }
            if (input[i] == '+') {
                continue;
            }
            //ignores f literal for conversion into float
            if (i == positionF) {
                break;
            }
            temp = temp + input[i];
        }
        charToFloat = stringConversionFloat(temp);

    }

    //Logic for string containing, both, a float and exponential literal
    else if (checkF == true && checkE == true) {
        //For loop iterates through input and turns string into float by dropping the f literal
        for (int i = 0; i < strLen; i++) {
            if (input[i] == '_') {
                continue;
            }
            if (input[i] == '+') {
                continue;
            }
            //ignores both e and f literal for conversion into float
            if (i == positionE) {
                continue;
            }
            if (i == positionF) {
                break;
            }
            //Accounts for the full value of the exponent for float calculation
            if (i > positionE) {
                exponentStr = exponentStr + input[i];
                continue;
            }
            temp = temp + input[i];
        }
        exponent = stringConversionInt(exponentStr);
        charToFloat = stringConversionFloat(temp);
        //Process of getting 10^n for calculations
        if (exponent < 0) {
            for (int i = 0; i > exponent; i--) {
                exponentCalcNeg = exponentCalcNeg / 10;
            }
            charToFloat = charToFloat * exponentCalcNeg;
        }
        else {
            exponentCalc = pow(10, exponent);
            charToFloat = charToFloat * exponentCalc;
        }
    }
    //exponential calculation with the float number
    //Checks datatype
    cout << "Type: " << typeid(charToFloat).name() << endl;
    cout << charToFloat << endl;
    return charToFloat;


}

//Method to check if the character is a digit
bool isDigit(char a)
{
    bool digit = false;
    if (a == '0' || a == '1' || a == '2' || a == '3' || a == '4' || a == '5' || a == '6' || a == '7' || a == '8' || a == '9')
    {
        digit = true;
    }
    return digit;
}

//To check the validation of the input
bool checkIfValid(string input)
{
    bool ans = true;
    int eCounter = 0;
    int fCounter = 0;
    for (int i = 0; i < input.length(); i++)
    {
        //All the conditions to check if 'e' vioaltes any of the conditions   
        if (input.at(i) == 'e' || input.at(i) == 'E')
        {
            eCounter++;
            //If more than 1 e
            if (eCounter > 1)
            {
                ans = false;
                break;
            }
            //if e is the first in the input
            if (i == 0)
            {
                ans = false;
                break;
            }
            //if e is the last in the input
            if (i == input.length() - 1)
            {
                ans = false;
                break;
            }
            //if it has a digit before and after the e OR digit before the e and - after
            else if (isDigit(input.at(i - 1)) && isDigit(input.at(i + 1)) || isDigit(input.at(i - 1)) && input.at(i+1) == '-')
            {
                
            }
            else
            {
                ans = false;
                break;
            }

        }
        
        //Conditions to check if it is valid regarding F
        if (input.at(i) == 'f' || input.at(i) == 'F')
        {
            fCounter++;
            //if f is not the last in the input
            if (i != input.length() - 1)
            {
                ans = false;
                break;
            }
            //if the previous to this f is not a digit
            else if (isDigit(input.at(i - 1)))
            {
                
            }
            else
            {
                ans = false;
                break;
            }
        }

        //Invalid if there are characters other than digits, e, E, f, F, _ , ., or -
        if (isDigit(input.at(i)) || input.at(i) == 'q' || input.at(i) == 'e' || input.at(i) == 'E' || input.at(i) == 'F' || input.at(i) == 'f' || input.at(i) == '_' || input.at(i) == '.' || input.at(i) == '-')
        {
            
        }
        else
        {
            ans = false;
            break;
        }

        //Conditions for -
        if (input.at(i) == '-')
        {
            //if it is the very first one in the input or right after the e with digits right after
            if (i == 0 || input.at(i - 1) == 'e' && isDigit(input.at(i+1)))
            {
                
            }
            else
            {
                ans = false;
                break;
            }
        }

        //Check for invalid conditions for '_'
        if (input.at(i) == '_')
        {
            //if the _ is the very first or the last of the input
            if (i == 0 || i == input.length() - 1)
            {
                ans = false;
                break;
            }
            //rules for the _
            else if (isDigit(input.at(i - 1)) && isDigit(input.at(i + 1)) || isDigit(input.at(i-1)) && input.at(i + 1) == '_' || input.at(i - 1) == '_' && isDigit(input.at(i + 1)) || input.at(i - 1) == '_' && input.at(i + 1) == '_')
            {
                
            }
            else
            {
                ans = false;
                break;
            }
        }

    }
    //If there's no f, not valid
    if (fCounter == 0)
    {
        ans = false;
    }
    return ans;
}

//Unit test
int main() {
    string input;
    int positionF, positionE, position_;
    bool checkF, checkE, check_;
    for (; true; ) {
        input = "";
        positionF = -1;
        positionE = -1;
        position_ = -1;
        checkF = false;
        checkE = false;
        check_ = false;
        cout << "Enter input with f literal, also takes in e literal in combination. (enter q to quit):" << endl;
        cin >> input;


        if (input == "q") break;

        if(!checkIfValid(input))
        {
            cout << "Invalid Input" << endl;
            continue;
            continue;
        }

        //Looks for the position of f or F within the inputted string 
        if (checkF == false) {
            positionF = input.find("f");
            if (positionF != -1) {
                checkF = true;
            }
        }
        if (checkF == false) {
            positionF = input.find("F");
            if (positionF != -1) {
                checkF = true;
            }
        }

        //Looks for the position of e or E within the inputted string
        if (checkE == false) {
            positionE = input.find("e");
            if (positionE != -1) {
                checkE = true;
            }
        }
        if (checkE == false) {
            positionE = input.find("E");
            if (positionE != -1) {
                checkE = true;
            }
        }



        if(check_ == false)


        //Chooses the function depending on input
        
        fLiteral(input, checkF, checkE, positionF, positionE, check_, position_);
    }


    return 0;
}