#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#pragma warning (disable: 4996)
#define num_of_alphabets 26

int main() {
	int n, m;//n代表總長度n，m代表總共會有m次操作。
	scanf("%d%d", &n, &m);

	int *pos_of_letter[num_of_alphabets];
	int count_num_of_letter[num_of_alphabets]; memset(count_num_of_letter, 0, sizeof(count_num_of_letter));
	for (int i = 0; i < num_of_alphabets; i++) {
		pos_of_letter[i] = (int*)malloc(sizeof(int)*n);
	}

	for (int i = 0; i < n; i++) {
		char c;
		while (isspace(c = getchar()))continue;

		pos_of_letter[c - 'a'][count_num_of_letter[c - 'a']++] = i;
	}

	while (m--) {
		char x, y;
		while (isspace(x = getchar()))continue;
		while (isspace(y = getchar()))continue;
		int exchanger1 = x - 'a';
		int exchanger2 = y - 'a';

		if (exchanger1 == exchanger2)continue;
		else {
			int *temp_address_for_exchanging_two_arrays;
			temp_address_for_exchanging_two_arrays = pos_of_letter[exchanger1];
			pos_of_letter[exchanger1] = pos_of_letter[exchanger2];
			pos_of_letter[exchanger2] = temp_address_for_exchanging_two_arrays;


			int temp_for_count_num_of_letter;
			temp_for_count_num_of_letter = count_num_of_letter[exchanger1];
			count_num_of_letter[exchanger1] = count_num_of_letter[exchanger2];
			count_num_of_letter[exchanger2] = temp_for_count_num_of_letter;
		}
	}

	char *output = (char *)malloc(sizeof(char)*(n + 3));
	for (int i = 0; i < num_of_alphabets; i++)
		for (int j = 0; j < count_num_of_letter[i]; j++) output[pos_of_letter[i][j]] = i + 'a';
	output[n] = '\0';

	printf("%s\n", output);

	free(output);
	for (int i = 0; i < num_of_alphabets; i++) free(pos_of_letter[i]);

	system("pause");
}