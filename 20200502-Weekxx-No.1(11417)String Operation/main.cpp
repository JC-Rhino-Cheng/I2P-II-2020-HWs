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
		s[index++] = new Str(input);//���令s[i]=new Str(input);�]�i
    }
	
	while (1) {
		char op[3];//�����إi�઺operand:(1)"si" (2)"is" (3)"s" (4)"i" (5)"e"
		cin >> op;
		if (op[0] == 'e')break;

		int idx1, idx2;
		cin >> idx1;
		cin >> idx2;

		Str &s1 = *s[idx1];//�o�ӪF�褣�Opass-by-value�A�]�N�O���o�ӪF�褣�Ocopy!!!�o�ӪF��Oalias�A�]�N�O�������Ъ��F��!!!���n�Mpass-by-value�d�V!!Q���а�: �������Ъ��F��쩳�O����F��??���ઽ���g��Str *s1��? A:�i�H��~���O�o�˪��ܴN����xxx.function()�F�A�󤣯�cascaded function!
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


