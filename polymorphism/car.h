#include <iostream>
#include <string>
using namespace std;

class car
{
private: 
	std::string model;
protected:
	size_t maxspeed;
public:
	car() : maxspeed(0),model(nullptr)
	{
		
	}

	car(std::string name, size_t speed) : model(name), maxspeed(speed)
	{
	  	
	}
	
	void print()
	{
		cout << maxspeed << endl;
		cout << model << endl;
	}
	virtual ~car()
	{
	}

};

class bus : public car
{
public:
	bus() : car(), _maxpas(0)
	{
	}

	bus(std::string name, size_t speed, size_t maxpas): car(name, speed), _maxpas(maxpas)
	{
	}

	void print()
	{
		car::print();
		cout << _maxpas << endl;
	}

	~bus()
	{
	}
private:
	size_t _maxpas;
};
