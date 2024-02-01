#include <stdlib.h>
#include "mint.f"

int main(int argc, char *argv[]) {
	//Test 00: Empty Test
	//Expect: ""

	//Test 01: Empty String
	mintf("");
	//Expect: ""

	//Test 02: Integer Test
	mintf("98275927");
	//Expect: 98275927

	//Test 03: Negative Test
	mintf("-18928");
	//Expect: -18928

	//Test 04: Symbol Test
	mintf("-$294")
	//Expect: -$294

	//Test 05: Binary Test
	mintf("%b", 125);
	//Expect: 0b1111101

	//Test 06: Hexadecimal Test
	mintf("%x", 985);
	//Expect: 0x3D9

	//Test 07: Sentence Test
	mintf("Tommy has %d dogs.", 3);
	//Expect: Tommy has 3 dogs.

	//Test 08: Multiple Input Test
	mintf("There are %d red, %d green, an %d blue balls in the bag.", 20, 50, 30);
	//Expect: There are 20 red, 50 green, and 30 blue balls in the bag.

	//Test 09: Symbol Sentence Test
	mintf("After buying a $%d phone, Ryan has -$%d and is currently in debt.", 1000, 100);
	//Expect: After buyin a $1000 phone, Ryan has -$100 and is currently in debt.

	//Test 10: Sentence Test With Binary Input
	mintf("The number %d is %b in binary.", 47, 47);
	//Expect: The number 47 is 0b101111 in binary.
}
