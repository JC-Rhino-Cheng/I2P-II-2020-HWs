#include <iostream>
#include <map>
#include <string>
using namespace  std;

map<string, string>mapping = {//記得不要從OJ上面複製，否則會弄到一堆人類真的真的真的看不到的隱藏字元，像是'\t'之類的。
	{"Wa","Waninoko"},
	{"Mi","Milotic"},
	{"Ma","Magikarp"},
	{"Va","Vaporeon"},
	{"Sh","Sharpedo"},
	{"Tapu","Tapu Fini"},
	{"Em","Empoleon"},
	{"La","Lapras"},
	{"Pi","Pikachu"},
	{"Pe","Pikachu"},
	{"Me","Mega Gyarados"}
};

int main() {
	int N; cin >> N;
	while (N--) {
		string name, school;
		cin >> name >> school;
		bool flag_printed = false;
		
		for (const auto &i : mapping) {
			if (name.substr(0, i.first.length()) == i.first) {
				cout << name << " the " << school << " " << i.second << endl;
				flag_printed = true;
				break;
			}
		}

		if (!flag_printed)cout << name << " is looking for a Chinese tutor, too!" << endl;
	}

	system("pause");
}