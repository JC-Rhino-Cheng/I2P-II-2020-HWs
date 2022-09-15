#include "function.h"
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

void RleCodec::encode() {
	encoded = true;

	int count = 0;
	string coded;
	char before = '-';
	for(auto &c : code_str) {
		if(c!=before) {
			if (before != '-') {
				if (count == 1 || count == 2) 
					coded.insert(coded.end(), count, before);//string-class物件可以支援在某處一次性地新增數個同樣的char。
					//上面一行相當於coded.push_back(before);
				else {
					string cnt(to_string(count));//先把count轉換成一串string，因為string-class的insert的上方用法不接受一個string物件
					coded = coded + cnt;//也可寫成: coded += cnt;或者coded.append(cnt);
					//上面兩行其實可以整合，寫成: coded.insert(coded.length(), to_string(count));
					coded.insert(coded.end(), 1, before);
				}
			}
			
			count = 1;
			before = c;
		}
		else count++;
	}
	if (count == 1 || count == 2)
		coded.insert(coded.end(), count, before);//string-class物件可以支援在某處一次性地新增數個同樣的char。
	else {
		coded.insert(coded.length(), to_string(count));
		coded.insert(coded.end(), 1, before);
	}

	code_str = coded;
	return;
}


void RleCodec::decode() {
	encoded = false;

	string num_str;//如果code_str是3A7DBB5GC4125252E的話，就依次紀錄3、7、5、4125252。
	string decoded;
	for (const auto &tmp : code_str) {
		if (isdigit(tmp)) {
			num_str.insert(num_str.end(), 1, tmp);
			continue;
		}
		else {
			//用stringstream來把string取成整數果然還是比較方便
			stringstream num_str_temp(num_str);
			int num = 0; num_str_temp >> num;
			
			if (num == 0)decoded.push_back(tmp);
			else decoded.insert(decoded.length(), num, tmp);
			
			num_str.clear();
		}
	}

	code_str = decoded;
}


std::ostream& operator<<(std::ostream& os, Codec& data) {//Operator Overloading。一般來講就是寫: os(我一般習慣這個parameter叫做output)<< data.???。而這裡只不過是外包給外部的函式運作而已
	data.show(os);
	return os;
}


void encode_decode(Codec & data) {//如果現在是encoded，就decode。如果現在是decoded狀態，就encode。
	if (!data.is_encoded()) data.encode();
	else data.decode();
}