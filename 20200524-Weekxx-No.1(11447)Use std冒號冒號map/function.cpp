#include "function.h"
#include <iostream>
#include <set>

void oj::insert(std::map<int, oj::String> &ma, int key, const std::string &str) {
	auto goal = ma.find(key);
	std::string temp;

	if (goal != ma.end()) {//�p�G�T��o��key���Q���A�Y�p�G�o��key�T�꦳�b��map�̭�
		temp = str + goal->second.str;//�]��find��return�O��iterator�A�ҥH��"->"�Ӥ���"."�C
		ma.erase(goal);//erase����iterator�@���Ѽ�
	}
	else temp = str;
	//�H�Wif-else�O�b�B�z�s���r��A�s��temp�C�p�G�o��key���w�s�b�A�S���Y�A�ڴN�O�t�зs���A�åB���ª���էR���A�ϥ�����A���շs����ƶ�^map�Y�i

	ma.insert(std::pair<int, oj::String>(key, temp));
}


void oj::output(const std::map<int, oj::String> &ma, int begin, int end) {
	for(const auto &i :ma) {//�`�N!!�p�G���g&i�Ӽgi�A�L�O!!!�|!!!��bma�ҧ�쪺�ثe�ҳB�z���@�ո�ƶi��copy��!!!!
		if (i.first > end)break;

		if (i.first >= begin) std::cout << i.second.str << ' ';
	}
}


void oj::erase(std::map<int, oj::String> &ma, int begin, int end) {
	std::set<int> key_of_to_be_erased_data;
	for (const auto &i : ma) {
		if (i.first > end)break;

		if (i.first >= begin)key_of_to_be_erased_data.insert(i.first);
	}

	for (const auto key : key_of_to_be_erased_data) {
		ma.erase(key);//map�������F��A�n�R�����ɭԥu�ݶǤJkey�A�Ӥ��ݶǤJ�ukey-value�v�o��ո��
	}
}


std::ostream& oj::operator<<(std::ostream &output, const std::map<int, oj::String> &ref_map) {
	for (auto &i : ref_map) {
		output << i.second.str << ' ';
	}

	return output;

}

/*
insert 14 vY
range output 20 30
range output -30 -24
insert -14 Wt
range output 14 21
range erase 4 12
range output -19 -8
range output 25 30
insert 7 Dv
insert -13 Dm
range output -12 26
insert -28 if
range output 26 28
range output -28 21
range erase -11 29
range erase -21 7
insert -24 Yd
range erase -24 -15

 */

/*
 �ڭ쥻�O�o�˼g
 void oj::erase(std::map<int, oj::String> &ma, int begin, int end) {
	for (auto &i : ma) {
		if (i.first > end)break;

		if (i.first >= begin) ma.erase(i.first);//map�o��container�b�i��R�����ɭԡA�����Okey�A�Ӥ��O��ո�ơA�ҥH�u��ǤJfirst
	}
}
���O�]���p�G�brange-based��for-loop�̭��p�G��o�Ӯe���i��W�R���ܡAfor-loop�b�U�@���d��iterator���ɭԷ|�X���A
�ҥH�u��̷ӧU�Ъ��g�k�A���h�u�@���ʦa�v��Ҧ����ӧR�����@��ո�ƪ�key���x�s��set�̭��A
����A�b�ufor-loop�~���v�̾�set�̭������e�@���ʦa��ӧR�����F��R���C
 */