#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable: 4996)
#define swap(a, b) (a^=b^=a^=b)

int main() {
	int N;//N�N��Bob��N�ӪB��
	scanf("%d", &N); N++;//�]���n�᭱�n�Ĥ@��Ū�JBob����m�A�ҥHN+1�C

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