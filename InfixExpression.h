#ifndef INFIXEXPRESSION_H
#define INFIXEXPRESSION_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "ArrayStack.h"
#include "LinkedStack.h"

using namespace std;


class InfixExpression
{
private:
	void tokenize();
	double strToDouble(const string &token);
	bool isOperator(const string &token);
	int precedence(const string &token);
	string infixStr;
	vector<string> tokensVect;
	int precVal;
	double result;
public:
	InfixExpression() { result = 0; }
	InfixExpression(string infix) { setinFix(infix); }
	void execute(ArrayStack<string> &opStack, LinkedStack<double> &valStack);
	void evaluate();
	void setinFix(string infixStr);
	string getinFix() { return infixStr; }			//Return what's in the string.
	double getresult() const { return result; }		//Return the result of the operation
	
};


void InfixExpression::tokenize()
{
	stringstream ss(infixStr); // makes an input stream out of infixStr
	string token;

	tokensVect.clear(); // tokensVect is a member vector<string> variable

	while (ss >> token) // read a string from ss into token delimited by spaces
	{
		tokensVect.push_back(token);
	}
}



double InfixExpression::strToDouble(const string &token)
{
	double doubNum = 0;

	stringstream ss(token);// make an input stream out of token
	ss >> doubNum;  // convert the token to a double, store in doubNum
	return doubNum;
}



bool InfixExpression::isOperator(const string &token)
{
	// you finish this so it checks if token is "+", "-", "*" or "/" ONLY
	// and returns true if so, false otherwise
	for (int i = 0; i < tokensVect.size(); i++)
	if(token == "+" || token == "-" || token == "*" || token == "/")
	{
		return true;
	}
	else
	{
		return false;
	}
}



int InfixExpression::precedence(const string& token)
{
	int value = 0;
	if (token == "*" || token == "/")
	{
		value = 3;							//assigns the value of 3 (highest order) for * and /
	}
	if (token == "+" || token == "-")
	{
		value = 2;							//assigns the value of 2 (middle order) for + and -
	}
	if (token == "(" || token == ")")
	{
		value = 1;							//assigns the value of 1 (lowest order) for ( and )
	}
	return value;
}



void InfixExpression::execute(ArrayStack<string> &opStack,
	LinkedStack<double> &valStack)
{
	string op;
	double temp, rightOperand, leftOperand;
	op = opStack.peek(); //top of the opStack
	opStack.pop(); 		//pop the opStack
	if (valStack.isEmpty())
	{
		return;
	}
	rightOperand = valStack.peek(); //(call peek())
	valStack.pop(); 	//pop the valStack

	if (valStack.isEmpty())
	{
		return;
	}
	leftOperand = valStack.peek(); //(call peek())
	valStack.pop(); 		//pop the valStack
		switch (op[0])
	{
		case '+':  temp = leftOperand + rightOperand; break;
		case '-':  temp = leftOperand - rightOperand; break;
		case '*':  temp = leftOperand * rightOperand; break;
		case '/':  temp = leftOperand / rightOperand; break;
	}
	valStack.push(temp); 	//push temp onto valStack
}



void InfixExpression::evaluate()
{
	// fill in here using this algorithm (MUST BE NON-RECURSIVE):

	//declare a stack of string for the operators (use an ArrayStack, I'll call opStack)
	//declare a stack of double for the operands (use a LinkedStack, I'll call valStack)
	ArrayStack<string> opStack;
	LinkedStack<double> valStack;
	for (int i = 0; i < tokensVect.size(); i++) //each() token in the vector of strings(member variable)
	{
		if (tokensVect[i] == "+" || tokensVect[i] == "-" || tokensVect[i] == "*" || tokensVect[i] == "/")
		{
			if (opStack.isEmpty())
			{
				opStack.push(tokensVect[i]); 	//push token onto opStacfk
			}
			else if (precedence(tokensVect[i]) > precedence(opStack.peek()))
			{
				opStack.push(tokensVect[i]); //push token onto opStack
			}
			else
			{
				while (!opStack.isEmpty() && precedence(tokensVect[i]) <= precedence(opStack.peek())) //opStack isn't empty AND precedence(token) <= precedence(top of opStack)
				{
					execute(opStack, valStack);
				}
				opStack.push(tokensVect[i]); //push token onto opStack
			}
		}

		else if (tokensVect[i] == "(")
		{
				opStack.push(tokensVect[i]); //push token onto opStack
		}

		else if (tokensVect[i] == ")")
		{
			while (opStack.peek() != "(")
			{
				execute(opStack, valStack);
			}
			opStack.pop(); //pop the opStack
		}

		else
		{
			double doubVal = strToDouble(tokensVect[i]); //convert the token to a double value
			valStack.push(doubVal);			//push the double value onto the valStack
		}
	}

	while (!opStack.isEmpty())
	{
		execute(opStack, valStack);
	}
	if (valStack.size() == 1)
	{
		result = valStack.peek();
	}
	else
	{
		result = 0;
	}
}


void InfixExpression::setinFix(string infixStr)
{
	this->infixStr = infixStr;
	tokenize();
	evaluate();
}

#endif