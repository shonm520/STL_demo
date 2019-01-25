#include <stdio.h>
#include "vector.h"

using namespace TinySTL;

int main()  {
	printf("haha\n");
	MyVector<int> vtInt;
	vtInt.push_back(1);
	vtInt.push_back(2);
	vtInt.push_back(2);

	printf("size of vtInt is %d\n", vtInt.size());
	printf("cap of vtInt is %d\n", vtInt.max_size());
	printf("[0] is %d \n", vtInt[0]);
	printf("[1] is %d \n", vtInt[1]);
	return 0;
}