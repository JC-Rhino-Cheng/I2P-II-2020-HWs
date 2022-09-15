#include <stdio.h>
#include <stdlib.h>
#include "function.h"
#pragma warning (disable: 4996)

int main() {
    int n, m;

	while (scanf("%d%d", &n, &m) != EOF) {
        head = createList(n);
        printf("%d\n", solveJosephus(m));
        freeList();
    }
	system("pause");
}

