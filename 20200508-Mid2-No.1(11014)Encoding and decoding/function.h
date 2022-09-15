#ifndef _FUNC_H
#define _FUNC_H
#include <iostream>
#include <string>
#pragma warning (disable: 4996)

class Codec {
public:
	virtual void encode() = 0;
	virtual void decode() = 0;
    virtual ~Codec() { } //�U�л�: ��������Ʊ�
	virtual void show(std::ostream& os) const = 0;
	virtual bool is_encoded() const = 0;
};


class DummyCodec : public Codec{
public:
	DummyCodec(std::string s) : encoded{ false }, code_str{ s } { }//�@��Default Constructor

	void encode() {
		encoded = true;//�o��DummyCodec��encode�Bdecode��²��A�N�O��r�꧹�����B�z�A�����⪬�A�����Aencoded��decoded�Fdecoded��encoded==
    }

	void decode() {
		encoded = false;
    }

	void show(std::ostream& os) const {//���N�Ooperator overloading���F��A�u���L�]��operator overloading�禡�S��L�~�]�X�h���o�Ө禡
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
