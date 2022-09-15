#ifndef FUNCTION_H_
#define FUNCTION_H_
#pragma warning (disable: 4996)
#include <iostream>
using namespace std;

class BigInt{
private:
	constexpr static int N = 150;//N代表總共有N個被切斷的數組。ex: 100,101,102是個很大的數，所以切成好幾組，我這裡是切成三組(一組100，一組101，一組102，每組的width都是3)
	constexpr static int WIDTH = 8, BASE = 100000000;//一個數組的寬度是8，ex: 12345678是一個數組，寬度是8。base是指一組所能儲存到的上限(不含)，在這裡，base是1e9，因為一組只有八個數字。
	bool sign;//儲存是正數還是負數。由此可知他是想要我們把數值的絕對值存起來，而正負號另外處理。
	int bigInt[N];//一個儲存N個數組的array

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
