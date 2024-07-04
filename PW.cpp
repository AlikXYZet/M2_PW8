#include <iostream>
#include <vector>
#include <algorithm>
#include "MyHeap.h"



/* ---   My Struct   --- */

#pragma pack(push, 4)
struct MyS
{
	double D = 4;
	int A = 1;
	int B = 2;
	int C = 3;

	// Дружественная ф-ция для вывода на консоль
	friend std::ostream& operator<<(std::ostream& out, const MyS& in_MyS)
	{
		out
			<< "{ "
			<< in_MyS.A << ", "
			<< in_MyS.B << ", "
			<< in_MyS.C << ", "
			<< in_MyS.D << " }\n";
		return out;
	}
};
#pragma pack(pop)
//---------------------------------------------------------------------------------------



/* ---   My Vector   --- */

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
//---------------------------------------------------------------------------------------



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
	int test_V = 6;



	for (int i = 1; i < 10; ++i)
	{
		V1.push_back({ double(rand() % 10 + 10), i, 23 - i, -i });
	}

	print_MyV(V1);
	std::cout << V1 << std::endl;



	switch (test_V)
	{
	case 1:
	{
		std::cout << "Пузырьковая сортировка: A по убыванию:\n" << std::endl;
		V1.bubble_sort(
			[](const MyS& first, const MyS& second)
			{ return first.A < second.A; });
	}
	break;
	case 2:
	{
		std::cout << "Сортировка выбором: B по возрастанию:\n" << std::endl;
		V1.selection_sort(
			[](const MyS& first, const MyS& second)
			{ return first.B > second.B; });
	}
	break;
	case 3:
	{
		std::cout << "Сортировка вставками: C по возрастанию:\n" << std::endl;
		V1.insertion_sort(
			[](const MyS& first, const MyS& second)
			{ return first.C > second.C; });
	}
	break;
	case 4:
	{
		std::cout << "\"Быстрая\" сортировка: D по возрастанию:\n" << std::endl;
		V1.quick_sort(
			[](const MyS& first, const MyS& second)
			{ return first.D > second.D; });
	}
	break;
	case 5:
	{
		std::cout << "Сортировка слиянием: D по возрастанию:\n" << std::endl;
		V1.merge_sort(
			[](const MyS& first, const MyS& second)
			{ return first.D > second.D; });
	}
	break;
	case 6:
	{
		std::cout << "Сортировка Шелла: D по убыванию:\n" << std::endl;
		V1.shell_sort(
			[](const MyS& first, const MyS& second)
			{ return first.D > second.D; });
	}
	break;
	case 7:
	{
		std::cout << "Сортировка кучей: D по возрастанию:\n" << std::endl;
		V1.heap_sort(
			[](const MyS& first, const MyS& second)
			{ return first.D > second.D; });
	}
	break;
	}



	print_MyV(V1);
	std::cout << V1 << std::endl;



	return 0;
}