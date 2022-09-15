#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable: 4996)

int check_is_leap(int year) {
	return (year % 400 == 0) ? 1 : (year % 4 == 0 && year % 100 != 0) ? 1 : 0;
}

int main() {
	int T; scanf("%d", &T);

	while (T--) {
		int original_year; scanf("%d", &original_year);
		int year = original_year;
		int flag_is_original_year_leap = check_is_leap(original_year);

		int count_displacement_of_days = 0;//�ڭn����original_year�M�{�b�ҭp�⪺�~������������@��(ex: 1/1or5/4)���P���X�t�Z�C�Ҧp: 2020�~��228�O§�����A��2021�~��228�O§����A�hcount_displacement_of_days=2�C
		int flag_goal_year_found = 0;

		while (!flag_goal_year_found) {
			count_displacement_of_days += (check_is_leap(++year)) ? (366 % 7) : (365 % 7);//�Y: "2:1"�A�i�H�ۤv����h�ݡA�u���N�t1��2�ѡC
			count_displacement_of_days %= 7;
			if (count_displacement_of_days == 0)
				if (check_is_leap(year) == flag_is_original_year_leap) flag_goal_year_found = 1;//�p�G��ӳ��O���~�A���NOK�i�H��X�C�Ϊ̨�ӳ��O�|�~�A���]�OOK�i�H��X�C���Y�O�@���@�|�A���N����A�����X�C
		}

		printf("%d\n", year);
	}

	system("pause");
}