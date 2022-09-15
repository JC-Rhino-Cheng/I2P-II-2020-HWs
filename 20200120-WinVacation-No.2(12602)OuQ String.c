#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable: 4996)

int k;
unsigned long long l, r, tmp, len[53];

void rec(int k) {
	if (tmp + len[k] <= l) {    //優化時間複雜度
		tmp += len[k];
		return;
	}
	else if (tmp <= r) {    //如果tmp>r，直接return
		if (tmp >= l && tmp <= r) printf("O");
		tmp++;
		if (k != 1 && tmp <= r) rec(k - 1);
		if (tmp >= l && tmp <= r) printf("u");
		tmp++;
		if (k != 1 && tmp <= r) rec(k - 1);
		if (tmp >= l && tmp <= r) printf("Q");
		tmp++;
	}//tmp在範圍內就print，k不等於1以及tmp在範圍內就遞迴
	else return;
}

//反正長度都固定，用陣列記下來可以省時間(dp)
long long lenk(int k) {
	if (k == 1) return len[1] = 3;
	return len[k] = 3 + 2 * lenk(k - 1);
}

int main() {
	lenk(50);

	while (~scanf("%d %llu %llu", &k, &l, &r)) {
		tmp = 0;
		rec(k);
		printf("\n");
	}

	system("pause");
}