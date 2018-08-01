#include <stdio.h>
void main()
{
	int q, w, i, x, y, value = 0, C = 0, temp, great = 0, min = 0, o, p, count = 0;
	printf("enter x\n");
	scanf("%d", &q);
	printf("enter y\n");
	scanf("%d", &w);
	if (q>w) {                                  //gcd(x,y)=gcd(y,x mod y);
		temp = q;                              //gcd(x,0)=|x|;
		q = w;                                  //big integer is back, small integer is front.
		w = temp;
		value = 1;
	}
	x = q;
	y = w;
	C = x%y;
	if (C != 0) {
		while (C != 0) {                  //find  greatest common divisor
			C = x%y;
			x = y;
			y = C;
		}
		great = x;
		printf("great: %d\n", great);
	}
	else {                                //if x,y is equal
		great = y;
		printf("great: %d\n", great);
	}
	min = (q / great)*(w / great)*great;         //find the least common multiple
	printf("min: %d\n", min);
	if (q != w) {                                //by-d=ax
		for (i = 0; i<(min / w); i++) {
			if (((w*(i + 1)) - great) % q == 0) {
				o = (((w*(i + 1)) - great) / q)*-1;
				p = i + 1;
				count = 1;
				break;
			}
			else
				continue;
		}
		if (count == 0)
			printf("not found\n");
		else {
			if (value == 1)              //if swap them
				printf("%d %d %d\n", p, o, great);
			else
				printf("%d %d %d\n", o, p, great);
		}
	}
	else                                //if they are equal
		printf("%d %d %d\n", 0, 1, great);
}