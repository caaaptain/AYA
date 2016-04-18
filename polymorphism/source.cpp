#include "stdlib.h"
#include "car.h"
#include <iostream>
#include <string>


using namespace std;

template <class A>
void print(A & a)
{
	a.print();
}

int main()
{
	string name = "Bugatti Veyron :";
	string name2 = "Bus :";
	car _car(name, 430);
	bus _bus(name2, 170, 30);
	print<car>(_car);
	print<bus>(_bus);
	return 0;
}
