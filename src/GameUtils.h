#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CHANCES 10


typedef struct Ply{

	//User user;
	char* user_name;
	char* g_word;
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
	intialize the Ply with username and word and chances.
	Get user at the start of the game itself.
*/
Ply *InitGame(char* user_name){
	
	Ply* new_ply = (Ply*)malloc(sizeof(Ply));
	char *game_word = PickWord();
	
	new_ply->user_name = user_name;
	new_ply->chances = CHANCES;
	new_ply->len_word = strlen(game_word);
	new_ply->word = (char*)malloc(sizeof(char) * strlen(game_word));
	new_ply->g_word = (char*)malloc(sizeof(char) * strlen(game_word));
	
	strcpy(new_ply->g_word, game_word);
	memset(new_ply->g_word, '_', strlen(new_ply->g_word));
	strcpy(new_ply->word, game_word);
	return new_ply;
}



/*
	After each guess of the word check whether the word is completed or not.
*/
bool VerifyWord(Ply *ply){

	bool flag = true;
	for (int i = 0; ply->g_word[i] != 0; i++){
		if (ply->g_word[i] == '_'){
			flag = false;
			break;
		}
	}
	return flag;
}



/*
	Take input from the user
*/
int Check(Ply *ply, char letter){

	int flag = false;
	for (int i = 0; ply->word[i] != 0; i++){
		if (ply->word[i] == letter){
			ply->g_word[i] = letter;
			flag = true;
		}
	}
	return flag;
}


void PrintPly(Ply *ply){

	printf("%s\n %s\n chances left: %d\n", ply->user_name, ply->g_word, ply->chances);
}