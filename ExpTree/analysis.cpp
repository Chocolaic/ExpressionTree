#include "analysis.h"

ExpressionReader::ExpressionReader(std::string str)
{
	_str = str;
	_ptr = 0;
}

bool isNum(char c)
{
	return (c >= '0' && c <= '9' || c == '.');
}

double ExpressionReader::readNumber()
{
	int startPos = _ptr;

	if (_str[_ptr] == '-') ++_ptr;
	while(isNum(_str[_ptr])) ++_ptr;

	return atof(_str.substr(startPos, _ptr - startPos).c_str());
}

char ExpressionReader::read()
{
	return _str[_ptr++];
}

bool ExpressionReader::readable() const
{
	return _ptr >= _str.length();
}

bool ExpressionReader::peekNumber() const
{
	if (_str[_ptr] == '-') return _ptr == 0 || !isNum(_str[_ptr - 1]); //允许负号出现在非俩数之间，判断上一个字符是否为数字
	return isNum(_str[_ptr]);
}

char ExpressionReader::peek() const
{
	return _str[_ptr];
}