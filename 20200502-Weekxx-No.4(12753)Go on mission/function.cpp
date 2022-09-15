#include <iostream>
#include "function.h"
#include <string.h>
#include <iomanip>//setw()�Msetfill()��library
#pragma warning (disable: 4996)

BigInt::BigInt() :sign(0)/*0����*/ {//main��line9�|�Ψ�
	for (int i = 0; i < N; i++) bigInt[i] = 0;

	//Constructor��return����F��
}


BigInt::BigInt(char *blood) :sign(0) {//istream& operator >> (istream&input, BigInt&to_be_assigned_obj) �|�Ψ�
	for (int i = 0; i < N; i++)bigInt[i] = 0;//�H���U�@�A��������l�Ƭ�0

	int length = strlen(blood);//�p���q���Ʀr����

	int num_of_digits_of_first_group = length % WIDTH;//�����Q����᪺�Ҧ��Ʋդ��A�̰���ƩҦb���Ʋժ�����
	int num_of_groups = (num_of_digits_of_first_group == 0) ? (length / WIDTH) : (length / WIDTH + 1);
	num_of_groups--;//���M�W���@��⪺�O���X��group�A���]���ڤ���ĥΪ��O0-based��index�A�ҥH���


	char temp[WIDTH + 5];
	if (num_of_digits_of_first_group) {//�̰���ƪ��Ʋժ����׭Y����0
		strncpy(temp, blood, num_of_digits_of_first_group); temp[num_of_digits_of_first_group] = '\0';
		bigInt[num_of_groups] = atoi(temp);
		//�H�W�w�g��̰���ƩҦb���ƲճB�z����

		//�}�l��Ѿl���Ʋն�J
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

	//�`�N�A�ڧ�̰���Ʀr�Ҧb���Ʋճ]�w���̤j�A�ӫD0�Cex: 12345�Awidth=2�A�hbigInt[0]=45�BbigInt[1]=23�Bbig[2]=1�C!!!!���Obig[0]=1�Bbig[1]=23�Bbig[2]=45�C!!!!
	//Constructor��return����F��
}


BigInt::BigInt(const BigInt&from) :sign(from.sign) {//copy constructor�A��code�|�b+��-��function�����Ψ�
	for (int i = 0; i < N; i++)bigInt[i] = from.bigInt[i];

	//Constructor��return����F��
}


BigInt &BigInt::operator = (const BigInt&from) {//�o�Oassignment operator�A�]�O�����ncopy���ʧ@�C�bmain��line11�|�Ψ�
	sign = from.sign;
	for (int i = 0; i < N; i++)bigInt[i] = from.bigInt[i];

	return *this;//enables cascaded calls
}


bool BigInt::operator < (BigInt from) {
	if (sign == 1 && from.sign == 0)//true�N��1�A�O�t�ƪ��N��Cfalse�N��0�A�O���ƪ��N��
		return true;
	else if (sign == 0 && from.sign == 1)
		return false;
	else {//�p�G��ӦP��
		if (sign == 1) {//�p�G���O�t��
			for (int i = N - 1; i >= 0; i--)
				if (bigInt[i] < from.bigInt[i])return false;
				else if (bigInt[i] > from.bigInt[i]) true;

			return false;//���᳣̫�@�ˡA�N���Ƭ۵�
		}
		else {//�p�G���O����
			for (int i = N - 1; i >= 0; i--)
				if (bigInt[i] < from.bigInt[i])return true;
				else if (bigInt[i] > from.bigInt[i]) return false;

			return false;
		}
	}
}


bool BigInt::operator > (BigInt from) {// a > b�A �۷�� -a < -b�A�ҥH�����ե�bool BigInt::operator < (BigInt from)�禡
	if (sign == 1 && from.sign == 0) return false;
	else if (sign == 0 && from.sign == 1) return true;
	else {//�p�G��ӦP��
		if (sign == 1) {//�p�G���O�t��
			for (int i = N - 1; i >= 0; i--)
				if (bigInt[i] < from.bigInt[i])return true;
				else if (bigInt[i] > from.bigInt[i]) return false;

			return false;//���᳣̫�@�ˡA�N���Ƭ۵�
		}
		else {//�p�G���O����
			for (int i = N - 1; i >= 0; i--)
				if (bigInt[i] < from.bigInt[i])return false;
				else if (bigInt[i] > from.bigInt[i]) return true;

			return false;
		}
	}
}


bool BigInt::operator == (BigInt from) {
	if (sign != from.sign)return false;//�����Q" -0 == +0 ��"��edge condition�A�]���b�[��k��function�̭��A�ڷ|��-0�@�߳]�w��+0�C
	else {//�p�G��ӦP��
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
	//���|�زզX: 
	//(1)����+���� (2)����+�t�� (3)�t��+���� (4)�t��+�t��
	//��(2)�M(3)��X�b�@�_�A�p�G�O(3)�N�մ���ӼƦr����m�A�ܦ�(2)�A
	//��(1)�M(4)��X�b�@�_�A�p�G�O(4)�A�N�μƾǧޥ�: ( -10 + -20 ) = - ( 10 + 20 )
	//�ҥH�`�@��ر��p

	if (sign == from.sign) {//�p�G�P��
		if (sign == 0) {//�p�G�O����+����
			int CO = 0;
			for (int i = 0; i < N; i++) {
				bigInt[i] += from.bigInt[i] + CO;
				CO = bigInt[i] / BASE;
				bigInt[i] %= BASE;
			}

			return *this;
		}
		else {//�p�G�O�t��+�t��
			//������ӼƦr������ȡA����եΤ@���o�Ө禡(�۷�󻼰j)�A������+���ƪ��B��C�����B��᪺���G�[�W�t���Y�i�C
			BigInt abs_this = *this; abs_this.sign = 0;
			BigInt abs_from = from; abs_from.sign = 0;

			*this = abs_this + abs_from; this->sign = 1;

			return *this;
		}
	}
	else {//�p�G����
		if (sign == 0) {//�p�G�O����+�t��
			//�n�P�_�[�X�Ӫ����G�O�����٬O�t�ơA�ҥH����t�ƨ�����ȨӧP�_�C
			BigInt absolute_from = from; absolute_from.sign = 0;

			if (*this < absolute_from) {//�p�G�O 123 + (-1234) �������A�令 -(1234 - 123)�ӹB��A�Y�A��Ʀr�ݫe��մ�
				BigInt temp = *this;
				*this = absolute_from;
				absolute_from = temp;

				int flag_have_jieweied = 0;
				for (int i = 0; i < N; i++) {
					if (flag_have_jieweied) {//�p�G�k�䪺�Ʋզ��ɦ�A�N����o�@��Ƶ����A����A�B��o�@��Ưu���n�⪺�F��
						bigInt[i]--;
						flag_have_jieweied = 0;
					}

					if (bigInt[i] < absolute_from.bigInt[i]) {//�p�G������A�N��ݭn�ɦ�
						flag_have_jieweied = 1;
						bigInt[i] = bigInt[i] + BASE - absolute_from.bigInt[i];
					}
					else  bigInt[i] = bigInt[i] - absolute_from.bigInt[i];
				}
				sign = 1;

				return *this;
			}
			else {//�p�G�O1234 + (-123)  �������A!!!!�Ϊ̹B��L�ᬰ�s!!!!�A�N�����B��
				int flag_have_jieweied = 0;
				for (int i = 0; i < N; i++) {
					if (flag_have_jieweied) {//�p�G�k�䪺�Ʋզ��ɦ�A�N����o�@��Ƶ����A����A�B��o�@��Ưu���n�⪺�F��
						bigInt[i]--;
						flag_have_jieweied = 0;
					}

					if (bigInt[i] < absolute_from.bigInt[i]) {//�p�G������A�N��ݭn�ɦ�
						flag_have_jieweied = 1;
						bigInt[i] = bigInt[i] + BASE - absolute_from.bigInt[i];
					}
					else bigInt[i] = bigInt[i] - absolute_from.bigInt[i];
				}
				sign = 0;

				return *this;
			}
		}
		else if (sign == 1) {//�p�G�O�t��+���ơA�N�令����+�t�ơC�ثe�A"this"�O�t�ơA��from�O����
			*this = from + *this;//�w�g�令����+�t��

			return *this;
		}
	}
}


BigInt BigInt::operator - (BigInt from) {
	//���|�زզX: 
	//(1)����-���� (2)����-�t�� (3)�t��-���� (4)�t��-�t��
	//���O�۷��
	//(1)����+�t�� (2)����+���� (3)�t��+�t�� (4)�t��+����
	//����: �@�ߧ�᭱���Ʀr�h�[�@�ӭt���A�Ӵ�k�ܦ��[�k

	from.sign = !from.sign;
	*this = *this + from;
	return *this;
}


istream& operator >> (istream&input, BigInt&to_be_assigned_obj) {//��l�ƤH������q��Ū���A�H�Τ���X���Ȯɪ��l�˦�q��Ū���A�@�Φ��禡
	char blood[to_be_assigned_obj.N * to_be_assigned_obj.WIDTH + 5]; cin >> blood;

	to_be_assigned_obj = BigInt(blood);

	return input;//enables cascaded calls
}


ostream& operator << (ostream&output, BigInt& to_be_printed) {
	if (to_be_printed.sign)cout << "-";//�u���t�Ƥ~�ݭn�L�Xsign

	int flag_sth_has_been_printed = 0;
	int flag_first_group_printed = 0;
	for (int i = to_be_printed.N - 1; i >= 0; i--) {
		if (to_be_printed.bigInt[i]) {//�p�G�o�ӼƦr���O0�A�@�ߦL�X
			if (flag_first_group_printed)cout << setw(8) << setfill('0') << to_be_printed.bigInt[i];//�p�G�w�g��Ĥ@�ӼƲզL�X�F�A�N�i�H��ߪ��⤤���Ʀr����8�Ӧr�����Ʋն뺡�K�ӼƦr
			else if (!flag_first_group_printed) {//�p�G�Ĥ@�ӼƲ��٨S�Q�L�X�ӡA�N�����0��Ĥ@�ӼƲն�
				cout << to_be_printed.bigInt[i];
				flag_first_group_printed = 1;
			}
			flag_sth_has_been_printed = 1;
		}
		else if (to_be_printed.bigInt[i] == 0 && flag_sth_has_been_printed)//�p�G�o�ӼƦr�O0�A���O�O���N�q��0�A�]�L�X�C�L�N�q�O��: ex: 000000000001���s�C
			cout << setw(8) << setfill('0') << to_be_printed.bigInt[i];
	}

	if (!flag_sth_has_been_printed)cout << "0";//�p�G�������O0�A�ܤ֭n�L�X�@�ӹs�A���ઽ���N����

	return output;
}


void solution(BigInt &tanjiro, BigInt &zenitsu, BigInt &inosuke, int n) {
	while (n--) {
		BigInt Compromised_blood;
		cin >> Compromised_blood;

		if (inosuke >= tanjiro && inosuke >= zenitsu)inosuke = inosuke - Compromised_blood;//����ϥ�a-=b���覡�A�u���a=a-b���覡�C�]���S��overload"-="�o��operator
		else if (tanjiro >= inosuke && tanjiro >= zenitsu)tanjiro = tanjiro - Compromised_blood;
		else if (zenitsu >= inosuke && zenitsu >= tanjiro)zenitsu = zenitsu - Compromised_blood;
	}
}