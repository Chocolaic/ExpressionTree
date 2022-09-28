#include <iostream>
#include <Windows.h>

#include "expression.h"

using namespace std;

bool setcolor(int code) 
{
	return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), code);
}

void writeNodePrefix(OperatorNode* node)
{
	if (node->priority == 0)
	{
		setcolor(0xA);
		cout << node->value << ' ';
	}
	else
	{
		setcolor(0xB);
		cout << node->sign << ' ';
	}

	if (node->lChild != nullptr) writeNodePrefix(node->lChild);
	if (node->rChild != nullptr) writeNodePrefix(node->rChild);
}

void Expression::printPrefix()
{
	cout << "Prefix> ";
	writeNodePrefix(_root);
	setcolor(0x7);
	cout << endl;
}


void writeNodeInfix(OperatorNode* node)
{
	if (node->lChild != nullptr) writeNodeInfix(node->lChild);

	if (node->priority == 0)
	{
		setcolor(0xA);
		cout << node->value << ' ';
	}
	else
	{
		setcolor(0xB);
		cout << node->sign << ' ';
	}

	if (node->rChild != nullptr) writeNodeInfix(node->rChild);
}

void Expression::printInfix()
{
	cout << "Infix> ";
	writeNodeInfix(_root);
	setcolor(0x7);
	cout << endl;
}

void writeNodePostfix(OperatorNode* node)
{
	if (node->lChild != nullptr) writeNodePostfix(node->lChild);
	if (node->rChild != nullptr) writeNodePostfix(node->rChild);

	if (node->priority == 0)
	{
		setcolor(0xA);
		cout << node->value << ' ';
	}
	else
	{
		setcolor(0xB);
		cout << node->sign << ' ';
	}
}

void Expression::printPostfix()
{
	cout << "Postfix> ";
	writeNodePostfix(_root);
	setcolor(0x7);
	cout << endl;
}