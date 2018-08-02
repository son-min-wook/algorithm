#include <stdio.h>
#include <math.h>
int find_e(int);                   //find e
int find_d(int, int);               //find d
int square(int, int, int);           //using repeated squaring algorithm.
int recover(int, int, int);          //recover the code
int check(int);                    // check this integer is prime
void main()
{
	char message[30] = { NULL, }, m = NULL;
	int code[20], i = 0, count = 0, p, q, n, on, e = 0, d = 0, c[20];
	printf("Hi alice! please enter the message! less that 20 letter\n");
	gets_s(message);
	while (message[i] != NULL) {                   //count the letter
		count++;
		i++;
	}
	for (i = 0; i<count; i++) {                     //copy
		code[i] = message[i];
	}
	for (i = 0; i<count; i++) {                     //show letters by ASCII code
		printf("%d ", code[i]);
	}
	printf("\n");
	printf("select 2 prime multiple is less than 1000\n");
	scanf("%d %d", &p, &q);
	if (check(p) != 1 || check(q) != 1) {              //check they are  prime or not
		while (check(p) != 1 || check(q) != 1) {
			printf("enter prime again\n");
			scanf("%d %d", &p, &q);
		}
	}
	n = p*q;
	on = (p - 1)*(q - 1);            //pie(n)
	e = find_e(on);
	d = find_d(e, on);
	for (i = 0; i<count; i++) {
		c[i] = square(message[i], e, n);
	}
	printf("----------------------------------------------\n");
	printf("MESSAGE\n");
	for (i = 0; i<count; i++) {
		printf("%d ", c[i]);
	}
	printf("\n");
	printf("PUBLIC KEY\n");
	printf("N: %d\n", n);
	printf("E: %d\n", e);
	printf("PRIVATE KEY\n");
	printf("D: %d\n", d);
	printf("N: %d\n", n);
	for (i = 0; i<count; i++) {
		c[i] = recover(c[i], d, n);
	}
	printf("RECOVER\n");
	for (i = 0; i<count; i++) {
		printf("%d ", (char)c[i]);
	}
	printf("\n");
	for (i = 0; i<count; i++) {
		printf("%c", (char)c[i]);
	}
}
int find_e(int x)
{
	int t, b, r, q, a;
	a = x;
	printf("Please enter E. I will check it is correct\n");
	scanf("%d", &t);
	b = t;
	while (1) {                                        //check e is relatively prime with on
		q = a / b;
		r = a%b;
		if (r == 0)
			break;
		if (q == 0 && r != 0)
			break;
		a = b;
		b = r;
	};
	if (b == 1 || q == 0) {
		printf("OKAY\n");
		return t;
	}
	else {
		printf("AGAIN\n");
		return find_e(x);
	}
}
int find_d(int e, int on)
{
	int d, z = 0, i = 1;
	while (z == 0) {                          //maybe it can be lots of integer.
		if (((e*i) - 1) % on == 0) {              //but i choose only one
			z = ((e*i) - 1) / on;
			break;
		}
		else {
			i++;
		}
	}
	d = (1 + (z*on)) / e;
	return d;
}
int square(int m, int e, int n)
{
	int i, j, k, l, m1 = 1, num = e;
	int result[10], power[10], total = 1;
	if (e>2) {
		for (i = 0; num>0; i++) {
			result[i] = num % 2;                    //change squared by binary
			num = num / 2;
		}
		for (l = 0; l<i; l++) {
			if (l == 0) {
				power[0] = m%n;
			}
			else {
				power[l] = (power[l - 1] * power[l - 1]) % n;          //save each rest of squared
			}
		}
		for (j = 0; j<i; j++) {
			if (result[j] == 0)
				continue;
			total = (total*(result[j] * power[j])) % n;           //multiple each binary value and
		}                                                   // get rest  divided by n
		return total;
	}
	else {
		for (k = 0; k<e; k++)
			m1 = m1*m;
		return m1%n;
	}
}
int recover(int c, int d, int n)
{                                            //get original sentence
	int i, j, k, l, m1 = 1, num = d;
	int result[10], power[10], total = 1;
	if (d>2) {
		for (i = 0; num>0; i++) {
			result[i] = num % 2;
			num = num / 2;
		}

		for (l = 0; l<i; l++) {
			if (l == 0) {
				power[0] = c%n;
			}
			else {
				power[l] = (power[l - 1] * power[l - 1]) % n;
			}
		}
		for (j = 0; j<i; j++) {
			if (result[j] == 0)
				continue;
			total = (total*(result[j] * power[j])) % n;
		}
		return total;
	}
	else {
		for (k = 0; k<d; k++)
			m1 = m1*c;
		return m1%n;
	}
}
int check(int a)             //check this integer is prime number or not
{
	int num;
	int i;
	int ok = 1;
	for (i = 2; i<a; i++) {
		if (a%i == 0) {
			ok--;
			break;
		}
	}
	if (ok == 1)
		return 1;
	else
		return 0;
}
