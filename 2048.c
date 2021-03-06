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
	/*
	arraya[0] =0;
	arraya[1] =2;
	arraya[2] =4;
	arraya[3] =8;
	arraya[4] =0;
	arraya[5] =0;
	arraya[6] =4;
	arraya[7] =8;
	arraya[8] =0;
	arraya[9] =0;
	arraya[10] =8;
	arraya[11] =2;
	arraya[12] =0;
	arraya[13] =4;
	arraya[14] =8;
	arraya[15] =16;
	*/
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
						j=4;
					}
				}
			}
		}
	}
	else if(direction == 1){
		for(i = 3;i >0; i--){
			if(*array[i] == 0){
				for(j=i-1;j>=0;j--){
					if(*array[j] !=0){
						exchange(array[i],array[j]);
						j =-1;
					}
				}
			}
		}
	}
	return 0;
}

//merge column/row from left or up.
int mergerowleft(int** array){
	int i;
	
	moverow(array,0);
	for(i=0;i<3;i++){
		if(*(array[i]) == *(array[i+1]) && *(array[i]) != 0){
			*(array[i]) *=2;
			score += *(array[i]);
			*(array[i+1]) = 0;
		}
	}
	moverow(array,0);

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
int mergerowright(int **array){
	int i;
	
	moverow(array,1);
	for(i=3;i>0;i--){
		if(*(array[i]) == *(array[i-1]) && *(array[i]) != 0){
			*(array[i]) *=2;
			score += *(array[i]);
			*(array[i-1]) = 0;
		}
	}
	moverow(array,1);

	return 0;
}

int mergeright(int** array){
	mergerowright(array);
	mergerowright(array+4);
	mergerowright(array+8);
	mergerowright(array+12);
	return 0;
}

int equalneighboor(int** array,int direction){
	int i,j;
	if(direction == 0){
		for(i = 0;i < 4;i++){
			for(j = 0;j<3;j++){
				if((*array[i*4+j] == *array[i*4+j+1])&&(*array[i*4+j] !=0)){
					return 1;
				}
			}
		}
	}
	else{
		for(i = 0;i<4;i++){
			for( j = 3;j>0;j--){
				if((*array[i*4+j] == *array[i*4+j-1])&&(*array[i*4+j] !=0)){
					return 1;
				}
			}
		}
	}
	return 0;
}

int haveempty(int** array,int direction){
	int i,j,k;
	if(direction == 0){
		for(i = 0;i<4;i++){
			for(j=0;j<3;j++){
				if(*array[i*4+j] ==0){
					k = j;
					j = 3;
				}
			}
			for(j=k+1;j<4;j++){
				if(*array[i*4+j] !=0){
					return 1;
				}
			}
		}
	}
	else{
		for(i = 0;i < 4;i++){
			for(j=3;j>0;j--){
				if(*array[i*4+j] == 0){
					k = j;
					j = 0;
				}
			}
			for(j = k-1;j>=0;j--){
				if(*array[i*4+j] != 0){
					
					return 1;
				}
			}
		}
	}
	return 0;
}

int executable(int** array,int direction){
	int i =haveempty(array,direction);
	int j =equalneighboor(array,direction);
	return i||j;
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


//generate a new number in one of empty slot
int generatenew(){
	if(emptynum != 0){
		int newnum;
		int r =rand()%2;
		if(r==1){
			newnum = 2;
		}
		else{
			newnum = 4;
		}
	
		int r2 = rand() % emptynum;
		*(empty[r2]) = newnum;
	}
	return 0;
}

int action(){
	int c = getchar();
	while(c == 27 || c == 10 || c == 91){
		c = getchar();
	}

	if(c == 65){
		if(executable(upbased,0) == 1){
			mergeleft(upbased);
			checkempty();
			generatenew();
			printf("----------------------------up!\n");
		}
		else{
			printf("cannot do up\n");
		}
	}
	else if(c == 66){
		if(executable(upbased,1) == 1){
			mergeright(upbased);
			checkempty();
			generatenew();
			printf("----------------------------down!\n");
		}
		else{
			printf("cannot do down\n");
		}
	}
	else if(c == 67){
		if(executable(basearray,1) == 1){
			mergeright(basearray);
			checkempty();
			generatenew();
			printf("----------------------------right!\n");
		}
		else{
			printf("cannot do right\n");
		}
	}
	else if(c == 68){
		if(executable(basearray,0) == 1){
			mergeleft(basearray);
			checkempty();
			generatenew();
			printf("----------------------------left!\n");
		}
		else{
			printf("cannot do left\n");
		}
	}
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
				if(*(basearray[j+4*i]) == *(basearray[j+1+4*i]) || *(upbased[j+4*i]) == *(upbased[j+1+4*i])){

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
		
		printmatrix();
		
	}
	printscore();
	return 0;
}



int main() {
	
	srand(time(NULL));
	init();
	
	checkempty();
	generatenew();
	checkempty();
	generatenew();
	
	score = 0;
	printmatrix();
	play();
   	return 0;
}