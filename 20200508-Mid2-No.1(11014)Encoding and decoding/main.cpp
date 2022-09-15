#include <iostream>
#include "function.h"
#pragma warning (disable: 4996)




int main() {
	std::string input_string;
	std::cin >> input_string;

	DummyCodec dummy{ input_string };
	encode_decode(dummy);//如果現在是decoded，就encode。如果現在是encoded，就decode。目前是decoded，所以要encode
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
