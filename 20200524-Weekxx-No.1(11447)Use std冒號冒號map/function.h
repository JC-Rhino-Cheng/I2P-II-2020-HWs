#ifndef FUNCTION_H
#define FUNCTION_H
#include<cstddef>
#include<map>
#include<string>

namespace oj {
	struct String {
		std::string str;
		String(const std::string &);
		String(const String &);
		String& operator=(const String &);
	};

	
	std::ostream& operator<<(std::ostream &, const String &);//助教寫好了
	//以下四個function需要實作
	void insert(std::map<int, String> &ma, int key, const std::string &str);
	void output(const std::map<int, String> &ma, int begin, int end);
	void erase(std::map<int, String> &ma, int begin, int end);

	std::ostream& operator<<(std::ostream &, const std::map<int, String> &);
}

#endif