#include "function.h"
#pragma warning (disable: 4996)

Str :: Str(char *input) :head(NULL), tail(NULL) {
	if (input[0] != '\0') {
		head = new Char(input[0]);

		tail = head;

		for (int i = 1; input[i] != '\0'; i++) {
			Char *temp = new Char(input[i]);
			tail->next = temp;

			tail = temp;
		}
	}

	//Constructor不return任何東西
}


Str :: Str(const Str &from) :head(NULL), tail(NULL) {//copy constructor
	head = new Char(from.head->text);
	tail = head;

	Char *temp_node_of_from = from.head->next;

	while (temp_node_of_from != NULL) {
		Char *new_char = new Char(temp_node_of_from->text);
		tail->next = new_char;
		tail = new_char;

		temp_node_of_from = temp_node_of_from->next;
	}

	//Constructor不return任何東西
}


Str& Str::strInsert(const Str &from) {
	Str *to_be_inserted_after = new Str(from);

	tail->next = to_be_inserted_after->head;//善用Str的copy constructor
	tail = to_be_inserted_after->tail;

	return *this;
}
