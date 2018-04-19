#pragma once
#ifndef CALCULATOR_H  
#define CALCULATOR_H  

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

class Expression {
private:
	string preExpression;//一次性读取表达式，用字符串存  
	stack<char> operators;//记录表达式中的操作符  
	stack<double> operand;//记录表达式中的操作数  
	int loc;//记录读取到preExpression的第几个位置了  
	int length;//记录preExpression的长度  
	char ch;//记录当前读取到的preExpression的字符  
	//记录loc是否读取到preExpression的最后一个字符,1为未读取到最后一个字符，0为读取到最后一个字符  
	bool sign;

			  //start辅助函数  
	void show();//提醒输入表达式，并存入preExpression中  
	void operating();//开始进行计算过程  
	int isOperator(char ch);//判断ch是否是操作符，返回0说明是数字，返回1说明是操作符，返回2说明非法符号  
	double readOpend();//读取操作数  
	int opera(char ch, char top);//读取操作符，返回0说明操作正常，返回1说明除法有问题，返回2说明表达式出错,3说明表达式不合法  
	bool compareOpe(char ch, char top);//判断操作符的优先级  

public:
	void start();//开始程序  
};

void Expression::show() {//提醒输入表达式，并存入preExpression中  
	cout << "Enter an arithmetic expression:\nExample:(((2+3)*5-7)/15)*34=\n";
	cout << "quit to quit" << endl;
	cin >> preExpression;
	if (preExpression == "quit") {
		cout << "Bye!" << endl;
		system("pause");
		exit(1);
	}
	length = preExpression.length();
	loc = 0;
	sign = 0;
}

void Expression::operating() {//开始进行计算过程  
	operators.push('=');//设置栈顶标志  
	while (!operators.empty()) {
		if (!sign) {
			ch = preExpression[loc];
			//判断ch  
			if (isOperator(ch) == 3) { //如果ch不是操作数也不是操作符  
				cout << "Sorry,expressions containing illegal characters." << endl;
				cout << "Please re-enter!" << endl;
				cout << endl;
				return;
			}
			else if (ch == '='&&loc != length - 1) {//=符号出现在中间  
				cout << "\'=\' couldn't in the middle of arithmetic expression!" << endl;
				cout << "Please re-enter!" << endl;
				cout << endl;
				return;
			}
			else if (isOperator(ch)) {//如果ch是操作符  
				if (operators.empty()) {
					cout << "There may hava some errors!" << endl;
					cout << "Bye!" << endl;
					system("pause");
					exit(1);
				}
				char top = operators.top();
				operators.pop();
				int wrong;
				wrong = opera(ch, top);
				++loc;
				if (loc == length)sign = 1;
				if (wrong == 1) {
					cout << "Divisor can not be zero!" << endl;
					cout << "Please re-enter!" << endl;
					cout << endl;
					return;
				}
				else if (wrong == 2) {
					cout << this->preExpression << " is not an arithmetic expression!" << endl;
					cout << "Please re-enter!" << endl;
					cout << endl;
					return;
				}
				else if (wrong == 3) {
					if (operand.empty()) {
						cout << "Sorry,expressions doesn't illegal." << endl;
						cout << "Please re-enter!" << endl;
						cout << endl;
						return;
					}
					double opend = operand.top();
					if (operand.empty()) {
						cout << "Sorry,expressions doesn't illegal." << endl;
						cout << "Please re-enter!" << endl;
						cout << endl;
						return;
					}
					else {
						cout << "The result is " << opend << endl;
						cout << endl;
						return;
					}
				}
			}
			else {//如果ch是操作数  
				double opend = readOpend();
				operand.push(opend);
			}
		}
		else {
			if (operators.empty()) {
				cout << "There may hava some errors!" << endl;
				cout << "Bye!" << endl;
				system("pause");
				exit(1);
			}
			operators.pop();
			if (operators.empty()) {
				cout << "There may hava some errors!" << endl;
				cout << "Bye!" << endl;
				system("pause");
				exit(1);
			}
			char top = operators.top();
			operators.pop();
			int wrong;
			wrong = opera(ch, top);
			if (wrong == 1) {
				cout << "Divisor can not be zero!" << endl;
				cout << "Please re-enter!" << endl;
				cout << endl;
				return;
			}
			else if (wrong == 2) {
				cout << this->preExpression << " is not an arithmetic expression!" << endl;
				cout << "Please re-enter!" << endl;
				cout << endl;
				return;
			}
			else if (wrong == 3) {
				if (operand.empty()) {
					cout << "Sorry,expressions doesn't illegal." << endl;
					cout << "Please re-enter!" << endl;
					cout << endl;
					return;
				}
				double opend = operand.top();
				operand.pop();
				if (!operand.empty()) {
					cout << "Sorry,expressions doesn't illegal." << endl;
					cout << "Please re-enter!" << endl;
					cout << endl;
					return;
				}
				else {
					cout << "The result is " << opend << endl;
					cout << endl;
					return;
				}

			}
		}
	}
}
int Expression::isOperator(char ch) {//判断是否是操作符  
	if ((ch >= '0'&&ch <= '9') || ch == '.')
		return 0;
	else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '(' || ch == ')')
		return 1;
	else return 3;
}

double Expression::readOpend() {//读取操作数  

								//开始读取整数部分  
	double opend = 0;
	double opendInte = 0, opendDeci = 0;//整数部分与小数部分  
	while (ch >= '0'&&ch <= '9' && !sign) {
		opendInte = opendInte * 10 + ch - '0';
		++loc;
		if (loc == length)sign = 1;
		else ch = preExpression[loc];
	}
	//如果下一个不是0-9的字符而是小数点，那么开始读取小数部分  
	if (ch == '.') {
		++loc;
		ch = preExpression[loc];
		int rank = 10;
		while (ch >= '0'&&ch <= '9' && !sign) {
			opendDeci = opendDeci + (ch - '0')*1.0 / rank;
			rank *= 10;
			++loc;
			if (loc == length)sign = 1;
			else ch = preExpression[loc];
		}
	}
	opend = opendInte + opendDeci;
	return opend;
}

int Expression::opera(char ch, char top) {//读取操作符  
	if (ch == '='&&top == '=') {
		return 3;
	}
	else {
		if (!compareOpe(ch, top)) {//如果ch的优先级比top高  
			operators.push(top);
			operators.push(ch);
		}
		else {//如果ch的优先级比top低或者相等  
			double A, B;
			if (!operand.empty())//弹出操作数A  
				A = operand.top();
			else return 2;
			operand.pop();
			if (!operand.empty())//弹出操作数B  
				B = operand.top();
			else return 2;
			operand.pop();

			if (top == '+')
				operand.push(A + B);
			else if (top == '-')
				operand.push(B - A);
			else if (top == '*')
				operand.push(A*B);
			else if (top == '/') {
				if (A == 0) return 1;
				else operand.push(B / A);
			}
			if (ch == ')') {//判断ch是否为')'  
				top = operators.top();
				operators.pop();
				while (top != '(' && !operators.empty()) {
					double A, B;
					if (!operand.empty())//弹出操作数A  
						A = operand.top();
					else return 2;
					operand.pop();
					if (!operand.empty())//弹出操作数B  
						B = operand.top();
					else return 2;
					operand.pop();

					if (top == '+')
						operand.push(A + B);
					else if (top == '-')
						operand.push(B - A);
					else if (top == '*')
						operand.push(A*B);
					else if (top == '/') {
						if (A == 0) return 1;
						else operand.push(B / A);
					}
					top = operators.top();
					operators.pop();
				}
				if (operators.empty())return 2;
			}
			else {
				operators.push(ch);
			}
		}
	}
}

bool Expression::compareOpe(char ch, char top) {//判断操作符的优先级  

	if (ch == '=' || ch == ')')return true;

	else if (ch == '(')return false;//ch==(  

	else if (ch == '+' || ch == '-') {//ch==+||ch==-,只有top==+,-,*,/  
		if (top == '(' || top == '=')return false;
		else return true;
	}

	else if (ch == '*' || ch == '/') {//ch==*||ch==/,只有top==*,/  
		if (top == '*' || top == '/')return true;
		else return false;
	}
}

void Expression::start() {

	show();
	operating();
}
#endif  