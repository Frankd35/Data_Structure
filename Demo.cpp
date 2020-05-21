#include<ctype.h>
#include<stdio.h>
#include "Stack.h"

#define LENGTH 50



//���ַ���ջ��������
int isp(char ch) {	//in stack priority
	switch (ch)
	{
	case '+':
	case '-':
		return 3;
	case '*':
	case '/':
	case '%':
		return 5;
	case '(':
		return 1;
	case ')':
		return 8;
	case ';':
		return 0;
	case '^':
		return 7;
	default:
		break;
	}
}

//���ַ���ջ��������
int icp(char ch) {	//in coming priority
	switch (ch)
	{
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
	case '%':
		return 4;
	case '(':
		return 8;
	case ')':
		return 1;
	case ';':
		return 0;
	case '^':
		return 6;
	default:
		break;
	}
}



//��׺���ʽת��׺���ʽ
char* to_pastorder_expression(char* expression) {
	//Ϊ��׺���ʽ����ռ�
	static char pastorder_expression[LENGTH];
	char ch;	//����ջ�ַ�
	int index = 0;	//д���׺���ʽ��λ���±�
	int i = 0;	// ch ��λ���±�
	Stack_c c_stack = Stack_c();
	Stack* c = &c_stack;	//ʵ�ֶ�̬

	char end_label = ';';
	char top;

	// ����������;����ջ
	c->push(&end_label);
	while (1)
	{
		// ��ch�ǲ�����ֱ��д���׺���ʽ
		if (isdigit(expression[i]))
		{
			pastorder_expression[index] = expression[i];
			index++;
			// ��' '��ʶһ������
			if (!isdigit(expression[i + 1]))
			{
				pastorder_expression[index] = ' ';
				index++;
			}

		}
		//��ch�ǲ��������ж�ch�����ȼ�icp��ջ�������������ȼ�isp
		else
		{
			c->get_top(&top);	//top��ջ��������

			//�� icp (ch) > isp (op)��ch��ջ
			if (icp(expression[i]) > isp(top))
				c->push(&expression[i]);

			//icp (ch) < isp (op)����ջ�����
			else if (icp(expression[i]) < isp(top))
			{
				c->pop(&ch);
				pastorder_expression[index] = ch;
				index++;
				continue;
			}

			//��icp (ch) = isp (op)����ջ�������
			else if (icp(expression[i]) == isp(top))
			{
				c->pop(&ch);

				//���˳����� ( �Ŷ�����һ���ַ�ch
				if (ch == '(')
				{
					i++;
					continue;
				}
				break;	//���˳�����';'�㷨����
			}
		}
		i++;	// ch �±����
	}
	pastorder_expression[index] = ';';
	return pastorder_expression;
}



//�����׺���ʽ��ֵ
int calculate(char* expression)	{

	Stack_c c_stack;
	Stack_i i_stack;
	Stack* OPTR = &c_stack;	//��������
	Stack* OPND = &i_stack;	//������ջ
	char operand;	//������

	//�����׺���ʽ�����ַ�
	for (int i = 0; expression[i] != ';'; i++)
	{
		//��ջ���ַ������е������ַ�ת��Ϊint�����������ջ
		if (isdigit(expression[i]))
		{
			operand = expression[i] - '0';	//���������
			OPTR->push(&operand);	//ѹջ��λ���ߵ��Ƚ�ջ
			if (expression[i + 1] == ' ')	//' '��־�����Ľ���
			{
				int integer = 0;
				for (int times = 1; OPTR->get_size() != 0; times *= 10)	//times��������λ��
				{
					char e;	//������ȡ��
					OPTR->pop(&e);
					integer += times * (int)e;	//����������
				}
				OPND->push(&integer);
				i++;
			}
		}
		//���ݲ��������м���
		else if (expression[i] == '+')
		{
			int a, b;
			OPND->pop(&b);
			OPND->pop(&a);
			a += b;
			OPND->push(&a);
		}
		else if (expression[i] == '-')
		{
			int a, b;
			OPND->pop(&b);
			OPND->pop(&a);
			a -= b;
			OPND->push(&a);
		}
		else if (expression[i] == '*')
		{
			int a, b;
			OPND->pop(&b);
			OPND->pop(&a);
			a *= b;
			OPND->push(&a);
		}
		else if (expression[i] == '/')
		{
			int a, b;
			OPND->pop(&b);
			OPND->pop(&a);
			a *= b;
			OPND->push(&a);
		}
	}
	int result;	//���ر��ʽ���
	OPND->pop(&result);
	return result;
}



//���Դ���
/*
int main(void)
{
	char expression[LENGTH];
	int i = 0;
	do {
		expression[i] = getchar();
		i++;
	} while (expression[i - 1] != ';');
	char* poex = to_pastorder_expression(expression);
	i = 0;
	do {
		printf("%c", (poex[i]));
		i++;
	} while (poex[i - 1] != ';');
	printf("\nresult:%d", calculate(poex));
}
*/
