
#include <iostream>
#include "expression.h"
#include "solver.h"

using namespace std;

void readExpression()
{
    cout << "EXPRESSION>";
    Expression* exp;
    string str;
    cin >> str;

    try
    {
        exp = Expression::fromInfix(str);

        exp->printInfix();
        exp->printPrefix();
        exp->printPostfix();

        Solver solver;

        cout << endl << "RESULT>" << solver.getResult(*exp) << endl << endl;
    }
    catch (const char* e)
    {
        std::cout << "!Exception: " << e << std::endl;
    }
}

int main()
{
    while(true) readExpression();
}
