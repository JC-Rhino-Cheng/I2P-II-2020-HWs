#include <iostream>
#include "function.h"
#include <string.h>
#include <iomanip>//setw()和setfill()的library
#pragma warning (disable: 4996)

BigInt::BigInt() :sign(0)/*0表正數*/ {//main的line9會用到
	for (int i = 0; i < N; i++) bigInt[i] = 0;

	//Constructor不return任何東西
}


BigInt::BigInt(char *blood) :sign(0) {//istream& operator >> (istream&input, BigInt&to_be_assigned_obj) 會用到
	for (int i = 0; i < N; i++)bigInt[i] = 0;//以防萬一，全部先初始化為0

	int length = strlen(blood);//計算血量的數字長度

	int num_of_digits_of_first_group = length % WIDTH;//紀錄被分拆後的所有數組中，最高位數所在的數組的長度
	int num_of_groups = (num_of_digits_of_first_group == 0) ? (length / WIDTH) : (length / WIDTH + 1);
	num_of_groups--;//雖然上面一行算的是有幾個group，但因為我之後採用的是0-based的index，所以減減


	char temp[WIDTH + 5];
	if (num_of_digits_of_first_group) {//最高位數的數組的長度若不為0
		strncpy(temp, blood, num_of_digits_of_first_group); temp[num_of_digits_of_first_group] = '\0';
		bigInt[num_of_groups] = atoi(temp);
		//以上已經把最高位數所在的數組處理完畢

		//開始把剩餘的數組填入
		for (int i = num_of_groups - 1, pos_of_num = num_of_digits_of_first_group; i >= 0; i--, pos_of_num += WIDTH) {
			strncpy(temp, blood + pos_of_num, WIDTH); temp[WIDTH] = '\0';
			bigInt[i] = atoi(temp);
		}
	}
	else {
		for (int i = num_of_groups, pos_of_num = 0; i >= 0; i--, pos_of_num += WIDTH) {
			strncpy(temp, blood + pos_of_num, WIDTH); temp[WIDTH] = '\0';
			bigInt[i] = atoi(temp);
		}
	}

	//注意，我把最高位數字所在的數組設定為最大，而非0。ex: 12345，width=2，則bigInt[0]=45、bigInt[1]=23、big[2]=1。!!!!不是big[0]=1、big[1]=23、big[2]=45。!!!!
	//Constructor不return任何東西
}


BigInt::BigInt(const BigInt&from) :sign(from.sign) {//copy constructor，此code會在+或-的function內部用到
	for (int i = 0; i < N; i++)bigInt[i] = from.bigInt[i];

	//Constructor不return任何東西
}


BigInt &BigInt::operator = (const BigInt&from) {//這是assignment operator，也是類似要copy的動作。在main的line11會用到
	sign = from.sign;
	for (int i = 0; i < N; i++)bigInt[i] = from.bigInt[i];

	return *this;//enables cascaded calls
}


bool BigInt::operator < (BigInt from) {
	if (sign == 1 && from.sign == 0)//true代表1，是負數的意思。false代表0，是正數的意思
		return true;
	else if (sign == 0 && from.sign == 1)
		return false;
	else {//如果兩個同號
		if (sign == 1) {//如果都是負號
			for (int i = N - 1; i >= 0; i--)
				if (bigInt[i] < from.bigInt[i])return false;
				else if (bigInt[i] > from.bigInt[i]) true;

			return false;//比到最後都一樣，代表兩數相等
		}
		else {//如果都是正號
			for (int i = N - 1; i >= 0; i--)
				if (bigInt[i] < from.bigInt[i])return true;
				else if (bigInt[i] > from.bigInt[i]) return false;

			return false;
		}
	}
}


bool BigInt::operator > (BigInt from) {// a > b， 相當於 -a < -b，所以直接調用bool BigInt::operator < (BigInt from)函式
	if (sign == 1 && from.sign == 0) return false;
	else if (sign == 0 && from.sign == 1) return true;
	else {//如果兩個同號
		if (sign == 1) {//如果都是負號
			for (int i = N - 1; i >= 0; i--)
				if (bigInt[i] < from.bigInt[i])return true;
				else if (bigInt[i] > from.bigInt[i]) return false;

			return false;//比到最後都一樣，代表兩數相等
		}
		else {//如果都是正號
			for (int i = N - 1; i >= 0; i--)
				if (bigInt[i] < from.bigInt[i])return false;
				else if (bigInt[i] > from.bigInt[i]) return true;

			return false;
		}
	}
}


bool BigInt::operator == (BigInt from) {
	if (sign != from.sign)return false;//不必想" -0 == +0 嗎"的edge condition，因為在加減法的function裡面，我會把-0一律設定為+0。
	else {//如果兩個同號
		for (int i = N - 1; i >= 0; i--)
			if (bigInt[i] != from.bigInt[i])return false;

		return true;
	}
}


bool BigInt::operator >= (BigInt from) {
	return (*this > from) || (*this == from);
}


bool BigInt::operator <= (BigInt from) {
	return (*this < from) || (*this == from);
}


BigInt BigInt::operator + (BigInt from) {
	//有四種組合: 
	//(1)正數+正數 (2)正數+負數 (3)負數+正數 (4)負數+負數
	//把(2)和(3)整合在一起，如果是(3)就調換兩個數字的位置，變成(2)，
	//把(1)和(4)整合在一起，如果是(4)，就用數學技巧: ( -10 + -20 ) = - ( 10 + 20 )
	//所以總共兩種情況

	if (sign == from.sign) {//如果同號
		if (sign == 0) {//如果是正數+正數
			int CO = 0;
			for (int i = 0; i < N; i++) {
				bigInt[i] += from.bigInt[i] + CO;
				CO = bigInt[i] / BASE;
				bigInt[i] %= BASE;
			}

			return *this;
		}
		else {//如果是負數+負數
			//先取兩個數字的絕對值，之後調用一次這個函式(相當於遞迴)，做正數+正數的運算。之後把運算後的結果加上負號即可。
			BigInt abs_this = *this; abs_this.sign = 0;
			BigInt abs_from = from; abs_from.sign = 0;

			*this = abs_this + abs_from; this->sign = 1;

			return *this;
		}
	}
	else {//如果異號
		if (sign == 0) {//如果是正數+負數
			//要判斷加出來的結果是正數還是負數，所以先把負數取絕對值來判斷。
			BigInt absolute_from = from; absolute_from.sign = 0;

			if (*this < absolute_from) {//如果是 123 + (-1234) 的類型，改成 -(1234 - 123)來運算，即，兩數字需前後調換
				BigInt temp = *this;
				*this = absolute_from;
				absolute_from = temp;

				int flag_have_jieweied = 0;
				for (int i = 0; i < N; i++) {
					if (flag_have_jieweied) {//如果右邊的數組有借位，就先把這一位數給減減，之後再運算這一位數真正要算的東西
						bigInt[i]--;
						flag_have_jieweied = 0;
					}

					if (bigInt[i] < absolute_from.bigInt[i]) {//如果不夠減，代表需要借位
						flag_have_jieweied = 1;
						bigInt[i] = bigInt[i] + BASE - absolute_from.bigInt[i];
					}
					else  bigInt[i] = bigInt[i] - absolute_from.bigInt[i];
				}
				sign = 1;

				return *this;
			}
			else {//如果是1234 + (-123)  的類型，!!!!或者運算過後為零!!!!，就直接運算
				int flag_have_jieweied = 0;
				for (int i = 0; i < N; i++) {
					if (flag_have_jieweied) {//如果右邊的數組有借位，就先把這一位數給減減，之後再運算這一位數真正要算的東西
						bigInt[i]--;
						flag_have_jieweied = 0;
					}

					if (bigInt[i] < absolute_from.bigInt[i]) {//如果不夠減，代表需要借位
						flag_have_jieweied = 1;
						bigInt[i] = bigInt[i] + BASE - absolute_from.bigInt[i];
					}
					else bigInt[i] = bigInt[i] - absolute_from.bigInt[i];
				}
				sign = 0;

				return *this;
			}
		}
		else if (sign == 1) {//如果是負數+正數，就改成正數+負數。目前，"this"是負數，而from是正數
			*this = from + *this;//已經改成正數+負數

			return *this;
		}
	}
}


BigInt BigInt::operator - (BigInt from) {
	//有四種組合: 
	//(1)正數-正數 (2)正數-負數 (3)負數-正數 (4)負數-負數
	//分別相當於
	//(1)正數+負數 (2)正數+正數 (3)負數+負數 (4)負數+正數
	//結論: 一律把後面的數字多加一個負號，而減法變成加法

	from.sign = !from.sign;
	*this = *this + from;
	return *this;
}


istream& operator >> (istream&input, BigInt&to_be_assigned_obj) {//初始化人物的血量的讀取，以及之後出任務時的損傷血量的讀取，共用此函式
	char blood[to_be_assigned_obj.N * to_be_assigned_obj.WIDTH + 5]; cin >> blood;

	to_be_assigned_obj = BigInt(blood);

	return input;//enables cascaded calls
}


ostream& operator << (ostream&output, BigInt& to_be_printed) {
	if (to_be_printed.sign)cout << "-";//只有負數才需要印出sign

	int flag_sth_has_been_printed = 0;
	int flag_first_group_printed = 0;
	for (int i = to_be_printed.N - 1; i >= 0; i--) {
		if (to_be_printed.bigInt[i]) {//如果這個數字不是0，一律印出
			if (flag_first_group_printed)cout << setw(8) << setfill('0') << to_be_printed.bigInt[i];//如果已經把第一個數組印出了，就可以放心的把中間數字不滿8個字元的數組塞滿八個數字
			else if (!flag_first_group_printed) {//如果第一個數組還沒被印出來，就不能用0把第一個數組填滿
				cout << to_be_printed.bigInt[i];
				flag_first_group_printed = 1;
			}
			flag_sth_has_been_printed = 1;
		}
		else if (to_be_printed.bigInt[i] == 0 && flag_sth_has_been_printed)//如果這個數字是0，但是是有意義的0，也印出。無意義是指: ex: 000000000001的零。
			cout << setw(8) << setfill('0') << to_be_printed.bigInt[i];
	}

	if (!flag_sth_has_been_printed)cout << "0";//如果全部都是0，至少要印出一個零，不能直接就換行

	return output;
}


void solution(BigInt &tanjiro, BigInt &zenitsu, BigInt &inosuke, int n) {
	while (n--) {
		BigInt Compromised_blood;
		cin >> Compromised_blood;

		if (inosuke >= tanjiro && inosuke >= zenitsu)inosuke = inosuke - Compromised_blood;//不能使用a-=b的方式，只能用a=a-b的方式。因為沒有overload"-="這種operator
		else if (tanjiro >= inosuke && tanjiro >= zenitsu)tanjiro = tanjiro - Compromised_blood;
		else if (zenitsu >= inosuke && zenitsu >= tanjiro)zenitsu = zenitsu - Compromised_blood;
	}
}