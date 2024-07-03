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
	//std::cout << iv_MyV.begin << " : begin" << '\n';
	//std::cout << iv_MyV.end << " : end" << '\n';
	//std::cout << iv_MyV.end_cap << " : end_cap" << '\n';
	std::cout << std::endl;
}

void print_SinV(const MyVector<MyS>& iv_MyV)
{
	for (size_t i = 0; i < iv_MyV.size(); ++i)
		std::cout << iv_MyV[i];
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
	MyS asd{ 1, 2, 3, 4 };
	std::cout << "MyS:\n";
	std::cout << "sizeof(MyS): " << sizeof(MyS) << '\n';
	std::cout << "alignof(MyS): " << alignof(MyS) << '\n';
	std::cout << std::endl;

	int test_V = 0;

	switch (test_V)
	{
	case 0:
	{
		for (int i = 10; i < 16; i++)
		{
			V2.push_back({ i, i + 1, i + 2, double(i + 3) });
		}

		print_test(V2);
		print_SinV(V2);

		//---
	}
	break;
	}

	return 0;
}