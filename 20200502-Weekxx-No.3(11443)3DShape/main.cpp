#include <iostream>
#include <string>
#include "function.h"
using namespace std;


int main() {
	using namespace oj;

	string s;
	double a, b, c;
	double totalVolume = 0.0, totalPerimeter = 0.0;//Perimeter: ©Pªø

	while (cin >> s) {
		if (s == "Sphere") {
			cin >> a >> b;
			Sphere sphere(a, b);
			totalVolume += sphere.getVolume();
        }
		else if (s == "Cone") {
			cin >> a >> b >> c;
			Cone cone(a, b, c);
			totalVolume += cone.getVolume();
        }
		else if (s == "Cuboid") {
			cin >> a >> b >> c;
			Cuboid cuboid(a, b, c);
			totalVolume += cuboid.getVolume();
        }
		else if (s == "Cube") {
			cin >> a;
			Cube cube(a);
			totalVolume += cube.getVolume();
        }
    }

	cout << totalVolume << endl;

	system("pause");
}