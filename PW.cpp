#include <iostream>
#include <vector>
#include <algorithm>
#include "MyHeap.h"

#pragma pack(push, 4)
struct MyS
{
	int Q = 1;
	int W = 2;
	int E = 3;
	double R = 4;

	// Дружественная ф-ция для вывода на консоль
	friend std::ostream& operator<<(std::ostream& out, const MyS& in_MyS)
	{
		out
			<< "{ "
			<< in_MyS.Q << ", "
			<< in_MyS.W << ", "
			<< in_MyS.E << ", "
			<< in_MyS.R << " }\n";
		return out;
	}
};
#pragma pack(pop)

MyVector<MyS> V1(5);

void print_MyV(const MyVector<MyS>& iv_MyV)
{
	std::cout << "MyVector" << '\n';
	std::cout << iv_MyV.size() << " : size" << '\n';
	std::cout << iv_MyV.capacity() << " : capacity" << '\n';
	std::cout << iv_MyV.begin << " : begin" << '\n';
	std::cout << iv_MyV.end << " : end" << '\n';
	std::cout << iv_MyV.end_cap << " : end_cap" << '\n';
	std::cout << std::endl;
}

void print_SinMyV(const MyVector<MyS>& iv_MyV)
{
	for (size_t i = 0; i < iv_MyV.size(); ++i)
		std::cout << iv_MyV[i];
	std::cout << std::endl;
}

std::vector<MyS> V0;

void print_V()
{
	std::cout << "V0:" << '\n';
	std::cout << V0.size() << " : size" << '\n';
	std::cout << V0.capacity() << " : capacity" << '\n';
	std::cout << V0.data() << " : data" << '\n';
	std::cout << &(V0.back()) << " : & back" << '\n';
	std::cout << std::endl;
}

int main()
{
	// Локализация
	setlocale(LC_ALL, "Russian");
	// Использовать текущее время в качестве начального значения для генератора псевдослучайных чисел
	srand(time(0));

	MyS asd{ 1, 2, 3, 4 };
	std::cout << "MyS:\n";
	std::cout << "sizeof(MyS): " << sizeof(MyS) << '\n';
	std::cout << "alignof(MyS): " << alignof(MyS) << '\n';
	std::cout << std::endl;



	// Выбор проверяемой сортировки
	int test_V = 0;



	for (int i = 1; i < 10; ++i)
	{
		V1.push_back({ i, 23 - i, -i, double(rand() % 10 + 10) });
	}

	print_MyV(V1);
	print_SinMyV(V1);

	// Условие сортировки
	auto lambda{
		[](const MyS& first, const MyS& second)
		{ return first.Q < second.Q; } 
	};



	switch (test_V)
	{
	case 0:
	{
		V1.bubble_sort(lambda);
	}
	break;
	case 1:
	{
		V1.bubble_sort(lambda);
	}
	break;
	case 2:
	{
		V1.bubble_sort(lambda);
	}
	break;
	}



	print_MyV(V1);
	print_SinMyV(V1);



	return 0;
}