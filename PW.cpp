#include <iostream>
#include <vector>
#include "MyHeap.h"

int main()

{
	std::vector<int> V1 = { 2, 5, 85 };
	V1.push_back(3);
	V1.begin();
	V1.size();
	std::vector<int>::iterator it;

	MyVector<int> V2(5);
	MyVector<int>::value_type r;

	std::cout << "capacity: " << V2.capacity() << '\n';
	std::cout << "begin: " << V2.begin << '\n';
	std::cout << "end: " << V2.end << '\n';
	std::cout << "end_cap: " << V2.end_cap << '\n';
	std::cout << std::endl;

	return 0;
}