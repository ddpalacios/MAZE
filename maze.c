#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

FILE* loadFile(char* filename);
char **inputMaze(FILE* fp, int rowCount, int colNum);
int **outputMaze(FILE *fp, int rowCount, int colNum, char **in_maze);
int getRowCount(FILE *fp, char *filename);
int getColCount(FILE *fp, char *filename);
void Print_inMaze(int rows, int col, char **maze);
void Print_outMaze(int rowCount,int colNum, int** out_maze);
void solve_maze(int row, int column, char**in_maze, int** out_maze,FILE* journal_fp);
int *get_start_cordinates(char** in_maze,int rows,int columns);
void solve_by_recursion(int x_pos,int y_pos, int **maze_out, int distance,int rows,int columns,FILE*fp);
int isOpen(int testRow,int testCol,int row, int col);
void go_left(int** maze_out, int x_pos, int y_pos, int distance, int rows, int columns,FILE*fp);
void go_right(int** maze_out, int x_pos, int y_pos, int distance, int rows, int columns,FILE*fp);
void step_up(int** maze_out,int x_pos, int y_pos, int distance, int rows, int columns,FILE*fp);
void step_down(int** maze_out, int x_pos, int y_pos, int distance, int rows, int columns,FILE*fp);
void test();
void complete_maze_solver(FILE* fp,FILE* journal_fp ,char* filename);


FILE* loadFile(char*filename){

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
char** inputMaze(FILE *fp, int rows, int columns)
{
  int i,j;
  char **maze = (char**)malloc(rows*sizeof(char*));
  for (i=0; i<rows; i++){
     maze[i] = (char*)malloc(columns+1*sizeof(char));
  }

  char brick;
 for (int i=0; i<rows; i++)
  {
   for (int j=0; j<columns+1; j++)
   {
      brick = getc(fp);
      maze[i][j] = brick;
    }
  }

    Print_inMaze(rows, columns, maze);
    return maze;
}
int **outputMaze(FILE *fp, int rowCount, int colNum, char**in_maze){
      int brick;
      int** out_maze =  (int**)malloc(rowCount*sizeof(int*));
        for (int i=0; i<rowCount; i++){
          out_maze[i] = (int*)malloc(colNum*sizeof(int));
        }
                for (int i=0; i < rowCount; i ++){
                  for (int j=0; j<colNum; j++){
                if (in_maze[i][j] == ' ')
                    out_maze[i][j] = -1;
                    if (in_maze[i][j] == 'b')
                    out_maze[i][j] = -2;
                    else if (in_maze[i][j] == 's')
                    out_maze[i][j] = -3;
                  }

                }
          return out_maze;

}
void Print_outMaze(int row, int col, int **out_maze){
    printf("\n");
    for (int i=0; i<row; i++)
      {
        for (int j=0; j<col; j++)
        {
            printf(" %d ",out_maze[i][j]);
        }
        printf("\n");
      }


    }


void Print_inMaze(int row, int col, char ** maze){
  for (int i=0; i<row; i++)
    {
      for (int j=0; j<col; j++)
      {
          printf(" %c ",maze[i][j]);
      }
      printf("\n");
    }


  }

int getRowCount(FILE *fp, char *filename)
{
  fp = fopen(filename,"r");
  int rowCount = 0;
  char chr;
  while (chr!=EOF)
  {
    if (chr=='\n')
    {
      rowCount = rowCount + 1;
    }
    chr = getc(fp);
  }
  fclose(fp);
  return rowCount;
}
int getColCount(FILE *fp, char *filename)
{
  fp = fopen(filename,"r");
  int colCount = 0;
  char chr;
  while (chr!='\n')
  {
    colCount = colCount+1;
    chr = fgetc(fp);
  }
  fclose(fp);
  colCount = colCount-1;
  return colCount;
}
int* get_start_cordinates(char** in_maze,int rows,int columns){
int *starting_pos = malloc(3* sizeof(int));
//Allocating 1-D Array
for (int i=0; i<3;i++){
        starting_pos[i] = 4*i;

}

  for (int i=0; i < rows; i++){
    for (int j=0; j< columns; j++){
      if (in_maze[i][j]== 's'){
        starting_pos[0] = i;
        starting_pos[1] = j;

      }

    }
  }

    return starting_pos;


}
int position_is_open(int testRow,int testCol,int row, int col)
{
  if (testRow<0 || testRow>=row)
    return 0;
  if (testCol<0 || testCol>=col)
    return 0;
return 1;
}
void step_up(int** maze_out, int x_pos, int y_pos, int distance, int rows, int columns,FILE*fp){
   if (maze_out[x_pos-1][y_pos]==-1)
       {

        fprintf(fp, "Step Up at --> <Row: %d> <columns: %d>\t\t<Prev Cell: %d> <New Cell: %d>\n", x_pos-1, y_pos, distance, distance+1);
        if (x_pos-1 == 0){
        fprintf(fp, "\n\t\t\t---SOLVED---\t\t\t\n");
        fprintf(fp, " \n\t\tDetecting other possible paths...\t\n\n");
        }

         solve_by_recursion(x_pos-1,y_pos, maze_out, distance+1,rows,columns, fp);
       }

}
void step_down(int** maze_out, int x_pos, int y_pos, int distance, int rows, int columns,FILE*fp){
    if (maze_out[x_pos+1][y_pos]==-1)
       {
        fprintf(fp, "Step Down at --> <Row: %d> <columns: %d>\t\t\t<Prev Cell: %d> <New Cell: %d>\n", x_pos-1, y_pos, distance, distance+1);
          solve_by_recursion(x_pos+1,y_pos,maze_out,distance+1,rows,columns,fp);
       }


}
void go_left(int** maze_out, int x_pos, int y_pos, int distance, int rows, int columns,FILE*fp){
 if (maze_out[x_pos][y_pos-1]==-1)
         {
        fprintf(fp, "Left at --> <Row: %d> <columns: %d>\t\t\t<Prev Cell: %d> <New Cell: %d>\n", x_pos-1, y_pos, distance, distance+1);
         solve_by_recursion(x_pos,y_pos-1,maze_out,distance+1,rows,columns,fp);
       }


}
void go_right(int** maze_out, int x_pos, int y_pos, int distance, int rows, int columns,FILE*fp){

      if (maze_out[x_pos][y_pos+1]==-1)
            {
              fprintf(fp, "Right at --> <Row: %d> <columns: %d>\t\t\t<Prev Cell: %d> <New Cell: %d>\n", x_pos-1, y_pos, distance, distance+1);
              solve_by_recursion(x_pos,y_pos+1,maze_out,distance+1,rows,columns,fp);
            }

}
void solve_by_recursion(int x_pos,int y_pos, int **maze_out, int distance,int rows,int columns,FILE*fp){
  int curr_body_pos = maze_out[x_pos][y_pos];
  if (curr_body_pos == -3 || curr_body_pos == -1 ||curr_body_pos < distance){
    maze_out[x_pos][y_pos] = distance;
  }

   if (position_is_open(x_pos -1,y_pos,rows,columns))
        step_up(maze_out, x_pos, y_pos, distance,rows, columns, fp);

   if (position_is_open(x_pos+ 1,y_pos,rows,columns))
       step_down(maze_out, x_pos, y_pos,distance, rows, columns,fp);

   if (position_is_open(x_pos,y_pos+1,rows,columns))
       go_right(maze_out, x_pos, y_pos, distance,rows, columns,fp);

   if (position_is_open(x_pos,y_pos-1,rows,columns))
      go_left(maze_out, x_pos, y_pos,distance, rows, columns,fp);

}


void solve_maze(int rows, int columns, char** maze_in, int** maze_out, FILE* journal_fp)
{
    int *starting_pos = get_start_cordinates(maze_in, rows, columns);
    int x_pos = starting_pos[0];
    int y_pos = starting_pos[1];

    solve_by_recursion(x_pos, y_pos, maze_out, 0,rows,columns, journal_fp);
    Print_outMaze(rows,columns, maze_out);
    printf("\nStaring Position--> x: %d, y: %d\n", x_pos, y_pos);
    printf("\n\nThis maze was recorded under .journal file\n");
    printf("\n\nTo View:  ./yourmazefilename -j yourjournalname\n\n");



}


void complete_maze_solver(FILE* fp,FILE* journal_fp, char* filename){
        int columns = getColCount(fp,filename);
        int rows = getRowCount(fp, filename);
        char** in_maze = inputMaze(fp,rows,columns);
        int** out_maze = outputMaze(fp,rows,columns, in_maze);
        solve_maze(rows,columns, in_maze,out_maze, journal_fp);

}

int main(int argc, char **argv){
  FILE* fp = NULL;
  int chosen_flag;
  char* filename[100];
  char* replay_file;
  char* filename_journal;
  char journal_contents;
  FILE* replay_fp;
  FILE* journal_fp = NULL; //Just for testing on linux Nvidia

        while((chosen_flag = getopt(argc,argv,"o:j:"))!=-1)
        {
                switch (chosen_flag){
                        case 'o':
                        /*
                        -o takes char parameter as filename to update journal usage
                        journal_fp --> where you would write journal usage in
                        -j loads journal from previous run and replays changes in maze
                        */
                    printf("Enter Maze File:\n> ");
                    scanf("%s",filename);
                    fp = fopen(filename, "r");
                                filename_journal = optarg;
                                journal_fp = fopen(filename_journal, "a+");
                                break;
                        case 'j':
                                printf("\n\t\t\tREPLAYS MAZE UPDATES\n\n");
                    replay_file = optarg;
                    replay_fp = fopen(replay_file, "r");
                    while (journal_contents !=EOF){
                                    printf("%c", journal_contents);
                        journal_contents = getc(replay_fp);
                        }
                    exit(0);
                        }

        }if (fp == NULL){
              printf("\n\nNo MAZE FILE detected.  missing -o ?\nHint: Add -o and create a journal file\n\n");
              exit(0);
              }
        else{
        complete_maze_solver(fp, journal_fp,filename);
        }
  return 0;
}
