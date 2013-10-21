#ifndef PRIMITIVES_H
#define PRIMITIVES_H

typedef struct _Point
{
	float x;
	float y;
}Point;

typedef struct _Vector2d
{
	float x;
	float y;
}Vector2d;

typedef struct _Box
{
	Point upper_left;
	int width;
	int height;
}Box;

bool check_colision (Box b1, Box b2);

Point add_vector2d (Vector2d vector2d, Point point);
Vector2d sub_points (Point p1, Point p2);
Vector2d multiply_vector2d (Vector2d vector2d, float number);
Vector2d divide_vector2d (Vector2d vector2d, float number);
Vector2d normalized_vector2d (Vector2d vector2d);
Vector2d add_vector2d (Vector2d v1, Vector2d v2);
Vector2d sub_vector2d (Vector2d v1, Vector2d v2);

float length (Vector2d vector2d);
float length_sqrt (Vector2d vector2d);

void print_point (Point point);
void print_vector2d (Vector2d vector2d);

#endif