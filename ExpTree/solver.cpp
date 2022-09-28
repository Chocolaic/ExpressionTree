#include "solver.h"
#include <math.h>
#include <stack>

double add(double a, double b) 
{
	return a + b;
}

double sub(double a, double b) 
{
	return a - b;
}

double mul(double a, double b) 
{
	return a * b;
}

double div(double a, double b) 
{
	return a / b;
}

double mod(double a, double b) 
{
	return fmod(a, b);
}

Solver::Solver()
{
	_operations['^'] = pow;
	_operations['*'] = mul;
	_operations['/'] = div;
	_operations['%'] = mod;
	_operations['+'] = add;
	_operations['-'] = sub;
}

void readNode(Solver &solver, std::stack<double> &nums, OperatorNode* node)
{
	if (node->lChild != nullptr) readNode(solver, nums, node->lChild);
	if (node->rChild != nullptr) readNode(solver, nums, node->rChild);

	if (node->priority == 0) //为数字
	{
		nums.push(node->value);
	}
	else //为操作符，计算并入栈
	{
		double rNum = nums.top(); nums.pop();
		
		double lNum = nums.top(); nums.pop();
		
		double result = solver.getResult(lNum, rNum, node->sign);
		nums.push(result);
	}
}

double Solver::getResult(Expression& exp)
{
	std::stack<double> nums;
	readNode(*this, nums, exp.getRoot());
	return nums.top();
}

double Solver::getResult(double lNum, double rNum, char opera)
{
	return _operations[opera](lNum, rNum);
}