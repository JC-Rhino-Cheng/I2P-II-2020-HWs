#include <iostream>
#include "function.h"
#pragma warning (disable: 4996)




int main() {
	std::string input_string;
	std::cin >> input_string;

	DummyCodec dummy{ input_string };
	encode_decode(dummy);//�p�G�{�b�Odecoded�A�Nencode�C�p�G�{�b�Oencoded�A�Ndecode�C�ثe�Odecoded�A�ҥH�nencode
	std::cout << "Dummy encoding: ";
	std::cout << dummy << std::endl;
	encode_decode(dummy);
	std::cout << "Dummy decoding: ";
	std::cout << dummy << std::endl;

	RleCodec rle{ input_string };
	encode_decode(rle);
	std::cout << "RLE encoding: ";
	std::cout << rle << std::endl;
	encode_decode(rle);
	std::cout << "RLE decoding: ";
	std::cout << rle << std::endl;

	system("pause");
}
