#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include "Utility.h"

#define CHANCES 10

char collectionOfWords[][20] = {  "car", "cash", "laptop", "wallet"  };
int range = 4;


typedef struct GameState{
	
	char listOfWords[50][20]; // 50 words max-len 20
	int number_words;
	char user_name[20];
	char* currentWord;
	char* wordToGuess;
	int chances_left;
	int chances;
	bool areFileEnabled;
};



/*char* PickWord(GameState* gamestate);
char* getWordAtIndex(GameState* gamestate, int index);
char* CreateCurrentWord(char* word);
char* getMessage(int type);
int isPresent(char* word_to_match, char* current_word, char guessed_letter);
void PrintGameState(GameState *GameState);
void LoadWords(GameState* gamestate, int areFileEnabled);
bool isChancesZero(int chances);
bool isWordCompleted(char* word_to_guess, char* current_word);
void updateGame(GameState* gamestate, int index, char guess_letter);
GameState* initGameState(int areFileEnabled, int total_chances);*/




/*
args: gamestate: GameState, areFilesEnables: bool
init listOfWords of gamestate to the loaded words
init total number of words
*/
void LoadWords(GameState* gamestate, bool areFileEnabled){


	if (areFileEnabled == 0){
		// return static words
		memcpy(gamestate->listOfWords, collectionOfWords, sizeof(char) * range * 20);
		gamestate->number_words = 4;
	}
	else if (areFileEnabled == 1){
		// return wrods from file
		FILE * fp = fopen("words.txt", "r");
		int lines = 0;
		char word_read[20];
		if (fp != NULL){
			while (fgets(word_read, sizeof(word_read), fp) != NULL)
				strcpy(gamestate->listOfWords[gamestate->number_words++], word_read);
		}
	}
}


/*
args: gamestate: GameState, index: int
return: word at index
*/
char* getWordAtIndex(GameState* gamestate, int index){
	return gamestate->listOfWords[index];
}



/*
args: gameState: GameState
*/
char* PickWord(GameState* gamestate){

	// get a randome int
	int index = getRandomInt(gamestate->number_words);

	// return the word from list of words
	return getWordAtIndex(gamestate, index);

}


/*
	args: areFileEnabled: bool
			total_chances: int
	return: fabricated GameState 
*/
GameState* initGameState(bool areFileEnabled, int total_chances){

	GameState *gamestate = (GameState*)malloc(sizeof(GameState));

	gamestate->number_words = 0;
	LoadWords(gamestate, areFileEnabled);

	// create the game init 
	strcpy(gamestate->user_name, TakeInputUserName());
	//gamestate->listOfWords = collectionOfWords;
	gamestate->chances = total_chances;
	gamestate->chances_left = total_chances;
	gamestate->wordToGuess = PickWord(gamestate);
	gamestate->currentWord = CreateCurrentWord(gamestate->wordToGuess);
	gamestate->areFileEnabled = areFileEnabled;

	return gamestate;

}
/*
return: -1 if not present else the index of the letter
*/
int isPresent(char* word_to_match, char* current_word, char guessed_letter){

	for (int i = 0; word_to_match[i] != 0; i++){
		if (word_to_match[i] == guessed_letter && current_word[i] == '_')
			return i;
	}
	return -1;
}


/*
update gamesatate according to index
*/
void updateGame(GameState* gamestate, int index, char guess_letter){

	if (index == -1){
		// made a wrong chioce
		gamestate->chances_left -= 1;
	}
	else{
		// made a right choice
		gamestate->currentWord[index] = guess_letter;
	}
}



/*
	args: gamestate: GameState
			guessed_letter: char
	return: is played correct or not: bool
*/
bool PlayMove(GameState* gamestate, char guessed_letter){

	// validate the input
	if (!ValidateInput(guessed_letter))
		return false;

	int index = isPresent(gamestate->wordToGuess, gamestate->currentWord, guessed_letter);
	updateGame(gamestate, index, guessed_letter);
	return true;
}

/*
check if chances zero
*/
bool isChancesZero(int chances){

	if (chances == 0) return 1;
	return NULL;
}


/*
check if word_to_guess matched with current_word
*/
bool isWordCompleted(char* word_to_guess, char* current_word){

	if (strcmp(word_to_guess, current_word) == 0)
		return 2;
	return NULL;
}


/*
	args: gamestate: GameState
	return: bool
*/
bool isGameOver(GameState* gamestate){

	// checking number of chances
	if (isChancesZero(gamestate->chances_left)){
		printf("%s", getMessage(3));
		return true;
	}

	// checking the word if complete
	if (isWordCompleted(gamestate->wordToGuess, gamestate->currentWord)){
		printf("%s", getMessage(4));
		return true;
	}

	// or should game cont..
	return false;
}



/*
	if areFIleEnabled is true, save the game details into leaderGameState.txt
	csv format: username,wordToGuess,chancesleft,currentword
*/
void endGame(GameState *gamestate, int areFileEnabled){

	if (areFileEnabled == 1){
		FILE *fp;
		fp = fopen("leaderGameState.txt", "a");
		if (fp != NULL){
			fprintf(fp, "%s,%s,%d,%s\n", gamestate->user_name, gamestate->wordToGuess, gamestate->chances_left,
				gamestate->currentWord);
			fclose(fp);
		}
		else{
			printf("File not opening..Game is not saved");
		}
	}
	printf("%s", getMessage(2));
}


/*
	print the state of current game play
	eg, Aravind chances left are 10
		c _ _ h
*/
void PrintGameState(GameState *GameState){

	printf("%s\n chances left: %d\n", GameState->user_name, GameState->chances_left);
	for (int i = 0; GameState->currentWord[i] != 0; i++)
		printf("%c ", GameState->currentWord[i]);
	printf("\n");
}