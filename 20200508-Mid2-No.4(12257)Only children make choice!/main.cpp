#pragma warning (disable: 4996)
#include "function.h"
#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);

	Zoo z;
	int N;	cin >> N;

	Animal *arr[12];

	for (int i = 0; i < N; i++) {
		int aniTypes; cin >> aniTypes;
		if (aniTypes == 0) arr[i] = new Cat(&z);
		else if (aniTypes == 1) arr[i] = new Dog(&z);
		else if (aniTypes == 2) arr[i] = new Caog(&z);
  }

	Animal *Ref;
	int T; cin >> T;
	for (int i = 0; i < T; i++) {
		int idx, inst; cin >> idx >> inst;
		Ref = arr[idx];
		Ref->printSpecies();
		if (inst == 0) Ref->barking();
		else if (inst == 1) Ref->throwBall(); 
		else if (inst == 2) Ref->carton();
  }

	for (int i = 0; i < N; i++) delete arr[i];

	system("pause");
}