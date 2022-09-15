#include "function.h"
#include <iostream>
#include <set>

void oj::insert(std::map<int, oj::String> &ma, int key, const std::string &str) {
	auto goal = ma.find(key);
	std::string temp;

	if (goal != ma.end()) {//如果確實這個key有被找到，即如果這個key確實有在此map裡面
		temp = str + goal->second.str;//因為find的return是個iterator，所以用"->"而不用"."。
		ma.erase(goal);//erase接收iterator作為參數
	}
	else temp = str;
	//以上if-else是在處理新的字串，叫做temp。如果這個key早已存在，沒關係，我就是另創新的，並且把舊的整組刪掉，反正之後再把整組新的資料塞回map即可

	ma.insert(std::pair<int, oj::String>(key, temp));
}


void oj::output(const std::map<int, oj::String> &ma, int begin, int end) {
	for(const auto &i :ma) {//注意!!如果不寫&i而寫i，他是!!!會!!!把在ma所找到的目前所處理的一組資料進行copy的!!!!
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
		ma.erase(key);//map類型的東西，要刪除的時候只需傳入key，而不需傳入「key-value」這整組資料
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
 我原本是這樣寫
 void oj::erase(std::map<int, oj::String> &ma, int begin, int end) {
	for (auto &i : ma) {
		if (i.first > end)break;

		if (i.first >= begin) ma.erase(i.first);//map這種container在進行刪除的時候，收的是key，而不是整組資料，所以只能傳入first
	}
}
但是因為如果在range-based的for-loop裡面如果對這個容器進行增刪的話，for-loop在下一次查找iterator的時候會出錯，
所以只能依照助教的寫法，先去「一次性地」把所有應該刪除的一整組資料的key先儲存到set裡面，
之後再在「for-loop外面」依據set裡面的內容一次性地把該刪除的東西刪除。
 */