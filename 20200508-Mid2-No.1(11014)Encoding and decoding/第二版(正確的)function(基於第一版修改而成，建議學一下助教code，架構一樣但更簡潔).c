#pragma warning (disable: 4996)
#include <string>
#include "function.h"
#include <sstream>
#define Max_length (int)1e5

std::ostream& operator<<(std::ostream& os, Codec& data) {//Operator Overloading。一般來講就是寫: os(我一般習慣這個parameter叫做output)<< data.???。而這裡只不過是外包給外部的函式運作而已
	data.show(os);
	return os;
}

void encode_decode(Codec & data) {//如果現在是encoded，就decode。如果現在是decoded狀態，就encode。
	if (!data.is_encoded()) data.encode();
	else data.decode();
}

void RleCodec::encode() {
	encoded = true;//先把狀態的flag改好

	int strlen = code_str.length();
	
	std::stringstream encoded_str;

	int count_num_of_diff_char = 0;
	char former_char = '0';
	for (int i = 0; i < strlen; i++) {
		if (code_str[i] != former_char) {
			if (i) {//只有在不為開頭位置的時候，才要針對這個已知長度的連續相同字元做處理
				if (count_num_of_diff_char == 1)
					encoded_str << former_char;
				else if (count_num_of_diff_char == 2) {
					encoded_str << former_char;
					encoded_str << former_char;
				}
				else {
					//如果是100個A，要儲存為100A，如果是1234567890個A，要儲存1234567890A，所以首先計算數字是幾位數，順便把每一位數的數字提取出來
					int num_of_digits = 0; int num_of_every_digit[Max_length];
					for (int temp = count_num_of_diff_char; temp; temp /= 10)//如果是3A，3/10=0，就結束運算了。如果是1234A，則1234/10=123，123/10=12，12/10=1，1/10=0。由此兩例可知，除到等於零，之後看除幾次，就是幾位數
						num_of_every_digit[num_of_digits++] = temp % 10;
					
					for (int i = 0; i < num_of_digits; i++)
						encoded_str << (char)(num_of_every_digit[num_of_digits - 1 - i] + '0');
					encoded_str << former_char;
				}
			}
			
			//以下兩行，更新資料為新的應該處理的連續相同字元
			count_num_of_diff_char = 1;
			former_char = code_str[i];
		}
		else count_num_of_diff_char++;
	}
	if (count_num_of_diff_char == 1)
		encoded_str << former_char;
	else if (count_num_of_diff_char == 2) {
		encoded_str << former_char;
		encoded_str << former_char;
	}
	else {
		//如果是100個A，要儲存為100A，如果是1234567890個A，要儲存1234567890A，所以首先計算數字是幾位數，順便把每一位數的數字提取出來
		int num_of_digits = 0; int num_of_every_digit[Max_length];
		for (int temp = count_num_of_diff_char; temp; temp /= 10)//如果是3A，3/10=0，就結束運算了。如果是1234A，則1234/10=123，123/10=12，12/10=1，1/10=0。由此兩例可知，除到等於零，之後看除幾次，就是幾位數
			num_of_every_digit[num_of_digits++] = temp % 10;

		for (int i = 0; i < num_of_digits; i++)
			encoded_str << (char)(num_of_every_digit[num_of_digits - 1 - i] + '0');
		encoded_str << former_char;
	}

	code_str = encoded_str.str();//把我弄的新字串全部assign給目前所要的string。

	return;
}

void RleCodec::decode() {
	encoded = false;//先把狀態的flag改好
	std::stringstream decoded_str;
	
	int old_string_len = code_str.length();
	for (int i = 0; i < old_string_len; i++) {
		if (!isdigit(code_str[i])) 	decoded_str << code_str[i];
		else {
			int num = 0;
			for (; isdigit(code_str[i]); i++)
				num *= 10; num += code_str[i] - '0';
			for (int j = 0; j < num; j++)
				decoded_str << code_str[i];
		}
	}

	code_str = decoded_str.str();
}