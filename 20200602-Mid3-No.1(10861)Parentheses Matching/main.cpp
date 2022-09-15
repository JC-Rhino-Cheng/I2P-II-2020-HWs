#include <stack>
#include <string>
#include <iostream>
#include  <map>
using namespace  std;

map<char, char> mapping = {//不能冠以const，因為map沒有overload 所有const類型，導致會找不到
	{'{','}'}, {'[',']'}, {'(',')'}, {'<','>'}
};

int main() {
	int N; cin >> N;
	string trash; getline(cin, trash);//會有空格，而cin吃不到空格，所以用getline。

	for (int i = 1; i <= N; i++) {
		stack<char>S;
		string input; /*cin >> input;*/ getline(cin, input);//因為即便是完全空的也是有效input，而cin不吃完全空的的string，所以要用getline強迫他吃換行和空格
		bool valid = true;
		
		for (const auto &c : input) {
			if (c == '{' || c == '[' || c == '(' || c == '<') S.push(c);
			else if (c == '}' || c == ']' || c == ')' || c == '>') {
				if (S.empty()) {
					valid = false;
					break;
				}
				
				const auto top = S.top(); S.pop();
				if (mapping[top] != c) {
					valid = false;
					break;
				}
			}
		}
		if (!S.empty()) valid = false;

		cout << "Case " << i << ": " << (valid ? "Yes" : "No") << endl;
	}

	system("pause");
}