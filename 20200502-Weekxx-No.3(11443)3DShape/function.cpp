#include "function.h"
#pragma warning (disable: 4996)

namespace oj {
	void Shape3D :: setVolume(double v) {
		volume = v;
	}


	double Shape3D :: getVolume() {
		return volume;
	}


	Sphere :: Sphere(double r, double pi) {
		double vol = (4.0 / 3.0) * pi * (r*r*r);
		setVolume((r > 0 && pi > 0) ? vol : 0);
	}


	Cone :: Cone(double r, double h, double pi) {
		double vol = (1.0 / 3.0) * pi * (r*r*h);
		setVolume((r > 0 && h > 0 && pi > 0) ? vol : 0);
	}


	Cuboid :: Cuboid(double l, double w, double h) {
		double vol = l * w * h;
		setVolume((l > 0 && w > 0 && h > 0) ? vol : 0);
	}


	Cube :: Cube(double l) : Cuboid::Cuboid(l, l, l) {//先呼叫Cube所繼承的Cuboid-class的constructor: Cuboid來做事情
		//因為已經先呼叫Cuboid做事情了，所以就不用再做任何事情
	}
}