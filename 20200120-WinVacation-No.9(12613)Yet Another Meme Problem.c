#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning (disable: 4996)

int main() {
	int t; scanf("%d", &t);

	while (t--) {
		int A, B; scanf("%d%d", &A, &B);
		printf("%.0f\n", A * floor(log10(B + 1)));
	}
	system("pause");
}
// By tunajaw