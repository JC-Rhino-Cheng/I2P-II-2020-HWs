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
		if (belong != NULL) belong->dead(species);//�p�G�o���ʪ��T�w�����ݪ��ʪ���A�ӥB�o���ʪ����F�A�N�n�w��o���ʪ��u���ݪ��v�ʪ���M�z������o���ʪ�����T
	};//�U��say: �ȥ����o��destructor�b�F��
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


class Caog : public Dog, public Cat{//�`�N�ACaog�O���class��inheritance
public:
	Caog(Zoo *zoo);         // TODO
	virtual void barking() { cout << "woof!woof!meow!\n"; }
	void carton() { cout << "it looks so happy!\n"; }
	void throwBall() { cout << "it looks happy!\n"; }
	~Caog();                // TODO
};