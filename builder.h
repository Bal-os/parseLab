//variant 15
//Balashov Oleksandr
#pragma once
#include <fstream>
#include "info.h"
#include "lexer.h"

int convert(const std::string& s);

class Builder
{
public:
	bool loadData(Info&, const char* fileName);
private:
    void loadOneLine();
    void loadLine();
    void parseLine();
	void loadHeader();
	void loadFooter();
	void parseHeader();
	void parseFooter();

    Info *i = nullptr;
    std::string s;

	bool isHeaderLoaded = 0;
	bool isFooterLoaded = 0;

	unsigned maxTextSize = 0;
	unsigned maxLoadN = 0;

    int line=0;
    unsigned problems=0;
    unsigned loaded=0;

	std::string sNum;
    std::string sName, sSurname, sPatronym, sScore, sYear, sText;
	std::string sHead, sFoot;

    int score, year;
    Lexer lex;
};
