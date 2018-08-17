#include<stdio.h>
int nods[30][2], edge_x[30], edge_y[30], changecolor[30], colorresult[30] = { 1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 };
int nod, edge;
int backtracking(int);
void main()
{
	int i = 0, result;
	printf("enter number of nods & count of edges\n");
	scanf("%d %d", &nod, &edge);
	for (i = 0; i<edge; i++) {
		printf("enter %d edge_x & edge_y\n", i);
		scanf("%d %d", &edge_x[i], &edge_y[i]);
	}
	for (i = 0; i<nod; i++) {
		nods[i][0] = i;
	}
	nods[0][1] = 1;    //color 1
	printf("nod 0's color is 1\n");
	result = backtracking(0);
	if (result == 0)
		printf("two-color graph\n");
	else
		printf("not two-color graph\n");
}
int backtracking(int x)
{
	printf("start backtracking\n");
	int i, changecount = 0, result = 0;
	for (i = 0; i<edge; i++) {
		if (edge_x[i] == x) {
			if (nods[x][1] == 0) {
				if (colorresult[edge_y[i]] == 3) {
					colorresult[edge_y[i]] = 1;
					nods[edge_y[i]][1] = 1;
					changecolor[changecount] = edge_y[i];
					changecount++;
				}
				else if (colorresult[edge_y[i]] == 0)
					return 1;
			}
			else {
				if (colorresult[edge_y[i]] == 3) {
					colorresult[edge_y[i]] = 0;
					nods[edge_y[i]][1] = 0;
					changecolor[changecount] = edge_y[i];
					changecount++;
				}
				else if (colorresult[edge_y[i]] == 1)
					return 1;
			}
		}
		else
			continue;
	}
	for (i = 0; i<changecount; i++)
		result = result + backtracking(changecolor[i]);
	return result;
}