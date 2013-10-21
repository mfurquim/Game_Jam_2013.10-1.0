#include <iostream>
#include "primitives.h"

using namespace std;

int main ()
{
	Point p1;
	Point p2;
	Point p3;

	Vector2d v1;
	Vector2d v2;

	p1.x = 1;	p1.y = 2;
	p2.x = 4;	p2.y = 6;
	p3.x = 3;	p3.y = 4;
	v1.x = 0;	v1.y = 0;
	v2.x = 0;	v2.y = 0;

	v1 = sub_points (p1, p2);
	v2 = sub_points (p2, p3);

//	p1 = add_vector2d (v1, p1);

	cout << "Ponto 1: ";
	print_point(p1);
	cout << endl;

	cout << "Ponto 2: ";
	print_point(p2);
	cout << endl;

	cout << "Ponto 3: ";
	print_point(p3);
	cout << endl;

	p3 = add_vector2d (v2, p3);

	cout << "Ponto 4: ";
	print_point(p3);
	cout << endl;

	cout << "Vetor 1 = ";
	print_vector2d (v1);
	cout << endl;

	cout << "Vetor 2 = ";
	print_vector2d (v2);
	cout << endl;

	cout << "|Vetor 1| = ";
	cout << length (v1);
	cout << " ";
	cout << length_sqrt (v1);
	cout << endl;

	cout << "|Vetor 2| = ";
	cout << length (v2);
	cout << " ";
	cout << length_sqrt (v2);
	cout << endl;

	cout << "2 * Vetor 1 = ";
	print_vector2d (multiply_vec (v1, 2));
	cout << endl;

	cout << "3 * Vetor 2 = ";
	print_vector2d (multiply_vec (v2, 3));
	cout << endl;

	cout << "2 / Vetor 1 = ";
	print_vector2d (divide_vec (v1, 2));
	cout << endl;

	cout << "3 / Vetor 2 = ";
	print_vector2d (divide_vec (v2, 3));
	cout << endl;
	
	cout << "Normalized Vetor 1 = ";
	print_vector2d (normalized_vec (v1));
	cout << endl;
	
	cout << "Length Normalized Vetor 1 = " << length (normalized_vec (v1)) << endl;
	

	return 0;
}