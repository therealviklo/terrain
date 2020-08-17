#pragma once
#include <cmath>

const double invSqrt2 = 1.0 / sqrt(2.0);
const double pi = acos(-1.0);

struct Point
{
	double x;
	double y;
};

Point operator+(const Point& a, const Point& b);
Point operator-(const Point& a, const Point& b);
Point operator*(const Point& p, double x);
Point operator*(double x, const Point& p);

struct Point3D
{
	double x;
	double y;
	double z;

	Point project() const noexcept;
};

enum Direction
{
	DIR_NONE = 0b0000,
	DIR_N    = 0b0001,
	DIR_S    = 0b0010,
	DIR_E    = 0b0100,
	DIR_W    = 0b1000,
	DIR_NE   = 0b0101,
	DIR_NW   = 0b1001,
	DIR_SE   = 0b0110,
	DIR_SW   = 0b1010
};

double angleAround(Point p, Point centre);
Point moveAngle(Point p, double angle, double distance);
Point rotateAround(Point p, Point centre, double angle);
double distance(Point a, Point b);
Point moveTowards(Point p, Point dest, double distance);