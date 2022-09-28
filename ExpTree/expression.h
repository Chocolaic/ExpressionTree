#pragma once

#include "analysis.h"

struct OperatorNode
{
public:
	OperatorNode* lChild = nullptr;
	OperatorNode* rChild = nullptr;
	int priority; //��������ȼ���0��ʾΪ���ֽ��
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
		/// ȡ�����ָ��
		/// </summary>
		/// <returns></returns>
		OperatorNode* getRoot() const;
		/// <summary>
		/// �����������
		/// </summary>
		void printInfix();
		/// <summary>
		/// �����������
		/// </summary>
		void printPostfix();
		/// <summary>
		/// ���ǰ������
		/// </summary>
		void printPrefix();
	private:
		OperatorNode* _root;
};