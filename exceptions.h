//variant 15
//Balashov Oleksandr
#include<string>
#include<stdexcept>

class MyException :public std::exception
{
public:
	MyException(const std::string& text, const int& code = 0, const int& lineN = -1);
	operator std::string() const;
	int code();
private:
	std::string text_;
	int code_;
	int lineN_;
};
