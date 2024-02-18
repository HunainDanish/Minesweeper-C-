#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;


bool t=false;//used for cls
int timeover = 60;//used to time over game
int won = 0;//used if user win
int revealedBoxes = 0;//used for score
const int rows=9;
const int cols=9;
bool mines[rows][cols];//used in valid and mineplacings
char board[rows][cols];//used in inboard to print initial board
int rowin, colin; //used to take input for row and col

time_t startTime;//timer function
struct ScoreRecord //class for file handling
 {
    int rollNumber;
    int highestScore;
};

const int maxScoreRecords = 10;  //max number of users
ScoreRecord scoreRecords[maxScoreRecords];//array for max roll numbers  
int totalScoreRecords = 0; //initialy zero

void startTimer()//time starting from 0 
{
    startTime = time(0);
}

int getElapsedTime() //time calculations
{
    return static_cast<int>(time(0) - startTime);
}
void loadScores() //load scores from where left before
{
    ifstream file("scores.txt");
    if (file.is_open()) {
        file >> totalScoreRecords;
        for (int i = 0; i < totalScoreRecords; ++i) {
            file >> scoreRecords[i].rollNumber >> scoreRecords[i].highestScore;
        }
        file.close();
    }
}


void saveScores() //save the scores to file
{
    ofstream file("scores.txt");
    if (file.is_open()) {
        file << totalScoreRecords << endl;
        for (int i = 0; i < totalScoreRecords; ++i) {
            file << scoreRecords[i].rollNumber << " " << scoreRecords[i].highestScore << endl;
        }
        file.close();
    }
}
void updateScore(int rollNumber, int score) //update rollnumer and score
{
    for (int i = 0; i < totalScoreRecords; ++i) {
        if (scoreRecords[i].rollNumber == rollNumber) {
            if (score > scoreRecords[i].highestScore) {
                scoreRecords[i].highestScore = score;
                cout << "New highest score for roll number " << rollNumber << ": " << score << endl;
            }
            return;
        }
    }

    // If roll number not found, add a new score record
    if (totalScoreRecords < maxScoreRecords) {
        scoreRecords[totalScoreRecords].rollNumber = rollNumber;
        scoreRecords[totalScoreRecords].highestScore = score;
        ++totalScoreRecords;
        cout << "New highest score for roll number " << rollNumber << ": " << score << endl;
    } else {
        cout << "Max score records reached. Cannot add a new record." << endl;
    }
}

void displayScores() //display score
{
    cout << "Scores:\n";
    for (int i = 0; i < totalScoreRecords; ++i) {
        cout << "Roll Number: " << scoreRecords[i].rollNumber << ", Highest Score: " << scoreRecords[i].highestScore << endl;
    }
}
void resetScores() //reset the score
{
    totalScoreRecords = 0;
    saveScores();  
}
void displayLeaderboard()//display leaderboard
 {
    cout << "Leaderboard:\n";
    if (totalScoreRecords == 0) {
        cout << "No scores available.\n";
        return;
    }

    //rank the users
    for (int i = 0; i < totalScoreRecords - 1; ++i) {
        for (int j = 0; j < totalScoreRecords - i - 1; ++j) {
            if (scoreRecords[j].highestScore < scoreRecords[j + 1].highestScore) {
    
                swap(scoreRecords[j], scoreRecords[j + 1]);
            }
        }
    }

    for (int i = 0; i < min(totalScoreRecords, maxScoreRecords); ++i) {
        cout << "Rank " << i + 1 << ": Roll Number " << scoreRecords[i].rollNumber
             << ", Highest Score: " << scoreRecords[i].highestScore << endl;
    }
}


void inboard()//printing initial board 
{
    revealedBoxes = 0; // score 0 at start
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "[] ";
            mines[i][j] = false;//all boxes are false initialy
            board[i][j] = ' ';//spaces
        }
        cout << "\n";
    }
}

void minesplacing() //places mines
{
    int placed = 0;
    int numofmine;
    char y;	
    cout<<"Press Y to customize number of mines, N to play non-customized\n";
    cin>>y;
    if(y=='Y')
    {
    	cout<<"Declare the number of mines\n";
    	cin>>numofmine;
	}
	else if ( y=='N')
	{
		numofmine=10;
	}
    
    while (placed < numofmine) //loop to place mines 
	{
        int randomcol = rand() % cols;//mines on random col
        int randomrow = rand() % rows;//mines on random row
        if (!mines[randomrow][randomcol]) {
            mines[randomrow][randomcol] = true;//mines turning true
            placed++;
        }
    }
}

void minesplacing1() {
    int placed = 0;
    int numofmine;
    char y;
    cout<<"Press Y to customize number of mines, N to play non-customized\n";
    cin>>y;
    if(y=='Y')
    {
    	cout<<"Declare the number of mines\n";
    	cin>>numofmine;
	}
	else if ( y=='N')
	{
		numofmine=10;
	}
    while (placed < numofmine) {
        int randomcol = rand() % cols;
        int randomrow = rand() % rows;
        if (!mines[randomrow][randomcol]) {
            mines[randomrow][randomcol] = true;
            placed++;
        }
    }
}

void minesplacing2() {
    int placed = 0;
    int numofmine;
    char y;
    cout<<"Press Y to customize number of mines, N to play non-customized\n";
    cin>>y;
    if(y=='Y')
    {
    	cout<<"Declare the number of mines\n";
    	cin>>numofmine;
	}
	else if ( y=='N')
	{
		numofmine=10;
	}
    while (placed < numofmine) {
        int randomcol = rand() % cols;
        int randomrow = rand() % rows;
        if (!mines[randomrow][randomcol]) {
            mines[randomrow][randomcol] = true;
            placed++;
        }
    }
}

void display() //The board being displaced
{
    cout << "  ";
    for (int i = 0; i < cols; i++) {
        cout << i << " ";
    }
    cout << "\n";

    for (int i = 0; i < rows; i++) {
        cout << i << " ";
        for (int j = 0; j < cols; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

void valid() {
	
    if (rowin < 0 || colin < 0 || rowin >= rows || colin >= cols) {
        cout << "Invalid Move\n\n";
        t=true;//t is true for cls
        return;
    }
}

int minenumber(int rowin, int colin)//calculating mines on adjacent tiles
 {
    int minecount = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newRow = rowin + i;
            int newCol = colin + j;
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && mines[newRow][newCol]) {
                minecount++;
            }
        }
    }
    return minecount;
}

void show(int rowin, int colin) //showing mines on adjacent tiles 
{
    if (rowin < 0 || colin < 0 || rowin >= rows || colin >= cols) {
        return;
    }

    if (board[rowin][colin] != ' ') {
        
        return;
    }

    int near = minenumber(rowin, colin);
    if (mines[rowin][colin]) {
        board[rowin][colin] = '$';
    } else {
        board[rowin][colin] = near + '0';
        revealedBoxes++;
        won++;
        if (won == rows * cols - 5) {
           // User has revealed all non-mine cells  won
            cout << "Congratulations! You've won!\n";
            exit(0);
        }
        if (near == 0) {
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    // printing on places where adjacent mines are zero
                    if (i != 0 || j != 0) {
                        show(rowin + i, colin + j);
                    }
                }
            }
        }
    }
}

void input() //input for row and col
{
    cout << "\nInput the row and column\n";
    cin >> rowin >> colin;
}

void overreveal() //mine hit and reveal col and row
{
    if (mines[rowin][colin]) {
        cout << "\nGame Over, You hit a mine\n";
        cout << "\nScore " << revealedBoxes << endl; // Add this line
        exit(0);
    } else {
        show(rowin, colin);
    }
}

void clear() //cls function
{
	if(!t)
	{
	
    system("cls");
}
}

void timer()//checking if time is over
 {
    int elapsed = getElapsedTime();
    if (elapsed > timeover) {
        cout << "\nGame over, you ran out of time\n";
        
        exit(0);
    }

    cout << "\nTime elapsed: " << getElapsedTime() << " seconds\n";
}

int main() 
{
	char p,l;
	loadScores();
	int rollNumber;
    cout << "\nEnter your roll number: ";
    cin >> rollNumber;
    srand(time(0));
    char x;
    cout<<"Press L to see leaderboard";
	 		cin>>l;
    
    if(l=='L')
    {
    	displayLeaderboard();
	}
    
    cout << "\nSelect The Difficulty\n";
    cout << "E for Easy\n";
    cout << "M for Medium\n";
    cout << "H for Hard\n";
    cin >> x;
    cout<<"Press P to reset all the scores";
    cin>>p;
        if(p=='P')
    {
    	resetScores();
	}
	system("cls");
	 
    switch (x) {
    case 'E':
        clear();
        inboard();
        minesplacing();
        startTimer();
        while (true) 
		{
         	cout << "\nScore: " << revealedBoxes << endl;
		 	updateScore(rollNumber, revealedBoxes);
        	displayScores();
        	saveScores();   
            timer();
            display();
            input();
            valid();
            overreveal();
            clear();
        }
      
    
        
        return 0;
        break;
    case 'M':
        clear();
        inboard();
        minesplacing1();
        startTimer();
        while (true) {
         	cout << "\nScore: " << revealedBoxes << endl;
		 	updateScore(rollNumber, revealedBoxes);
        	displayScores();
        	saveScores();  
            timer();
            display();
            input();
            valid();
            overreveal();
            clear();
        }
        
        return 0;
        break;
    case 'H':
        clear();
        inboard();
        minesplacing2();
        startTimer();
        while (true) {
         	cout << "\nScore " << revealedBoxes << endl;
		 	updateScore(rollNumber, revealedBoxes);
        	displayScores();
        	saveScores();  
            timer();
            display();
            input();
            valid();
            overreveal();
            clear();
        }
        
        return 0;
        break;
    }

    return 0;
}
