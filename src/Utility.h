#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>


/*
	return: accepted username string from the user
*/
char* TakeInputUserName(){

	char user[20];
	printf("enter user name: ");
	scanf(" %s", &user);
	return(user);
}

/*
	return: accepted guessing letter from the user
*/
char TakeInput(){

	char letter;
	printf("guess a letter: ");
	scanf(" %c", &letter);
	return letter;
}


/*
	args: FIlE pointer of listOfWords
	return: current line of the file, ending with '\n'
*/
char* readLine(FILE* fp){

	char word_read[20];
	fscanf(fp, "%s", &word_read);
	return word_read;
}


/*
	args: random word generated from the array
	return: memory allocated for current word. Init to all _(userscores)
*/
char* CreateCurrentWord(char* word){

	char* current_word = (char*)malloc(sizeof(char) * strlen(word));
	strcpy(current_word, word);
	memset(current_word, '_', strlen(current_word));
	return current_word;
}


/*
	args: range: int
	return: return a random int in range
*/
int getRandomInt(int range){

	srand(time(NULL));
	int line_num = rand();
	return line_num % range;
}

/*
	args: letter:char
*/
bool ValidateInput(char letter){

	if (isalpha(letter))
		return true;
	return false;
}


void AlignCenter(){
	printf("\t\t\t\t");
}


void printHangman(){


	printf("\t\t\t\t   ____     \n");
	printf("\t\t\t\t  |    |    \n");
	printf("\t\t\t\t  |    o    \n");
	printf("\t\t\t\t  |   /|\   \n");
	printf("\t\t\t\t  |    |    \n");
	printf("\t\t\t\t  |   / \   \n");
	printf("\t\t\t\t _|_        \n");
	printf("\t\t\t\t|   |______ \n");
	printf("\t\t\t\t|          | \n");
	printf("\t\t\t\t|__________|\n");
}