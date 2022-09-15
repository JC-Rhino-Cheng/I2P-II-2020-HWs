#include "function.h"
#include <stdlib.h>
#pragma warning (disable: 4996)


Graph::Graph(int n) {
	numberOfVertices = n;
	adjacencyList = (Vertex **) malloc ( sizeof(Vertex *) * n );//�����new�A�]��new�O�Ыءu��@�@�ӡvVertex�åB�^�ǥ���pointer�A�o�˨ä��ŦX�ڪ��ݨD�C�ڻݭn���O�u�x�sVertex*�v ���}�C
	vertexInfo = (int *) malloc ( sizeof(int) * n );// VertexInfo�N��: �u��Vertex�v���ʧO�A1�N��k�A0�N��k�A-1�N��|���[���

	for (int i = 0; i < n; i++) {
		adjacencyList[i] = new Vertex(i);//adjacencyList[0]�N���O�H0�������C���ⶤ����Vertex���Ыئn�A���ᶤ�������pô����H���ִN�i�H��Vertex-class�̭���nextptr�h��_�ӡC
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

bool Graph::dfs(int vertex) { return 1; }//�@�ӨS�Ϊ��F��

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
���:
�إߤ@������global�������}�C�A�x�s���O�C�ӽs�����H�쩳�O�k�O�k?1�N��k�A0�N��k�A-1�N��|���[���
����A�ڥu�n�إߤ@�i�a�ϡA�C�ӤH����C�ӤH�����pô����H���ƱƯ����n�A�q�s��0���Ҧ������pô���H�}�l�ᤩ���T���ʧO�C�p�G�o�Ӧ��N���ʧO�A�N�ˬd���O�_���T�A�p�G�����T�A�N����return false
ex�D�ش���:
0 1
1 2
2 3
1 3
0 3�A

����ڪ��a�ϴN�O:
�s��:  0�B1�B2�B3
����:  1�B0�B1�B2
           3�B2�B3�B1
		     �B3�B   �B0
���pô�C
(PS�a�ϭn�����ݡA�Y: 0���M1�B3�����pô�C1���M0�B2�B3�����pô�Cetc)
�ڥ��ᤩ�s��0�O�k�C
�M�s��0�����pô���O�s��1�M3�C
�ˬd�ݬݽs��1���ʧO?�p�G�٨S�[���A�N�]�w���M�s��0���P�C�ҥH�b�o�̴N��s��1�]���k�C
�A���ˬd�s��3���ʧO?�p�G�٨S�[���A�N�]�w���M�s��0���P�C�ҥH�b�o�̴N��s��3�]���k�C

���U�Ӵ��s��1�������C
�ˬd�ݬݽs��1���ʧO?�p�G�٨S�[���A�N�]�w���k�C
.......
*/