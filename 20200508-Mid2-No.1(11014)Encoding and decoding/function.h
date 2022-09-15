#ifndef _FUNC_H
#define _FUNC_H
#include <iostream>
#include <string>
#pragma warning (disable: 4996)

class Codec {
public:
	virtual void encode() = 0;
	virtual void decode() = 0;
    virtual ~Codec() { } //助教說: 不做任何事情
	virtual void show(std::ostream& os) const = 0;
	virtual bool is_encoded() const = 0;
};


class DummyCodec : public Codec{
public:
	DummyCodec(std::string s) : encoded{ false }, code_str{ s } { }//一個Default Constructor

	void encode() {
		encoded = true;//這個DummyCodec的encode、decode很簡單，就是對字串完全不處理，直接把狀態互換，encoded換decoded；decoded換encoded==
    }

	void decode() {
		encoded = false;
    }

	void show(std::ostream& os) const {//其實就是operator overloading的東西，只不過因為operator overloading函式又把他外包出去給這個函式
		os << code_str;
    }

	bool is_encoded() const { return encoded; }

private:
	bool encoded;
	std::string code_str;
};


class RleCodec : public Codec{
public:
	RleCodec(std::string s) : encoded{ false }, code_str{ s } { }

	void encode();

	void decode();

	void show(std::ostream& os) const {
		os << code_str;
    }

	bool is_encoded() const { return encoded; }


private:
	bool encoded;
	std::string code_str;
};



void encode_decode(Codec & data);
std::ostream& operator<<(std::ostream& os, Codec& data);
#endif
