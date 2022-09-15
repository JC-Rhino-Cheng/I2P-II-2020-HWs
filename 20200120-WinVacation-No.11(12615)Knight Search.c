#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable: 4996)
#define Max_side_length 100

void finding(int Now_At, int Now_Progress);

int N;//N代表正方形的邊長
char map[Max_side_length][Max_side_length];
char goal_string[] = "ICPCASIASG";// 先建一個題目要求要符合的陣列
int flag_all_found = 0;// 用flag_all_found來紀錄是否有至少一組符合的答案

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)for (int j = 0; j < N; j++)scanf(" %c", &map[i][j]);//注意!!!" %c"(%c前面有空格)和"%c"(%c前面無空格)之間的差異!!!

	int count = -1;
	
	while (!flag_all_found && count < N * N) {
		count++;
		if (map[count / N][count % N] == goal_string[0]) finding(count, 1);
	}

	flag_all_found ? puts("YES") : puts("NO");

	system("pause");
}


void finding(int Now_At, int Now_Progress) {// Now_At是當前位置(以一維紀錄二維)。Now_Progress是進度，代表我已經到第幾個想要的字了。
	if (Now_Progress == strlen(goal_string)) { flag_all_found = 1; return; }

	for (int i = -2; i <= 2 && !flag_all_found; i++)for (int j = -2; j <= 2 && !flag_all_found; j++) {// i是x軸的位移量，j是y軸的偏移量。x、y兩軸是程式裡的方向，不是數學笛卡兒坐標系的方向
		if (i * i + j * j != 5 || Now_At / N + i < 0 || Now_At / N + i >= N || Now_At % N + j < 0 || Now_At % N + j >= N)continue;//如果一步的長度不等於五(i * i + j * j != 5)，或者移動後會超出邊界(後面四個條件)，就直接continue。
		if (map[Now_At / N + i][Now_At % N + j] == goal_string[Now_Progress])finding(Now_At + i * N + j, Now_Progress + 1);//在確定目前的方格是可到的範圍之內之後，要確認方格的內容物是不是吻合我想要的。如果吻合，就進入新的遞迴階段。
	}

	return;
}