#include "primitives.h"
#include <iostream>
#include <cmath>

using namespace std;

bool
Box::check_colision (Box b1. Box b2)
{
	if (b1.upper_left.y <= (b2.upper_left.y + b2.height))
	{
		return true;
	}
	else if (b1.upper_left.x <= (b2.upper_left.x + b2.width))
	{
		return true;
	}
	else if ((b1.upper_left.y + b1.height) <= b2.upper_left.y)
	{
		return true;
	}
	else if ((b1.upper_left.x + b1.width) <= b2.upper_left.x)
	{
		return true;
	}
	else
	{
		//There is no colision
	}

	return false;
}

Point
add_vector2d (Vector2d vector2d, Point point)
{
	Point p;

	p.x = point.x + vector2d.x;
	p.y = point.y + vector2d.y;

	return p;
}

Vector2d
sub_points (Point p1, Point p2)
{
	Vector2d vector2d;

	vector2d.x = p1.x - p2.x;
	vector2d.y = p1.y - p2.y;

	return vector2d;
}

void
print_point (Point point)
{
	cout << "(" << point.x << ", " << point.y << ")";
}

void
print_vector2d (Vector2d vector2d)
{
	cout << "(" << vector2d.x << ") î + " << "(" << vector2d.y << ") ĵ";
}

float
length (Vector2d vector2d)
{
	return (float) sqrt (pow (vector2d.x, 2) + pow (vector2d.y, 2));
}

float length_sqrt (Vector2d vector2d)
{
	return (float) (pow (vector2d.x, 2) + pow (vector2d.y, 2));
}

Vector2d
multiply_vector2d (Vector2d vector2d, float number)
{
	Vector2d v;
	
	v.x = vector2d.x * number;
	v.y = vector2d.y * number;

	return v;
}

Vector2d
divide_vector2d (Vector2d vector2d, float number)
{
	Vector2d v;
	
	v.x = vector2d.x / number;
	v.y = vector2d.y / number;

	return v;	
}

Vector2d
normalized_vector2d (Vector2d vector2d)
{
	Vector2d normalized;

	normalized.x = vector2d.x / length (vector2d);
	normalized.y = vector2d.y / length (vector2d);

	return normalized;
}

Vector2d
add_vector2d (Vector2d v1, Vector2d v2)
{
	Vector2d v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;

	return v;
}

Vector2d
sub_vector2d (Vector2d v1, Vector2d v2)
{
	Vector2d v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;

	return v;
}

