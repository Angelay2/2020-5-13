#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

// 1. const���κ���(��ȥ����thisָ���) --> ��ʾ�����Ϊconst Date* const this
// thisָ��ֻ�����еĳ�Ա��������
// ������ͨ��������const����, û������, ��Ϊ��û��thisָ��
class Date
{
public:
	void Display()    // void Dispaly( Date* const this) 
	{
		cout << "Display ()" << endl;
		cout << "year:" << _year << endl;
		cout << "month:" << _month << endl;
		cout << "day:" << _day << endl << endl;
		_day = 10;

		// ��const��Ա�������Ե���const��Ա����  Ȩ�޿��Ա���С
		fun1();
		fun2();
	}
	void Display() const  // void Dispaly(const Date* const this) ��ʾ���ݲ��ɱ�
	{
		cout << "Display () const" << endl;
		cout << "year:" << _year << endl;
		cout << "month:" << _month << endl;
		cout << "day:" << _day << endl << endl;
		//_day = 10;

		// const��Ա�������ܵ��÷�const��Ա����  ����Ȩ�޲��ܱ��Ŵ�
		fun2();
		// fun1();  
	}
	void fun1(){}; //��const��Ա����
	void fun2() const {}; // const��Ա����
private:
	int _year; // ��
	int _month; // ��
	int _day; // ��
};
class Time
{
public:
	Time(int h = 1, int m = 1, int s = 1)
		:_h(h)
		, _m(m)
		, _s(s)
	{
		cout << "Time(int h = 1, int m = 1, int s = 1)" << endl;
	}
private:
	int _h;
	int _m;
	int _s;
};

// 2. ��ʼ���б�
class Date
{
public:
	//��ʼ���б� ��Ա������ʼ���ĵط���Ҳ�ǳ�Ա����ĵط�
	//           ÿһ����Ա����ֻ�ܳ���һ��
	//   :��Ա����(��ʼֵ���߳�ʼ�����ʽ), �����ĳ�Ա���� 
	Date(int y = 1, int m = 1, int d = 1)
		: _ra(d)   //�������ͱ����ڳ�ʼ���б��г�ʼ����
		, _ca(1)  //const��Ա�����ڳ�ʼ���б��г�ʼ��
		//, _t(23,59,59) //û��Ĭ�Ϲ��캯�����Զ����Ա�����ڳ�ʼ���б��г�ʼ��
	{
		/*
		//��ֵ����
		_year = y;
		_month = m;
		_day = d;

		_year = y;
		_year = y;
		*/
		//_t = Time(23, 12, 12);
	}

	Date(const Date& date)
		:_year(date._year)
		, _month(date._month)
		, _ra(date._ra)
		, _ca(date._ca)
		, _t(date._t)
	{}


	//ȡ��ַ��Ա���� &  ����Ҫʵ��&���غ���
	Date* operator&()
	{
		return this;
	}
	//const ȡ��ַ��Ա����
	const Date* operator&() const
	{
		return this;
	}
private:
	int _year; // ��
	int _month; // ��
	int _day; // ��
	int& _ra;
	const int _ca;
	Time _t;
};

class Test
{
public:
	//��Ա�ĳ�ʼ��˳�������˳��һ�£������ڳ�ʼ���б��е�˳��û�й�ϵ
	//����������˳�򱣳�һ��
	Test(int b)
		:_b(b)
		, _a(2 * _b)
	{}
private:
	int _a;
	int _b;
};

//��ͨ��������const���εģ���Ϊ����û��thisָ��
void fun(int a)//const
{
	cout << "fun" << endl;
}

void t1()
{
	Date d(2020, 5, 13);
	Date* pd = &d;
	Date* const cpd = pd;
	const Date cd(2020, 5, 1);
	const Date* pcd = &cd;
	const Date* const cpcd = pcd;
	d.Display();
	cd.Display();
}

void t2()
{
	Test t(100);

}

void t3()
{
	Date d(2020, 5, 13);
}

int main()
{
	//t1();
	//t2();
	t3();
	return 0;
}