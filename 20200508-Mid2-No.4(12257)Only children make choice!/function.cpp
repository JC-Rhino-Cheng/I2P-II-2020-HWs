#pragma warning (disable: 4996)
#include "function.h"

Animal::Animal(Zoo *zoo, string name) {
	zoo->born(name);
	belong = zoo;
	species = name;

	//��return����F��
}


Dog::Dog(Zoo *zoo):Animal(zoo, "Dog") {
	//��return����F��
}


Dog::~Dog() {
	//��return����F��
}


Cat::Cat(Zoo *zoo) :Animal(zoo, "Cat") {
	//��return����F��
}


Cat::~Cat() {
	//��return����F��
}


Caog::Caog(Zoo *zoo) :Animal(zoo, "Caog"), Dog(zoo), Cat(zoo) {
	//��return����F��
}


Caog::~Caog() {
	//��return����F��
}