#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "malloc.h"


struct Letter{
	//number following colon maps the number of bits to the int variable
	int firstFiveBits : 5;
	int switchBit : 1;
	int lastTwoBits : 2;
};
void main() {
	char buffer[] = { "C Bitwise Operators" };
	//char* example = new char[strlen(buffer) + 1];  ----Same as below
	char* example = (char*)malloc(strlen(buffer) + 1);


	//changing the char to upper case involves bit wise operations
	//'A' = 65
	//'a' = 97
	//difference of 32

	printf("First Character: %c \n", buffer[0]);
	//buffer[0] += 32; same as below
	buffer[0] = buffer[0] | 32;
	printf("Modified first character: %c \n", buffer[0]);


	//from lower case to upper case

	buffer[0] = buffer[0] & 223  ;
	printf("Again Modified first character: %c \n", buffer[0]);

	//explanation for operations in notes

	Letter* ptrLetter = (Letter*)&buffer[0];
	//ptrLetter->switchBit = ptrLetter->switchBit ^ 1; //same as below --  ^ = xor operator
	ptrLetter->switchBit = ~ptrLetter->switchBit; // ~ inverts the bit
	printf("%c \n", *ptrLetter);


	int size = strlen(buffer);
	for (int i = 0; i < size; i++) {
		Letter* ptrLetter = (Letter*)&buffer[i];
		ptrLetter->switchBit = ~ptrLetter->switchBit;
		printf("%c", buffer[i]);
	}

	//homework, make this statement work
	//printf("\n %c", buffer);


	int value = -23;
	printf("\n %d ", value);
	value = value ^ 4294967294;
	printf("\n %d ", value);


}