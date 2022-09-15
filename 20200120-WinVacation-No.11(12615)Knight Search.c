#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable: 4996)
#define Max_side_length 100

void finding(int Now_At, int Now_Progress);

int N;//N�N����Ϊ����
char map[Max_side_length][Max_side_length];
char goal_string[] = "ICPCASIASG";// ���ؤ@���D�حn�D�n�ŦX���}�C
int flag_all_found = 0;// ��flag_all_found�Ӭ����O�_���ܤ֤@�ղŦX������

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)for (int j = 0; j < N; j++)scanf(" %c", &map[i][j]);//�`�N!!!" %c"(%c�e�����Ů�)�M"%c"(%c�e���L�Ů�)�������t��!!!

	int count = -1;
	
	while (!flag_all_found && count < N * N) {
		count++;
		if (map[count / N][count % N] == goal_string[0]) finding(count, 1);
	}

	flag_all_found ? puts("YES") : puts("NO");

	system("pause");
}


void finding(int Now_At, int Now_Progress) {// Now_At�O��e��m(�H�@�������G��)�CNow_Progress�O�i�סA�N��ڤw�g��ĴX�ӷQ�n���r�F�C
	if (Now_Progress == strlen(goal_string)) { flag_all_found = 1; return; }

	for (int i = -2; i <= 2 && !flag_all_found; i++)for (int j = -2; j <= 2 && !flag_all_found; j++) {// i�Ox�b���첾�q�Aj�Oy�b�������q�Cx�By��b�O�{���̪���V�A���O�ƾǲåd�৤�Шt����V
		if (i * i + j * j != 5 || Now_At / N + i < 0 || Now_At / N + i >= N || Now_At % N + j < 0 || Now_At % N + j >= N)continue;//�p�G�@�B�����פ�����(i * i + j * j != 5)�A�Ϊ̲��ʫ�|�W�X���(�᭱�|�ӱ���)�A�N����continue�C
		if (map[Now_At / N + i][Now_At % N + j] == goal_string[Now_Progress])finding(Now_At + i * N + j, Now_Progress + 1);//�b�T�w�ثe�����O�i�쪺�d�򤧤�����A�n�T�{��檺���e���O���O�k�X�ڷQ�n���C�p�G�k�X�A�N�i�J�s�����j���q�C
	}

	return;
}