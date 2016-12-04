#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "UserUtils.h"

typedef struct Ply{

	User user;
	char* g_word;
	int chances;
	int len_word; // (test) kept if used a lot
	char* word;
};

/*
Generate a random word from the collection of words in the file
*/
char* PickWord(){

	return NULL;
}


/*
	intialize the Ply with username and word and chances.
	Get user at the start of the game itself.
*/
void InitGame(User new_user){
	
}



/*
	After each guess of the word check whether the word is completed or not.
*/
bool VerifyWord(){

}



/*
	Take input from the user
*/
void Guessing(char letter, int index){


}