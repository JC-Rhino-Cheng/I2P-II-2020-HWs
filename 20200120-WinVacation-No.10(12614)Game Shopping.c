#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable: 4996)
#define Max_num 1000

int main() {
	int n, m; scanf("%d%d", &n, &m);
	int c[Max_num], a[Max_num];
	for (int i = 0; i < n; i++)scanf("%d", &c[i]);
	for (int i = 0; i < m; i++)scanf("%d", &a[i]);

	int count_how_many_he_can_buy = 0;
	int now_at_merchandise_index = 0, now_at_bill_index = 0;
	while (now_at_merchandise_index < n&&now_at_bill_index < m) {
		if (c[now_at_merchandise_index] <= a[now_at_bill_index]) {
			count_how_many_he_can_buy++;
			now_at_bill_index++;
			now_at_merchandise_index++;
		}
		else now_at_merchandise_index++;
	}

	printf("%d\n", count_how_many_he_can_buy);
	system("pause");
}