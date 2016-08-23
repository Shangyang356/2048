#include <stdio.h>
#include <time.h>

int basearray[16];
/*
---------------
0 | 1 | 2 | 3
---------------
4 | 5 | 6 | 7
---------------
8 | 9 | 10| 11
---------------
12| 13| 14| 15
---------------
*/

int rightbased[16];
/*
---------------
3 | 2 | 1 | 0
---------------
7 | 6 | 5 | 4
---------------
11| 10| 9 | 8
---------------
15| 14| 13| 12
---------------
*/

int upbased[16];
/*
---------------
0 | 4 | 8 | 12
---------------
1 | 5 | 9 | 13
---------------
2 | 6 | 10| 14
---------------
3 | 7 | 11| 15
---------------
*/

int bottombased[16]
/*
---------------
3 | 7 | 11| 15
---------------
2 | 6 | 10| 14
---------------
1 | 5 | 9 | 13
---------------
0|  4 | 8 | 12
---------------
*/

int empty[14];
int emptynum;


int init(){
	int i;
	for(i = 0; i<16;i++){
		upbased+i = basearray +(i/4 + i%4*4);
	}
	return 0;
}

int exchange(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
	return 0;
}

int mergeleft(){
	int i;
	for(i=0;i<3;i++){
		if(basearray[i] == 0){
			exchange(basearray[i],basearray[i+1]);
		}
	}
	return 0;
}

int mergeright(){
	int i;
	for(i = 3;i>0;i--){
		if(basearray[i] == 0){
			exchange(basearray[i],basearray[i-1]);
		}
	}
	return 0;
}

int mergeup(){
	int i;
	for(i=0;i<3;i++){
		if(upbased[i] == 0){
			exchange(upbased[i],upbased[i+1]);
		}
	}
	return 0;
}

int mergebottom(){
	int i;
	for(i = 3;i>0;i--){
		if(upbased[i] == 0){
			exchange(upbased[i],upbased[i-1]);
		}
	}
	return 0;
}





int checkempty(){
	int i;
	emptynum = 0;
	for(i = 0;i < 16; i++){
		if(basearray[i] == 0){
			emptynum ++;
			empty[i] = basearray + i;
		}
	}
	return 0;
}

int generatenew(){
	int newnum;
	int r =rand()%2;
	if(r==1){
		newnum = 2;
	}
	else{
		newnum = 4;
	}
	checkempty();
	int r2 = rand() % emptynum;
	int* ptr = empty[r2];
	*ptr = r;
}

int main() {
   /* my first program in C */
   	
	srand(time(NULL));

   	return 0;
}