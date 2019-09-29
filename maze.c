#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
FILE* loadFile(char* filename);
char **inputMaze(FILE* fp, int rowCount, int colNum);
int **outputMaze(FILE *fp, int rowCount, int colNum, char **in_maze);
int getRowCount(FILE *fp, char *filename);
int getColCount(FILE *fp, char *filename);
void Print_inMaze(int rows, int col, char **maze);
void Print_outMaze(int rowCount,int colNum, int** out_maze);
void solve_maze(int row, int column, char**in_maze, int** out_maze,FILE* journal_fp, FILE* fp, char filename);
int *get_start_cordinates(char** in_maze,int rows,int columns);
void solve_by_recursion(int x_pos,int y_pos, int **maze_out, int distance,int rows,int columns,FILE*fp);
int isOpen(int testRow,int testCol,int row, int col);
void go_left(int** maze_out, int x_pos, int y_pos, int distance, int rows, int columns,FILE*fp);
void go_right(int** maze_out, int x_pos, int y_pos, int distance, int rows, int columns,FILE*fp);
void step_up(int** maze_out,int x_pos, int y_pos, int distance, int rows, int columns,FILE*fp);
void step_down(int** maze_out, int x_pos, int y_pos, int distance, int rows, int columns,FILE*fp);
void complete_maze_solver(FILE* fp,FILE* journal_fp ,char* filename);
void read_ints(FILE* replay_fp, FILE* fp, char filename, int x_pos, int y_pos, int** maze_out,char** maze_in,int rows, int columns);
void show_results(int row, int columns, int**maze_out);
struct Move{

	int Add,Subtract;

}move = {1,-1};

struct journal_replay{
	bool replay;

}Replay={false};


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

void step_up(int** maze_out, int x_pos, int y_pos, int distance, int rows, int columns,FILE*fp){
   if (maze_out[x_pos-1][y_pos]==-1)
       {
	//Every maze is located somewhere at row 0. Thus creating condition to recognize its exit.
	if (x_pos-1 == 0){
	fprintf(fp,"%d\n\n\n", move.Subtract); //Recall our sturct to record its directions
	++distance;
	maze_out[x_pos-1][y_pos] = distance;
	show_results(rows,columns,maze_out); //Prints out our resulted INT maze with its updated postions the algorithim took and exits program

	}
	else{
	 fprintf(fp,"%d\n", move.Subtract);
         solve_by_recursion(x_pos-1,y_pos, maze_out, distance+1,rows,columns, fp); //Recursively updating our parameters.  Consider lessening # of parameters
       }
}

}
void step_down(int** maze_out, int x_pos, int y_pos, int distance, int rows, int columns,FILE*fp){
    if (maze_out[x_pos+1][y_pos]==-1)
       {
	  fprintf(fp,"%d\n", move.Add);
          solve_by_recursion(x_pos+1,y_pos,maze_out,distance+1,rows,columns,fp);
      }


}
void go_left(int** maze_out, int x_pos, int y_pos, int distance, int rows, int columns,FILE*fp){
 if (maze_out[x_pos][y_pos-1]==-1)
	 {

	 fprintf(fp,"%d\n", move.Subtract);
	 solve_by_recursion(x_pos,y_pos-1,maze_out,distance+1,rows,columns,fp);
       }


}
void go_right(int** maze_out, int x_pos, int y_pos, int distance, int rows, int columns,FILE*fp){


      if (maze_out[x_pos][y_pos+1]==-1)
            {
	      fprintf(fp,"%d\n", move.Add);

              solve_by_recursion(x_pos,y_pos+1,maze_out,distance+1,rows,columns,fp);
            }

}
void solve_by_recursion(int x_pos,int y_pos, int **maze_out, int distance,int rows,int columns,FILE*fp){
/* There are a few things to take into consideration here.
	We have to prevent the algorithim to revist cells,
	update out positions, 
	and give directions on where to move. (In our case that is N. E. S. W.)
*/


//This condition allows the algorithim prevent revisiting previous cells and updating our current maze
int curr_body_pos = maze_out[x_pos][y_pos];
 if (curr_body_pos == -3 || curr_body_pos == -1 ||curr_body_pos < distance){
    maze_out[x_pos][y_pos] = distance;
  }
	//Here are our directions. 
	//Each direction holds a condition to know when a cell is empty or not.
	 step_up(maze_out, x_pos, y_pos, distance,rows, columns, fp);
	 step_down(maze_out, x_pos, y_pos,distance, rows, columns,fp);
	 go_right(maze_out, x_pos, y_pos, distance,rows, columns,fp);
         go_left(maze_out, x_pos, y_pos,distance, rows, columns,fp);

}


void solve_maze(int rows, int columns, char** maze_in, int** maze_out, FILE* journal_fp, FILE* fp, char filename)
{
	/*
	As soon as we reached this function, we grab all the information we need
	 for our general maze from its text file. As you can see, we are calling the .replay var from
	struct to indicate whether or not we are solving the maze with the recursive algorithim or the
	journal itself.
	 */

    int *starting_pos = get_start_cordinates(maze_in, rows, columns);
    int x_pos = starting_pos[0];
    int y_pos = starting_pos[1];

	if (Replay.replay){ //If this is True then solve maze using the journals instructions
		printf("Replaying journal...\n");
		read_ints(journal_fp, fp, filename, x_pos,y_pos,maze_out, maze_in,rows,columns);
		exit(0);

		}else{ //otherwise solve it recursively
    		  solve_by_recursion(x_pos, y_pos, maze_out, 0,rows,columns, journal_fp);
		  fprintf(journal_fp,"\n\n");
     		  printf("\nStaring Position--> x: %d, y: %d\n", x_pos, y_pos);


}

}


void complete_maze_solver(FILE* fp,FILE* journal_fp, char* filename){
	//This is our general maze data that needs to be collected
	int columns = getColCount(fp,filename);
        int rows = getRowCount(fp, filename);
        char** in_maze = inputMaze(fp,rows,columns);
        int** out_maze = outputMaze(fp,rows,columns, in_maze);

	/*Once we have gathered our information,
	 our next method will set up our coordinates to solve 
	for 'training' or 'testing'
	*/
        solve_maze(rows,columns, in_maze,out_maze, journal_fp, fp,filename);

}


void read_ints(FILE* replay_fp, FILE* fp, char filename,int x_pos, int y_pos, int** maze_out,char** maze_in, int rows, int columns){

/*

So now that we have all the general information needed, we are now able to
'solve' the maze using the journal's instructions...

Remember,  -1 --> indicates movement is subtracting row or col
	   +1 --> indicates movement is adding a row or col


for instructions in journal:
	if (instructions == -1):
		Go_left || Go_up if positionIsOpen();
	if (instuctions == 1):
		Go_right || Go_down if positionIsOpen();


*/
int instruction;
char journal_contents;
int distance = 0;
printf("Starting at: xpos: %d, ypos: %d\n\n",x_pos,y_pos);


/*
At this point of our code, as we can clearly see that this code is a bit messy.

Lets try adding function 'Update();' in order to see less code and have it run more effitently.

Meaning, the practice of preventing repeating code.


However, these conditions follow the intructions of our .journal file.
While it is running, we are able to see how our testing maze is being updated accoding to its instructions on
how and where to move.
*/

printf("\n\n\t---Reading Instructions to solve... Please Wait...\n\n");
//While loop reads through entire .journal file as an INT
fscanf(replay_fp, "%d", &instruction);
while(!feof(replay_fp) && journal_contents != EOF){

//Checks neighbors... again,  it is not neccessary to repeat code.
//Create function 'Check_Neighbors();'
int curr_body_pos = maze_out[x_pos][y_pos];
 if (curr_body_pos == -3 || curr_body_pos == -1 ||curr_body_pos < distance){
    maze_out[x_pos][y_pos] = distance;
  }

/*
	if (instruction == -1){
	printf("Checking to go Up or left...\n\n");
	}
	else{
	printf("Checking to go Down or right...\n\n");
	}
*/
	sleep(1);



	if (instruction == -1 && maze_out[x_pos-1][y_pos]==-1 ){
		--x_pos;
		if (x_pos == 0){
		printf("\nSolved! Found exit! At row: %d and col: %d\n\n",x_pos,y_pos);
		Print_inMaze(rows,columns, maze_in);
		exit(0);
		}
		++distance;
		maze_in[x_pos][y_pos] = '*';
		Print_inMaze(rows,columns, maze_in);

		printf("\tDecided to go up at x: %d and y: %d\n\n", x_pos, y_pos);
	}else if (instruction == -1 && maze_out[x_pos][y_pos-1]==-1){
		--y_pos;
		++distance;
		maze_in[x_pos][y_pos] = '*';
		Print_inMaze(rows,columns, maze_in);
		printf("\tDecided to go left at x: %d and y: %d\n\n", x_pos, y_pos);
	}else if (instruction == 1 && maze_out[x_pos][y_pos+1] == -1){
		++y_pos;
		++distance;
		maze_in[x_pos][y_pos] = '*';
		Print_inMaze(rows,columns, maze_in);
		printf("\tDecided to go right at x: %d and y: %d\n\n", x_pos, y_pos);
	}else if(instruction == 1 && maze_out[x_pos+1][y_pos]== -1){
		++x_pos;
		++distance;
		maze_in[x_pos][y_pos] = '*';
		Print_inMaze(rows,columns, maze_in);
		printf("\tDecided to go down at x: %d and y: %d\n\n", x_pos, y_pos);
	}



	fscanf(replay_fp, "%d", &instruction);
	journal_contents = getc(replay_fp); //Allows to detect end of file


   }

	if (x_pos != 0){
		printf("\nJournal Replay could not find exit for this maze.\n\n\tContinue by solve recursively?(1/0)\n\n");
		sleep(2);
	//	solve_by_recursion(x_pos, y_pos, maze_out, 0,rows,columns, replay_fp);         #Clean code before solve recursively
	}

}





void show_results(int row, int columns, int** maze_out){
   printf("SOLVED AND RECORDED\n\n");
   Print_outMaze(row,columns, maze_out);
    exit(0);
}


int main(int argc, char **argv){
  FILE* fp = NULL;
  int chosen_flag;
  char* filename[100];
  char* replay_file;
  char* filename_journal;
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

				filename_journal = optarg;
                                journal_fp = fopen(filename_journal, "a+");

				printf("Enter Maze File To Train With:\n> ");
  				scanf("%s",filename);
  				fp = fopen(filename, "a+");


                                break;

                        case 'j':
			filename_journal = optarg;
			journal_fp = fopen(filename_journal,"r"); //Allows access to journal file
			/*
			Once we take users flag input, we also need to opt the user for
			the new maze to solve using the journals instructions, so lets create that option.

			--> Consider creating a method so we can avoid repetition
			*/
			printf("Enter Maze File To Test With:\n> ");
			scanf("%s",filename);
			fp = fopen(filename, "a+");
			Replay.replay = true;
			complete_maze_solver(fp, journal_fp,filename);
                        }

        }

        complete_maze_solver(fp, journal_fp,filename);


  return 0;
}
