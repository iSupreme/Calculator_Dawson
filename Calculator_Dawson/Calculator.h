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
	string preExpression;//һ���Զ�ȡ���ʽ�����ַ�����  
	stack<char> operators;//��¼���ʽ�еĲ�����  
	stack<double> operand;//��¼���ʽ�еĲ�����  
	int loc;//��¼��ȡ��preExpression�ĵڼ���λ����  
	int length;//��¼preExpression�ĳ���  
	char ch;//��¼��ǰ��ȡ����preExpression���ַ�  
	//��¼loc�Ƿ��ȡ��preExpression�����һ���ַ�,1Ϊδ��ȡ�����һ���ַ���0Ϊ��ȡ�����һ���ַ�  
	bool sign;

			  //start��������  
	void show();//����������ʽ��������preExpression��  
	void operating();//��ʼ���м������  
	int isOperator(char ch);//�ж�ch�Ƿ��ǲ�����������0˵�������֣�����1˵���ǲ�����������2˵���Ƿ�����  
	double readOpend();//��ȡ������  
	int opera(char ch, char top);//��ȡ������������0˵����������������1˵�����������⣬����2˵�����ʽ����,3˵�����ʽ���Ϸ�  
	bool compareOpe(char ch, char top);//�жϲ����������ȼ�  

public:
	void start();//��ʼ����  
};

void Expression::show() {//����������ʽ��������preExpression��  
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

void Expression::operating() {//��ʼ���м������  
	operators.push('=');//����ջ����־  
	while (!operators.empty()) {
		if (!sign) {
			ch = preExpression[loc];
			//�ж�ch  
			if (isOperator(ch) == 3) { //���ch���ǲ�����Ҳ���ǲ�����  
				cout << "Sorry,expressions containing illegal characters." << endl;
				cout << "Please re-enter!" << endl;
				cout << endl;
				return;
			}
			else if (ch == '='&&loc != length - 1) {//=���ų������м�  
				cout << "\'=\' couldn't in the middle of arithmetic expression!" << endl;
				cout << "Please re-enter!" << endl;
				cout << endl;
				return;
			}
			else if (isOperator(ch)) {//���ch�ǲ�����  
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
			else {//���ch�ǲ�����  
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
int Expression::isOperator(char ch) {//�ж��Ƿ��ǲ�����  
	if ((ch >= '0'&&ch <= '9') || ch == '.')
		return 0;
	else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '(' || ch == ')')
		return 1;
	else return 3;
}

double Expression::readOpend() {//��ȡ������  

								//��ʼ��ȡ��������  
	double opend = 0;
	double opendInte = 0, opendDeci = 0;//����������С������  
	while (ch >= '0'&&ch <= '9' && !sign) {
		opendInte = opendInte * 10 + ch - '0';
		++loc;
		if (loc == length)sign = 1;
		else ch = preExpression[loc];
	}
	//�����һ������0-9���ַ�����С���㣬��ô��ʼ��ȡС������  
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

int Expression::opera(char ch, char top) {//��ȡ������  
	if (ch == '='&&top == '=') {
		return 3;
	}
	else {
		if (!compareOpe(ch, top)) {//���ch�����ȼ���top��  
			operators.push(top);
			operators.push(ch);
		}
		else {//���ch�����ȼ���top�ͻ������  
			double A, B;
			if (!operand.empty())//����������A  
				A = operand.top();
			else return 2;
			operand.pop();
			if (!operand.empty())//����������B  
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
			if (ch == ')') {//�ж�ch�Ƿ�Ϊ')'  
				top = operators.top();
				operators.pop();
				while (top != '(' && !operators.empty()) {
					double A, B;
					if (!operand.empty())//����������A  
						A = operand.top();
					else return 2;
					operand.pop();
					if (!operand.empty())//����������B  
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

bool Expression::compareOpe(char ch, char top) {//�жϲ����������ȼ�  

	if (ch == '=' || ch == ')')return true;

	else if (ch == '(')return false;//ch==(  

	else if (ch == '+' || ch == '-') {//ch==+||ch==-,ֻ��top==+,-,*,/  
		if (top == '(' || top == '=')return false;
		else return true;
	}

	else if (ch == '*' || ch == '/') {//ch==*||ch==/,ֻ��top==*,/  
		if (top == '*' || top == '/')return true;
		else return false;
	}
}

void Expression::start() {

	show();
	operating();
}
#endif  