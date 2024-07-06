#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
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



/* ---   Heavy Struct   --- */

// Класс с инициализацией в 1 сек 
class Heavy_S {
public:
	int data;

	Heavy_S(int in_data = rand() % 100) : data(in_data)
	{
		//every element creation takes 2 seconds
		std::cout << "Construction started.\n";
		std::chrono::seconds sec(1);
		std::this_thread::sleep_for(sec);
		std::cout
			<< "Constructed."
			<< std::endl;
	};

	~Heavy_S() {
		std::cout << "Destroyed.\n";
	};

	// Дружественная ф-ция для вывода на консоль
	friend std::ostream& operator<<(std::ostream& out, const Heavy_S& in_S)
	{
		out << "{ " << in_S.data << " }\n";
		return out;
	}
};
//---------------------------------------------------------------------------------------



/* ---   My Vector   --- */

template <typename T>
void print_MyV(const MyVector<T>& iv_MyV)
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

	std::cout
		<< "Список алгоритмов для \"MyS\":\n"
		<< "1. Пузырьковая сортировка: A по убыванию;\n"
		<< "2. Сортировка выбором: B по возрастанию;\n"
		<< "3. Сортировка вставками: C по возрастанию;\n"
		<< "4. \"Быстрая\" сортировка: D по возрастанию;\n"
		<< "5. Сортировка слиянием: D по возрастанию;\n"
		<< "6. Сортировка Шелла: D по убыванию;\n"
		<< "7. Сортировка кучей (Пирамидальная): D по возрастанию;\n"
		<< "8. Проверка на перестановку V1(V0) (is_permutation).\n"
		<< "\n"
		<< "[10 сек]  Список алгоритмов для \"Heavy_S\":\n"
		<< "[+36 сек] 11. Пузырьковая сортировка: по убыванию;\n"
		<< "[+4 сек]  12. Сортировка выбором: по убыванию;\n"
		<< "[+36 сек] 13. Сортировка вставками: по убыванию;\n"
		<< "[+8 сек]  14. \"Быстрая\" сортировка: по убыванию;\n"
		<< "[+8 сек]  15. Сортировка слиянием: по убыванию;\n"
		<< "[+8 сек]  16. Сортировка Шелла: по убыванию;\n"
		<< "[+21 сек] 17. Сортировка кучей (Пирамидальная): по убыванию;\n"
		<< "          18. Проверка на перестановку V1(V0) (is_permutation).\n"
		<< std::endl;



	// Переменные для отсчёта времени
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point finish;



	// Выбор проверяемой сортировки
	int test_V = 0;
	std::cout << "Выбор тестируемого алгоритма: ";
	std::cin >> test_V;
	std::cout << std::endl;
	bool check_test = true;



	if (1 <= test_V && test_V <= 8)
	{
		check_test = false;

		// Обзор выбранной структуры
		if (test_V < 10)
			std::cout
			<< "Тип данных: MyS\n"
			<< "Кол. Байт: " << sizeof(MyS) << '\n'
			<< "Компоновка: " << alignof(MyS) << '\n'
			<< std::endl;

		// Предварительная инициализация
		MyS test_MyS{ 1, 2, 3, 4 };

		// Предварительная инициализация и заполнение контейнера
		MyVector<MyS> V1(5);
		for (int i = 1; i < 10; ++i)
		{
			V1.push_back({ double(rand() % 10 + 10), i, 23 - i, -i });
		}



		// Вывод данных контейнера
		std::cout << "------------------------------------------\n";
		print_MyV(V1);
		std::cout << V1;
		std::cout << "------------------------------------------" << std::endl;



		switch (test_V)
		{
		case 1:
		{
			start = std::chrono::steady_clock::now();

			std::cout << "Пузырьковая сортировка: A по убыванию:\n" << std::endl;
			V1.bubble_sort(
				[](const MyS& first, const MyS& second)
				{ return first.A < second.A; });
		}
		break;
		case 2:
		{
			start = std::chrono::steady_clock::now();

			std::cout << "Сортировка выбором: B по возрастанию:\n" << std::endl;
			V1.selection_sort(
				[](const MyS& first, const MyS& second)
				{ return first.B > second.B; });
		}
		break;
		case 3:
		{
			start = std::chrono::steady_clock::now();

			std::cout << "Сортировка вставками: C по возрастанию:\n" << std::endl;
			V1.insertion_sort(
				[](const MyS& first, const MyS& second)
				{ return first.C > second.C; });
		}
		break;
		case 4:
		{
			start = std::chrono::steady_clock::now();

			std::cout << "\"Быстрая\" сортировка: D по возрастанию:\n" << std::endl;
			V1.quick_sort(
				[](const MyS& first, const MyS& second)
				{ return first.D > second.D; });
		}
		break;
		case 5:
		{
			start = std::chrono::steady_clock::now();

			std::cout << "Сортировка слиянием: D по возрастанию:\n" << std::endl;
			V1.merge_sort(
				[](const MyS& first, const MyS& second)
				{ return first.D > second.D; });
		}
		break;
		case 6:
		{
			start = std::chrono::steady_clock::now();

			std::cout << "Сортировка Шелла: D по убыванию:\n" << std::endl;
			V1.shell_sort(
				[](const MyS& first, const MyS& second)
				{ return first.D > second.D; });
		}
		break;
		case 7:
		{
			start = std::chrono::steady_clock::now();

			std::cout << "Сортировка кучей (Пирамидальная): D по возрастанию:\n" << std::endl;
			V1.heap_sort(
				[](const MyS& first, const MyS& second)
				{ return first.D > second.D; });
		}
		break;
		case 8:
		{
			start = std::chrono::steady_clock::now();

			std::cout << "Проверка на перестановку V1(V0) (is_permutation):" << std::boolalpha << "\n\n";

			MyVector<MyS> V0 = V1;
			std::cout << "Проверка #1: при V0 = V1\n" << V1.is_permutation(V0) << "\n\n";

			MyS buf = V1[3];
			V1.erase(3);
			V1.insert(8, buf);
			std::cout << "Проверка #2: при swap(V1[3], V1[8])\n" << V1.is_permutation(V0) << "\n\n";

			V1.push_back(test_MyS);
			std::cout << "Проверка #3: после V1.push_back(test_MyS)\n" << V1.is_permutation(V0) << "\n\n";

			V1.erase(5);
			std::cout << "Проверка #4: после V1.erase(5)\n" << V1.is_permutation(V0) << "\n\n";

			std::cout
				<< std::noboolalpha
				<< "------------------------------------------"
				<< std::endl;

		}
		break;
		}

		finish = std::chrono::steady_clock::now();


		// Вывод данных изменённого контейнера
		print_MyV(V1);
		std::cout << V1;
	}
	else if (11 <= test_V && test_V <= 18)
	{
		check_test = false;

		// Обзор выбранной структуры
		if (test_V < 10)
			std::cout
			<< "Тип данных: Heavy_S\n"
			<< "Кол. Байт: " << sizeof(Heavy_S) << '\n'
			<< "Компоновка: " << alignof(Heavy_S) << '\n'
			<< std::endl;

		// Предварительная инициализация
		Heavy_S test_Heavy_S;

		// Предварительная инициализация и заполнение контейнера
		MyVector<Heavy_S> V1(5);
		for (int i = 1; i < 10; ++i)
		{
			V1.push_back(Heavy_S{ i });
		}



		// Вывод данных контейнера
		std::cout << "------------------------------------------\n";
		print_MyV(V1);
		std::cout << V1;
		std::cout << "------------------------------------------" << std::endl;



		switch (test_V)
		{
		case 11:
		{
			start = std::chrono::steady_clock::now();

			std::cout << "Пузырьковая сортировка: по убыванию:\n" << std::endl;
			V1.bubble_sort(
				[](const Heavy_S& first, const Heavy_S& second)
				{ return first.data < second.data; });
		}
		break;
		case 12:
		{
			start = std::chrono::steady_clock::now();

			std::cout << "Сортировка выбором: по убыванию:\n" << std::endl;
			V1.selection_sort(
				[](const Heavy_S& first, const Heavy_S& second)
				{ return first.data < second.data; });
		}
		break;
		case 13:
		{
			start = std::chrono::steady_clock::now();

			std::cout << "Сортировка вставками: по убыванию:\n" << std::endl;
			V1.insertion_sort(
				[](const Heavy_S& first, const Heavy_S& second)
				{ return first.data < second.data; });
		}
		break;
		case 14:
		{
			start = std::chrono::steady_clock::now();

			std::cout << "\"Быстрая\" сортировка: по убыванию:\n" << std::endl;
			V1.quick_sort(
				[](const Heavy_S& first, const Heavy_S& second)
				{ return first.data < second.data; });
		}
		break;
		case 15:
		{
			start = std::chrono::steady_clock::now();

			std::cout << "Сортировка слиянием: по убыванию:\n" << std::endl;
			V1.merge_sort(
				[](const Heavy_S& first, const Heavy_S& second)
				{ return first.data < second.data; });
		}
		break;
		case 16:
		{
			start = std::chrono::steady_clock::now();

			std::cout << "Сортировка Шелла: по убыванию:\n" << std::endl;
			V1.shell_sort(
				[](const Heavy_S& first, const Heavy_S& second)
				{ return first.data > second.data; });
		}
		break;
		case 17:
		{
			start = std::chrono::steady_clock::now();

			std::cout << "Сортировка кучей (Пирамидальная): по убыванию:\n" << std::endl;
			V1.heap_sort(
				[](const Heavy_S& first, const Heavy_S& second)
				{ return first.data < second.data; });
		}
		break;
		case 18:
		{
			start = std::chrono::steady_clock::now();

			std::cout << "Проверка на перестановку V1(V0) (is_permutation):" << std::boolalpha << "\n\n";

			MyVector<Heavy_S> V0 = V1;
			std::cout << "Проверка #1: при V0 = V1\n" << V1.is_permutation(V0) << "\n\n";

			Heavy_S buf = V1[3];
			V1.erase(3);
			V1.insert(8, buf);
			std::cout << "Проверка #2: при swap(V1[3], V1[8])\n" << V1.is_permutation(V0) << "\n\n";

			V1.push_back(test_Heavy_S);
			std::cout << "Проверка #2: после V1.push_back(test_Heavy_S)\n" << V1.is_permutation(V0) << "\n\n";

			V1.erase(5);
			std::cout << "Проверка #3: после V1.erase(5)\n" << V1.is_permutation(V0) << "\n\n";

			std::cout
				<< std::noboolalpha
				<< "------------------------------------------"
				<< std::endl;

		}
		break;
		}

		finish = std::chrono::steady_clock::now();


		// Вывод данных изменённого контейнера
		std::cout << '\n';
		print_MyV(V1);
		std::cout << V1;
	}

	if (check_test)
	{
		std::cout << "\nТестируемый алгоритм НЕ выбран\n\n";
	}

	// Расчёт времени
	auto dif = std::chrono::duration<double>(finish - start);

	std::cout
		<< "==========================================\n"
		<< "Затраченное время:\n"
		<< std::chrono::duration_cast<std::chrono::seconds>(dif).count() << " s\n"
		<< std::chrono::duration_cast<std::chrono::milliseconds>(dif).count() << " ms\n"
		<< (float)std::chrono::duration_cast<std::chrono::nanoseconds>(dif).count() / 1000 << " us\n"
		<< std::endl;

	return 0;
}