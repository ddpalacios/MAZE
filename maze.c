#include <stdio.h>
#include <stdlib.h>

FILE* loadFile(char* filename);
int getRowCount(FILE* fp);
int getColCount(FILE* fp);
char **inputMaze(FILE* fp, int rowCount, int colNum);
int **outMaze(char** maze, FILE* fp, int rowCount, int colNum);

FILE* loadFile(char* filename){
     
     FILE *fp;
     fp = fopen(filename, "r");
      if (fp == NULL){
        printf("Could not open file %s",filename);
        return 0;
    }
    else{
        printf("FILE LOADED...\n\n");

        fclose(fp); //close file
        fp = fopen(filename, "r");   //reopen


        return fp;
        
    }
    
    
    
    
}
int getColCount(FILE* fp){
    char col[200];
     int colNum;
     
    fscanf(fp,"%[^\n]", col);
    colNum = strlen(col) +1; //get total col count
       
       
return colNum;    
    
}
int getRowCount(FILE* fp){
     char c;
     int Rowcount =1;
     
     for (c = getc(fp); c != EOF; c = getc(fp)) {
        if (c == '\n'){ // Increment count if this character is newline 
            Rowcount = Rowcount + 1; 
        }
}
return Rowcount;

}



int **outMaze(char** maze, FILE * fp, int rowCount, int colNum){

int **mazeOut = (int**)malloc(rowCount*sizeof(int*));
for (int i=0; i<rowCount; i++){
	mazeOut[i] = (int*)malloc(colNum+1*sizeof(int));


}

for (int i=0; i<rowCount; i++){
	for(int j=0; j< colNum; j++){
		if (maze[i][j] == "b"){
		mazeOut[i][j] = -1;

	}
		if (maze[i][j] == "s"){
    		mazeOut[i][j] = 0;


}

printf("%c", mazeOut[i][j]);

}

}
return mazeOut;




}




char **inputMaze(FILE* fp, int rowCount, int colNum){



char **maze = (char**)malloc(rowCount*sizeof(char*));
for (int i=0; i<rowCount; i++){
	maze[i] = (char*)malloc(colNum+1*sizeof(char));


}
	char brick;
        for (int i = 0; i < rowCount; i++) {

             for (int j = 0; j < colNum+1; j++) {
                    brick = getc(fp);

                     maze[i][j] = brick;



}
    }

for (int i=0; i<rowCount; i++){
	for (int j=0; j<colNum; j++){
		printf("%c", maze[i][j]);
}

printf("\n");
}

return maze;

}











int main()
{
char *c = "maze.txt";
FILE *fp= loadFile(c);

int colNum = getColCount(fp);
int rowCount = getRowCount(fp);

printf("%d, %d\n", rowCount, colNum);

char **inMaze = inputMaze(fp,rowCount, colNum);

//int **outmaze = outMaze(inMaze,fp, rowCount, colNum);

fclose(fp);

 return 0;
}
int colNum = getColCount(fp);
        int rowCount = getRowCount(fp);
int colNum = getColCount(fp);
        int rowCount = getRowCount(fp);
