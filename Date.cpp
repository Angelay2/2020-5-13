#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

// �������󶼴��ڵĻ�, �������������
// Ҫ����һ�������ڵĻ� ���ǿ�������

// �������ʵ��
class Date
{
public:
	Date(int year = 1, int month = 1, int day = 1)
	{
		//�жϲ����Ƿ���Ч
		if (year <= 0
			|| month <= 0 || month > 12
			|| day > getMonthDay(year, month))
		{
			cout << "�Ƿ�����!" << endl;
			_year = _month = _day = 1;
			cout << "��������Ϊ��1-1-1" << endl;
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
	// d.operator+=(day)   d += day     ����Ƿ���ֵ�Ļ�, ��û�п�����, ���������ò��ÿ��� ���Ч��
	Date& operator+=(int day)
	{
		//�ж��Ƿ�Ϊ��ֵ
		if (day < 0)
			return *this -= -day;

		_day += day;
		//�ж������Ƿ񳬳���ǰ�·ݵ�����
		while (_day > getMonthDay(_year, _month))
		{
			//��λ�� ��ȥ��ǰ�µ����������·ݽ�λ
			_day -= getMonthDay(_year, _month);
			++_month;

			//�ж�����Ƿ���Ҫ��λ
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

		//�ж��Ƿ���Ҫ��λ
		while (_day <= 0)
		{
			//��λ
			--_month;
			//�ж��Ƿ���Ҫ������ݵ���λ
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
		//�������⴦��
		if (month == 2
			&& ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
			++day;

		return day;
	}

	//ǰ���Լ�  ++date --> �����Լӣ��ٷ����Լ�֮���ֵ   
	Date& operator++(){
		// Date operator(Date* this) ++d  --> d.operator++()  
		// thisָ��ľ���d
		return *this += 1;
	}

	//�����Լ� date++ --> �����Լ�֮ǰ��ֵ���ٽ����Լ�����
	Date operator++(int){
		// int �൱����һ����ǲ���, û������ ���Ǳ����д �൱�����﷨�涨
		// �ȿ������� ��û��+=֮ǰ��ֵ����, ��++
		Date ret(*this);
		*this += 1; // (*this).operator += 1
		return ret; // �ٷ��ر����ֵ

	}

	//ǰ���Լ�
	Date& operator--(){
		return (*this) -= 1;
	}

	//�����Լ�
	Date operator--(int){
		Date ret(*this);
		(*this) -= 1;
		return ret;
	}

	// int a = 2, b = 3; a - b;  ����ı�a��b��ֵ  --> *this��ֵ���ܸı�
	Date operator+(int day){
		Date ret(*this);
		return ret += day; // ֻ�������֮��Ľ�� ���ı�(*this)
	}

	Date operator-(int day){
		Date ret(*this);
		return ret -= day;
	}

	//�Ƚ�
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

	// eg: 2020.5.13  -  2019.4.15  ���߲����ǰ���ϼ��϶������ܵ�ǰ��
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
ȫ����ͨ����
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
	//(++d).print(); //ǰ��++ ����һ������ֵ��
	//d.print();
	//(d++).print();
	//d.print();

	d.print();
	(--d).print(); //ǰ��++ ����һ������ֵ��
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