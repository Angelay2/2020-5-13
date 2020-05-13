#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

// 两个对象都存在的话, 就是运算符重载
// 要是有一个不存在的话 就是拷贝构造

// 日期类的实现
class Date
{
public:
	Date(int year = 1, int month = 1, int day = 1)
	{
		//判断参数是否有效
		if (year <= 0
			|| month <= 0 || month > 12
			|| day > getMonthDay(year, month))
		{
			cout << "非法日期!" << endl;
			_year = _month = _day = 1;
			cout << "日期重置为：1-1-1" << endl;
		}
		else
		{
			_year = year;
			_month = month;
			_day = day;
		}

	}
	/*
	Date(const Date& date);

	Date& operator=(const Date& date);

	~Date();
	*/
	// 2020-5-1 + 10 ----> 2020-5-21
	// 5-101 --> - 31  --> 6-70 --> -30 --> 7-40 --> -31 --> 8-9
	// d.operator+=(day)   d += day     如果是返回值的话, 就没有拷贝了, 而返回引用不用拷贝 提高效率
	Date& operator+=(int day)
	{
		//判断是否为负值
		if (day < 0)
			return *this -= -day;

		_day += day;
		//判断天数是否超出当前月份的天数
		while (_day > getMonthDay(_year, _month))
		{
			//进位： 减去当前月的天数，向月份进位
			_day -= getMonthDay(_year, _month);
			++_month;

			//判断年份是否需要进位
			if (_month == 13)
			{
				++_year;
				_month = 1;
			}
		}

		return *this;
	}
	//2020-5-1  - 100
	//2020-5-(-99) --> +30 --> 4-(-69) --> + 31 --> 3-(-38) --> + 29 --> 2-(-9) --> + 31 --> 1-22
	Date& operator-=(int day)
	{
		if (day < 0)
			return *this += -day;

		_day -= day;

		//判断是否需要退位
		while (_day <= 0)
		{
			//退位
			--_month;
			//判断是否需要进行年份的退位
			if (_month == 0)
			{
				--_year;
				_month = 12;
			}

			_day += getMonthDay(_year, _month);
		}
		return *this;
	}

	int getMonthDay(int year, int month)
	{
		static int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day = days[month];
		//二月特殊处理
		if (month == 2
			&& ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
			++day;

		return day;
	}

	//前置自加  ++date --> 首先自加，再返回自加之后的值   
	Date& operator++(){
		// Date operator(Date* this) ++d  --> d.operator++()  
		// this指向的就是d
		return *this += 1;
	}

	//后置自加 date++ --> 返回自加之前的值，再进行自加运算
	Date operator++(int){
		// int 相当于是一个标记参数, 没有意义 但是必须得写 相当于是语法规定
		// 先拷贝构造 把没有+=之前的值保存, 再++
		Date ret(*this);
		*this += 1; // (*this).operator += 1
		return ret; // 再返回保存的值

	}

	//前置自减
	Date& operator--(){
		return (*this) -= 1;
	}

	//后置自减
	Date operator--(int){
		Date ret(*this);
		(*this) -= 1;
		return ret;
	}

	// int a = 2, b = 3; a - b;  不会改变a或b的值  --> *this的值不能改变
	Date operator+(int day){
		Date ret(*this);
		return ret += day; // 只返回相加之后的结果 不改变(*this)
	}

	Date operator-(int day){
		Date ret(*this);
		return ret -= day;
	}

	//比较
	bool operator<(const Date& date){
		if (_year < date._year)
			return true;
		else if (_year == date._year){
			if (_month < date._month)
				return true;
			else if (_month == date._month){
				if (_day < date._day)
					return true;
			}
		}
		return false;
	}

	bool operator>(const Date& date){
		return !(*this <= date);
	}

	bool operator==(const Date& date){
		return this->_year == date._year
			&& this->_month == date._month
			&& this->_day == date._day;
	}

	bool operator>=(const Date& date){
		return *this > date || *this == date;
	}

	bool operator<=(const Date& date){
		return *this < date || *this == date;
	}

	bool operator!=(const Date& date){
		return !(*this == date);
	}

	// eg: 2020.5.13  -  2019.4.15  后者不变的前提上加上多少天能到前者
	int operator-(Date& date){
		if (*this > date){
			int day = 0;
			Date ret = date;
			while (ret != *this){
				++ret;
				++day;
			}
			return day;
		}
		else{
			Date ret = date;
			int day = 0;
			while (ret != *this){
				--ret;
				--day;
			}
			return day;
		}
	}


	void print(){
		cout << _year << "-" << _month << "-" << _day << endl;
	}

private:
	int _year;
	int _month;
	int _day;
};

/*
全局普通函数
Date& operator++(Date& date){
	return date += 1;
}
Date operator++(Date& date, int){
	Date ret = date;
	date += 1;
	return ret;
}
*/
void test1(){
	Date d1(2020, 5, 1);
	d1.print();
	Date d2(2020, 5, 32);
	d2.print();
	Date d3(2020, 13, 2);
	d3.print();
	d1 += -100;
	d1.print();
	d1 += 100;
	d1.print();
	d1 += 150;
	d1.print();
	d1 += 3650;
	d1.print();
	d1 += -365;
	d1.print();
	d1 -= 3650;
	d1.print();

	++d1;
	d1.print();
	++d1;
	d1.print();
	++d1;
	d1.print();
	++d1;
	d1.print();
	++d1;
	d1.print();
	for (int i = 0; i < 100; ++i){
		++d1;
		d1.print();
	}

	cout << (d1 == d2) << endl;

}

void test2(){
	Date d(2020, 5, 13);
	//d.print();
	//(++d).print(); //前置++ 是由一个返回值的
	//d.print();
	//(d++).print();
	//d.print();

	d.print();
	(--d).print(); //前置++ 是由一个返回值的
	d.print();
	(d--).print();
	d.print();
}

void test3(){
	Date d(2020, 5, 13);
	Date ret = d - 365;
	ret.print();
	d.print();
	ret = d + 365;
	ret.print();
	d.print();

}
int main(){
	//test1();
	//test2();
	test3();
	system("pause");
	return 0;
}