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
	bool areFilesEnabled;
};


/*
args: gamestate: GameState, areFilesEnables: bool
init listOfWords of gamestate to the loaded words
init total number of words
*/
void LoadWords(GameState* gamestate, bool areFilesEnabled){


	if (areFilesEnabled == 0){
		// return static words
		memcpy(gamestate->listOfWords, collectionOfWords, sizeof(char) * range * 20);
		gamestate->number_words = 4;
	}
	else if (areFilesEnabled == 1){
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
return empty string for any exception conditions
*/
char* getWordAtIndex(GameState* gamestate, int index){

	if (index < 0 || gamestate->number_words-1 < index) return "";

	char* word =  gamestate->listOfWords[index];

	if (word == NULL) return "";
	return word;
}



/*
args: gameState: GameState
*/
char* pickWord(GameState* gamestate){

	// get a randome int
	int index = getRandomInt(gamestate->number_words);

	// return the word from list of words
	return getWordAtIndex(gamestate, index);

}


/*
	args: areFilesEnabled: bool
			total_chances: int
	return: fabricated GameState 
*/
GameState* initGameState(bool areFilesEnabled, int total_chances, char* user_name){

	GameState *gamestate = (GameState*)malloc(sizeof(GameState));

	gamestate->number_words = 0;
	LoadWords(gamestate, areFilesEnabled);

	// create the game init 
	strcpy(gamestate->user_name, user_name);
	//gamestate->listOfWords = collectionOfWords;
	gamestate->chances = total_chances;
	gamestate->chances_left = total_chances;
	gamestate->wordToGuess = pickWord(gamestate);
	gamestate->currentWord = CreateCurrentWord(gamestate->wordToGuess);
	gamestate->areFilesEnabled = areFilesEnabled;

	return gamestate;

}
/*
return: -1 if not present else the index of the letter
*/
int isPresent(GameState *gamestate, char guessed_letter){

	for (int i = 0; gamestate->wordToGuess[i] != 0; i++){
		if (gamestate->wordToGuess[i] == guessed_letter && gamestate->currentWord[i] == '_')
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
		AlignCenter();
		printf("not present..try agian!\n");
		gamestate->chances_left -= 1;
	}
	else{
		// made a right choice
		AlignCenter();
		printf("good one!\n");
		gamestate->currentWord[index] = guess_letter;
	}
}



/*
	args: gamestate: GameState
			guessed_letter: char
	return: is played correct or not: bool

	first validate the user input, return false if not valid.
	check where the guessed letter is present in the word
	and update the GameState accordingly and return true.

*/
bool PlayMove(GameState* gamestate, char guessed_letter){

	// validate the input
	if (!ValidateInput(guessed_letter))
		return false;

	int index = isPresent(gamestate, guessed_letter);
	updateGame(gamestate, index, guessed_letter);
	return true;
}

/*
check if chances zero
*/
bool isChancesZero(GameState *gamestate){

	if (gamestate->chances_left == 0) return 1;
	return 0;
}


/*
check if word_to_guess matched with current_word
*/
bool isWordCompleted(GameState *gamestate){

	if (strcmp(gamestate->wordToGuess, gamestate->currentWord) == 0)
		return 1;
	return 0;
}


/*
	args: gamestate: GameState
	return: bool

	check if number of chances reached zero 
	or if whole word is guessed right then return true
	else return false
*/
bool isGameOver(GameState* gamestate){

	// checking number of chances
	if (isChancesZero(gamestate)){
		AlignCenter();
		printf("%s", "Game lost!\n");
		return true;
	}

	// checking the word if complete
	if (isWordCompleted(gamestate)){
		AlignCenter();
		printf("%s", "Game won!\n");
		return true;
	}

	// or should game cont..
	return false;
}



/*
	if areFilesEnabled is true, save the game details into leaderGameState.txt
	csv format: username,wordToGuess,chancesleft,currentword
*/
void endGame(GameState *gamestate, int areFilesEnabled){

	if (areFilesEnabled == 1){
		FILE *fp;
		fp = fopen("leaderGameState.txt", "a");
		if (fp != NULL){
			fprintf(fp, "%s,%s,%d,%s\n", gamestate->user_name, gamestate->wordToGuess, gamestate->chances_left,
				gamestate->currentWord);
			fclose(fp);
		}
		else{
			AlignCenter();
			printf("File not opening..Game is not saved");
		}
	}


//	_getch();
	system("cls");
	printHangman();
	AlignCenter();
	printf("Thank you for playing, %s :)", gamestate->user_name);
}


/*
	print the state of current game play
	eg, Aravind chances left are 10
		c _ _ h
*/
void PrintGameState(GameState *GameState){

	system("cls");
	AlignCenter();
	printf("Welcome to HangManC\n");

	AlignCenter();
	printf("chances left: %d\n", GameState->chances_left);

	AlignCenter();
	for (int i = 0; GameState->currentWord[i] != 0; i++)
		printf("%c ", GameState->currentWord[i]);
	printf("\n");
}