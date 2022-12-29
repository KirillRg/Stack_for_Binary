#include <iostream>
#include <cmath>
#include <string>
#include "Binary.h"

using namespace std;

class BinaryStackList
{
private:
	class Node
	{
	public:
		Node* pNext;
		Binary data;

		Node(Binary data, Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;

		}
	};
	int Size;
	Node* head;

public:
	BinaryStackList()
	{
		Size = 0;
		head = nullptr;
	}

	~BinaryStackList()
	{
		clear();
	}
	void push(Binary data)
	{
		head = new Node(data, head);
		Size++;
	}

	int GetSize() { return Size; }

	void pop()
	{
		Node* temp = head;

		head = head->pNext;

		delete temp;

		Size--;
	}
	void clear()
	{
		while (Size)
		{
			pop();
		}
	}
	Binary GetLast()
	{
		Node* current = this->head;
		return current->data;
	}
};

class SignStackList {
private:
	class Node
	{
	public:
		Node* pNext;
		string data;

		Node(string data, Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;

		}
	};
	int Size;
	Node* head;

public:
	SignStackList()
	{
		Size = 0;
		head = nullptr;
	}

	~SignStackList()
	{
		clear();
	}
	void push(string data)
	{
		head = new Node(data, head);
		Size++;
	}

	int GetSize() { return Size; }

	void pop()
	{
		Node* temp = head;

		head = head->pNext;

		delete temp;

		Size--;
	}
	void clear()
	{
		while (Size)
		{
			pop();
		}
	}

	string GetLast()
	{
		Node* current = this->head;
		return current->data;
	}
};

class Calculator
{
private:
	string expression;
public:
	Calculator(string expr)
	{
		expression = checkInput(expr);
	}
	string checkInput(string expr)
	{
		string result;

		for (int i = 0; i < expr.length(); i++) {
			if ((isdigit(expr[i]) == false) && (expr[i] != '+') && (expr[i] != '-') && (expr[i] != '*') && (expr[i] != ' '))
			{
				cout << "Incorrect input.Try again >> " << endl;
				getline(cin, expr);
				continue;
			}
		}

		string new_str;
		for (int i = 0; i < expr.length(); ) {
			if (expr[i] == ' ') {
				if (i == 0 || i == expr.length() - 1) {
					i++;
					continue;
				}
				while (expr[i + 1] == ' ')
					i++;
			}
			new_str += expr[i++];
		}
		expr = new_str;
		if (expr[0] == ' ') expr.erase(0, 1);
		if (expr[expr.length()-1] == ' ') expr.erase(expr.length()-1, 1);
		
		result = expr;
		return result;
	}
	
	Binary calculateRPN()
	{
		BinaryStackList binLst;
		SignStackList signLst;

		cout << "RPN >> " << expression << endl;
		bool oneNumber = true;
		for (int i = 0; i < expression.length(); i++)
		{
			if(expression[i] == ' ')
			{
				oneNumber = false;
				break;
			}
		}
		if (oneNumber == true) return Binary(stoi(expression));

		int left = 0;
		for (int i = 0; i < expression.length(); i++)
		{
			if ((expression[i] == ' ') || (i == expression.length() - 1))
			{
				string temp = "";
				int right = i;
				if (i == expression.length() - 1)
				{
					temp = expression[i];
				}
				else {
					for (int j = left; j < right; j++)
					{
						temp += expression[j];
					}
				}
				if (temp == "+" || temp == "-" || temp == "*")
				{
					cout <<" " << temp << " ";
					signLst.push(temp);

					if (signLst.GetSize() == 1 && binLst.GetSize() > 1)
					{
						string current = "";
						current = signLst.GetLast();

						if (current == "-")
						{
							Binary a = binLst.GetLast();
							binLst.pop();
							Binary b = binLst.GetLast();
							binLst.pop();
							binLst.push(b - a);
							signLst.pop();

							current = "";
						}
						if (current == "+")
						{
							Binary a = binLst.GetLast();
							binLst.pop();
							Binary b = binLst.GetLast();
							binLst.pop();

							binLst.push(a + b);
							signLst.pop();

							current = "";
						}
						if (current == "*")
						{
							Binary a = binLst.GetLast();
							binLst.pop();
							Binary b = binLst.GetLast();
							binLst.pop();

							binLst.push(a * b);
							signLst.pop();

							current = "";
						}
					}
				}
				else {
					Binary b(stoi(temp));
					b.print();
					binLst.push(b);
				}
				left = right + 1;
			}
		}

		if ((binLst.GetSize() == 1) && (signLst.GetSize() == 0))
		{
			return binLst.GetLast();
		}
		else {
			cout << "\nIncorrect RPN !!!" << endl;
		}
	}
};

int main()
{
	string input;
	cout << "Enter the RPN diveded by spaces >>" << endl;
	getline(cin, input);
	Calculator value(input);
	Binary result = value.calculateRPN();
	cout << "\nFinal answer >> \n" << result.toDecimal() << endl;
	result.print();

	return 0;
}