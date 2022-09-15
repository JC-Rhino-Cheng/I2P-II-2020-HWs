#include <iostream>
#include <queue>
#include <string.h>
using namespace  std;
#define bound_Max_level 15+1//1-based。
#define bound_My_Max_HP 300+1
#define  bound_Enemy_Max_HP 400+1

class Level {
public:
	int DMG, HL;//這個level的damge和heal。
};

class State {
public:
	int level, my_HP, enemy_HP, depth;
	State(int lv, int my_HP, int enemy_HP, int depth = 0) : level(lv), my_HP(my_HP), enemy_HP(enemy_HP), depth(depth) {};
};

bool flag_visited[bound_Max_level][bound_My_Max_HP][bound_Enemy_Max_HP];//放function裡面會stack overflow。


int main() {
	int Max_level, My_Max_HP, Enemy_Max_HP, Enemy_attack;
	cin >> Max_level >> My_Max_HP >> Enemy_Max_HP >> Enemy_attack;
	//Max_level上限: 15。My_Max_HP: 300。Enemy_Max_P: 400。
	
	memset(flag_visited, false, sizeof(flag_visited));

	Level level[bound_Max_level];

	for (int i = 1; i <= Max_level; i++)cin >> level[i].DMG >> level[i].HL;
	//以上全部初始化完畢

	//以下進行Queue(BFS)運算
	queue<State>Q;
	Q.push(State(1, My_Max_HP, Enemy_Max_HP));

	while (!Q.empty()) {
		const auto &cur_state = Q.front();
		if (cur_state.enemy_HP <= 0)break;
		Q.pop();

		//三個情況(Level up、Attack、Heal)各自判斷是否需要進入Q。
		//情況1: Level up。
		if (cur_state.level + 1 <= Max_level && cur_state.my_HP > Enemy_attack) {//如果我level+1之後不會爆表，而且level_up之後必吃的那頓揍吃完之後確定可以存活，才弄進Q。
			const State new_state(cur_state.level + 1, cur_state.my_HP - Enemy_attack, cur_state.enemy_HP, cur_state.depth + 1);

			if (!flag_visited[new_state.level][new_state.my_HP][new_state.enemy_HP]) {
				flag_visited[new_state.level][new_state.my_HP][new_state.enemy_HP] = true;
				Q.push(new_state);
			}
		}

		//情況2: Attack。
		if (level[cur_state.level].DMG >= cur_state.enemy_HP || cur_state.my_HP > Enemy_attack) {//如果我一打，敵人就爆掉的話，那就打。如果敵人不會爆掉的話，那我至少要確保我吃揍之後不會死。
			//const State new_state(cur_state.level, (level[cur_state.level].DMG >= cur_state.enemy_HP) ? cur_state.my_HP : cur_state.my_HP - Enemy_attack, cur_state.enemy_HP - level[cur_state.level].DMG, cur_state.depth + 1);
			//上面那個的enemy_HP可能為負，會造成flag_visited[..][..][負數]，導致出錯。
			const State new_state(cur_state.level, (level[cur_state.level].DMG >= cur_state.enemy_HP) ? cur_state.my_HP : cur_state.my_HP - Enemy_attack, max(0, cur_state.enemy_HP - level[cur_state.level].DMG), cur_state.depth + 1);
			
			if (!flag_visited[new_state.level][new_state.my_HP][new_state.enemy_HP]) {
				flag_visited[new_state.level][new_state.my_HP][new_state.enemy_HP] = true;
				Q.push(new_state);
			}
		}

		//情況3: Heal。
		if (My_Max_HP > Enemy_attack && level[cur_state.level].HL > Enemy_attack) {//如果我滿血也照樣會被敵人打敗的話，就不要浪費時間做無謂的掙扎。 如果我HL的血量小於或等於敵人的攻擊，那Heal就沒什麼用，甚至是在浪費時間。這時應該是趕快殺敵或者level up。
			const State new_state(cur_state.level, min(cur_state.my_HP + level[cur_state.level].HL, My_Max_HP) - Enemy_attack, cur_state.enemy_HP, cur_state.depth + 1);

			if (!flag_visited[new_state.level][new_state.my_HP][new_state.enemy_HP]) {
				flag_visited[new_state.level][new_state.my_HP][new_state.enemy_HP] = true;
				Q.push(new_state);
			}
		}
	}

	if (Q.empty()) cout << "-1" << endl;
	else cout << Q.front().depth << endl;

	system("pause");
}