#include <iostream>
#include <vector>
#include "MyHeap.h"

struct MyS
{
	int Q = 1;
	int W = 2;
	int E = 3;
	int R = 4;
};

MyVector<MyS> V2(5);
//MyVector<int> V2(5);

void print_test()
{
	std::cout << "V2: " << '\n';
	std::cout << V2.size() << " : size" << '\n';
	std::cout << V2.capacity() << " : capacity" << '\n';
	std::cout << V2.begin << " : begin" << '\n';
	std::cout << V2.end << " : end" << '\n';
	std::cout << V2.end_cap << " : end_cap" << '\n';
	std::cout << std::endl;
}

std::vector<MyS> V1;

void print_V()
{
	std::cout << "V1: " << '\n';
	std::cout << V1.size() << " : size" << '\n';
	std::cout << V1.capacity() << " : capacity" << '\n';
	std::cout << V1.data() << " : data" << '\n';
	std::cout << &(V1.back()) << " : & back" << '\n';
	std::cout << std::endl;
}


int main()

{
	MyS asd{ 2,5,8 };
	std::cout << "sizeof(MyS): " << int(sizeof(MyS)) << "\n\n";

	bool test_V = 0;

	if (test_V)
	{
		V1.push_back(asd);
		V1.begin();
		V1.size();

		print_V();

		print_V();

		V1.push_back(asd);
		V1.push_back(asd);
		V1.push_back(asd);
		V1.push_back(asd);

		print_V();

		V1.push_back(asd);

		print_V();
	}
	else
	{
		print_test();
		V2.push_back(asd);

		print_test();

		V2.push_back(asd);
		V2.push_back(asd);
		V2.push_back(asd);
		V2.push_back(asd);

		print_test();

		V2.push_back(asd);

		print_test();
	}



	return 0;
}