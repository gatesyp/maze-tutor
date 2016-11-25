/*
   COPYRIGHT (C) 20YY Student Name (UANET ID) All rights reserved.
   CSI project 2 and 3 - Blind Dead
   Author.  Your name
   Version. 1.01 MM.DD.20YY.
   Purpose: Place a description here...
*/
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<cctype>
using std::cout;
using std::cin;
using std::endl;
using std::fstream;

//gameArray indicies
//gameArray[0] = players current room
const int CURRENT_ROOM_INDEX = 0;
//gameArray[1] = current room of zombie
const int ZOMBIE_ROOM_INDEX = 1;
//gameArray[2]
const int NUM_BULLETS_INDEX = 2;
//gameArray[3]
const int NUM_ROOMS_INDEX = 3;
//boolean whether player has grail or not
const int HAVE_GRAIL_INDEX = 4;

//roomArray indices
//roomArray[gameArray[CURRENT_ROOM_INDEX]][4] = 1 or 0 if the player is
//	or is not in the current room
const int PLAYER_INDEX = 4;
//roomArray[gameArray[ZOMBIE_ROOM_INDEX]][5] = 1, tracks where the zombie is
const int ZOMBIE_INDEX = 5;
//roomArray[room][6] = the room that the grail is in should be marked 1, all others 0
const int GRAIL_INDEX = 6;
// the number of rooms and number of bullets to fend off the zombies
const int MAX_ROOMS = 11;
const int MAX_BULLETS = 6;

//PART 1A prototypes
//reset simply resets the primary game variables
void reset(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail);
//print game instructions
void instructions();
//print layout of game memory
void printMemory(int gameArray[],int roomArray[][7]);
// the menu (which calls functions printMemory and instructions)
bool menu(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int gameArray[],int roomArray[][7]);

//PART 1B prototypes
//read in the input file for the map
void readMaze(int roomArray[][7], int gameArray[5]);
//return a random room
int getRandomRoom(int gameArray[5]);
//place the zombie
void placeZombie(int roomArray[][7], int gameArray[5]);
//place the grail
void placeGrail(int roomArray[][7], int gameArray[5]);
// the setup function
void setup(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int roomArray[][7], int gameArray[5]);

//PART 2 prototypes

//PART 3 prototypes

int main()
{
	// these variables are passed throughout this program
	int roomArray[MAX_ROOMS][7] = {0},
	    gameArray[5] = {0},
	    currentRoom = 0,
        zombieRoom = 0,
        numBullets = 0,
        numRooms = 0,
        menuSelection = 0;
        bool menuBool;
   bool haveGrail = false;
   gameArray[0] = currentRoom;
   gameArray[1] = zombieRoom;
   gameArray[2] = numBullets;
   gameArray[3] = numRooms;
   gameArray[4] = menuSelection;

    menuBool = menu(currentRoom, zombieRoom, numBullets, numRooms, haveGrail, gameArray,roomArray);


	return 0;
}




// build your functions here. Don't forget your pre and post conditions
void reset(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail)
{
    currentRoom = 0;
    zombieRoom = 0;
    numBullets = 0;
    numRooms = 0;
    haveGrail = false;
}

void instructions()
{
    cout << "YOUR MISSION, SHOULD YOU CHOOSE TO ACCEPT IT, IS TO SEEK THE HOLY"
    <<"\nGRAIL WITHIN THE RUINS OF AN ANCIENT CHURCH. TO SUCCEED YOU MUST\n"
    <<"ENTER THE CHURCH, AVOID THE UNDEAD GUARDIANS, FIND THE GRAIL AND"
    <<"\nESCAPE. YOU HAVE SIX SILVER BULLETS TO PROTECT YOU. IF THE ZOMBIES\n"
    <<"FIND YOU OR YOU RUN OUT OF BULLETS YOU WILL LOSE!" << endl << endl;
}

void printMemory(int gameArray[],int roomArray[][7])
{

    cout << "Game Array:\n  [current][bullets][  rooms]\n"
         << "  [      " << gameArray[0] << "][      " << gameArray[1] << "][      " << gameArray[2] << "]\n";
    cout << "Room Array:\n  [ north][ south][  west][  east][player][zombie][ grail]\n";
    for (int i = 0; i < MAX_ROOMS; i++)
    {
        cout << "  [R" << i + 1
         << "]  ->[     " << roomArray[i][0] << "][     " << roomArray[i][1] << "][     " << roomArray[i][2] << "][     " << roomArray[i][3] << "][     " << roomArray[i][4] << "][     " << roomArray[i][5] << "][     " << roomArray[i][6] << "]" <<endl;
    }
    cout << endl;
}


bool menu(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int gameArray[],int roomArray[][7])
{
    int bruh;
    bool loopflag = true;
    cout << "       Enter, If you dare...           \n"
         << "*** THE TOMB OF THE BLIND DEAD ***" << endl;

    do
        {
    cout <<"     Main Menu\n1. Instructions\n2. Being\n3. Exit" << endl << endl;
    cout <<"Enter menu Selection: ";

    cin >> bruh;

    if(bruh == 1)
    {
        instructions();
    }
    if(bruh == 2)
    {
        printMemory(gameArray, roomArray);
    }
    if(bruh == 3)
    {
        return 0;
    }
        }while(loopflag);



}

void readMaze(int roomArray[][7], int gameArray[5])
{
    std::ifstream in;
    in.open("easyMaze.txt");

    in >> gameArray[3];

}

