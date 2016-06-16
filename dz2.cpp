#include <iostream>
#include "dz_1_part2.h"



int main()
{
	set<int> a;

	a.insert(3);
	a.insert(1);
	a.insert(2);
	a.insert(1);


	for (auto it = a.begin(); it != a.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	set<int> b = a;
	b.erase(1);
	b.print();

	system("pause");
	return 0;
}
