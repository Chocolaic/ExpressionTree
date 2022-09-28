#include "stack"
#include "expression.h"

using namespace std;

/// <summary>
/// 后序遍历删除
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
/// 结算栈里操作符
/// </summary>
/// <param name="operas">操作符</param>
/// <param name="nums">操作数</param>
/// <param name="matchLP">匹配到左括号后停止</param>
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
	operaNode->rChild = pop(nums); //右操作数
	
	operaNode->lChild = pop(nums); //左操作数
	

	nums.push(operaNode); //结果作为子树
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