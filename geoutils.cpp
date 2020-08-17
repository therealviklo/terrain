#include "geoutils.h"

Point operator+(const Point& a, const Point& b)
{
	return {a.x + b.x, a.y + b.y};
}

Point operator-(const Point& a, const Point& b)
{
	return {a.x - b.x, a.y - b.y};
}

Point operator*(const Point& p, double x)
{
	return {p.x * x, p.y * x};
}

Point operator*(double x, const Point& p)
{
	return {p.x * x, p.y * x};
}

Point Point3D::project() const noexcept
{
	return {x, z - y};
}

double angleAround(Point p, Point centre)
{
	return atan2(p.y - centre.y, p.x - centre.x);
}

Point moveAngle(Point p, double angle, double distance)
{
	return {p.x + cos(angle) * distance, p.y + sin(angle) * distance};
}

Point rotateAround(Point p, Point centre, double angle)
{
	return moveAngle(centre, angleAround(p, centre) + angle, distance(p, centre));
}

double distance(Point a, Point b)
{
	return hypot(a.x - b.x, a.y - b.y);
}

Point moveTowards(Point p, Point dest, double distance)
{
	return moveAngle(p, angleAround(dest, p), distance);
}