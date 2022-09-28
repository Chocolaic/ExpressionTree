#pragma once

#include <map>

#include "expression.h"

typedef double (*Operation)(double, double);

struct Solver
{
public:
	Solver();
	double getResult(double lNum, double rNum, char opera);
	double getResult(Expression& exp);
private:
	std::map<char, Operation> _operations;
};