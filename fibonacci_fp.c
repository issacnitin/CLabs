#include <stdio.h>



int fibonacci(int i, int fp(int, int ())){
	if(i == 0)
		return 0;
	if(i == 1)
		return 1;
	else
		return fp(i-1, fp) + fp(i-2, fp);
}


int main(){
	int (*fp)(int, int ());

	fp = fibonacci;
	printf("3 fib %d", fp(3, fp));

	return 0;
}
