#pragma once

#include <string>

#define EXCEPTION_NOT_A_NUMBER "not a number"
#define EXCEPTION_PARENTHESIS "parenthesis doesnt match"
#define EXCEPTION_ILLEGAL_EXPRESSION "illegal expression"

class ExpressionReader
{
	private:
		std::string _str;
		int _ptr;
	public:
		ExpressionReader(std::string str);
		double readNumber();
		char read();
		bool readable() const;
		bool peekNumber() const;
		char peek() const;
};

bool isNum(char);
