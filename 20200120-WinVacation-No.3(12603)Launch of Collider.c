#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable: 4996)
#define Max 200000
int pos_of_R_which_is_located_left_in_every_pair_of_RL[Max];

int main() {
	int n; scanf("%d", &n);

	char previous = '0', now = '0';
	int num_of_qualified_pairs = 0;
	for (int i = 0; i < n; i++) {
		scanf("%c", &now);
		if (isspace(now)) {
			i--;
			continue;
		}
		if (previous == 'R' && now == 'L')pos_of_R_which_is_located_left_in_every_pair_of_RL[num_of_qualified_pairs++] = i - 1;
		previous = now;
	}

	if (num_of_qualified_pairs == 0) { printf("-1\n"); system("pause"); return 0; }
	else {
		int *array_of_the_distance_between_RL = (int *)malloc(sizeof(int)*num_of_qualified_pairs);

		for (int i = 0, num_of_Rs_of_qualified_RLs_found = 0; num_of_Rs_of_qualified_RLs_found < num_of_qualified_pairs; i++) {
			int pos; scanf("%d", &pos);
			if (i == pos_of_R_which_is_located_left_in_every_pair_of_RL[num_of_Rs_of_qualified_RLs_found]) {
				i++;
				int pos_of_L_of_RL; scanf("%d", &pos_of_L_of_RL);
				array_of_the_distance_between_RL[num_of_Rs_of_qualified_RLs_found++] = pos_of_L_of_RL - pos;
			}
		}

		int min_distance = 200000000;
		for (int i = 0; i < num_of_qualified_pairs; i++) if (array_of_the_distance_between_RL[i] < min_distance)min_distance = array_of_the_distance_between_RL[i];
		printf("%d\n", min_distance / 2);
		//return 0;
		system("pause");
	}



}