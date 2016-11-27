
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
#include<string>
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


// helper function to convert string to int -- couldnt get c++11 to work for stoi
int toint(std::string s) //The conversion function
{
    return atoi(s.c_str());
}
//PART 1A prototypes
//reset simply resets the primary game variables
void reset(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail);
//print game instructions
void instructions();
//print layout of game memory
void printMemory(int gameArray[],int roomArray[][7]);
// the menu (which calls functions printMemory and instructions)
bool menu(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int gameArray[],int roomArray[][7], bool &win);

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
void setup(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int roomArray[][7], int gameArray[5], bool &win);

int winOrLose(int roomArray[][7], int gameArray[5], bool &haveGrail);

void showConnectedRooms(int roomArray[][7], int gameArray[5]);

bool isConnected(int roomArray[][7], int gameArray[5], int choice);

void moveRoom(int roomArray[][7], int gameArray[5], int choice, bool &haveGrail, bool &win);

void moveZombie(int roomArray[][7], int gameArray[5]);

bool validateSelection(char bruh[]);

void running(int roomArray[][7], int gameArray[5], bool &win, bool &haveGrail, int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms);

void checkRoom(int roomArray[][7], int gameArray[5], bool &win, bool &haveGrail);

void waitForMove(int roomArray[][7], int gameArray[5], bool &win, bool &haveGrail);
void doSelection(int roomArray[][7], int gameArray[5], char str[], bool &win, bool &haveGrail);




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
        bool win = false;
        bool menuBool;
   bool haveGrail = false;
   gameArray[0] = currentRoom;
   gameArray[1] = zombieRoom;
   gameArray[2] = numBullets;
   gameArray[3] = numRooms;
   gameArray[4] = menuSelection;

    menuBool = menu(currentRoom, zombieRoom, numBullets, numRooms, haveGrail, gameArray,roomArray, win);

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
         << "  [      " << gameArray[0] << "][      " << gameArray[1] << "][      " << gameArray[3] << "]\n";
    cout << "Room Array:\n          [ north][ south][  west][  east][player][zombie][ grail]\n";
    for (int i = 0; i < MAX_ROOMS; i++)
    {
        cout << "  [R" << i + 1
         << "]  ->[     " << roomArray[i][0] << "][     " << roomArray[i][1] << "][     " << roomArray[i][2] << "][     " << roomArray[i][3] << "][     " << roomArray[i][4] << "][     " << roomArray[i][5] << "][     " << roomArray[i][6] << "]" <<endl;
    }

    //cout << endl << roomArray[10][5];
    cout << endl;
}


bool menu(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int gameArray[],int roomArray[][7], bool &win)
{
    int bruh;
    bool loopflag = true;
    cout << "       Enter, If you dare...           \n"
         << "*** THE TOMB OF THE BLIND DEAD ***" << endl;

    do
        {
    bool loopFlag = true;
    cout <<"     Main Menu\n1. Instructions\n2. Begin\n3. Exit" << endl << endl;
    cout <<"Enter menu Selection: ";

    cin >> bruh;

    cout << endl ;

    if(bruh == 1)
    {
        instructions();
    }
    if(bruh == 2)
    {
        setup(currentRoom, zombieRoom, numBullets, numRooms, haveGrail, roomArray, gameArray, win);
       break;

    }
    if(bruh == 3)
    {
        return 0;
    }}while(loopflag);




}

void readMaze(int roomArray[][7], int gameArray[5])
{
    std::ifstream in;
    in.open("easyMaze.txt");

    in >> gameArray[3];

    for(int h = 0; h < 11; h++)
    {
        for(int p = 0; p < 7; p++)
        {
            in >> roomArray[h][p];
        }
    }





}

/*int getRandomRoom(int gameArray[5]);
{




}*/

int getRandomRoom(int gameArray[5])
{
    // return number from 1 to MAX_ROOMS
    int xRan;

	xRan=rand()%(MAX_ROOMS - 1)+1; // Randomizing the number between 1-15.
    return xRan;

}

void placeZombie(int roomArray[][7], int gameArray[5])
{
    int randx = getRandomRoom(gameArray);
    while(randx < 6)
    {
        randx = getRandomRoom(gameArray);
    }
    roomArray[randx][5] = 1;

}

void placeGrail(int roomArray[][7], int gameArray[5]){
    int randomRoom = getRandomRoom(gameArray);
    while(randomRoom < 6)
    {
        randomRoom = getRandomRoom(gameArray);
    }
    roomArray[randomRoom][GRAIL_INDEX] = 1;
}

void setup(int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms, bool &haveGrail, int roomArray[][7], int gameArray[5], bool &win)
{
        srand( time(0));
        gameArray[0] = 1;
        currentRoom = 1;
        gameArray[1] = MAX_BULLETS;
        numBullets = MAX_BULLETS;
        haveGrail = false;
        roomArray[0][4] = 1;

        readMaze(roomArray, gameArray);
        placeZombie(roomArray, gameArray);
        placeGrail(roomArray, gameArray);
        running(roomArray, gameArray, win, haveGrail, currentRoom, zombieRoom, numBullets, numRooms);
}

bool checkZombie(int index, int roomArray[][7])
{
    return (roomArray[index - 1][ZOMBIE_INDEX] == 1);
}

bool checkGrail(int index, int roomArray[][7])
{
    return (roomArray[index - 1][GRAIL_INDEX] == 1);
}

int winOrLose(int roomArray[][7], int gameArray[5], bool &haveGrail)
{
    if(gameArray[0] == 1 && haveGrail == true)
    {
        gameArray[0] = -1;
        return 0;
    }
    if( gameArray[0] == gameArray[1])
    {
        gameArray[0] = -1;
        return 1;
    }

    return 2;
}



bool checkNearZombie(int index, int roomArray[][7])
{
    for(int q = 0; q < 4; q++)
    {
        if(roomArray[index][q] != 0)
        {
            if(roomArray[roomArray[index][q] - 1][5] == 1)
            {
                return true;
            }
        }
    }

    return false;
}
bool checkNearGrail(int index, int roomArray[][7])
{
    for(int q = 0; q < 4; q++)
    {
        if(roomArray[index][q] != 0)
        {
            if(roomArray[roomArray[index][q] - 1][GRAIL_INDEX] == 1)
            {
                return true;
            }
        }
    }

    return false;
}

void showConnectedRooms(int roomArray[][7], int gameArray[5])
{
    //int temp = gameArray[0];

    for(int q = 0; q < 4; q++)
    {
        if(roomArray[gameArray[0]][q] != 0)
        {
            cout << roomArray[gameArray[0]][q] << " is a connected room. ";
        }
    }
    cout << endl;
}

bool isConnected(int roomArray[][7], int gameArray[5], int choice)
{


    for(int q = 0; q < 4; q++)
    {
     //   cout << roomArray[gameArray[0]][q] << "****************";
        if(roomArray[gameArray[0]][q] == choice)
        {
            return true;
        }
    }
    return false;

}

void moveRoom(int roomArray[][7], int gameArray[5], int choice, bool &haveGrail, bool &win)
{
    int achoice = choice;
    --choice;
        if (isConnected(roomArray, gameArray, achoice) == 1)
            {

               // roomArray[choice][5] = 1;
                  for (int c = 0; c < 11; c++)
                    {
                        roomArray[c][4] = 0;
                    }
                    roomArray[choice][4] = 1;

                       gameArray[0] = choice;


                if(haveGrail == true)
                {
                    for (int c = 0; c < 11; c++){
                        roomArray[c][6] = 0;
                    }
                    roomArray[choice][6] = 1;
                }

                if(checkGrail(achoice, roomArray) == true)
                {
                    haveGrail = true;
                }
                if(achoice == 1 && haveGrail == true)
                    win = true;

            }

       else if (isConnected(roomArray, gameArray, achoice) != 1)
            {
                cout << "You cannot move there." << endl;
            }

}

void shootRoom(int roomArray[][7], int gameArray[5], int choice)
{
    if(gameArray[1] > 0)
    {
    gameArray[1] -= 1;
    for(int q = 0; q < 4; q++)
    {
        if(roomArray[gameArray[0]][q] != 0)
        {
            if(roomArray[gameArray[0]][q] == choice)
            {
                if(checkZombie(choice, roomArray))
                {
                    roomArray[choice - 1][ZOMBIE_INDEX] = 0;
                    cout << "You have SLAIN the ZOMBIE!" << endl;
                    return;
                }
                else
                {
                    cout << "COMPLETE MISS. FAILURE." << endl;
                    return;
                }
            }
        }
    }
    cout << "You cannot shoot a room that isn't adjacent to yours." << endl;
}
    else
        cout << "You have no bullets left." << endl;
}

bool randomBool() {
  return rand() % 2 == 1;
}

void moveZombie(int roomArray[][7], int gameArray[5])
{
    int found = 0;

    for(int s = 0; s < 11; s++)
    {
        if(roomArray[s][5] == 1)
        {
            for(int q = 0; q < 4; q++)
            {
                if(roomArray[s][q] != 0)
                {
                    if(found == rand() % 4)
                    {
                        roomArray[s][5] = 0;
                        roomArray[roomArray[s][q] - 1][5] = 1;
                        return;
                    }
                    found += 1;
                }
            }
            for(int q = 0; q < 4; q++)
            {
                if(roomArray[s][q] != 0)
                {
                    roomArray[s][5] = 0;
                    roomArray[roomArray[s][q] - 1][5] = 1;
                    return;
                }
            }
        }
    }
}

bool validateSelection(char bruh[])
{

        return true;
    cout << "Please enter a valid command" << endl << endl;
    return false;
}

void doSelection(int roomArray[][7], int gameArray[5], char str[], bool &win, bool &haveGrail)
{
    std::string myStr(str);
    myStr = myStr.substr(1, 2);
    int x = toint(myStr);
    //int x = std::stoi(myStr);
    if(str[0] == 'Q' || str[0] == 'q')
        gameArray[0] = -1;
    if(str[0] == 'D' || str[0] == 'd')
        printMemory(gameArray, roomArray);
    if(str[0] == 'M' || str[0] == 'm')
    {
        moveRoom(roomArray, gameArray, x, haveGrail, win);
        moveZombie(roomArray, gameArray);
    }
    if(str[0] == 'S' || str[0] == 's')
    {
        shootRoom(roomArray, gameArray, x);
        moveZombie(roomArray, gameArray);
    }

}

void waitForMove(int roomArray[][7], int gameArray[5], bool &win, bool &haveGrail)
{
    bool loopFlag= false;
    char bruh[50] = {0};
    do{
    cout << "Please choose a command" << endl << "Q-Quit Game\nD-Print Memory\nS#-Shoot in # room\nM#-Move in # room" << endl;
    cin >> bruh;
    cout << endl;
    loopFlag = validateSelection(bruh);
    }while(!loopFlag);
    doSelection(roomArray, gameArray, bruh, win, haveGrail);
}

void checkRoom(int roomArray[][7], int gameArray[5], bool &win, bool &haveGrail)
{for(int m = 0; m < 11; m++)
    {
        if(roomArray[m][4] == 1 && roomArray[m][5] == 1)
        {
            cout << "\nYou went into the same room as the ZOMBIE! He ate your brains.\n\nYou lose. ☺" ;
            gameArray[0] = -1;
        }
    }
    for(int m = 0; m < 11; m++)
    {
        if(roomArray[m][4] == 1 && gameArray[0] != -1)
            cout << "You are in room " << m + 1 << " With " << gameArray[1] << " Bullets." << endl;
    }
    if(haveGrail == true && gameArray[0] != -1)
        cout << "You have the grail" << endl;


      for(int m = 0; m < 11; m++)
    {
        if(roomArray[m][4] == 1 && gameArray[0] != -1)
        {
            if(checkNearZombie(m, roomArray) && gameArray[0] != -1)
                cout << "You sense a ZOMBIEEEEE nearby...." << endl;
        }
    }
     for(int m = 0; m < 11; m++)
    {
        if(roomArray[m][4] == 1 && gameArray[0] != -1)
        {
            if(checkNearGrail(m, roomArray) && !haveGrail && gameArray[0] != -1)
                cout << "You sense a grail nearby...." << endl;
        }
    }
    if(gameArray[0] != -1)
    {
    showConnectedRooms(roomArray, gameArray);
    waitForMove(roomArray, gameArray, win, haveGrail);
    }
}

void running(int roomArray[][7], int gameArray[5], bool &win, bool &haveGrail, int &currentRoom, int &zombieRoom, int &numBullets, int &numRooms)
{
    while(win == false && gameArray[0] != -1)
    {
        checkRoom(roomArray, gameArray, win, haveGrail);

    }

    if(win == true)
        {
            cout<<"CONGRATULATIONS YOU WIN!!!";
        }

}


