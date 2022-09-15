#include "function.h"
#include <stdlib.h>
#pragma warning (disable: 4996)

int main() {
	int N; cin >> N;

	char input[100];
	int index = 0;
	Str *s[100];
	
	for (int i = 0; i < N; i++) {
		cin >> input;
		s[index++] = new Str(input);//其實改成s[i]=new Str(input);也可
    }
	
	while (1) {
		char op[3];//有五種可能的operand:(1)"si" (2)"is" (3)"s" (4)"i" (5)"e"
		cin >> op;
		if (op[0] == 'e')break;

		int idx1, idx2;
		cin >> idx1;
		cin >> idx2;

		Str &s1 = *s[idx1];//這個東西不是pass-by-value，也就是說這個東西不是copy!!!這個東西是alias，也就是類似指標的東西!!!不要和pass-by-value搞混!!Q那請問: 類似指標的東西到底是什麼東西??不能直接寫成Str *s1嗎? A:可以唷~但是這樣的話就不能xxx.function()了，更不能cascaded function!
		Str &s2 = *s[idx2];


		if (op[0] == 's'&&op[1] == 'i')
			s1.strSwap(s2).strInsert(s2);
		else if (op[0] == 'i'&&op[1] == 's')
			s1.strInsert(s2).strSwap(s2);
		else if (op[0] == 's')
			s1.strSwap(s2);
		else if (op[0] == 'i')
			s1.strInsert(s2);
	}

	for (int i = 0; i < N; i++) {
		s[i]->strPrint();
		delete s[i];
	}

	system("pause");
}


