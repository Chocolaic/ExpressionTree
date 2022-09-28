#include "stack"
#include "expression.h"

using namespace std;

/// <summary>
/// �������ɾ��
/// </summary>
/// <param name="operas"></param>
/// <param name="node"></param>
void deleteNode(OperatorNode* node)
{
	if (node->lChild != nullptr) deleteNode(node->lChild);
	if (node->rChild != nullptr) deleteNode(node->rChild);

	delete node;
}

Expression::Expression(OperatorNode* root)
{
	_root = root;
}

Expression::~Expression() 
{
	deleteNode(_root);
}

OperatorNode* Expression::getRoot() const
{
	return _root;
}

OperatorNode* pop(stack<OperatorNode*>& stack)
{
	if (stack.empty()) throw EXCEPTION_ILLEGAL_EXPRESSION;
	auto node = stack.top();
	stack.pop();
	return node;
}
/// <summary>
/// ����ջ�������
/// </summary>
/// <param name="operas">������</param>
/// <param name="nums">������</param>
/// <param name="matchLP">ƥ�䵽�����ź�ֹͣ</param>
void appendAllNode(stack<OperatorNode*>& operas, stack<OperatorNode*>& nums, bool matchLP)
{
	OperatorNode* operaNode = nullptr;
	while (!operas.empty())
	{
		operaNode = operas.top();
		operas.pop();
		if (operaNode->sign == '(')
		{
			if (matchLP) return;
			else throw EXCEPTION_PARENTHESIS;
		}

		operaNode->rChild = pop(nums);
		operaNode->lChild = pop(nums);

		nums.push(operaNode);
	}
	if (matchLP) throw EXCEPTION_PARENTHESIS;
}

void appendNode(stack<OperatorNode*> &operas, stack<OperatorNode*> &nums, OperatorNode* node)
{
	if (operas.empty())
	{
		operas.push(node);
		return;
	}

	auto operaNode = operas.top();

	if (operaNode->priority < node->priority)
	{
		operas.push(node);
		return;
	}

	operas.pop();
	operaNode->rChild = pop(nums); //�Ҳ�����
	
	operaNode->lChild = pop(nums); //�������
	

	nums.push(operaNode); //�����Ϊ����
	operas.push(node);

}

Expression* Expression::fromInfix(string str)
{
	ExpressionReader reader(str);
	stack<OperatorNode*> operas;
	stack<OperatorNode*> nums;

	while(true)
	{
		if (reader.peekNumber())
		{
			nums.push(OperatorNode::instantiate(reader.readNumber(), '\0', 0));
		}
		else
		{
			switch (reader.read())
			{
			case '+':
				appendNode(operas, nums, OperatorNode::instantiate(0, '+', 10));
				break;
			case '-':
				appendNode(operas, nums, OperatorNode::instantiate(0, '-', 10));
				break;
			case '*':
				appendNode(operas, nums, OperatorNode::instantiate(0, '*', 11));
				break;
			case '/':
				appendNode(operas, nums, OperatorNode::instantiate(0, '/', 11));
				break;
			case '^':
				appendNode(operas, nums, OperatorNode::instantiate(0, '^', 12));
				break;
			case '(':
				operas.push(OperatorNode::instantiate(0, '(', 0));
				break;
			case ')':
				appendAllNode(operas, nums, true);
				break;
			case '\0':
				appendAllNode(operas, nums, false);
				return new Expression(nums.top());
			default:
				throw EXCEPTION_NOT_A_NUMBER;
			}
		}
	}
}