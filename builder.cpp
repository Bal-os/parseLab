//variant 15
//Balashov Oleksandr
#include "Builder.h"
using namespace std;

bool Builder::loadData(Info& i_, const char* fileName)
{
	ifstream inFile;
	inFile.clear();
	inFile.open(fileName);
	cout << "opening input file " << fileName << endl;
	i = &i_;
	if (inFile.fail())
		throw MyException(string("Unable to open input file ") + string(fileName), 400);
	isFooterLoaded = 0; isHeaderLoaded = 0;
	line = 0; problems = 0; loaded = 0;
    while (getline(inFile,s))
    {
		++line;
        try {loadOneLine();}
		catch (MyException & ex)
		{
			++problems;
			cout << (string)MyException(ex.what(), ex.code(), line) << endl;
		}
		if ((to_string(line - 1)) != sNum)
			cout << (string)MyException("Incorrect number field", 301, line) << endl;
	}
	inFile.close();
	if (!isFooterLoaded)
		throw MyException("There is no footer", 200);
	if(loaded > maxLoadN + 1)
		throw MyException("Too mach loaded lines", 202);
	return (problems == 0);
}

void Builder::loadOneLine()
{
  switch(lex.load(s))
  {
    case LineType::Empty: return;
	case LineType::Header: loadHeader(); return;
	case LineType::Footer: loadFooter(); return;
	case LineType::Line: loadLine(); return;
    default: ++problems; throw MyException(string("Unknown field"), 303);
  }
}

int convert(const string& s)
{
    if (s.find("-") != string::npos) 
		throw MyException(string("unsigned ["+s+"] could not be negative"));
    int v;
	try 
	{ 
		v = stoi(s);
	}
    catch(out_of_range &ex) 
	{
		throw MyException(string("unsigned ["+s+"] is out of range ("+ex.what()+")"));
	}
    catch(invalid_argument &ex) 
	{
		throw MyException(string("unsigned ["+s+"] is invalid ("+ex.what()+")"));
	}
    if (v > INT_MAX) 
		throw MyException(string("int ["+s+"] is out of range"));
    return v;
}

void Builder::loadLine()
{
	try { parseLine(); }
	catch (MyException & ex)
	{
		throw MyException(ex.what(), 303);
	}
	try
	{
		score = convert(sScore);
	}
	catch (MyException & ex)
	{
		throw MyException(ex.what(), 303);
	}
	i->load(sName,sPatronym,sSurname);
	if(!isHeaderLoaded)
		throw MyException(string("condution is too long"), 100);
	if(sText.size() > maxTextSize)
		throw MyException(string("condution is too long"), 102);
	i->load(sName,sPatronym,year,score,sSurname,sText);
	++loaded;
}

void Builder::loadHeader()
{
	if(isHeaderLoaded)
		throw MyException(string("there is more than one header"), 101);
	parseHeader();
	try
	{
		maxTextSize = convert(sHead);
	}
	catch (MyException & ex)
	{
		throw MyException(ex.what(), 104);
	}
	++loaded;
	isHeaderLoaded = true;
}

void Builder::loadFooter()
{
	if (isFooterLoaded)
		throw MyException(string("there is more than one footer"), 201);
	parseFooter();
	try
	{
		maxLoadN = convert(sFoot);
	}
	catch (MyException & ex)
	{
		throw MyException(ex.what(), 204);
	}
	++loaded;
	isFooterLoaded = true;
}

void Builder::parseHeader()
{
	if (!lex.next(sHead)) throw MyException("Too less information in header", 103);
	if (lex.eof()) throw MyException("Too much information in header", 103);
}

void Builder::parseFooter()
{
	if (!lex.next(sFoot)) throw MyException("Too few information in footer", 203);
	if (lex.eof()) throw MyException("Too much information in footer", 203);
}

void Builder::parseLine()
{
  if (!lex.next(sNum))	throw MyException("Too few information in line:line number is absent");
  if (!lex.next(sName)) throw MyException("Too few information in line:student name is absent");
  if (!lex.next(sPatronym)) throw MyException("Too few information in line:student patronym is absent");
  if (!lex.next(sYear)) throw MyException("Too few information in line:year is absent");
  if (!lex.next(sScore)) throw MyException("Too few information in line:score is absent");
  if (!lex.next(sSurname)) throw MyException("Too few information in line:student surname is absent");
  if (!lex.next(sText)) throw MyException("Too few information in line:task text is absent");
  if (lex.eof()) throw MyException("Too much information in line");
}
