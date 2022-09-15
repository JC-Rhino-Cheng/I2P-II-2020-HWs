#pragma warning (disable: 4996)
#include <limits.h>
#include <string>//C++的標準string在這
#include <cstring>//to_string這個把value轉為string的超好用函式在這//!!!記得是: "std::to_string"!!!
#include "function.h"

Engineer::Engineer() {

	//不return任何東西
}


Engineer::~Engineer() {

	//不return任何東西
}


void Engineer::init() {
	count = 0;
}


void Engineer::MakeQuery(char* query_str) {
	static int l, r;
	if (count == 0) { l = INT_MIN; r = INT_MAX; }//因為可能玩完一局終極密碼，可以玩下一局，所以很可能很多局。所以每一局的第一次猜測都要手動初始化，因為如果不做的話，會被前一行的static擋住，就不正確
	else {
		if (answer_history[0])l = ((l + r) >> 1) + 1;//因為我的問題是「a>b嗎?」，所以如果a確實大於b的話，那麼可能密碼的數字範圍(「閉」區間)就不包含b，所以要記得加一
		else r = (l + r) >> 1;
		//不能把">>1"替換為"/2"，因為ex: 
		//-5 / 2 ，會變成-2，
		//而-5 >> 1，會變成-3
	}

	count++;

	std::string temp;
	if (l != r) temp = "greater " + std::to_string((l + r) >> 1);//記得greater後面要跟空格
	else temp = "guess " + std::to_string(l);

	strcpy(query_str, temp.c_str());//c_str()可以把C++的string，換成C的char型式。如果是stringstream這種class的話，是使用str();而且是轉換成string-class的object，而不是轉換成char。

	return;
}


void Engineer::GetAnswer(bool ans) {
	answer_history[0] = ans;
	return;
}


