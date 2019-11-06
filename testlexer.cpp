//variant 15//Balashov Oleksandr
#include <cstring>
#include <iostream>
#include "testlexer.h"
#include "Lexer.h"


using namespace std;

void testLexer ( const string &str)
{
    string curStr;
    Lexer lex;
    LineType testStr;
    testStr = lex.load(str);
    if(testStr == LineType::Empty)
        cout << "[]\n";
    else
        while (lex.next(curStr))
        {
            cout << "[" << curStr << "]\n";
        }
}

