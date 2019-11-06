#include "builder.h"
#include "info.h"
//#include "copyright.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>

using namespace std;

void input(Info &info, const char *fName)
{
    cout << "input" << fName << ":";
    Builder b;
    b.loadData(info,fName);
    cout << "OK" << endl;
}

ostream& output(ostream& o, Info& info)
{
    return o;
}

ostream& stat(ostream& f, Info& info)
{
    string s = "";
    info.stat(s);
    f << s;
    return f;
}

using InfoResults = ostream& (ostream&, Info&);

bool doCommand(Info& info, const char* fName, InfoResults f)
{
    if(strcmp(fName,"#con") == 0)
        return bool(f(cout, info));
    ofstream ff(fName);
    bool res = bool(f(ff,info));
    ff.close();
    if(ff.fail())
        res = false;
    return res;
}

void wFunk(Info& info, const char* fName, InfoResults f)
{
    if(fName == 0)
        cout << "undefined" << endl;
    else
    {
        cout << fName << ":";
        if(doCommand(info, fName, f))
        {
            if(strcmp(fName,"#con") == 0)
                cout << " " << endl;
            else
                cout << "OK" << endl;
        }
        else
            cout << "UPS" << endl;
    }
}

void help()
{
    cout << "command line:<executable file><input file name{-<command><output file name>}\n";
}

int main(int argc, char **argv)
{
//    copyright();
	cout << "!";
    help();
    cout << "*****" << endl;
    try
    {
        Info info;
        if(argc == 1)
        {
            cout << "nothing to do/n";
        }
        else
        {
            input(info, argv[1]);
            for(int i = 2; i < argc; ++i)
            {
                if(strcmp(argv[i],"-output") == 0)
                {
                    cout << "output";
                    wFunk(info, argv[i+1], output);
                    ++i;
                }
                else if(strcmp(argv[i],"-output") == 0)
                    {
                        cout << "stat";
                        wFunk(info, argv[i+1], stat);
                        ++i;
                    }
                    else
                    {
                        cout << argv[i] << " ";
                        cout << ":ignored" << endl;
                    }
            }
        }
    }
    catch (const MyException& ex)
    {
        cout << (string)ex << endl;
    }

    return 0;
}
