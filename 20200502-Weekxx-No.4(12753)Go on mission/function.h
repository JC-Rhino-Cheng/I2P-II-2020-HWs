#ifndef FUNCTION_H_
#define FUNCTION_H_
#pragma warning (disable: 4996)
#include <iostream>
using namespace std;

class BigInt{
private:
	constexpr static int N = 150;//N�N���`�@��N�ӳQ���_���ƲաCex: 100,101,102�O�ӫܤj���ơA�ҥH�����n�X�աA�ڳo�̬O�����T��(�@��100�A�@��101�A�@��102�A�C�ժ�width���O3)
	constexpr static int WIDTH = 8, BASE = 100000000;//�@�ӼƲժ��e�׬O8�Aex: 12345678�O�@�ӼƲաA�e�׬O8�Cbase�O���@�թү��x�s�쪺�W��(���t)�A�b�o�̡Abase�O1e9�A�]���@�եu���K�ӼƦr�C
	bool sign;//�x�s�O�����٬O�t�ơC�Ѧ��i���L�O�Q�n�ڭ̧�ƭȪ�����Ȧs�_�ӡA�ӥ��t���t�~�B�z�C
	int bigInt[N];//�@���x�sN�ӼƲժ�array

public:
    BigInt();// constructor
    BigInt(char*);// constructor
    BigInt(const BigInt&); //copy constructor

   
    BigInt &operator = (const BigInt&); // copy assignment operator

    // comparison operator
    bool operator < (BigInt);//Overloading Binary Operators(as a member func)
    bool operator > (BigInt);//Overloading Binary Operators(as a member func)
    bool operator == (BigInt);//Overloading Binary Operators(as a member func)
    bool operator >= (BigInt);//Overloading Binary Operators(as a member func)
    bool operator <= (BigInt);//Overloading Binary Operators(as a member func)

    // arithmetic operator
    BigInt operator + (BigInt);//Overloading Binary Operators(as a member func)
    BigInt operator - (BigInt);//Overloading Binary Operators(as a member func)

    // insertion & extraction operator
    friend istream& operator >> (istream&, BigInt&);
    friend ostream& operator << (ostream&, BigInt&);
};

void solution(BigInt &tanjiro, BigInt &zenitsu, BigInt &inosuke, int n);

/*
 * Suggestions on implemention
 *
 * Try to implement operator >> with the help of BigInt(char *num)
 * For example, 
    istream &operator >> (istream &in, BigInt &n) {
    char str[100]; cin >> str;
    n = BigInt(str);
    // some more necessary codes ...
}
 */

#endif  // FUNCTION_H_
