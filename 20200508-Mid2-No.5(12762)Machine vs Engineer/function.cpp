#pragma warning (disable: 4996)
#include <limits.h>
#include <string>//C++���з�string�b�o
#include <cstring>//to_string�o�ӧ�value�ରstring���W�n�Ψ禡�b�o//!!!�O�o�O: "std::to_string"!!!
#include "function.h"

Engineer::Engineer() {

	//��return����F��
}


Engineer::~Engineer() {

	//��return����F��
}


void Engineer::init() {
	count = 0;
}


void Engineer::MakeQuery(char* query_str) {
	static int l, r;
	if (count == 0) { l = INT_MIN; r = INT_MAX; }//�]���i�઱���@���׷��K�X�A�i�H���U�@���A�ҥH�ܥi��ܦh���C�ҥH�C�@�����Ĥ@���q�����n��ʪ�l�ơA�]���p�G�������ܡA�|�Q�e�@�檺static�צ�A�N�����T
	else {
		if (answer_history[0])l = ((l + r) >> 1) + 1;//�]���ڪ����D�O�ua>b��?�v�A�ҥH�p�Ga�T��j��b���ܡA����i��K�X���Ʀr�d��(�u���v�϶�)�N���]�tb�A�ҥH�n�O�o�[�@
		else r = (l + r) >> 1;
		//�����">>1"������"/2"�A�]��ex: 
		//-5 / 2 �A�|�ܦ�-2�A
		//��-5 >> 1�A�|�ܦ�-3
	}

	count++;

	std::string temp;
	if (l != r) temp = "greater " + std::to_string((l + r) >> 1);//�O�ogreater�᭱�n��Ů�
	else temp = "guess " + std::to_string(l);

	strcpy(query_str, temp.c_str());//c_str()�i�H��C++��string�A����C��char�����C�p�G�Ostringstream�o��class���ܡA�O�ϥ�str();�ӥB�O�ഫ��string-class��object�A�Ӥ��O�ഫ��char�C

	return;
}


void Engineer::GetAnswer(bool ans) {
	answer_history[0] = ans;
	return;
}


