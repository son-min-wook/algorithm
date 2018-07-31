#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define cityLength 20
typedef struct passing {
	char starttime[5];
	char startcity[11];
}passing;
typedef struct timetable {
	int passingcitycount;
	struct passing *pass;
}timetable;
typedef struct scenario {
	int citycount;
	char **city;
	int traincount;
	struct timetable *table;
	char departuretime[5];
	char departurecity[11];
	char arrivecity[11];
}scenario;
int **saveedge;     // save all edges. save about where is start city, where is finish city, start time, finish time.
int scen;
void search(int, int, int);
int edge = 0;
int course[100] = { -1, };
int beforedeparttime = 99999, k = 0, smalleststart = 99999, bestk, beforestarttime = 0;
scenario rio;
void main() {
	int citynum, totalcount = 0, i, j, k, l, depart, arrive, start;
	char starthour[3] = { '\0', }, startmin[3] = { '\0', }, hour1[3] = { '\0', }, minute1[3] = { '\0', }, hour2[3] = { '\0', }, minute2[3] = { '\0', };  //for compute by minutes by using atoi. So we have to save each hour and minute
	printf("enter count of scenario\n");
	scanf("%d", &scen);                  //how many input do you wnat
	while (totalcount<scen) {
		printf("%dth input\n", totalcount);
		printf("enter count of entire city\n");
		scanf("%d", &rio.citycount);
		rio.city = (char **)malloc(sizeof(char*) * rio.citycount);        //malloc for each city
		for (i = 0; i<rio.citycount; i++)
			rio.city[i] = (char*)malloc(sizeof(char)*cityLength);       //malloc for city name
		for (i = 0; i<rio.citycount; i++) {
			printf("enter %dth city name\n", i + 1);
			scanf("%s", rio.city[i]);
		}
		printf("enter count of train\n");                 //how many train work 
		scanf("%d", &rio.traincount);
		rio.table = (struct timetable*)malloc(sizeof(struct timetable)*rio.traincount);  //malloc for timetable(train schedule)
		for (i = 0; i<rio.traincount; i++) {
			printf("enter count of passing city this %d train\n", i + 1);       // how many station pass
			scanf("%d", &rio.table[i].passingcitycount);
			edge = edge + rio.table[i].passingcitycount - 1;    //count  all of  possible edge
			rio.table[i].pass = (struct passing*)malloc(sizeof(struct passing)*rio.table[i].passingcitycount);  //malloc 
			for (j = 0; j<rio.table[i].passingcitycount; j++) {          //start station and finish station of train
				printf("enter start time of %d train\n", j + 1);    //last station is not start time but this question is doesn't matter
				scanf("%s", rio.table[i].pass[j].starttime);     //we just arrived as soon as possible
				printf("enter start city of %d train\n", j + 1);
				scanf("%s", rio.table[i].pass[j].startcity);
			}
		}
		for (i = 0; i<rio.traincount; i++) {                            //print table
			for (j = 0; j<rio.table[i].passingcitycount; j++) {
				printf("%s %s\n", rio.table[i].pass[j].starttime, rio.table[i].pass[j].startcity);
			}
		}
		printf("enter when you can start\n");  //when i can start
		scanf("%s", rio.departuretime);
		printf("enter departure city\n");             //where is my city
		scanf("%s", rio.departurecity);
		for (k = 0; k<rio.citycount; k++) {
			if (strcmp(rio.city[k], rio.departurecity) == 0)
				depart = k;
		}
		printf("enter arrivecity\n");           //my destination
		scanf("%s", rio.arrivecity);
		for (k = 0; k<rio.citycount; k++) {
			if (strcmp(rio.city[k], rio.arrivecity) == 0)
				arrive = k;                            //translte the city by integer  %dth city
		}
		totalcount++;
		saveedge = (int**)malloc(sizeof(int*)*edge);    //all information about edge
		for (i = 0; i<edge; i++)
			saveedge[i] = (int*)malloc(sizeof(int) * 4);    //save about where is start city, where is finish city, start time, finish time.
		for (i = 0; i<rio.traincount; i++) {
			for (j = 0; j<rio.table[i].passingcitycount - 1; j++) {   //change the city name by  %dth city
				for (k = 0; k<rio.citycount; k++) {
					if (strcmp(rio.city[k], rio.table[i].pass[j].startcity) == 0)
						saveedge[i][0] = k;  //start
					if (strcmp(rio.city[k], rio.table[i].pass[j + 1].startcity) == 0)
						saveedge[i][1] = k;  //finish
				}
				for (l = 0; l<4; l++) {   //save hours and minute         
					if (l == 0)
						strncat(hour1, &rio.table[i].pass[j].starttime[l], 2);
					else if (l == 2)
						strncat(minute1, &rio.table[i].pass[j].starttime[l], 2);
				}
				for (l = 0; l<4; l++) {            //save hours and minute   
					if (l == 0)
						strncat(hour2, &rio.table[i].pass[j + 1].starttime[l], 2);
					else if (l == 2)
						strncat(minute2, &rio.table[i].pass[j + 1].starttime[l], 2);
				}
				saveedge[i][2] = (atoi(hour1) * 60 + atoi(minute1));  //start time by minute
				saveedge[i][3] = (atoi(hour2) * 60 + atoi(minute2));  //finish time by minute
				hour1[0] = '\0', minute1[0] = '\0', hour2[0] = '\0', minute2[0] = '\0';  //reset
			}
		}
		for (i = 0; i<rio.traincount; i++) {     //print
			for (j = 0; j<4; j++)
				printf("saveedge[%d][%d]: %d\n", i, j, saveedge[i][j]);
		}
		for (l = 0; l<4; l++) {   //my start time   
			if (l == 0)
				strncat(starthour, &rio.departuretime[l], 2);
			else if (l == 2)
				strncat(startmin, &rio.departuretime[l], 2);
		}
		start = (atoi(starthour) * 60 + atoi(startmin));
		//-------------------------------------- save finish -----------------------------------------------------
		//.save edge that finish city is destination
		//while(until find the start city)
		search(arrive, start, depart);
		//--------------------------------------all reset for next input--------------------------------------------------------
		for (i = 0; i<edge; i++) {
			for (j = 0; j<4; j++)
				saveedge[i][j] = -1;
		}
		for (i = 0; i<100; i++)
			course[i] = -1;
		edge = 0, beforedeparttime = 99999, k = 0, smalleststart = 99999, bestk = 0;
		citynum, i, j, k, l, depart, arrive, start = 0;
		for (i = 0; i<3; i++) {
			starthour[i] = startmin[i] = hour1[i] = minute1[i] = hour2[i] = minute2[i] = '\0';
		}
		memset(&rio, 0, sizeof(struct scenario));
		free(saveedge);
		free(rio.city);
		free(rio.table);
		//---------------------------------------------------------------------------------
	}
}
void search(int arrive, int start, int depart)
{
	//arrive: finish city       start: my start time     depart:my destination
	int i, j, count = 0, l, temp, find, tempstart, t, m;
	int tempcourse[100] = { -1, }, candidate[100] = { -1, };
	for (i = 0; i<edge; i++) {            // save candidate(who finish is our destination. we start backwards
		if (saveedge[i][1] == arrive) {
			candidate[count] = i;
			count++;
		}
	}
	//sort candidate in small order
	for (i = 0; i<count; i++) {
		for (j = 0; j<count - 1; j++) {
			if (saveedge[candidate[j]][3]>saveedge[candidate[j + 1]][3]) {
				temp = candidate[j];
				candidate[j] = candidate[j + 1];
				candidate[j + 1] = temp;
			}
		}
	}                                 //sort end
	for (l = 0; l<count; l++) {   //we just loop candidate
		k = 0;
		tempcourse[0] = candidate[l];
		k++;
		arrive = saveedge[candidate[l]][0];             //finish city is candidate's start city
		for (j = 0; j<edge; j++) {
			if (saveedge[j][3]>beforedeparttime) {
				printf("first no\n");
				continue;
			}
			if (saveedge[j][0] == arrive && saveedge[j][3] <= beforedeparttime&&saveedge[j][2] >= start&&saveedge[j][0] == depart) {
				tempcourse[k] = j;
				tempstart = saveedge[j][2];
				if (tempstart<smalleststart&&tempstart >= beforestarttime) {
					smalleststart = tempstart;
					for (t = 0; t<k; t++)
						course[t] = tempcourse[t];
					bestk = k;
				}
				find = 1;
			}
			else if (saveedge[j][1] != arrive) {
				printf("second no\n");
			}
			else if (saveedge[j][1] == arrive && saveedge[j][3] <= beforedeparttime&&saveedge[j][2] >= start&&saveedge[j][0] != depart) {       //finish city is destination, finish time is less or same than before start time, start city is not our first city
				printf("all right but not first city\n");
				beforedeparttime = saveedge[j][2];
				tempcourse[k] = j;
				k++;
				search(saveedge[j][0], start, depart);   //recursive
			}
			else if (saveedge[j][1] == arrive && saveedge[j][3] <= beforedeparttime&&saveedge[j][2] >= start&&saveedge[j][0] == depart) {       //finish city is destination, finish time is less or same than before start time, start city is  our first city
				printf("find the first city\n");
				tempcourse[k] = j;
				tempstart = saveedge[j][2];
				k++;
				printf("k: %d\n", k);
				if (tempstart<smalleststart) {                 //check this is the best
					smalleststart = tempstart;
					for (t = 0; t<k; t++)
						course[t] = tempcourse[t];
					bestk = k;
				}
				find = 1;
			}
		}
		tempstart = 0;
		for (i = 0; i<k; i++)
			tempcourse[i] = -1;
		j = 0;
	}
	if (find == 1) {                      //if there exist the route
		printf("find: %d bestk: %d\n", find, bestk);
		for (m = 0; m<bestk; m++)
			printf("%d %s-> %d %s, ", ((saveedge[course[m]][3] / 60 * 100) + (saveedge[course[m]][3] % 60)), rio.city[saveedge[course[m]][1]], ((saveedge[course[m]][2] / 60 * 100) + (saveedge[course[m]][2] % 60)), rio.city[saveedge[course[m]][0]]);
	}
	else
		printf("not found\n");
}
