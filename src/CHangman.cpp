#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<ctype.h>
#include "GameUtils.h"

/*
	Designed by Aravind M
	Name : HangmanC
	Ojective of the game:
		This is simple game which can be played by a two players. You are supposed to build a hangman game
		in which one player is the computer.

		Rules of the game are detailed here : https://www.youtube.com/watch?v=ufw7wr_ZyKc

		How we are going to Design the Game .?

		The game design has 2 ways of loading the words.
			1) static words, areFilesEnabled = 0
			2) loaded from a file, areFilesEnabled = 1

		We are supposed to generate a random word from an array of words.
		Total chances a user/player gets are vary. User should guess each possible letter
		each word should be checked for it's validity. 
		If user guesses wrong chances decreases else game goes on 
		until user guesses the word or number of chances are decreased to zero.

		// programming details
		struture of GameState
		GameState{

			char listOfWords[50][20]; // 50 words max-len 20
			int number_words; // number of words in lisOfWords
			char user_name[20]; // username of the player
			char* currentWord; //current state of the word guessed by player
			char* wordToGuess; //Generated word 
			int chances_left; 
			int chances; // total number of chances
			int areFilesEnabled;
		};


		How Game is played :

			<user name>
			number of chances : 10
			<show the word that is guesses by user till now>
			
			input: u
			u -> guessed letter 
			
			...
			<user name>
			number of chances : 0
			<show the word that is guesses by user till now>
			
			print {{ user.name }} you are defeated !

			Rest directions are detailed at reach function.
*/

int main()
{

	AlignCenter();
	printf("Welcome to HangManC\n");

	// Init the Game State
	GameState *gamestate = initGameState(0, 10);

	char letter = 0;
	int play_move_status = -1;

	// print inti state of the game
	PrintGameState(gamestate);
	printf("hello, %s\n", gamestate->user_name);


	while (true)
	{
		
		if (isGameOver(gamestate))
			break;

		letter = TakeInput();

		play_move_status = PlayMove(gamestate, letter);
		if (play_move_status == false){
			printf("Wrong input\n");
			continue;
		}

		printf("press any key to continue...");
		_getch();
		PrintGameState(gamestate);
	}

	endGame(gamestate, gamestate->areFilesEnabled);
	_getch();
}




