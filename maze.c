#include <stdio.h>
#include <stdlib.h>



int loadFile(char* filename);
int getRowCount(FILE* fp);
int getColCount(FILE* fp);
void CreateGrid(char* filename,FILE* fp, int rowCount, int colNum);

int loadFile(char* filename){
     
     FILE *fp;
     fp = fopen(filename, "r");
      if (fp == NULL){
        printf("Could not open file %s",filename);
        return 0;
    }
    else{
        printf("FILE LOADED...\n\n");
        int colNum = getColCount(fp);
        int rowCount = getRowCount(fp);
        fclose(fp); //close file
        fp = fopen(filename, "r");   //reopen
        CreateGrid(filename,fp, rowCount, colNum);
        
       
        
        
        
        return 0;
        
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

void CreateGrid(char* filename, FILE* fp, int rowCount, int colNum){
    int i, j;
  

     char maze[rowCount][colNum];
        for (i = 0; i < rowCount; i++) {
           
             for (j = 0; j < colNum; j++) {
                    char brick = getc(fp);
                
                     maze[i][j] = brick;
                     
                    
                  
                
                  printf("%c", maze[i][j]);
        }
    }
   

}


int main()
{
char *c = "maze.txt";
loadFile(c);
  return 0;
}
