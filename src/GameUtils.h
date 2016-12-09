#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

#define CHANCES 10

char collectionOfWords[][20] = { "car", "cat", "cash", "wallet"  };
int range = 4;


typedef struct GameState{
	
	char listOfWords[50][20]; // 50 words max-len 20
	int number_words;
	char user_name[20];
	char* currentWord;
	char* wordToGuess;
	int chances_left;
	int chances;
	int difficulty;
};

char* TakeInputUserName(){

	char user[20];
	printf("enter user name: ");
	scanf(" %s", &user);
	return(user);
}

char* PickWord(GameState* gamestate);
char* CreateCurrentWord(char* word);

char* readLine(FILE* fp){

	char word_read[20];
	fscanf(fp, "%s", &word_read);
	return word_read;
}

void LoadWords(GameState* gamestate, int difficulty){

	
	if (difficulty == 0){
		// return static words
		memcpy(gamestate->listOfWords, collectionOfWords, sizeof(char) * range * 20);
		gamestate->number_words = 4;
	}
	else if (difficulty == 1){
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

GameState* initGameState(int difficulty, int total_chances){

	GameState *gamestate = (GameState*)malloc(sizeof(GameState));
	
	gamestate->number_words = 0;
	LoadWords(gamestate, difficulty);

	// create the game init 
	strcpy(gamestate->user_name, TakeInputUserName());
	//gamestate->listOfWords = collectionOfWords;
	gamestate->chances = total_chances;
	gamestate->chances_left = total_chances;
	gamestate->wordToGuess = PickWord(gamestate);
	gamestate->currentWord = CreateCurrentWord(gamestate->wordToGuess);
	gamestate->difficulty = difficulty;

	return gamestate;

}


char* CreateCurrentWord(char* word){

	char* current_word = (char*)malloc(sizeof(char) * strlen(word));
	strcpy(current_word, word);
	memset(current_word, '_', strlen(current_word));
	return current_word;
}

int getRandomInt(int range){

	srand(time(NULL));
	int line_num = rand();
	return line_num % range;
}

char* getWordAtIndex(GameState* gamestate, int index){

	// gamestate->listwords[index];
	return collectionOfWords[index];
}


/*
considering only alpha characters
*/

char TakeInput(){

	char letter;

	printf("guess a letter: ");
	scanf(" %c", &letter);

	if (isalpha(letter))
		return letter;

	return NULL;

}


/*
Generate a random word from the collection of words in the file
*/
// test cases: empty string, time elapse 
char* PickWord(GameState* gamestate){

	int index = getRandomInt(gamestate->number_words);

	return getWordAtIndex(gamestate, index);
	
}

bool ValidateInput(char letter){

	if (isalpha(letter))
		return true;
	return false;
}

int isPresent(char* word_to_match, char guessed_letter){

	for (int i = 0; word_to_match[i] != 0; i++){
		if (word_to_match[i] == guessed_letter)
			return i;
	}
	return -1;
}


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


bool PlayMove(GameState* gamestate, char guessed_letter){

	if (!ValidateInput(guessed_letter))
		return false;

	int index = isPresent(gamestate->wordToGuess, guessed_letter);
	updateGame(gamestate, index, guessed_letter);
	return true;
}

bool isChancesZero(int chances){

	if (chances == 0) return 1;
	return NULL;
}

bool isWordCompleted(char* word_to_guess, char* current_word){

	if (strcmp(word_to_guess, current_word) == 0)
		return 2;
	return NULL;
}

int isGameOver(GameState* gamestate){

	int status;

	status = isChancesZero(gamestate->chances_left);
	if (status != NULL)
		status = isWordCompleted(gamestate->wordToGuess, gamestate->currentWord);

	if (status != NULL)
		return status;
	else
		return 3; // game should conti.
}


char* PrintMessage(int type){

	if (type == 1){
		// welcome message
		return "Welcome to HangMan";
	}
	else if (type == 2){

		// end game message
		return "thanks for playing";
	}
	else
		return NULL;

}



/*
End the game by storing the details into a file for leader GameState purpose
(for now) Saving all the user details

saving details to leaderGameState
*/
// testcaase : NUll GameState, GameState values != null
void endGame(GameState *gamestate, int difficulty){

	if (difficulty == 1){
		FILE *fp;
		fp = fopen("leaderGameState.txt", "a");
		if (fp != NULL){
			fprintf(fp, "%s,%d,%s\n", gamestate->user_name, gamestate->chances_left, gamestate->currentWord);
			fclose(fp);
		}
		else{
			printf("File not opening..Game is not saved");
		}
	}
	PrintMessage(2);
}




/*
	After each guess of the word check whether the word is completed or not.
*/
bool VerifyWord(GameState *GameState){

	bool flag = true;
	for (int i = 0; GameState->currentWord[i] != 0; i++){
		if (GameState->currentWord[i] == '_'){
			flag = false;
			break;
		}
	}
	return flag;
}


// tc: own GameState check word format, check GameState
void PrintGameState(GameState *GameState){

	printf("%s\n chances left: %d\n", GameState->user_name, GameState->chances_left);
	for (int i = 0; GameState->currentWord[i] != 0; i++)
		printf("%c ", GameState->currentWord[i]);
	printf("\n");
}