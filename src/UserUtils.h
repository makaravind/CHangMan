#include <string.h>
#include <stdio.h>
#include<malloc.h>
#include <stdlib.h>

#define NAME_LEN 20

/*
Used to Store Name and His MovesCount , It will be later be used to generate High Scores Table
*/
typedef struct User{
	char *name;
};


/*
Create the user from Heap , Assign name to user->name , Make movesCount as 0.
Return the user .
*/
User* createUser(char *name){

	User *new_user = (User*)malloc(sizeof(User));
	// max length of name = 20
	new_user->name = (char*)malloc(sizeof(char) * NAME_LEN);
	strcpy(new_user->name, name);
	return new_user;
}
