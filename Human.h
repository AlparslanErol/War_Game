#pragma once
#include <vector>
#include <memory>
using namespace std;

class Manager;

class Human
{
protected:
	double x;
	double y;
	double speed;
	double hpmax;
	double hpcurrent;

public:
	Human();
	virtual void DrawHPBar() { };
};