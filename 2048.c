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

int empty[16];
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

int move(int* array,int direction){
	int i,j;
	if(direction == 0){
		for(i = 0;i<4;i++){
			if(array[i] == 0){
				for(j=i+1;j<4;j++){
					if(array[j] != 0){
						exchange(array[i],array[j]);
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
						exchange(array[i],array[j]);
					}
				}
			}
		}
	}
	return 0;
}

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

int mergeright(int *array){
	int i;
	
	move(array,1);
	for(i=3;i>0;i--){
		if(array[i] == array[i-1] && array[i] != 0){
			array[i] *=2;
			array[i-1] = 0;
		}
	}
	move(array,1);

	return 0;
}

int mergeup(int* array){
	int i;
	
	move(array,0);
	for(i=0;i<2;i++){
		if(array[i] == array[i+1] && array[i] != 0){
			array[i] *=2;
			array[i+1] = 0;
		}
	}
	move(array,0);

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

int action(char c){
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

int main() {
   /* my first program in C */
   	
	srand(time(NULL));
	generatenew();
	generatenew();
	int c = getchar();

    if(c==27)
    {
        printf("UP");
    }

    if(c==28)
    {
        printf("DOWN");
    }
   	return 0;
}