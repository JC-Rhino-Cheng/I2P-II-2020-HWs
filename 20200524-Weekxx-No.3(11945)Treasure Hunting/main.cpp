#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// G[i] is the neighbor towns of town i
vector<int> diamondTowns;
vector<int> G[100005];
int Dist[100005];

//struct其實就是一種Class，只不過Class預設為private，而struct全都是public。
struct node {
	int id;
	int dist;
	node(int id, int l) {//Constructor
		this->id = id;
		this->dist = l;
	}
};

int main() {
	int N, M, K; cin >> N >> M >> K;
	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	for (int i = 0; i < K; i++) {
		int x; cin >> x;
		diamondTowns.push_back(x);
	}
	fill(Dist, Dist + 100005, -1);//相當於memset(Dist, -1, sizeof(Dist));的感覺。

	queue<node> Q;

	// [TODO] complete the task!
	for (auto i : diamondTowns)//如果是範例測資，雖然是兩個town有鑽石，編號是2和7，但是這裡的i不會是「0、1」，也不是「1、2」，而是超精準的「2、7」，看來起來像是如果用了vector類型的東西，這個for的auto i 會直接取用容器內的數值進行處理，而不是像陣列一樣有連續的整數編號，我也不知道為什麼只知道很酷。
		Q.push(node(i, 0));//竟然還有這種東西!!!!在function call裡面直接調用Constructor來創建物件

	while (!Q.empty()) {
		node cur = Q.front(); Q.pop();//不能是node cur = &Q.front，因為在那之後這個東西會馬上被從Q裡面刪掉，因而調用destructor，自此之後這個物件就消失了

		if (Dist[cur.id] == -1) {
			Dist[cur.id] = cur.dist;
			
			for (auto j : G[cur.id])
				Q.push(node(j, cur.dist + 1));
		}
	}

	// Output
	for (int i = 1; i <= N; i++) {
		cout << Dist[i] << '\n';
	}
	
	system("pause");
}

/*
 7 10 2
1 2
1 4
1 5
2 3
2 5
3 4
3 7
4 5
4 6
5 6
2 7

 */