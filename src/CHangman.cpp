#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

/*
	
	Name : Hangman
	Ojective of the game:
		This is simple game which can be played by a two players. You are supposed to build a hangman game
		in which one player is the computer.

		Rules of the game are detailed here : https://www.youtube.com/watch?v=ufw7wr_ZyKc

		How we are going to Design the Game .?

		We are supposed to generate a random word from the collection of words retrived from the file.
		Total chances a user/player gets are 10. User should guess each possible letter and it's 
		index in the word and each word should be checked for it's validity. 
		If user guesses wrong chances decreases else game goes on 
		until user guesses the word or number of chances are decreased to zero.

		// programming detailed (editing)
		Here we user a Ply struture which consists of user name, chances count, generated word
		All funcitons realted to user are in UserUtils.
					  related to game in GameUtil.
		Each blank can be represented by any char other than alphabet

		
		How Game is played :

			<user name>
			number of chances : 10
			number of blank spaces: 5
			<show the word that is guesses by user till now>
			
			input: u 2
			u -> guessed letter 
			2 -> index (starting from 0 obviosuly!)

			<user name>
			number of chances : 0
			number of blank spaces: 2
			<show the word that is guesses by user till now>
			
			print {{ user.name }} you are defeated !
*/
int main()
{
	
	return NULL;
}




