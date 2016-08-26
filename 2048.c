#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int arraya[16];
int* basearray[16];
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

int* upbased[16];
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

int *empty[16];
int emptynum;
unsigned long score;
//update the upbased array.
int init(){
	int i;

	for(i = 0; i<16;i++){
		arraya[i] = 0;
	}
	for(i = 0; i<16;i++){
		basearray[i] =&arraya[i];
		upbased[i] = &arraya[(i/4 + i%4*4)];
	}
	return 0;
}
//exchange two varialbes' values
int exchange(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
	return 0;
}


//direction is 0 when press up and left, 1 when press down and right.
//move one column/row that all the elements stick together.


int moverow(int** array,int direction){
	int i,j;
	if(direction == 0){
		for(i = 0;i < 3; i++){
			if(*array[i] == 0){
				for(j=i+1;j<4;j++){
					if(*array[j] !=0){
						exchange(array[i],array[j]);
					}
				}
			}
		}
	}
	else if(direction == 1){
		for(i = 3;i >0; i--){
			if(*array[i] == 0){
				for(j=i-1;j>0;j++){
					if(*array[j] !=0){
						exchange(array[i],array[j]);
					}
				}
			}
		}
	}
	return 0;
}



int move(int** array,int direction){
	moverow(array,direction);
	moverow(array+4,direction);
	moverow(array+8,direction);
	moverow(array+12,direction);
	return 0;	
}

//merge column/row from left or up.
int mergerowleft(int** array){
	int i;
	
	move(array,0);
	for(i=0;i<3;i++){
		if(*(array[i]) == *(array[i+1]) && *(array[i]) != 0){
			*(array[i]) *=2;
			score += *(array[i]);
			*(array[i+1]) = 0;
		}
	}
	move(array,0);

	return 0;
}

int mergeleft(int** array){
	mergerowleft(array);
	mergerowleft(array+4);
	mergerowleft(array+8);
	mergerowleft(array+12);
	return 0;
}

//merge column/row from right or bottom.
int mergeright(int **array){
	int i;
	
	move(array,1);
	for(i=3;i>0;i--){
		if(*(array[i]) == *(array[i-1]) && *(array[i]) != 0){
			*(array[i]) *=2;
			score += *(array[i]);
			*(array[i-1]) = 0;
		}
	}
	move(array,1);

	return 0;
}



//update the number of empty slots and collect all of their pointers in one array.
int checkempty(){
	int i;
	emptynum = 0;
	int j = 0;
	for(i = 0;i < 16; i++){
		if(*basearray[i] == 0){
			emptynum ++;
			empty[j] = basearray[i];
			j++;
		}
	}
	
	return 0;
}

int action(){
	int c = getchar();
	while(c == 27 || c == 10 || c == 91){
		c = getchar();
	}

	if(c == 65){
		
		move(upbased,0);

		mergerowleft(upbased);
		mergerowleft(upbased+4);


		printf("press up!\n");
	}
	else if(c == 66){
		printf("press down!\n");
	}
	else if(c == 67){
		printf("press right!\n");
	}
	else if(c == 68){
		move(basearray,0);
		mergeleft(basearray);
		checkempty();
		printf("press left!\n");
	}
	return 0;
}

int testpress(){
	int c = getchar();
	while(c == 27 || c == 10 || c == 91){
		c = getchar();
	}
	printf("c is %d\n", c);
	return 0;
}

//generate a new number in one of empty slot
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
	int i;
	for(i = 0;i < 16; i++){
		if(*basearray[i] != 0){
			printf("%dth in basearray is not empty\n", i+1);
		}
	}
	int r2 = rand() % emptynum;
	*(empty[r2]) = newnum;
	printf("empty pos is %ldth and newnum is %d\n",(empty[r2]-basearray[0])+1 ,newnum);
	emptynum--;
	printf("emptynum is %d\n",emptynum );

	return 0;
}

//print the 4*4 matrix//

int printmatrix(){
	int i;
	for(i = 0; i < 16;i++){
		printf("%d    ",*(basearray[i]) );
		if(i%4 == 3){
			printf("\n");
			printf("\n");
		}
	}
	return 0;
}
//if the game is over return 0 else return 1;
int checklose(){
	if(emptynum != 0){
		return 1;
	}
	else{
		int i,j;
		for(i = 0;i<4; i++){
			for(j=0;j<3;j++){
				if(*(basearray[j]) == *(basearray[j+1]) || *(upbased[j]) == *(upbased[j+1])){
					return 1;
				}
			}
		}
	}
	return 0;
}

int printscore(){
	printf("your score is %lu\n",score );
	return 0;
}



int play(){
	checkempty();
	while(checklose() ==1){
		action();
		generatenew();
		printmatrix();
		
	}
	printscore();
	return 0;
}

int testarray(){
	int i;
	for(i = 0;i<16;i++){
		printf("upper %d is %d\n", i, *upbased[i]);
		printf("base %d is %d\n", i,*basearray[i]);
	}
	return 0;
}

int main() {
	
	srand(time(NULL));
	init();
	//testarray();
	generatenew();
	generatenew();
	score = 0;
	printmatrix();
	while(0){
		testpress();
	}
	play();
	//testarray();
   	return 0;
}