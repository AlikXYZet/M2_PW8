#include <iostream>
#include <vector>
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

MyVector<MyS> V2(5);
//MyVector<int> V2(5);

void print_test(const MyVector<MyS>& iv_MyV)
{
	std::cout << "MyVector" << '\n';
	std::cout << iv_MyV.size() << " : size" << '\n';
	std::cout << iv_MyV.capacity() << " : capacity" << '\n';
	std::cout << iv_MyV.begin << " : begin" << '\n';
	std::cout << iv_MyV.end << " : end" << '\n';
	std::cout << iv_MyV.end_cap << " : end_cap" << '\n';
	std::cout << std::endl;
}

void print_SinV(const MyVector<MyS>& iv_MyV)
{
	for (MyS* i = iv_MyV.begin; i < iv_MyV.end; ++i)
		std::cout << *i;
	std::cout << std::endl;
}

std::vector<MyS> V1;

void print_V()
{
	std::cout << "V1:" << '\n';
	std::cout << V1.size() << " : size" << '\n';
	std::cout << V1.capacity() << " : capacity" << '\n';
	std::cout << V1.data() << " : data" << '\n';
	std::cout << &(V1.back()) << " : & back" << '\n';
	std::cout << std::endl;
}

int main()

{
	MyS asd{ 2, 5 };
	std::cout << "MyS:\n";
	std::cout << "sizeof(MyS): " << sizeof(MyS) << '\n';
	std::cout << "alignof(MyS): " << alignof(MyS) << '\n';
	std::cout << std::endl;

	int test_V = 3;

	switch (test_V)
	{
	case 0:
	{
		V1.push_back(asd);

		print_V();

		V1.push_back(asd);
		V1.push_back(asd);
		V1.push_back(asd);
		V1.push_back(asd);

		print_V();

		V1.push_back(asd);
		V1.push_back(asd);

		print_V();

		V1.reserve(5);

		print_V();
	}
	break;
	case 1:
	{
		print_test(V2);
		V2.push_back(asd);

		print_test(V2);

		V2.push_back(asd);
		V2.push_back(asd);
		V2.push_back(asd);
		V2.push_back(asd);

		print_test(V2);

		V2.push_back({});

		print_test(V2);
		print_SinV(V2);

		V2.reserve(5);

		print_test(V2);

		V2.shrink_to_fit();

		print_test(V2);
		print_SinV(V2);

		V2.insert(2, { 9, 8, 7, 6 });

		print_test(V2);
		print_SinV(V2);
	}
	break;
	case 2:
	{
		print_test(V2);

		for (int i = 10; i < 16; i++)
		{
			V2.push_back({ i, i + 1, i + 2, double(i + 3) });
		}

		print_test(V2);
		print_SinV(V2);

		V2.insert(2, { 1, 2, 3, 4 });

		print_test(V2);
		print_SinV(V2);

		size_t check = V2.insert(V2.size(), { 101, 102, 103, 104 });

		std::cout << "check: " << check << "\n\n";
		print_test(V2);
		print_SinV(V2);

		check = V2.insert(V2.size() + 1, { 201, 202, 203, 204 });

		std::cout << "check: " << check << "\n\n";
		print_test(V2);
		print_SinV(V2);
	}
	break;
	case 3:
	{
		print_test(V2);

		for (int i = 10; i < 16; i++)
		{
			V2.push_back({ i, i + 1, i + 2, double(i + 3) });
		}

		print_test(V2);
		print_SinV(V2);

		int selection = 3;
		std::cout
			<< "V2[" << selection << "]: "
			<< V2[selection]
			<< std::endl;

		MyVector<MyS> V3;
		V3 = V2;

		print_test(V3);
		print_SinV(V3);
	}
	break;
	}

	return 0;
}