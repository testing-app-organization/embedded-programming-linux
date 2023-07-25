#include <iostream>
#include "error_handling.h"

bool isNumber(string& input, int& number)
{
    try {
        number = stoi(input);
        return true;
    } catch (const exception& e) {
        return false;
    }
}