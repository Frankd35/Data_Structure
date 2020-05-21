#pragma once
class Stack {
public:
	Stack(void);

	//子类需实现push方法
	//功能：将参数压栈	参数：该类型数据元素地址数据元素
	virtual void push(void* pnt) = 0;

	//子类需实现pop方法
	//功能：弹栈，将该数据元素赋值给参数	参数：该类型数据元素地址
	virtual void pop(void* pnt) = 0;

	//子类需实现get_top方法
	//功能：栈顶数据元素赋值给参数	参数：该类型数据元素地址
	virtual void get_top(void* pnt) = 0;

	//返回栈的长度
	int get_size(void);

	virtual ~Stack();
protected:
	void* top;
	void* base;
	int size;

};


// 数据元素类型为 int 的栈
//所有参数必须是int*，否则会发生错误
class Stack_i
	: public Stack {
public:
	Stack_i(void);

	void push(void* pnt);
	void pop(void* pnt);
	void get_top(void* pnt);

	~Stack_i(void);
};



// 数据元素类型为 char 的栈
//所有参数必须是char*，否则会发生错误
class Stack_c
	: public Stack {
public:
	Stack_c(void);

	void push(void* pnt);
	void pop(void* pnt);
	void get_top(void* pnt);

	~Stack_c(void);
};