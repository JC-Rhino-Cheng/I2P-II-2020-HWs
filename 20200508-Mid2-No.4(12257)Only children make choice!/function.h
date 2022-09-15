#include <iostream>
#include <string>
#pragma warning (disable: 4996)
using namespace std;

class Zoo {
	public:
		int animalCount;

		Zoo() :animalCount(0) {}//default constructor
		void born(string name) {
			animalCount ++;
			cout << "New " << name << " Born!\n";
			cnt();
		}
		void dead(string name) {
			animalCount --;
			cout << "One " << name << " Dead!\n";
			cnt();
		}
		void cnt() { cout << "Now Zoo have " << (animalCount) << " animals!\n"; }
};


class Animal {
public:
	Zoo *belong;
	string species;
	Animal(Zoo *zoo, string name);
	virtual void barking() = 0;
	virtual void throwBall() = 0;
	virtual void carton() = 0;
	void printSpecies() { cout << species << endl; }
	virtual ~Animal() {
		if (belong != NULL) belong->dead(species);//如果這隻動物確定有所屬的動物園，而且這隻動物死了，就要針對這隻動物「所屬的」動物園清理掉關於這隻動物的資訊
	};//助教say: 務必懂這個destructor在幹嘛
};


class Dog : public virtual Animal {
public:
	Dog(Zoo *zoo); // TODO
	void barking() { cout << "woof!\n"; }
	void throwBall() { cout << "it looks happy!\n"; }
	virtual void carton() {};
	~Dog(); // TODO
};


class Cat : public virtual Animal{
public:
	Cat(Zoo *zoo); // TODO
	void barking() { cout << "meow!\n"; }
	void carton() { cout << "it looks so happy!\n"; }
	virtual void throwBall() {};
	~Cat(); // TODO
};


class Caog : public Dog, public Cat{//注意，Caog是兩個class的inheritance
public:
	Caog(Zoo *zoo);         // TODO
	virtual void barking() { cout << "woof!woof!meow!\n"; }
	void carton() { cout << "it looks so happy!\n"; }
	void throwBall() { cout << "it looks happy!\n"; }
	~Caog();                // TODO
};