#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <algorithm>//find函式會用到
using namespace std;

int main() {
	int n; cin >> n;

	list<int>Country_line;//國家的排隊列表，ex: 美國->非洲->日本。
	queue<int>Country_idx_[3];//各個國家內部人民的排隊列表。[0]美國、[1]非洲、[2]日本。ex: Country_idx_[2]表示的是日本內部的日人1->日人2->日人3->日人4->......。

	while (n--) {
		string cmd; cin >> cmd;

		if (cmd == "ENQUEUE") {
			int idx; cin >> idx;

			Country_idx_[idx % 3].push(idx);//把這個人排進他們自己國家的隊伍裡面

			//再來處理處理國家排隊順序
			//只有在這個國家沒有在排隊隊伍裡面的時候，才要加入隊伍
			//因為要用這個find函式，所以不得不把Country_line設為list。queue不能用。QQ
			if (find(Country_line.cbegin(), Country_line.cend(), idx % 3) == Country_line.cend())Country_line.push_back(idx % 3);
		}
		else if (cmd == "DEQUEUE") {
			if (Country_line.cend() == Country_line.cbegin())continue;//預防完全沒人排隊的情況下，機掰測資照樣DEQUEUE。

			int idx_of_country = Country_line.front();
			int idx_of_person_in_that_country = Country_idx_[idx_of_country].front();
			Country_idx_[idx_of_country].pop();//queue的pop竟然是pop出最先進入Q的人，好酷ㄛ。stack好像則是last-in first-out。
			if (Country_idx_[idx_of_country].empty())Country_line.pop_front();

			cout << idx_of_person_in_that_country << endl;
		}
	}

	system("pause");
}