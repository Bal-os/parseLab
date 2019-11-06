//variant 15
//Balashov Oleksandr
#pragma once
#include <cstring>
#include <iostream>
#include <string>

enum class LineType
    {
        Empty,
        Footer,
        Header,
        Line
    };

class Lexer
{
public:

    LineType load (const std::string &inpStr);
    bool next(std::string &field);
    bool eof() const noexcept;

private:
    const std::string whitespaceStr = " \n\r\t\f\v";
    const std::string headStr = "header";
    size_t headStrSize = headStr.size();
    const std::string footStr = "footer";
    size_t eos = std::string::npos;
    std::string delWhite(std::string str);
    std::string delimStr = "!:,;";
    std::string tempStr;
    size_t tempPos;
    size_t len;
    bool isEof;
};

