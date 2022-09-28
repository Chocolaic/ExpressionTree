#pragma once

#include "analysis.h"

struct OperatorNode
{
public:
	OperatorNode* lChild = nullptr;
	OperatorNode* rChild = nullptr;
	int priority; //运算符优先级，0表示为数字结点
	char sign;
	double value;

	static OperatorNode* instantiate(double value, char sign, int priority)
	{
		auto p = new OperatorNode();
		p->sign = sign;
		p->value = value;
		p->priority = priority;
		return p;
	}
};

class Expression
{
	public:
		static Expression* fromInfix(std::string str);
		Expression(OperatorNode* root);
		~Expression();
		/// <summary>
		/// 取根结点指针
		/// </summary>
		/// <returns></returns>
		OperatorNode* getRoot() const;
		/// <summary>
		/// 输出中序序列
		/// </summary>
		void printInfix();
		/// <summary>
		/// 输出后序序列
		/// </summary>
		void printPostfix();
		/// <summary>
		/// 输出前序序列
		/// </summary>
		void printPrefix();
	private:
		OperatorNode* _root;
};