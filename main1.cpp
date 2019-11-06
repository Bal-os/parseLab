//variant 15//Balashov Oleksandr
#include <iostream>
#include "testlexer.h"
using namespace std;

int main()
{
    string S[] =
    {
        ";","input: success, output: fail", "header" , ";a","Hello world!","!Uno!,!DOS!,!Tres! ", "header\t123,456" ,
        "; abcd ;","a-ba-ga-la-ma-ga","di gi\tta_1iz\"a+tion"," ; abcd; ","abcd ; ","!:,;", "footer\t ; 54 ;", ""
    };
    for (int i=0; S[i].size()>0; i++)
    {
        testLexer(S[i]);
        cout<<"test"<<"     \n";
    }
    return 0;
}
