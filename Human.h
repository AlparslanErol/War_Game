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
	double getX();
	double getY();
	double getSpeed();
	double getHpmax();
	double getHpcurrent();
	void setX(double _);
	void setY(double _);
	void setSpeed(double _);
	void setHpmax(double _);
	void setHpcurrent(double _);

	virtual void DrawHPBar(int x, int y, int HPMax, int HPCurrent);
};