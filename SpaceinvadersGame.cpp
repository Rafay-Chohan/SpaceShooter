#include<iostream>
#include<stdlib.h>
#include<fstream>//Library for file handling
#include<conio.h>//Library used for getch() function
#include<windows.h>//Library used for Handle Function
#include<dos.h>//Library used for sleep function
using namespace std;

#define scrnWidth 80//Setting screen width for border, can be changed and program will automatically adjust everything else
#define scrnHeight 20//Setting screen height for border, can be changed and program will automatically adjust everything else
#define gameWidth 63//Setting game screen width, can be changed and program will automatically adjust everything else
#define boardWidth 17//Setting scoreboard width, can be changed and program will automatically adjust everything else
#define leftGapScrn 6//space of gap on the left side of the border
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//Using handle function
COORD CursorPosition;
char ship[3][3] = { ' ','^',' ',47,' ',92,45,45,45 };//Storing ship in Array
int alienRow[2];//Container to store Row/Y-axis of 2 aliens
int alienCol[2];//Container to store column/X-axis of 2 aliens
bool alienLifeCheck[2];//flag check for checking number of on screen aliens alive
int shipXpos = boardWidth + leftGapScrn + (gameWidth / 2);//Setting ship position with respect to the border and game screen defined 
int bullets[20][4];//containers for bullet path
int bulletMaxRow[20];//max range of bullet path
int bulletIndex = 0;//index of bullet for column/X axis of bullet
int points = 0;//In game Points(1-50)
int stage = 1;//In game stage(5 total)
int lifecount = 3;
void moveCursor(int col, int row) {//Function for repositioning cursor
	CursorPosition.X = col;
	CursorPosition.Y = row;
	SetConsoleCursorPosition(hStdOut, CursorPosition);
}
void printShip(int number) {//Function to print the ship stored in the array
	for (int i = 0; i < 3; i++) {
		cout << "\t|\t\t|";
		for (int j = 0; j < 30 + number; j++)
			cout << " ";
		SetConsoleTextAttribute(hStdOut, 6);
		for (int k = 0; k < 3; k++) {
			cout << ship[i][k];
		}
		SetConsoleTextAttribute(hStdOut, 7);
		for (int l = 0; l < 30 - number; l++)
			cout << " ";

		cout << "|";
		cout << endl;
	}

	cout << "\t|\t\t|\t\t\t\t\t\t\t\t|" << endl;

}
void printBorder(int number,int scr,int l) {//Function to Print the border with respect to the values given above
	cout << "\t";
	for (int i = 0; i < scrnWidth; i++)
		cout << "_";
	cout << endl;

	for (int i = 0; i < scrnHeight; i++)
		cout << "\t|\t\t|\t\t\t\t\t\t\t\t|" << endl;


	printShip(number);//Caling the function to print ship


	cout << "\t";
	for (int i = 0; i < scrnWidth; i++)
		cout << "_";
	SetConsoleTextAttribute(hStdOut, 6);//Changing Colors
	moveCursor(9, 8);
	cout << "Life: " << lifecount;//Printing current Points
	moveCursor(9, 9);
	cout << "POINTS: " << scr;//Printing current Points
	moveCursor(9, 10);
	cout << "STAGE: " << l;//Printing current stage
	moveCursor(9, 13);
	SetConsoleTextAttribute(hStdOut, 9);//Changing Colors
	cout << "A,D/Arrow(move)";//Printing instructions
	moveCursor(9, 14);
	cout << "SPACEBAR(SHOOT)";
	moveCursor(9, 16);
	SetConsoleTextAttribute(hStdOut, 10);//Changing Colors
	cout << "Each level will";
	moveCursor(9, 17);
	cout << "increase enemy";
	moveCursor(9, 18);
	cout << "speed";
	SetConsoleTextAttribute(hStdOut, 7);//Changing Colors
}
void makeAlien(int number) {//Function to generate alien randomly along column/X-axis
	alienCol[number] = 23 + rand() % (gameWidth);
	if (alienCol[number] <= 24 || alienCol[number] >= 85) {
		makeAlien(number);
	}
}
void drawAlien(int number) {//Function to draw Alien
	if (alienLifeCheck [number] == true) {
		SetConsoleTextAttribute(hStdOut, 6);//Changing Colors
		moveCursor(alienCol[number], alienRow[number]); cout << "   ";
		moveCursor(alienCol[number], alienRow[number]+1);   cout << "^--^";
		moveCursor(alienCol[number], alienRow[number] + 2); cout << "('')";
		moveCursor(alienCol[number], alienRow[number] + 3); cout << " vv ";
		SetConsoleTextAttribute(hStdOut, 7);//Changing Colors
	}
}
void removeAlien(int number) {//Function to remove alien 
	if (alienLifeCheck[number] == true) {
		moveCursor(alienCol[number], alienRow[number]); cout << "    ";
		moveCursor(alienCol[number], alienRow[number] + 1); cout << "    ";
		moveCursor(alienCol[number], alienRow[number] + 2); cout << "    ";
		moveCursor(alienCol[number], alienRow[number] + 3); cout << "    ";
	}
}
void resetAlien(int number) {//function to replace alien with new alien
	removeAlien(number);//calling function to remove old alien
	alienRow[number] = 4;
	makeAlien(number);//calling function to make new alien
}
void makeBullet() {//Funtion to make bullets with respect to the placement of ship
	bullets[bulletIndex][0] = 19;
	bullets[bulletIndex][1] = shipXpos;
	bullets[bulletIndex][2] = 19;
	bullets[bulletIndex][3] = shipXpos + 4;
	bulletIndex++;
	if (bulletIndex == 20)
		bulletIndex = 0;
}
void moveBullet() {//Position to move the bullets along row/Y-axis
	for (int i = 0; i < 20; i++) {
		if (bullets[i][0] > 2)
			bullets[i][0]--;
		else
			bullets[i][0] = 0;

		if (bullets[i][2] > 2)
			bullets[i][2]--;
		else
			bullets[i][2] = 0;
	}
}
void printBullets() {//function to print bullets on the respect place
	for (int i = 0; i < 20; i++) {
		if (bullets[i][0] > 1) {
			moveCursor(bullets[i][1], bullets[i][0]); cout << ".";
			moveCursor(bullets[i][3], bullets[i][2]); cout << ".";
		}
	}
}
void replaceBullets() {//function to replace old bullets with spaces
	for (int i = 0; i < 20; i++) {
		if (bullets[i][0] >= 1) {
			moveCursor(bullets[i][1], bullets[i][0]); cout << " ";
			moveCursor(bullets[i][3], bullets[i][2]); cout << " ";
		}
	}
}
void removeBullet(int i) {//function to remove bullets
	moveCursor(bullets[i][1], bullets[i][0]); cout << " ";
	moveCursor(bullets[i][3], bullets[i][2]); cout << " ";
}
bool impact() {//Function to check impact between ship and alien
	if (alienRow[0]+4 > 21) {//Condition for first alien
		if (alienCol[0] + 4 - shipXpos >= 0 && alienCol[0] + 4 - shipXpos <=7) {
			resetAlien[0];
			return 1;
		}
	}
	if (alienRow[1]+4 > 21) {//Condition for second alien
		if (alienCol[1] + 4 - shipXpos >= 0 && alienCol[1] + 4 - shipXpos <=7) {
			resetAlien[1];
			return 1;
		}
	}
	return 0;
}
int bulletImpact() {//Function to check if bullet hit alien
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 4; j ++) {
			if (bullets[i][j] != 0) {//Nested conditions for first alien
				if (bullets[i][j] >= alienRow[0] && bullets[i][j] <= alienRow[0] + 4) {
					if (bullets[i][j + 1] >= alienCol[0] && bullets[i][j + 1] <= alienCol[0] + 4) {
						removeBullet(i);//calling function to remove bullet in case of impact
						bullets[i][j] = 0;
						resetAlien(0);//calling function to reset alien in case of impact
						return 1;
					}
				}
				if (bullets[i][j] >= alienRow[1] && bullets[i][j] <= alienRow[1] + 4) {//Nested conditions for second alien
					if (bullets[i][j + 1] >= alienCol[1] && bullets[i][j + 1] <= alienCol[1] + 4) {
						removeBullet(i);//calling function to remove bullet in case of impact
						resetAlien(1);
						bullets[i][j] = 0;//calling function to reset alien in case of impact
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

void start(int &num) {//Function that starts the game
	shipXpos = boardWidth + leftGapScrn + (gameWidth / 2);
	alienLifeCheck[0] = 1;
	alienLifeCheck[1] = 1;
	alienRow[0] = alienRow[1] = 4;
	for (int r = 0; r < 20; r++) {
		bullets[r][0] = bullets[r][1] = 0;
	}
	printBorder(0,points,stage);//Calling function to build border
	makeAlien(0);//Calling function to randomly generate alien along column/x-axis
	makeAlien(1);//Calling function to randomly generate alien along column/x-axis
	int R = 1, L = -1;
	char ch = 0;
	while (1)
	{
		if (_kbhit()) {//Condition to check if any key button has been pressed
			ch = _getch();
			if (ch == 'd' || ch == 'D' || ch == 77) {//Condition for right direction
				if (R < 30) {
					moveCursor(0, 0);
					printBorder(R, points, stage);//Calling function to update screen
					L = R - 1;
					R++;
					shipXpos = shipXpos + 1;//Updating ship position
				}
				else if (R == 31) {
					moveCursor(0, 0);
					printBorder(R - 1, points, stage);//Calling function to update screen

				}

			}

			if (ch == 'a' || ch == 'A' || ch == 75) {//Condition for right direction
				if (L > (-30))
				{
					moveCursor(0, 0);
					printBorder(L, points, stage);//Calling function to update screen
					R = L + 1;
					L--;
					shipXpos = shipXpos - 1;//Updating ship position
				}
				else if (L == (-31))
				{
					moveCursor(0, 0);
					printBorder(L, points, stage);//Calling function to update screen

				}

			}
			if (ch == 32) {//condition for spacebar i.e shooting button
				makeBullet();//calling function to make bullets
				moveCursor(0, 0);
				printBorder(L + 1, points, stage);//Calling function to update screen
			}
		}
			drawAlien(0);//Calling function to draw first alien
			drawAlien(1);//Calling function to draw second alien
			printBullets();//Calling function to draw bullets
			if (impact() == 1) {//Condition for game over in case of impact between ship and alien
				lifecount = lifecount - 1;
				if (lifecount == 0) {
					system("cls");//Clearing screen
					SetConsoleTextAttribute(hStdOut, 11);//Changing Colors
					cout << "\n\n\n\t\t\t---------------------------\n";
					cout << "\t\t\t|         GAME OVER       |\n";
					cout << "\t\t\t|    Your Points were: "<<points<<"  |\n";
					cout << "\t\t\t|    Your Stage was: " << stage << "    |\n";
					cout << "\t\t\t|    Previous high:" << num << "      | \n";
					cout << "\t\t\t---------------------------\n";
					SetConsoleTextAttribute(hStdOut, 7);//Changing Colors
					if (points > num) {//Updating highest score
						num = points;
					}
					Sleep(500);
					return;
				}
			}
			if (bulletImpact() == 1) {//Condition to check impact between bullets and alien
				points++;//Updating Points
				SetConsoleTextAttribute(hStdOut, 6);//Changing Colors
				moveCursor(9, 9);
				cout << "POINTS: " << points;
				moveCursor(9, 10);
				cout << "STAGE: " << stage;
				SetConsoleTextAttribute(hStdOut, 7);//Changing Colors
			}
			if (stage == 1) {//Condition for stage 1 speed
				Sleep(400);
			}
			if (points >= 10 && points<20) {//Condition for stage 2 speed
				stage = 2;
				Sleep(300);
			}
			if (points >=20 && points < 30) {//Condition for stage 3 speed
				stage = 3;
				Sleep(200);
			}
			if (points >=30 && points < 40) {//Condition for stage 4 speed
				stage = 4;
				Sleep(150);
			}
			if (points >=40) {//Condition for stage 5 speed
				stage = 5;
				Sleep(100);
			}
			if (points >= 50)//Condition for completing the game in case of reaching 50 points
			{
				system("cls");
				SetConsoleTextAttribute(hStdOut, 11);//Changing Colors
				cout << "\n\n\n\t\t\t-----------------------------\n";
				cout << "\t\t\t|      CONGRATULATION        |\n";
				cout << "\t\t\t|    YOU ACHIEVED 50 Points  |\n";
				cout << "\t\t\t|    Previous high:"<<num<<"         | \n";
				cout << "\t\t\t-----------------------------\n";
				SetConsoleTextAttribute(hStdOut, 7);//Changing Colors
				if (points > num) {//Updating highest score
					num = points;
				}
				Sleep(500);
				return;
			}
			removeAlien(0);//Removing old alien 1
			removeAlien(1);//Removing old alien 2
			replaceBullets();//replacing old bullets with spaces
			moveBullet();

			if (alienLifeCheck[0] == 1)
				alienRow[0] += 1;

			if (alienLifeCheck[1] == 1)
				alienRow[1] += 1;

			if (alienRow[0] > scrnHeight ) {
				resetAlien(0);
			}
			if (alienRow[1] > scrnHeight ) {
				resetAlien(1);
			}
	}
}

int main() {
	char high[10] = { 0 };
	int highscore = 0;
	ifstream inFile;
	inFile.open("HighScore.txt");//Opening input file saved in the same directory
	if (!inFile)
	{
		fstream File;
		File.open("HighScore.txt", ios::out);//Creating File incase none is found
		ofstream outFile;
		outFile.open("HighScore.txt");
		outFile << highscore;
		outFile.close();
		if (!File) {
			cout << "Highest score file not found\n";//Output if file is not found
			system("pause");
			return 0;
		}
	}
	inFile >> high;//Entering Previous Highest Score
	highscore = atoi(high);//Converting into int
	int option;
		system("cls");
		SetConsoleTextAttribute(hStdOut, 3);//Changing Colors
		cout << "\n\n\n\t\t\t-------------------------\n";
		cout << "\t\t\t|      WELCOME TO       |\n";
		cout << "\t\t\t|     Space Shooter	|\n";
		cout << "\t\t\t-------------------------\n";
	SetConsoleTextAttribute(hStdOut, 9);//Changing Colors
	cout << "\n\n\t\t\tBy\n\t\t\tAbdul Rafay(21L-5497)";
	SetConsoleTextAttribute(hStdOut, 8);//Changing Colors
	cout << "\n\t\t\tPress 1 to play \n\t\t\tPress 0 to exit\n\t\t\t";
	SetConsoleTextAttribute(hStdOut, 7);//Changing Colors
	cin>>option;

	if (option == 1)
	{

		system("cls");
		start(highscore);//Starting game when user presses 1
	}
	else {
		system("pause");
		return 0;
	}
	cout << "\n\n";
	ofstream outFile;
	outFile.open("HighScore.txt");
	outFile << highscore;//Updating Score in File
	inFile.close();
	outFile.close();
	Sleep(500);
	return 0;
}
