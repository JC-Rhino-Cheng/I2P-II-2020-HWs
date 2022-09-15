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

		int count_displacement_of_days = 0;//我要紀錄original_year和現在所計算的年份之間的任何一天(ex: 1/1or5/4)的星期幾差距。例如: 2020年的228是禮拜五，而2021年的228是禮拜日，則count_displacement_of_days=2。
		int flag_goal_year_found = 0;

		while (!flag_goal_year_found) {
			count_displacement_of_days += (check_is_leap(++year)) ? (366 % 7) : (365 % 7);//即: "2:1"，可以自己找日曆去看，真的就差1或2天。
			count_displacement_of_days %= 7;
			if (count_displacement_of_days == 0)
				if (check_is_leap(year) == flag_is_original_year_leap) flag_goal_year_found = 1;//如果兩個都是平年，那就OK可以輸出。或者兩個都是閏年，那也是OK可以輸出。但若是一平一閏，那就不對，不能輸出。
		}

		printf("%d\n", year);
	}

	system("pause");
}