#pragma warning (disable: 4996)
#include "function.h"

Animal::Animal(Zoo *zoo, string name) {
	zoo->born(name);
	belong = zoo;
	species = name;

	//不return任何東西
}


Dog::Dog(Zoo *zoo):Animal(zoo, "Dog") {
	//不return任何東西
}


Dog::~Dog() {
	//不return任何東西
}


Cat::Cat(Zoo *zoo) :Animal(zoo, "Cat") {
	//不return任何東西
}


Cat::~Cat() {
	//不return任何東西
}


Caog::Caog(Zoo *zoo) :Animal(zoo, "Caog"), Dog(zoo), Cat(zoo) {
	//不return任何東西
}


Caog::~Caog() {
	//不return任何東西
}