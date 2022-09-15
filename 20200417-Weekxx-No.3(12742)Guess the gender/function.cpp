#include "function.h"
#include <stdlib.h>
#pragma warning (disable: 4996)


Graph::Graph(int n) {
	numberOfVertices = n;
	adjacencyList = (Vertex **) malloc ( sizeof(Vertex *) * n );//不能用new，因為new是創建「單一一個」Vertex並且回傳它的pointer，這樣並不符合我的需求。我需要的是「儲存Vertex*」 的陣列
	vertexInfo = (int *) malloc ( sizeof(int) * n );// VertexInfo代表: 「此Vertex」的性別，1代表男，0代表女，-1代表尚未觀察到

	for (int i = 0; i < n; i++) {
		adjacencyList[i] = new Vertex(i);//adjacencyList[0]代表的是以0為隊長。先把隊長的Vertex先創建好，之後隊長有所聯繫的對象有誰就可以用Vertex-class裡面的nextptr去串起來。
		vertexInfo[i] = -1;
	}

	//Constructor returns not anything
}


Graph::~Graph() {
	int n = numberOfVertices;
	for (int i = 0; i < n; i++) {
		Vertex* now = adjacencyList[i];
		while (now != nullptr)  {
			Vertex *next = now->nextVertex;
			delete now;
			now = next;
		}
	}

	//Destructor returns not anything
}


void Graph::addEdge(int source, int destination) {
	Vertex *member = new Vertex(destination);

	member->nextVertex = adjacencyList[source]->nextVertex;
	adjacencyList[source]->nextVertex = member;

	return;
}

bool Graph::dfs(int vertex) { return 1; }//一個沒用的東西

bool Graph::solver() {
	bool is_Correct = true;

	for (int i = 0; i < numberOfVertices && is_Correct; i++) {
		Vertex *leader = adjacencyList[i];
		Vertex *temp = adjacencyList[i]->nextVertex;

		if (vertexInfo[leader->index] == -1) vertexInfo[leader->index] = 1;

		while (temp != nullptr) {
			if (vertexInfo[temp->index] == -1) {
				vertexInfo[temp->index] = !vertexInfo[leader->index];

				temp = temp->nextVertex;
				continue;
			}
			else if (vertexInfo[temp->index] != vertexInfo[leader->index]) {
				temp = temp->nextVertex;
				continue;
			}
			else {
				is_Correct = false;
				break;
			}
		}

	}

	return is_Correct;
}












/*
思路:
建立一個類似global概念的陣列，儲存的是每個編號的人到底是男是女?1代表男，0代表女，-1代表尚未觀察到
那麼，我只要建立一張地圖，每個人都把每個人有所聯繫的對象都排排站站好，從編號0的所有有所聯繫的人開始賦予正確的性別。如果這個早就有性別，就檢查它是否正確，如果不正確，就直接return false
ex題目測資:
0 1
1 2
2 3
1 3
0 3，

那麼我的地圖就是:
編號:  0、1、2、3
有跟:  1、0、1、2
           3、2、3、1
		     、3、   、0
有聯繫。
(PS地圖要直的看，即: 0號和1、3都有聯繫。1號和0、2、3都有聯繫。etc)
我先賦予編號0是男。
和編號0有所聯繫的是編號1和3。
檢查看看編號1的性別?如果還沒觀察到，就設定為和編號0不同。所以在這裡就把編號1設為女。
再來檢查編號3的性別?如果還沒觀察到，就設定為和編號0不同。所以在這裡就把編號3設為女。

接下來換編號1的部分。
檢查看看編號1的性別?如果還沒觀察到，就設定為男。
.......
*/