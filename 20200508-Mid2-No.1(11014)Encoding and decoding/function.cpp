#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include "function.h"
#pragma warning (disable: 4996)

void RleCodec::encode() {
	int cnt = 0;
	char prev = '\0';
	std::stringstream ss;
	for (auto c : code_str) {
		if (c != prev) {
			if (cnt) {
				if (cnt == 1) ss << prev;
				else if (cnt == 2) ss << prev << prev;
				else ss << cnt << prev;
			}
			prev = c;
			cnt = 1;
		}
		else  cnt++;
	}
	if (cnt) {
		if (cnt == 1) ss << prev;
		else if (cnt == 2) ss << prev << prev;
		else ss << cnt << prev;
	}
	code_str = ss.str();
	encoded = true;
}

void RleCodec::decode() {
	std::stringstream os;
	std::string int_str;
	for (auto c : code_str) {
		if (std::isdigit(c)) int_str.push_back(c);
		else {
			int cnt = 0;
			std::stringstream is{ int_str };
			is >> cnt;
			if (cnt == 0) os << c;
			else for (int i = 0; i < cnt; ++i) os << c;
			int_str.clear();
		}
	}

	code_str = os.str();
	encoded = false;
}


std::ostream& operator<<(std::ostream& os, Codec& data) {//Operator Overloading。一般來講就是寫: os(我一般習慣這個parameter叫做output)<< data.???。而這裡只不過是外包給外部的函式運作而已
	data.show(os);
	return os;
}


void encode_decode(Codec & data) {//如果現在是encoded，就decode。如果現在是decoded狀態，就encode。
	if (!data.is_encoded()) data.encode();
	else data.decode();
}