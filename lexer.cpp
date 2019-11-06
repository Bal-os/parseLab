//variant 15
//Balashov Oleksandr
#include "Lexer.h"
using namespace std;

string Lexer::delWhite(string str)
{
    size_t pref = str.find_first_not_of(whitespaceStr);
    if(pref != eos)
        str = str.substr(pref);
    size_t suf = str.find_last_not_of(whitespaceStr);
    return (suf == eos) ? str : str.substr(0, suf + 1);
}

LineType Lexer::load(const string &str)
{
	tempStr = delWhite(str);
    LineType ownLineType = LineType::Line;
	if(tempStr.empty())
		ownLineType = LineType::Empty;
    else
    {
        isEof = false;
        tempPos = 0;
        len = tempStr.length();

        size_t nextDelim = tempStr.find_first_of(delimStr);
        string fieldStr;
        if(nextDelim != eos)
            fieldStr = delWhite(tempStr.substr(tempPos,nextDelim - tempPos));
        else
            fieldStr = delWhite(tempStr.substr(tempPos));
        if(fieldStr.size() == headStrSize)
        {
            if(fieldStr == headStr)
            {
                    ownLineType = LineType::Header;
                    tempPos = (nextDelim != eos) ? nextDelim + 1 : len;
            }
            else if(fieldStr == footStr)
            {
                    ownLineType = LineType::Footer;
                    tempPos = (nextDelim != eos) ? nextDelim + 1 : len;
            }
        }
        tempStr = tempStr.substr(tempPos);
    }
	return ownLineType;
}


bool Lexer::next(std::string &field)
{
    isEof = (tempPos == eos);
    if(isEof)
    {
        field = "";
    }
    else
    {
        size_t startPos = tempStr.find_first_not_of(whitespaceStr);

        size_t curPos = tempStr.find_first_of(delimStr);
        tempPos = curPos;
        if(curPos != eos)
        {
            field = delWhite(tempStr.substr(startPos, curPos - startPos));
            ++tempPos;
            tempStr = tempStr.substr(tempPos);
        }
        else
        {
            field = (startPos != eos) ? tempStr.substr(startPos) : "";
        }
    }
    return !isEof;
}

bool Lexer::eof() const noexcept
{
	return isEof;
}

