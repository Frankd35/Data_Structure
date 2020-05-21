#pragma once
class Stack {
public:
	Stack(void);

	//������ʵ��push����
	//���ܣ�������ѹջ	����������������Ԫ�ص�ַ����Ԫ��
	virtual void push(void* pnt) = 0;

	//������ʵ��pop����
	//���ܣ���ջ����������Ԫ�ظ�ֵ������	����������������Ԫ�ص�ַ
	virtual void pop(void* pnt) = 0;

	//������ʵ��get_top����
	//���ܣ�ջ������Ԫ�ظ�ֵ������	����������������Ԫ�ص�ַ
	virtual void get_top(void* pnt) = 0;

	//����ջ�ĳ���
	int get_size(void);

	virtual ~Stack();
protected:
	void* top;
	void* base;
	int size;

};


// ����Ԫ������Ϊ int ��ջ
//���в���������int*������ᷢ������
class Stack_i
	: public Stack {
public:
	Stack_i(void);

	void push(void* pnt);
	void pop(void* pnt);
	void get_top(void* pnt);

	~Stack_i(void);
};



// ����Ԫ������Ϊ char ��ջ
//���в���������char*������ᷢ������
class Stack_c
	: public Stack {
public:
	Stack_c(void);

	void push(void* pnt);
	void pop(void* pnt);
	void get_top(void* pnt);

	~Stack_c(void);
};