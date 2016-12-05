#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CHANCES 10


typedef struct board{

	char* user_name;
	char* guess_word;
	int chances;
	int len_word; // (test) kept if used a lot
	char* word;
};

/*
Generate a random word from the collection of words in the file
*/
char* PickWord(){

	// open the file
	/*FILE *fp = fopen("words.txt", "r");
	int num_words = 0;
	
	fscanf(fp, "%d", &num_words);
	// generate a random number
	srand(time(NULL));
	int r = rand();
	printf("%d", r % num_words);

	//fseek to the line numer to retriev word
	fseek(fp, r + 1, SEEK_SET);
	char *word = NULL;
	fscanf(fp, "%s", &word);
	printf("%s", word);*/

	return "cat";
}

/*
	intialize the board with username and word and chances.
	Get user at the start of the game itself.
*/
board *InitGame(char* user_name){
	
	board* new_board = (board*)malloc(sizeof(board));
	char *game_word = PickWord();
	
	new_board->user_name = user_name;
	new_board->chances = CHANCES;
	new_board->len_word = strlen(game_word);
	new_board->word = (char*)malloc(sizeof(char) * strlen(game_word));
	new_board->guess_word = (char*)malloc(sizeof(char) * strlen(game_word));
	
	strcpy(new_board->guess_word, game_word);
	memset(new_board->guess_word, '_', strlen(new_board->guess_word));
	strcpy(new_board->word, game_word);
	return new_board;
}


/*
	End the game by storing the details into a file for leader board purpose
	(for now) Saving all the user details
*/
void EndGame(board *board){

	FILE *fp;
	fp = fopen("leaderboard.txt", "a");
	if (fp != NULL){
		fprintf(fp, "%s,%d,%s\n", board->user_name, board->chances, board->guess_word);
		fclose(fp);
	}
	else{
		printf("File not opening..Game is not saved");
	}
	printf("Thank you for playing this game! Please come back!");
}


/*
	After each guess of the word check whether the word is completed or not.
*/
bool VerifyWord(board *board){

	bool flag = true;
	for (int i = 0; board->guess_word[i] != 0; i++){
		if (board->guess_word[i] == '_'){
			flag = false;
			break;
		}
	}
	return flag;
}



/*
	Take input from the user
*/
int Check(board *board, char letter){

	int flag = false;
	for (int i = 0; board->word[i] != 0; i++){
		if (board->word[i] == letter){
			board->guess_word[i] = letter;
			flag = true;
		}
	}
	return flag;
}


void Printboard(board *board){

	printf("%s\n chances left: %d\n", board->user_name, board->chances);
	for (int i = 0; board->guess_word[i] != 0; i++)
		printf("%c ", board->guess_word[i]);
	printf("\n");
}