#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

int *empty[16];
int emptynum;
unsigned long score;
//update the upbased array.
int update(){
	int i;
	for(i = 0; i<16;i++){
		*(upbased+i) = *(basearray +(i/4 + i%4*4));
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
int move(int* array,int direction){
	int i,j;
	if(direction == 0){
		for(i = 0;i<4;i++){
			if(array[i] == 0){
				for(j=i+1;j<4;j++){
					if(array[j] != 0){
						exchange(array+i,array+j);
					}
				}
			}
		}
	}
	else{
		for(i = 3; i>=0;i--){
			if(array[i] == 0){
				for(j = i-1;j>=0;j--){
					if(array[j] != 0){
						exchange(array+i,array+j);
					}
				}
			}
		}
	}
	return 0;
}

//merge column/row from left or up.
int mergeleft(int* array){
	int i;
	
	move(array,0);
	for(i=0;i<3;i++){
		if(array[i] == array[i+1] && array[i] != 0){
			array[i] *=2;
			array[i+1] = 0;
		}
	}
	move(array,0);

	return 0;
}

//merge column/row from right or bottom.
int mergeright(int *array){
	int i;
	
	move(array,1);
	for(i=3;i>0;i--){
		if(array[i] == array[i-1] && array[i] != 0){
			array[i] *=2;
			score += array[i];
			array[i-1] = 0;
		}
	}
	move(array,1);

	return 0;
}



/*update the number of empty slots and collect all of their pointers in one array.*/
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

int action(){
	int c = getchar();
	c =getchar();
	c = getchar();
	switch(c){
		case 65:
			printf("press up!\n");
			break;
		case 66:
			printf("press down!\n");
			break;
		case 67:
			printf("press right!\n");
			break;
		case 68:
			printf("press left!\n");
			break;
		}

	return 0;
}
/*
int action2(){
	if (getch() == '\033') { // if the first value is esc
    	getch(); // skip the [
    	switch(getch()) { // the real value
        	case 'A':
        		printf("press up!\n");
            // code for arrow up
            	break;
        	case 'B':
        		printf("press up\\down!\n");
            // code for arrow down
            	break;
        	case 'C':
        		printf("press right!\n");
            // code for arrow right
            	break;
        	case 'D':
        		printf("press left!\n");
            // code for arrow left
            	break;
    	}
	}
	return 0;
}
*/

/*generate a new number in one of empty slot*/
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
	return 0;
}

/*print the 4*4 matrix*/

int print(){
	int i;
	for(i = 0; i < 16;i++){
		printf("%d    \n",basearray[i] );
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
				if(basearray[j] == basearray[j+1] || upbased[j] == upbased[j+1]){
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


int main() {

   	
	srand(time(NULL));
	generatenew();
	generatenew();
	score = 0;
	printf("press a key!\n");
	action();
   	return 0;
}