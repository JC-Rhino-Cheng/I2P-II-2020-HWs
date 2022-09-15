//注意，本code的每個陣列的名稱取得都很英文，應該很容易看懂。如果不懂，請看main最開始的初始化的地方，仔細體會。
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#pragma warning (disable: 4996)
#define Max_string_length 5 //因為格式是: {move/pile/exit} {onto/over}，再考慮'\0'，就是5字元。
#define Max_num_of_books 25
#define Max_num_of_tables 25


int count_num_of_books_this_table_has[Max_num_of_tables];//翻譯: 第??號桌子總共放了這麼多書。
int Table[Max_num_of_tables][Max_num_of_books];//第??號桌子的第幾本書是編號多少。
int num_of_the_table_on_which_this_book_is[Max_num_of_books];//這本書在第幾號桌子。


void return_books_to_their_original_table(int book_num);
void put_A_onto_B(int book_A_num, int book_B_num);
void put_a_bunch_of_books_onto_B(int book_A_num, int book_B_num);
void print(int n);


int main() {
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++)count_num_of_books_this_table_has[i] = 1;//針對本陣列: int count_num_of_books_this_table_has[Max_num_of_tables];初始化。
	memset(Table, -1, sizeof(Table)); for (int i = 0; i < n; i++)Table[i][0] = i;//針對本陣列: int Table[Max_num_of_tables][Max_num_of_books];做初始化。
	for (int i = 0; i < n; i++) num_of_the_table_on_which_this_book_is[i] = i;

	char verb[Max_string_length], a[Max_string_length], adverb[Max_string_length], b[Max_string_length];
	while (scanf("%s %s %s %s", verb, a, adverb, b)) {
		if (strcmp(verb, "exit") == 0)break;

		int A = atoi(a), B = atoi(b);
		if (A == B)continue;//如果根本就同本書，就不動作。
		else if (num_of_the_table_on_which_this_book_is[A] == num_of_the_table_on_which_this_book_is[B])continue;//如果雖然不同本書，但是同個table，也不動作。

		if (strcmp(verb, "move") == 0) {
			if (strcmp(adverb, "onto") == 0) {
				return_books_to_their_original_table(A);
				return_books_to_their_original_table(B);

				put_A_onto_B(A, B);
			}
			else {//排除掉onto，就剩下over了。
				return_books_to_their_original_table(A);

				put_A_onto_B(A, B);
			}
		}
		else {//排除掉move也排除掉exit，就剩下pile了。
			if (strcmp(adverb, "onto") == 0) {
				return_books_to_their_original_table(B);

				put_a_bunch_of_books_onto_B(A, B);
			}
			else {//排除掉onto，就剩下over了。
				put_a_bunch_of_books_onto_B(A, Table[num_of_the_table_on_which_this_book_is[B]][count_num_of_books_this_table_has[num_of_the_table_on_which_this_book_is[B]] - 1]);
			}
		}
	}

	print(n);

	//system("pause");
}


void return_books_to_their_original_table(int book_num) {
	//這本書所在的桌子編號 num_of_the_table_on_which_this_book_is[book_num]
	//桌子i總共有幾本書 count_num_of_books_this_table_has[i]
	//編號i的桌子的第j本書的編號 Table[i][j]
	int original_table = num_of_the_table_on_which_this_book_is[book_num];

	int book_index_on_original_table;
	for (int i = 0; i < count_num_of_books_this_table_has[original_table]; i++)
		if (Table[original_table][i] == book_num) { book_index_on_original_table = i; break; }

	int i = book_index_on_original_table + 1;
	for (; Table[original_table][i] != -1; i++) {
		int goal_table = Table[original_table][i];
		//先更新這本書的新位置的三項資訊(三項資訊即三個陣列的內容)
		Table[goal_table][count_num_of_books_this_table_has[goal_table]++] = goal_table;
		num_of_the_table_on_which_this_book_is[Table[original_table][i]] = goal_table;

		//再更新這本書的舊位置的三項資訊(但其實只需要改動兩樣，因為「這本書所在的桌子編號」已經在上面改過了)
		Table[original_table][i] = -1;
		count_num_of_books_this_table_has[original_table]--;
	}

	return;
}



void put_A_onto_B(int book_A_num, int book_B_num) {
	//這本書所在的桌子編號 num_of_the_table_on_which_this_book_is[book_num]
	//桌子i總共有幾本書 count_num_of_books_this_table_has[i]
	//編號i的桌子的第j本書的編號 Table[i][j]

	int original_table = num_of_the_table_on_which_this_book_is[book_A_num], goal_table = num_of_the_table_on_which_this_book_is[book_B_num];

	int book_A_index_on_original_table;
	for (int i = 0; i < count_num_of_books_this_table_has[original_table]; i++)
		if (Table[original_table][i] == book_A_num) { book_A_index_on_original_table = i; break; }

	Table[goal_table][count_num_of_books_this_table_has[goal_table]++] = book_A_num;
	num_of_the_table_on_which_this_book_is[book_A_num] = goal_table;

	Table[original_table][book_A_index_on_original_table] = -1;
	count_num_of_books_this_table_has[original_table]--;

	return;
}


void put_a_bunch_of_books_onto_B(int book_A_num, int book_B_num) {
	int Table_of_A = num_of_the_table_on_which_this_book_is[book_A_num];
	int Table_of_B = num_of_the_table_on_which_this_book_is[book_B_num];

	int book_A_index_on_original_table, book_B_index_on_original_table;
	for (int i = 0; i < count_num_of_books_this_table_has[Table_of_A]; i++)
		if (Table[Table_of_A][i] == book_A_num) { book_A_index_on_original_table = i; break; }
	for (int i = 0; i < count_num_of_books_this_table_has[Table_of_B]; i++)
		if (Table[Table_of_B][i] == book_B_num) { book_B_index_on_original_table = i; break; }
	book_B_index_on_original_table++;//因為是B的index的上面一個才開始可以填，所以要+1

	while (Table[Table_of_A][book_A_index_on_original_table] != -1) {
		num_of_the_table_on_which_this_book_is[Table[Table_of_A][book_A_index_on_original_table]] = num_of_the_table_on_which_this_book_is[book_B_num];
		Table[Table_of_B][book_B_index_on_original_table] = Table[Table_of_A][book_A_index_on_original_table];
		Table[Table_of_A][book_A_index_on_original_table] = -1;
		count_num_of_books_this_table_has[Table_of_A]--;
		count_num_of_books_this_table_has[Table_of_B]++;

		book_A_index_on_original_table++;
		book_B_index_on_original_table++;
	}

	return;
}




void print(int n) {
	for (int i = 0; i < n; i++) {
		printf("%d:", i);

		for (int j = 0; j < count_num_of_books_this_table_has[i]; j++) {
			printf(" %d", Table[i][j]);
		}
		puts("");
	}

	return;
}