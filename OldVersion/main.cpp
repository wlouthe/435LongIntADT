#include <iostream>
#include "stdlib.h"
#include "LongIntADT.h"

using namespace std;


int main()
{
    int x;
    std::string longNum;
    x = 0;
    cout << "Enter a Long Number:\n";
    cin >> longNum;
    //int xlen = (sizeof(longNum)/sizeof(longNum[0]));
    LongIntADT myLIADT(longNum);
    //x = myLIADT.initialize(longNum);
    return 0;
}
