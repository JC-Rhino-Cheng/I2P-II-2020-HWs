#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable: 4996)
#define swap(a, b) (a^=b^=a^=b)

int main() {
	int N;//N代表Bob有N個朋友
	scanf("%d", &N); N++;//因為要後面要第一個讀入Bob的位置，所以N+1。

	int Max, min;
	scanf("%d%d", &Max, &min); N -= 2;
	if (Max < min) swap(Max, min);
	while (N--) {
		int temp; scanf("%d", &temp);

		if (temp > Max)Max = temp;
		else if (temp < min)min = temp;
	}

	printf("%d\n", 2 * (Max - min));

	system("pause");
}