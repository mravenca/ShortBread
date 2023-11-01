// ShortBreadDLLtest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ShortBreadLibrary.h"

using namespace std;

int main()
{
    cout << "Testing the ShortBreadDLL" << endl;

    bool res;

    string source = "short";
    string dest = "bread";

    if (source.length() != dest.length())
    {
        cout << "The strings must have a same length!" << endl;
        return 1;
    }

    res = GetFileContent("C:\\Users\\mrave\\source\\repos\\SB\\SB\\words.txt", source.length());
    res = PrepareGraph();
    res = getShortestDistance(source, dest);
    return 0;
}

