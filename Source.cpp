/*
Title: Assognment-5
Author: Leyalee Alsaadi
Objective: To use loading and sacing to a file by creating the game of Hangman
*/

#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>

using namespace std;

int menu();
void gotoXcoorYcoor(int xCoor, int yCoor);
void playGame();
void credits();
void showScores();
void bodyPart(int counter);

int main() {
	//boolean value that continues to run the main menu until the user quits
	bool running = true;

	int option = menu();

	while (running) {
		

		if (option == 1) {
			playGame();
		}
		else if (option == 2) {
			credits();
		}
		else if (option == 3) {
			showScores();
		}
		else if (option == 4) {
			exit(0);
		}

		option = menu();
	}
	

	system("pause");
	return 0;
}

//if the user enters 3 then the file with the scores will be opened,
//read in, and then the scores will be displayed to the user on the 
//console window
void showScores() {
	int option;

	ifstream scores;
	scores.open("highscores.txt");

	if (!scores.fail()) {
		while (!scores.eof()) {

			string score;

			getline(scores, score);

			cout << score << endl;
		}

		scores.close();
	}

	cout << "1. Return to menu: ";
	cin >> option;

	while (option != 1) {
		cout << "Hit 1 to return to the menu: ";
		cin >> option;
	}

	system("cls");
}

//menu function that displays the different options to the user
//makes sure the user enters a valid option
int menu() {
	int option = 0;

	gotoXcoorYcoor(53, 0);
	cout << "WELCOME" << endl;
	gotoXcoorYcoor(55, 1);
	cout << "To" << endl;

	//prints out the hangman
	gotoXcoorYcoor(48, 2);
	cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)201 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)187 << endl;
	gotoXcoorYcoor(48, 3);
	cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << endl;
	gotoXcoorYcoor(48, 4);
	cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)79 << endl;
	gotoXcoorYcoor(48, 5);
	cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)47 << (char)179 << (char)92 <<  endl;
	gotoXcoorYcoor(48, 6);
	cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)47 << (char)255 << (char)92 << endl;
	gotoXcoorYcoor(48, 7);
	cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << endl;
	gotoXcoorYcoor(48, 8);
	cout << (char)205 << (char)205 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)255 << endl;

	gotoXcoorYcoor(52, 9);
	cout << "HANGMAN" << endl;

	gotoXcoorYcoor(52, 10);
	cout << "~MENU~" << endl;
	gotoXcoorYcoor(48, 11);
	cout << "1. Play Game" << endl;
	gotoXcoorYcoor(48, 12);
	cout << "2. Credits" << endl;
	gotoXcoorYcoor(48, 13);
	cout << "3. Show Highscores" << endl;
	gotoXcoorYcoor(48, 14);
	cout << "4. Quit" << endl;
	gotoXcoorYcoor(48, 15);
	cout << "Option: ";
	cout << " ";
	cin >> option;


	while (option < 1 || option > 4) {
		gotoXcoorYcoor(48, 16);
		cout << "Enter a Valid Option: ";
		cin >> option;
	}

	system("CLS");

	return option;
}

//function that displays something based on the x and y coordinates passed into it
void gotoXcoorYcoor(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void playGame() {
	srand(time(0));

	//randomized index to choose the word from the dictionary vector
	int wordIndex;
	//string variable that will hold the word chosen
	string gameWord;
	//vector that holds all of the words read in from the dictionary
	vector<string> Dictionary;
	//vector that holds the word that need sto be guessed
	vector<string> guessWord;
	//vector that holds the letters that the user has guessed already
	vector<char> guessedLetters;
	//char variable that holds the letter guessed by the user
	char guessedLetter;
	//number of guesses the user has
	int counter = 6;
	//counts how many guesses the user gets right
	int rightGuess = 0;
	//boolean value to check whether the guesses letter was right or wrong
	bool rightOrWrong = false;
	//bollean value for a character that has already been guessed
	bool alreadyGuessed = false;
	//holds the highscore of the player and starts it off at 100000
	int highScore = 600;
	//string to hold the players name
	string playerName;
	//int to hold in the option user enters to go back to main menu
	int option;

	//reads in all of the words from the dictionary and pushes them back into a vector
	ifstream dictionary;
	dictionary.open("Dictionary.txt");

	if (!dictionary.fail()) {
		while (!dictionary.eof()) {

			string tempWord;

			getline(dictionary, tempWord);

			Dictionary.push_back(tempWord);
		}

		dictionary.close();
	}

	//selects what index to choose the word from and assigns it to gameWord
	wordIndex = rand() % (Dictionary.size() + 1);
	gameWord = Dictionary[wordIndex];

	//prints out the hangman post
	gotoXcoorYcoor(48, 2);
	cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)201 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)187 << endl;
	gotoXcoorYcoor(48, 3);
	cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << endl;
	gotoXcoorYcoor(48, 4);
	cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << endl;
	gotoXcoorYcoor(48, 5);
	cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << endl;
	gotoXcoorYcoor(48, 6);
	cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << endl;
	gotoXcoorYcoor(48, 7);
	cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << endl;
	gotoXcoorYcoor(48, 8);
	cout << (char)205 << (char)205 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)255 << endl;

	//cout << "Size of word: " << gameWord.length() << endl;

	//cout << "The Game Word is: " << gameWord << endl;

	cout << "Enter Your Name: ";
	cin >> playerName;

	gotoXcoorYcoor(45, 0);
	cout << "Welcome " << playerName << "!" << endl;

	//prints out the empty spaces for the letters of the chosen word
	gotoXcoorYcoor(45, 10);
	for (int i = 0; i < gameWord.length(); i++) {
		guessWord.push_back("_ ");
		cout << guessWord[i];
	}
	cout << endl;

	//loops through the game until the user runs out of guesses
	while (counter != 0) {
		rightOrWrong = false;

		gotoXcoorYcoor(45, 12);
		cout << "Guess a letter:  ";
		gotoXcoorYcoor(61, 12);
		cout << "  ";
		gotoXcoorYcoor(61, 12);
		cin >> guessedLetter;

		//goes through a vector containing already guessed letters to make sure
		//that the user does not guess it again
		for (int i = 0; i < guessedLetters.size(); i++) {
			if (guessedLetters[i] == guessedLetter) {
				alreadyGuessed = true;
			}
		}

		while (alreadyGuessed) {
			gotoXcoorYcoor(45, 12);
			cout << "Repeated Letter:  ";
			gotoXcoorYcoor(61, 12);
			cout << " ";
			cin >> guessedLetter;

			alreadyGuessed = false;

			for (int i = 0; i < guessedLetters.size(); i++) {
				if (guessedLetters[i] == guessedLetter) {
					alreadyGuessed = true;
				}
			}
		}
		//pushes the guessed letter into a vector
		guessedLetters.push_back(guessedLetter);

		//shows what letters have already been guessed
		gotoXcoorYcoor(45, 17);
		cout << "Letters Guessed : " << endl;

		gotoXcoorYcoor(45, 18);
		for (int i = 0; i < guessedLetters.size(); i++) {
			cout << guessedLetters[i] << " ";
		}

		//goes through the word to see if the gussed letter matches any letters in the word 
		//increases the user's score if they guess a right letter
		for (int i = 0; i < gameWord.length(); i++) {
			if (guessedLetter == gameWord[i]) {
				guessWord[i] = guessedLetter;
				rightGuess++;
				highScore += 100;
				rightOrWrong = true;
			}
		}
		
		//if the user didn't guess a right letter their score goes down and a body part is drawn
		if (rightOrWrong == false) {
			counter--;
			highScore -= 100;
		}

		//calls the function to draw a body part if a wrong guess was made
		bodyPart(counter);

		//goes through the vector with the empty spaces and replaces them with a letter if it was a right guess
		gotoXcoorYcoor(45, 10);
		for (int i = 0; i < guessWord.size(); i++) {
			cout << guessWord[i] << " ";
		}
		cout << endl;

		//if the user runs out of turns then they were hung
		if (counter == 0) {
			gotoXcoorYcoor(45, 14);
			cout << "You Were Hung!" << endl;
			gotoXcoorYcoor(45, 15);
			cout << "The Word was: " << gameWord;
		}

		//if the user guesses all of the right letters then they survive
		gotoXcoorYcoor(45, 13);
		if (rightGuess == gameWord.length()) {
			cout << "You Survived!" << endl;
			counter = 0;
		}

		//shows how many guesses the user has left
		gotoXcoorYcoor(45, 16);
		cout << "Number Guesses Left: " << counter << endl;		
	}

	//shows the user their score at the end
	gotoXcoorYcoor(45, 20);
	cout << playerName << " Score is: " << highScore << endl;

	//writes the user's score to a file
	ofstream HighScores;
	HighScores.open("highscores.txt", fstream::out | fstream::app);

	if (!HighScores.fail()) {
		HighScores << playerName << " " << highScore << endl;

		HighScores.close();
	}

	//takes the user back to the main menu when they hit 1
	gotoXcoorYcoor(45, 22);
	cout << "1. Return to menu: ";
	cin >> option;

	while (option != 1) {
		gotoXcoorYcoor(45, 22);
		cout << "Hit 1 to return to the menu: ";
		cin >> option;
	}

	system("cls");
} 

//shows credits to the user
void credits() {
	int option;

	cout << "Title: HANGMAN" << endl;
	cout << "Author: Leyalee Alsaadi" << endl;
	cout << "This game of Hangman was used to help us better understand how to\n use file loading and saving" << endl;

	cout << "1. Return to menu: ";
	cin >> option;

	while (option != 1) {
		cout << "Hit 1 to return to the menu: ";
		cin >> option;
	}

	system("cls");
}


//depending what the counter is, a certain body part will be printed out
void bodyPart(int counter) {
	if (counter == 5) {
		gotoXcoorYcoor(48, 2);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)201 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)187 << endl;
		gotoXcoorYcoor(48, 3);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << endl;
		gotoXcoorYcoor(48, 4);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)79 << endl;
		gotoXcoorYcoor(48, 5);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << endl;
		gotoXcoorYcoor(48, 6);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << endl;
		gotoXcoorYcoor(48, 7);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << endl;
		gotoXcoorYcoor(48, 8);
		cout << (char)205 << (char)205 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)255 << endl;
	}
	else if (counter == 4) {
		gotoXcoorYcoor(48, 2);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)201 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)187 << endl;
		gotoXcoorYcoor(48, 3);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << endl;
		gotoXcoorYcoor(48, 4);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)79 << endl;
		gotoXcoorYcoor(48, 5);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)179 << (char)255 << endl;
		gotoXcoorYcoor(48, 6);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << endl;
		gotoXcoorYcoor(48, 7);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << endl;
		gotoXcoorYcoor(48, 8);
		cout << (char)205 << (char)205 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)255 << endl;
	}
	else if (counter == 3) {
		gotoXcoorYcoor(48, 2);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)201 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)187 << endl;
		gotoXcoorYcoor(48, 3);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << endl;
		gotoXcoorYcoor(48, 4);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)79 << endl;
		gotoXcoorYcoor(48, 5);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)47 << (char)179 << (char)255 << endl;
		gotoXcoorYcoor(48, 6);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << endl;
		gotoXcoorYcoor(48, 7);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << endl;
		gotoXcoorYcoor(48, 8);
		cout << (char)205 << (char)205 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)255 << endl;
	}
	else if (counter == 2) {
		gotoXcoorYcoor(48, 2);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)201 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)187 << endl;
		gotoXcoorYcoor(48, 3);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << endl;
		gotoXcoorYcoor(48, 4);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)79 << endl;
		gotoXcoorYcoor(48, 5);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)47 << (char)179 << (char)92 << endl;
		gotoXcoorYcoor(48, 6);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << endl;
		gotoXcoorYcoor(48, 7);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << endl;
		gotoXcoorYcoor(48, 8);
		cout << (char)205 << (char)205 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)255 << endl;
	}
	else if (counter == 1) {
		gotoXcoorYcoor(48, 2);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)201 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)187 << endl;
		gotoXcoorYcoor(48, 3);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << endl;
		gotoXcoorYcoor(48, 4);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)79 << endl;
		gotoXcoorYcoor(48, 5);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)47 << (char)179 << (char)92 << endl;
		gotoXcoorYcoor(48, 6);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)47 << (char)255 << (char)255 << endl;
		gotoXcoorYcoor(48, 7);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << endl;
		gotoXcoorYcoor(48, 8);
		cout << (char)205 << (char)205 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)255 << endl;
	}
	else if (counter == 0) {
		gotoXcoorYcoor(48, 2);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)201 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)187 << endl;
		gotoXcoorYcoor(48, 3);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << endl;
		gotoXcoorYcoor(48, 4);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)79 << endl;
		gotoXcoorYcoor(48, 5);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)47 << (char)179 << (char)92 << endl;
		gotoXcoorYcoor(48, 6);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)47 << (char)255 << (char)92 << endl;
		gotoXcoorYcoor(48, 7);
		cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)186 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << endl;
		gotoXcoorYcoor(48, 8);
		cout << (char)205 << (char)205 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)255 << endl;
	}
}