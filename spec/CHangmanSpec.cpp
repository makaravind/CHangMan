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
			int chances, int chancesleft, int isfileenabled, int numberofwords){

			GameState* gamestate = (GameState*)malloc(sizeof(GameState));

			gamestate->number_words = 0;
			gamestate->listOfWords == NULL;
			strcpy(gamestate->user_name, username);
			gamestate->chances = chances;
			gamestate->chances_left = chances;
			//gamestate->wordToGuess = wordtoguess;
			//gamestate->currentWord = current_word;
			gamestate->wordToGuess = (char*)malloc(sizeof(char) * strlen(wordtoguess));
			strcpy(gamestate->wordToGuess, wordtoguess);

			gamestate->currentWord = (char*)malloc(sizeof(char) * strlen(current_word));
			strcpy(gamestate->currentWord, current_word);

			gamestate->areFilesEnabled = isfileenabled;

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
		[TestMethod, Timeout(1000)]
		void TestGameStates(){

			GameState *actual = CreateGameState("aravind", "___", "car", 10, 10, 0, 0);
			GameState *expected = CreateGameState("aravind", "___", "car", 10, 10, 0, 0);

			CompareGameState(actual, expected);

		}
		
	};
}
