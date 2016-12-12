#include "stdafx.h"
#include "../src/GameUtils.h"
//#include "../src/Utility.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace spec
{
	[TestClass]
	public ref class C15PuzzleSpec
	{
	private:
		TestContext^ testContextInstance;

	public:
		/// <summary>
		///Gets or sets the test context which provides
		///information about and functionality for the current test run.
		///</summary>
		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
		{
			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
			{
				return testContextInstance;
			}
			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
			{
				testContextInstance = value;
			}
		};

#pragma region Additional test attributes

#pragma endregion 

		
		/*
		[TestMethod, Timeout(1000)]
		void TestSub(){

			int a = 2;
			int b = 4;
			Assert::AreEqual(b - a, sub(b, a), "do proper substraction", 1, 2);
		}
		*/


		GameState* CreateGameState(char* username, char *current_word, char *wordtoguess,
			int chances, int chancesleft, int isfileenabled, int numberofwords, char listofwords[50][20]){

			GameState* gamestate = (GameState*)malloc(sizeof(GameState));

			memcpy(gamestate->listOfWords, listofwords, sizeof(char) * range * numberofwords);

			gamestate->number_words = numberofwords;
			gamestate->listOfWords == NULL;
			strcpy(gamestate->user_name, username);
			gamestate->chances = chances;
			gamestate->chances_left = chancesleft;
			gamestate->areFilesEnabled = isfileenabled;
			//gamestate->wordToGuess = wordtoguess;
			//gamestate->currentWord = current_word;

			if (current_word != NULL && wordtoguess != NULL){

				gamestate->wordToGuess = (char*)malloc(sizeof(char) * strlen(wordtoguess));
				strcpy(gamestate->wordToGuess, wordtoguess);

				gamestate->currentWord = (char*)malloc(sizeof(char) * strlen(current_word));
				strcpy(gamestate->currentWord, current_word);
			}

			return gamestate;
		}

		void ValidateGameState(GameState *gamestate){

			if (gamestate == NULL)
				Assert::Fail("gamestate should not be null");

			if (gamestate->currentWord == NULL || gamestate->wordToGuess == NULL)
				Assert::Fail("Accolate memory for string properly");
		}


		void CompareStrings(char *expectedStr, char *actualStr, char* err){

			System::String^ errmsg = gcnew System::String(err);

			int i = 0;
			char NULL_CHAR = '\0';
			while (expectedStr[i] != NULL_CHAR){
				Assert::AreEqual(expectedStr[i], actualStr[i], errmsg, 1, 2);
				i++;
			}
			Assert::AreEqual(expectedStr[i], actualStr[i], errmsg, 1, 2);
		}

		void CheckListOfWords(char actualList[50][20], char expectedList[50][20], int actualNumberOfWords, int expectedNumberOfWords){

			Assert::AreEqual(actualNumberOfWords,expectedNumberOfWords,
			"Number of items in collection of words should match", 1, 2);

			for (int i = 0; i < expectedNumberOfWords; i++){
				CompareStrings(actualList[i], expectedList[i],"load words properly");
			}
			
		}


		void CheckChancesLeft(int actual, int expected){

				Assert::AreEqual(actual, expected,
				"chances left mismatch", 1, 2);
		}


		void CheckCurrentWord(char *actualword, char* expectedword){
		
			CompareStrings(actualword, expectedword, "current word state mis match");
		}


		void CheckGeneratedWord(char *actualword, char* expectedword){

			CompareStrings(actualword, expectedword, "word is not picked correctly");
		}

		void CheckIsFileEnable(int actual, int expected){

			Assert::AreEqual(actual, expected, "isFileEnable is not set properly", 1, 2);
		}

		void CompareGameState(GameState *actual, GameState *expected){
			
			ValidateGameState(actual);
			ValidateGameState(expected);

			CheckListOfWords(actual->listOfWords, expected->listOfWords, actual->number_words, expected->number_words);

			CheckChancesLeft(actual->chances_left, expected->chances_left);

			CheckCurrentWord(actual->currentWord, expected->currentWord);

			CheckGeneratedWord(actual->wordToGuess, expected->wordToGuess);

			CompareStrings(actual->user_name, expected->user_name, "user name is not correct");

			CheckIsFileEnable(actual->areFilesEnabled, expected->areFilesEnabled);
		}




		//tests
		/*[TestMethod, Timeout(1000)]
		void TestGameStates(){

			char exampleWords[50][20] = { "car", "cat" };
			int numberWords = 2;

			GameState *actual = CreateGameState("aravind", "___", "car", 10, 10, 0, 0, exampleWords);
			GameState *expected = CreateGameState("aravind", "___", "car", 10, 10, 0, 0, exampleWords);

			CompareGameState(actual, expected);
		}*/

		// test for picked word
		[TestMethod, Timeout(1000)]
		void TestGetWordAtIndex(){

			char exampleWords[50][20] = { "car", "cat" };
			int numberWords = 2;

			GameState *test = CreateGameState("aravind", NULL, NULL, 10, 10, 0, numberWords, exampleWords);

			char *actual = getWordAtIndex(test, 0);
			char *expected = "car";

			CompareStrings(expected, actual, "word is not generated properly");
		}

		[TestMethod, Timeout(1000)]
		void TestGetWordAtIndexNegIndex(){

			char exampleWords[50][20] = { "car", "cat" };
			int numberWords = 2;

			GameState *test = CreateGameState("aravind", NULL, NULL, 10, 10, 0, numberWords, exampleWords);

			char *actual = getWordAtIndex(test, -1);
			char *expected = "";

			CompareStrings(expected, actual, "function should return an empty string");
		}
		
		[TestMethod, Timeout(1000)]
		void TestGetWordAtIndexIndexOutOfBounds(){
			
			char exampleWords[50][20] = { "car", "cat" };
			int numberWords = 2;

			GameState *test = CreateGameState("aravind", NULL, NULL, 10, 10, 0, numberWords, exampleWords);

			char *actual = getWordAtIndex(test, 2);
			char *expected = "";
			
			CompareStrings(expected, actual, "Handle index out of bounds condition");
		}


		//test isGameOver
		// cases : chances == 0, word complete, 
		[TestMethod, Timeout(1000)]
		void TestIsGameOverZeroChancesLeft(){

			char exampleWords[50][20] = { "car", "cat" };
			int numberWords = 2;

			char* testCurrentWord = "ca_";
			char* testGeneratedWord = "car";

			int chances_left = 0;

			GameState *test = CreateGameState("aravind", testCurrentWord, testGeneratedWord, 
				10, chances_left, 0, numberWords, exampleWords);

			bool actual = isGameOver(test);
			bool expected = 1;

			Assert::AreEqual(expected, actual, "Chances left game end conditions are not tested properly", 1, 2);
		}

		[TestMethod, Timeout(1000)]
		void TestIsGameOverWordCompleted(){

			char exampleWords[50][20] = { "car", "cat" };
			int numberWords = 2;

			char* testCurrentWord = "car";
			char* testGeneratedWord = "car";

			int chances_left = 3;

			GameState *test = CreateGameState("aravind", testCurrentWord, testGeneratedWord,
				10, chances_left, 0, numberWords, exampleWords);

			bool actual = isGameOver(test);
			bool expected = 1;

			Assert::AreEqual(expected, actual, "Word finished game end conditions are not tested properly", 1, 2);
		}


		[TestMethod, Timeout(1000)]
		void TestIsGameOverFalse(){

			char exampleWords[50][20] = { "car", "cat" };
			int numberWords = 2;

			char* testCurrentWord = "c_r";
			char* testGeneratedWord = "car";

			int chances_left = 3;

			GameState *test = CreateGameState("aravind", testCurrentWord, testGeneratedWord,
				10, chances_left, 0, numberWords, exampleWords);

			bool actual = isGameOver(test);
			bool expected = 0;

			Assert::AreEqual(expected, actual, "Game should not end this way", 1, 2);
		}

		//test update Game
		[TestMethod, Timeout(1000)]
		void TestUpdateGameRight(){

			char exampleWords[50][20] = { "car", "cat" };
			int numberWords = 2;

			char* testCurrentWordBefore = "c__";
			char* testGeneratedWord = "car";

			int chances_leftBefore = 3;

			GameState *testBefore = CreateGameState("aravind", testCurrentWordBefore, testGeneratedWord,
				10, chances_leftBefore, 0, numberWords, exampleWords);

			updateGame(testBefore, 1, 'a');


			char* testCurrentWordAfter = "ca_";
			int chances_leftAfter = 3;
			GameState *testAfter = CreateGameState("aravind", testCurrentWordAfter, testGeneratedWord,
				10, chances_leftAfter, 0, numberWords, exampleWords);

			CompareGameState(testBefore, testAfter);
		}

		[TestMethod, Timeout(1000)]
		void TestUpdateGameWrong(){

			char exampleWords[50][20] = { "car", "cat" };
			int numberWords = 2;

			char* testCurrentWordBefore = "c__";
			char* testGeneratedWord = "car";

			int chances_leftBefore = 3;

			GameState *testBefore = CreateGameState("aravind", testCurrentWordBefore, testGeneratedWord,
				10, chances_leftBefore, 0, numberWords, exampleWords);

			updateGame(testBefore, -1, 'z');

			char* testCurrentWordAfter = "c__";
			int chances_leftAfter = 2;
			GameState *testAfter = CreateGameState("aravind", testCurrentWordAfter, testGeneratedWord,
				10, chances_leftAfter, 0, numberWords, exampleWords);

			CompareGameState(testBefore, testAfter);
		}

		// test isPresent
		// wrong index, -1, ispresent 1
		[TestMethod, Timeout(1000)]
		void TestIsPresentPostive(){


			char exampleWords[50][20] = { "car", "cat" };
			int numberWords = 2;

			char* testCurrentWord = "c_r";
			char* testGeneratedWord = "car";

			int chances_left = 3;

			GameState *test = CreateGameState("aravind", testCurrentWord, testGeneratedWord,
				10, chances_left, 0, numberWords, exampleWords);

			int actual = isPresent(test, 'a');
			int expected = 1;

			Assert::AreEqual(expected, actual, "index of letter mismatch", 1, 2);
		}

		[TestMethod, Timeout(1000)]
		void TestIsPresentNot(){

			char exampleWords[50][20] = { "car", "cat" };
			int numberWords = 2;

			char* testCurrentWord = "c_r";
			char* testGeneratedWord = "car";

			int chances_left = 3;

			GameState *test = CreateGameState("aravind", testCurrentWord, testGeneratedWord,
				10, chances_left, 0, numberWords, exampleWords);

			int actual = isPresent(test, 'n');
			int expected = -1;

			Assert::AreEqual(expected, actual, "index of letter mismatch", 1, 2);
		}


		[TestMethod, Timeout(1000)]
		void TestIsPresentWrongIndex(){

			char exampleWords[50][20] = { "car", "cat" };
			int numberWords = 2;

			char* testCurrentWord = "c__";
			char* testGeneratedWord = "car";

			int chances_left = 5;

			GameState *test = CreateGameState("aravind", testCurrentWord, testGeneratedWord,
				10, chances_left, 0, numberWords, exampleWords);

			int actual = isPresent(test, 'r');
			int expected = 2;

			Assert::AreEqual(expected, actual, "index of letter mismatch", 1, 2);
		}



	};
}
