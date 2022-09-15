//�`�N�A��code���C�Ӱ}�C���W�٨��o���ܭ^��A���ӫܮe�������C�p�G�����A�Ь�main�̶}�l����l�ƪ��a��A�J����|�C
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#pragma warning (disable: 4996)
#define Max_string_length 5 //�]���榡�O: {move/pile/exit} {onto/over}�A�A�Ҽ{'\0'�A�N�O5�r���C
#define Max_num_of_books 25
#define Max_num_of_tables 25


int count_num_of_books_this_table_has[Max_num_of_tables];//½Ķ: ��??����l�`�@��F�o��h�ѡC
int Table[Max_num_of_tables][Max_num_of_books];//��??����l���ĴX���ѬO�s���h�֡C
int num_of_the_table_on_which_this_book_is[Max_num_of_books];//�o���Ѧb�ĴX����l�C


void return_books_to_their_original_table(int book_num);
void put_A_onto_B(int book_A_num, int book_B_num);
void put_a_bunch_of_books_onto_B(int book_A_num, int book_B_num);
void print(int n);


int main() {
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++)count_num_of_books_this_table_has[i] = 1;//�w�糧�}�C: int count_num_of_books_this_table_has[Max_num_of_tables];��l�ơC
	memset(Table, -1, sizeof(Table)); for (int i = 0; i < n; i++)Table[i][0] = i;//�w�糧�}�C: int Table[Max_num_of_tables][Max_num_of_books];����l�ơC
	for (int i = 0; i < n; i++) num_of_the_table_on_which_this_book_is[i] = i;

	char verb[Max_string_length], a[Max_string_length], adverb[Max_string_length], b[Max_string_length];
	while (scanf("%s %s %s %s", verb, a, adverb, b)) {
		if (strcmp(verb, "exit") == 0)break;

		int A = atoi(a), B = atoi(b);
		if (A == B)continue;//�p�G�ڥ��N�P���ѡA�N���ʧ@�C
		else if (num_of_the_table_on_which_this_book_is[A] == num_of_the_table_on_which_this_book_is[B])continue;//�p�G���M���P���ѡA���O�P��table�A�]���ʧ@�C

		if (strcmp(verb, "move") == 0) {
			if (strcmp(adverb, "onto") == 0) {
				return_books_to_their_original_table(A);
				return_books_to_their_original_table(B);

				put_A_onto_B(A, B);
			}
			else {//�ư���onto�A�N�ѤUover�F�C
				return_books_to_their_original_table(A);

				put_A_onto_B(A, B);
			}
		}
		else {//�ư���move�]�ư���exit�A�N�ѤUpile�F�C
			if (strcmp(adverb, "onto") == 0) {
				return_books_to_their_original_table(B);

				put_a_bunch_of_books_onto_B(A, B);
			}
			else {//�ư���onto�A�N�ѤUover�F�C
				put_a_bunch_of_books_onto_B(A, B);
			}
		}
	}

	print(n);

	system("pause");
}


void return_books_to_their_original_table(int book_num) {
	//�o���ѩҦb����l�s�� num_of_the_table_on_which_this_book_is[book_num]
	//��li�`�@���X���� count_num_of_books_this_table_has[i]
	//�s��i����l����j���Ѫ��s�� Table[i][j]
	int original_table = num_of_the_table_on_which_this_book_is[book_num];

	int book_index_on_original_table;
	for (int i = 0; i < count_num_of_books_this_table_has[original_table]; i++)
		if (Table[original_table][i] == book_num) { book_index_on_original_table = i; break; }

	int i = book_index_on_original_table + 1;
	int goal_table = Table[original_table][i];
	for (; Table[original_table][i] != -1; i++) {
		//����s�o���Ѫ��s��m���T����T(�T����T�Y�T�Ӱ}�C�����e)
		Table[goal_table][count_num_of_books_this_table_has[goal_table]++] = goal_table;
		num_of_the_table_on_which_this_book_is[Table[original_table][i]] = goal_table;

		//�A��s�o���Ѫ��¦�m���T����T(�����u�ݭn��ʨ�ˡA�]���u�o���ѩҦb����l�s���v�w�g�b�W����L�F)
		Table[original_table][i] = -1;
		count_num_of_books_this_table_has[original_table]--;
	}

	return;
}



void put_A_onto_B(int book_A_num, int book_B_num) {
	//�o���ѩҦb����l�s�� num_of_the_table_on_which_this_book_is[book_num]
	//��li�`�@���X���� count_num_of_books_this_table_has[i]
	//�s��i����l����j���Ѫ��s�� Table[i][j]

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
	book_B_index_on_original_table++;//�]���OB��index���W���@�Ӥ~�}�l�i�H��A�ҥH�n+1

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



/*
�U�Ц^�ЫH��:

�٦P�ǧA�n��

���������@�U�A�����Ѽg�o�ܸԲӡA�o�O�@�ӫD�`�n���ߺD�I
���H�R�W�ӻ����ܡA����ԲӪ��R�W�u���|�e���y���@�ǰ��D���
�L�׸ԲӪ��R�W�|�ϱo�Y���ܼƫܮe���Q�d�V�A�]���R�W���\�h��r�O���ƪ��A�^�P�ݤU�h�ӱ���F�A�N�e���g���A�ƫ�]���e���ˬd�A���L���]�|�v�T�\Ū���Ĳv
��ĳ�p�G�� count_num_of_books_this_table_has�Bnum_of_the_table_on_which_this_book_is �o�˪��ܼơA�i��]��H booksAmount�BbookTableMap �������覡�A���L�b���N�q���P�ɤS�e���Ϥ��@�I��

���U�ӬO������~������

1. Line 87 ���ӬO count_num_of_books_this_table_has �ӫD num_of_the_table_on_which_this_book_is

2. pile A over B �o�ӫ��O�|����|�� A ��� B ���|�W���A�]�N�O?�� B ���W�����ѮɡAA �|��b�o�ǮѤ��W�A�]���Y���n�ϥ� put_a_bunch_of_books_onto_B �o�� function�A�i��o�Q�Q�ݰѼƯu���ٯઽ���� A B �ܡH

3. �b�A�� return_books_to_their_original_table �禡���A�A�� goalTable �g�b�ĤG�Ӱj��H�~�A�����F�L�ײ{�b�ݨ�����Y�N�k�٪��ѡA�A���|�N���k�٨�Ĥ@���Ѫ���l��m�W�A�o�ˬO���X�z���A��ĳ�� goalTable ���ȯ���H�۰j�黼�Q�ӧ�s

�ھڴ��աA�b���H�W�X�I��A���ӴN�බ�QAC�o

Best regards,
TAs

*/