//variant 15
//Balashov Oleksandr
#include"exceptions.h"

using namespace std;

MyException::MyException(const std::string& text, const int& code, const int& lineN): text_(text), code_(code), 
lineN_(lineN) {}

MyException::operator string() const
{
	string s = to_string(code_) + " " + to_string(lineN_) + " " + text_;
	return s;
}

int MyException::code()
{
	return code_;
}
