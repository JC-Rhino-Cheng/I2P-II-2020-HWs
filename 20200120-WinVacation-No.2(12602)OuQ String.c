#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable: 4996)

int k;
unsigned long long l, r, tmp, len[53];

void rec(int k) {
	if (tmp + len[k] <= l) {    //�u�Ʈɶ�������
		tmp += len[k];
		return;
	}
	else if (tmp <= r) {    //�p�Gtmp>r�A����return
		if (tmp >= l && tmp <= r) printf("O");
		tmp++;
		if (k != 1 && tmp <= r) rec(k - 1);
		if (tmp >= l && tmp <= r) printf("u");
		tmp++;
		if (k != 1 && tmp <= r) rec(k - 1);
		if (tmp >= l && tmp <= r) printf("Q");
		tmp++;
	}//tmp�b�d�򤺴Nprint�Ak������1�H��tmp�b�d�򤺴N���j
	else return;
}

//�ϥ����׳��T�w�A�ΰ}�C�O�U�ӥi�H�ٮɶ�(dp)
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