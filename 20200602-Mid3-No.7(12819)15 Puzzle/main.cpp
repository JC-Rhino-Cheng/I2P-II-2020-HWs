#include <iostream>
#include <cmath>
#include <queue>
using namespace std;
#define side_len 4//邊長為4的正方形

const int goal_Row[] = { -1,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3};//因為我是直接用表格內的數字去做對照，而表格內的數字是1-based，所以就用1-based。
const int goal_Col[] = { -1,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2};

const int dx[] = {1, -1, 0, 0};//0號、1號、2號、3號分別是(1, 0)、(-1, 0)、(0, 1)、(0, -1)，這個排列有其意義，就是取flip的counter沒錯!在之後的XOR會用到。0號<-->1號互換、2號<-->3號互換。
const int dy[] = {0, 0, 1, -1};

class State {
public:
	int puzzle[side_len][side_len];
	int heuristic;//儲存這個state的heuristic。交給同是State-class的member function去計算和設定。
	int total_steps;//累計步數
	int prev_direction;//紀錄上一次的方向，避免回到同個State。只有0、1、2、3共四種可能。
	int empty_x, empty_y;//紀錄empty tile所在位置

	State(int input[side_len][side_len]) : total_steps(0), prev_direction(-1) {//Constructor，在讀入map之後使用
		for (int i = 0; i < side_len; i++)for (int j = 0; j < side_len; j++) {
			puzzle[i][j] = input[i][j];
			//順便處理empty_x、empty_x
			if (puzzle[i][j] == 0) {
				empty_x = i; empty_y = j;
			}
		}

		setHeuristic();//已經處理好heuristic
		
	}

	State(const State&from) :heuristic(from.heuristic), total_steps(from.total_steps), prev_direction(from.prev_direction), empty_x(from.empty_x), empty_y(from.empty_y) {//Copy Constructor
		for (int i = 0; i < side_len; i++)for (int j = 0; j < side_len; j++)
			puzzle[i][j] = from.puzzle[i][j];
	}

	void setHeuristic() {
		int h = 0;
		for (int i = 0; i < side_len; i++)for (int j = 0; j < side_len; j++) {
			if (puzzle[i][j]) {//先確保這格不是空的
				//開始計算曼哈頓距離
				int goal_X = goal_Row[puzzle[i][j]];
				int goal_Y = goal_Col[puzzle[i][j]];
				h += abs(goal_X - i) + abs(goal_Y - j);

				//計算這格的linear conflict。
				if (i == goal_X) {//只有這格已經到了目標row才需要動作
					for (int k = j + 1; k < side_len; k++) {//橫向掃過每一個格子
						if (puzzle[i][k] && goal_X == goal_Row[puzzle[i][k]] && puzzle[i][j] > puzzle[i][k]) {//先確定這格不是空的，再確定這格的目標row和我的是否一致，之後再確定這格真的有擋到我嗎(他是在我右邊而且比我小嗎)?
							h += 2;
						}
					}
				}
				if (j == goal_Y) {//只有這格已經到了目標row才需要動作
					for (int k = i + 1; k < side_len; k++) {//橫向掃過每一個格子
						if (puzzle[k][j] && goal_Y == goal_Col[puzzle[k][j]] && puzzle[i][j] > puzzle[k][j]) h += 2;
					}
				}
			}
		}

		heuristic = h;
	}

	void mustUpdate(const int new_dir = -1,const int new_empty_x = -1,const int new_empty_y = -1) {
		prev_direction = new_dir;
		swap(puzzle[new_empty_x][new_empty_y], puzzle[empty_x][empty_y]);
		empty_x = new_empty_x;
		empty_y = new_empty_y;
		total_steps++;

		setHeuristic();
	}


	//記得給Priority Queue比排序priority的的標準
	bool operator<(const State &rhs) const {//記得一定要加const，否則compile error，已經是第二次犯錯誤了
		return total_steps + heuristic > rhs.total_steps + rhs.heuristic;
	}
};


int main() {
	int map[side_len][side_len];
	//可用新版摩登版的for，成為: for (auto& i : map)for (int& j : i)cin >> j;
	for (int i = 0; i < side_len; i++)for (int j = 0; j < side_len; j++)cin >> map[i][j];

	const State s(map);

	priority_queue<State>PQ; PQ.push(s);

	//開始進行BFS
	while (!PQ.empty()) {
		const auto temp = PQ.top();//不能用&，因為之後會pop()掉。
		if (temp.heuristic == 0)break;//已經找到目標了

		PQ.pop();

		//開始把四周的tile排入BFS的Priority Queue裡面
		for (int new_dir = 0; new_dir < side_len; new_dir++) {
			if ((new_dir ^ 1) == temp.prev_direction)continue;//避免掉那種「空123」->「1空23」->「空123」迴還往復的無窮迴圈//!!!記得^的優先度比==低。

			int new_empty_x = temp.empty_x + dx[new_dir];//計算empty tile的新位置
			int new_empty_y = temp.empty_y + dy[new_dir];
			if (new_empty_x < 0 || new_empty_y < 0 || new_empty_x >= side_len || new_empty_y >= side_len)continue;//檢查是否超過邊界

			State new_state = temp;//先複製一份
			new_state.mustUpdate(new_dir, new_empty_x, new_empty_y);//針對new_state該修改的部分就修改
			PQ.push(new_state);
		}
		
	}

	if (PQ.empty())cout << -1 << endl;
	else cout << PQ.top().total_steps << endl;
	
	system("pause");
}