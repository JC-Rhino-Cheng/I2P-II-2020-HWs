#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable: 4996)
#define length 10001

void Shift(char *, int, int);

int main() {
	char s[length]; scanf("%s", s);

	int num_of_queries; scanf("%d", &num_of_queries);

	while (num_of_queries--) {
		int left_index, right_index, times;//記得，left和right的編號都是1-based。
		scanf("%d%d%d", &left_index, &right_index, &times);

		Shift(s + left_index - 1, right_index - left_index + 1, times);
	}

	printf("%s\n", s);

	system("pause");
}



void Shift(char *s, int partial_length, int times) {
	char *temp = (char*)malloc(sizeof(char)*partial_length);

	times %= partial_length;

	strncpy(temp, s + partial_length - times, times);
	strncpy(temp + times, s, partial_length - times);
	strncpy(s, temp, partial_length);

	free(temp);
	return;
}