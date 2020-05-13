#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

// 1. const修饰函数(是去修饰this指针的) --> 表示其参数为const Date* const this
// this指针只在类中的成员函数中有
// 所以普通函数不用const修饰, 没有作用, 因为其没有this指针
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

		// 非const成员函数可以调用const成员函数  权限可以被缩小
		fun1();
		fun2();
	}
	void Display() const  // void Dispaly(const Date* const this) 表示内容不可变
	{
		cout << "Display () const" << endl;
		cout << "year:" << _year << endl;
		cout << "month:" << _month << endl;
		cout << "day:" << _day << endl << endl;
		//_day = 10;

		// const成员函数不能调用非const成员函数  但是权限不能被放大
		fun2();
		// fun1();  
	}
	void fun1(){}; //非const成员函数
	void fun2() const {}; // const成员函数
private:
	int _year; // 年
	int _month; // 月
	int _day; // 日
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

// 2. 初始化列表
class Date
{
public:
	//初始化列表： 成员变量初始化的地方，也是成员定义的地方
	//           每一个成员变量只能出现一次
	//   :成员变量(初始值或者初始化表达式), 后续的成员变量 
	Date(int y = 1, int m = 1, int d = 1)
		: _ra(d)   //引用类型必须在初始化列表中初始化，
		, _ca(1)  //const成员必须在初始化列表中初始化
		//, _t(23,59,59) //没有默认构造函数的自定义成员必须在初始化列表中初始化
	{
		/*
		//赋值操作
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


	//取地址成员函数 &  不需要实现&重载函数
	Date* operator&()
	{
		return this;
	}
	//const 取地址成员函数
	const Date* operator&() const
	{
		return this;
	}
private:
	int _year; // 年
	int _month; // 月
	int _day; // 日
	int& _ra;
	const int _ca;
	Time _t;
};

class Test
{
public:
	//成员的初始化顺序和声明顺序一致，与其在初始化列表中的顺序没有关系
	//尽量和声明顺序保持一致
	Test(int b)
		:_b(b)
		, _a(2 * _b)
	{}
private:
	int _a;
	int _b;
};

//普通函数不用const修饰的，因为函数没有this指针
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