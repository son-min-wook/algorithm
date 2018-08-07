#include<stdio.h>
#include<math.h>
int count = 0;                  //count of possible position
void main() {
	int length, bishop, factorial;
	int table[10][10] = { 0 };
	int fact(int);                     //calculate factorial
	void backtracking(int[][10], int, int);
	printf("enter table && bishop\n");
	scanf("%d %d", &length, &bishop);
	backtracking(table, length, bishop);       //call backtracking function
	factorial = fact(bishop);               //call factorial function
	printf("%d\n", count / factorial);          //eliminate duplicate
}
int fact(int bishop) {
	int factorial = 1;          //for case bishop is 0
	while (bishop) {
		factorial = factorial*bishop;
		bishop--;
	}
	return factorial;
}
void backtracking(int table[][10], int length, int bishop) {
	int i, j, l, m, newbishop, value = 1;
	if (bishop == 0) {              //rigth position
		count++;
		return;
	}
	for (i = 0; i < length; i++) {
		for (j = 0; j < length; j++) {
			value = 1;
			for (l = 0; l < length; l++) {
				for (m = 0; m < length; m++) {
					if (table[l][m] != 0)
						if (abs(i - l) == abs(j - m)) {
							value = 0;
						}
				}
			}
			table[i][j] ++;
			newbishop = bishop - 1;
			if (value == 1)
				backtracking(table, length, newbishop);     //reculsive
			table[i][j] --;
		}
	}
}

