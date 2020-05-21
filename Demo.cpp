#include<ctype.h>
#include<stdio.h>
#include "Stack.h"

#define LENGTH 50



//求字符的栈内优先数
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

//求字符的栈外优先数
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



//中缀表达式转后缀表达式
char* to_pastorder_expression(char* expression) {
	//为后缀表达式申请空间
	static char pastorder_expression[LENGTH];
	char ch;	//待进栈字符
	int index = 0;	//写入后缀表达式的位置下标
	int i = 0;	// ch 的位置下标
	Stack_c c_stack = Stack_c();
	Stack* c = &c_stack;	//实现多态

	char end_label = ';';
	char top;

	// 将结束符‘;’进栈
	c->push(&end_label);
	while (1)
	{
		// 若ch是操作数直接写入后缀表达式
		if (isdigit(expression[i]))
		{
			pastorder_expression[index] = expression[i];
			index++;
			// 以' '标识一个整数
			if (!isdigit(expression[i + 1]))
			{
				pastorder_expression[index] = ' ';
				index++;
			}

		}
		//若ch是操作符，判断ch的优先级icp和栈顶操作符的优先级isp
		else
		{
			c->get_top(&top);	//top是栈顶操作符

			//若 icp (ch) > isp (op)，ch进栈
			if (icp(expression[i]) > isp(top))
				c->push(&expression[i]);

			//icp (ch) < isp (op)，弹栈并输出
			else if (icp(expression[i]) < isp(top))
			{
				c->pop(&ch);
				pastorder_expression[index] = ch;
				index++;
				continue;
			}

			//若icp (ch) = isp (op)，退栈但不输出
			else if (icp(expression[i]) == isp(top))
			{
				c->pop(&ch);

				//若退出的是 ( 号读入下一个字符ch
				if (ch == '(')
				{
					i++;
					continue;
				}
				break;	//若退出的是';'算法结束
			}
		}
		i++;	// ch 下标后移
	}
	pastorder_expression[index] = ';';
	return pastorder_expression;
}



//计算后缀表达式的值
int calculate(char* expression)	{

	Stack_c c_stack;
	Stack_i i_stack;
	Stack* OPTR = &c_stack;	//操作符符
	Stack* OPND = &i_stack;	//操作数栈
	char operand;	//操作符

	//历遍后缀表达式所有字符
	for (int i = 0; expression[i] != ';'; i++)
	{
		//用栈将字符数组中的数字字符转化为int并存入操作数栈
		if (isdigit(expression[i]))
		{
			operand = expression[i] - '0';	//计算出数字
			OPTR->push(&operand);	//压栈，位数高的先进栈
			if (expression[i + 1] == ' ')	//' '标志整数的结束
			{
				int integer = 0;
				for (int times = 1; OPTR->get_size() != 0; times *= 10)	//times代表数字位数
				{
					char e;	//将数字取出
					OPTR->pop(&e);
					integer += times * (int)e;	//求出这个整数
				}
				OPND->push(&integer);
				i++;
			}
		}
		//根据操作符进行计算
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
	int result;	//返回表达式结果
	OPND->pop(&result);
	return result;
}



//测试代码
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
