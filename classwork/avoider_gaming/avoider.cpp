#include "include.hpp"
#include "getch.hpp"
// The source code of getch.hpp below is from:
// https://stackoverflow.com/questions/3276546/how-to-implement-getch-function-of-c-in-linux
#include "overlap.hpp"
#include "get_time.hpp"
// The source code below is from:
// The code of this function is from: https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c

//struct to save the rank and the time when achieved that rank.
struct ranking
{
  int score;
  string Time;
  ranking(int score, string Time)
  {
    this -> score = score;
    this -> Time = Time;
  };
};

bool operator<(const ranking & a, const ranking & b)
{
    // The rank is sorted by the score descendingly
    // if the scores are the same, then it will sorted by date descendingly
    if (a.score == b.score)
    {
        if (a.Time.size() == b.Time.size())
        {
          return (a.Time > b.Time);
        }
        else
        {
            return(a.Time.size() > b.Time.size());
        }
      } else
      {
        return (a.score > b.score);
      }
}

vector<ranking> rankings;

//this is the instruction part to describe our game
void guide()
{
    cout << "Instruction:" << endl;
    cout << "There are some remainders before you play this game:" << endl;
    cout << "1.There are 2 kind of attack bullet and laser." << endl;
    cout << "  1.1.1.Bullet will only appear from the left to right or from the top to the bottom." << endl;
    cout << "  1.1.2.Bullet can eat each other when they contact with each other and remain either one of them." << endl;
    cout << "  1.2.1.Before laser release, a warning will come out.Take careful when you are playing!" << endl;
    cout << "  1.2.2.Laser can destroy bullet at any time!No matter when it is preparing or releasing the laser."  << endl;
    cout << "        So take care when you see a bullet is suddenly disappear.Laser is coming!" << endl;
    cout << "2.There are 2 mode for you to play." << endl;
    cout << "  2.1.Simple mode:" << endl;
    cout << "      You can play in a relaxing time. Save and continue when you want!" << endl;
    cout << "      Also, there is a rank list to check your top 5 records." << endl;
    cout << "  2.2.Hell mode:" << endl;
    cout << "      If you want to challenge yourself, just choose this mode!" << endl;
    cout << "      This mode cannot choose to save.If you dont finish it and you close the game.The game status will deleted" << endl;
    cout << "      Moreover, you only have 1 second to choose you next step.If you overrun, you will lose." << endl;
    cout << "      More attack, Less thinking time!" << endl;
}

void greet() // disply the name of the game
{
    cout << "       |||      |||         |||   ||||||    |||||||||   ||||||||       |||||||||   ||||||     " << endl;
    cout << "      |||||      |||       |||   |||  |||      |||      |||    |||     |||||||||   |||  |||   " << endl;
    cout << "     ||| |||     |||       |||  |||    |||     |||      |||     |||    |||         |||    ||| " << endl;
    cout << "    |||   |||     |||     |||   |||    |||     |||      |||     |||    |||         |||    ||| " << endl;
    cout << "   |||     |||    |||     |||   |||    |||     |||      |||     |||    |||||||||   ||||||||   " << endl;
    cout << "  |||       |||   |||     |||   |||    |||     |||      |||     |||    |||||||||   ||||||     " << endl;
    cout << "  |||||||||||||    |||   |||    |||    |||     |||      |||     |||    |||         ||| |||    " << endl;
    cout << "  |||||||||||||     ||| |||     |||    |||     |||      |||     |||    |||         |||  |||   " << endl;
    cout << "  |||       |||      |||||       |||  |||      |||      |||    |||     |||||||||   |||   |||  " << endl;
    cout << "  |||       |||       |||         ||||||    |||||||||   ||||||||       |||||||||   |||    ||| " << endl;
}

//this is the first page for our game and the place to choose what you want to do. e.g. new game,previous game,hell mode etc.
// for simple mode only
int start()
{
    //the name of our game
    cout << "       |||      |||         |||   ||||||    |||||||||   ||||||||       |||||||||   ||||||     " << endl;
    cout << "      |||||      |||       |||   |||  |||      |||      |||    |||     |||||||||   |||  |||   " << endl;
    cout << "     ||| |||     |||       |||  |||    |||     |||      |||     |||    |||         |||    ||| " << endl;
    cout << "    |||   |||     |||     |||   |||    |||     |||      |||     |||    |||         |||    ||| " << endl;
    cout << "   |||     |||    |||     |||   |||    |||     |||      |||     |||    |||||||||   ||||||||   " << endl;
    cout << "  |||       |||   |||     |||   |||    |||     |||      |||     |||    |||||||||   ||||||     " << endl;
    cout << "  |||||||||||||    |||   |||    |||    |||     |||      |||     |||    |||         ||| |||    " << endl;
    cout << "  |||||||||||||     ||| |||     |||    |||     |||      |||     |||    |||         |||  |||   " << endl;
    cout << "  |||       |||      |||||       |||  |||      |||      |||    |||     |||||||||   |||   |||  " << endl;
    cout << "  |||       |||       |||         ||||||    |||||||||   ||||||||       |||||||||   |||    ||| " << endl;


    //to get the input from the user about what he want to do
    char User_choice;
    cout << "What would you like to do? Enter N or P or R" << endl;
    cout << "N for new game, P for previous game, R to view the ranking, I for instruction" << endl;
    cin >> User_choice;

    while (true)
    {
        if (User_choice == 'N') //new game will return 1 to start the new board and games
        {
            return 1;
        }

        else if (User_choice == 'P') //previous game will return 0 to get the file input in order to continue the previous one.
        {
            return 0;
        }
        else if (User_choice == 'R')
        {
            // To display the current ranking
            cout << "Top 5 performance: " << endl;
            ifstream read_rank;
            read_rank.open("rank.txt");
            for ( int i = 0; i < 5; i++)
            {
              int score;
              string the_date;
              read_rank >> score >> the_date;
              cout << "No." << i + 1 << ": " << score << " Achieved on: " << the_date << endl;
            }
            read_rank.close();
            cout << endl << "N for new game, P for previous game" << endl;
            cin >> User_choice;
        }

        else if (User_choice == 'I') //choose instruction will clear screen first and then out put the instruction. Finally, let the user to chooce what they want to do
        {
            system("clear"); //clear screen
            guide(); //call function to print instruction
            cout << endl << "N for new game, P for previous game" << endl; //let user to choose the things they want to do
            cin >> User_choice;
        }

        //if wrong input, user need to enter the expected input
        else
        {
            system("clear");
            cout << "What would you like to do? Enter N or P or R" << endl;
            cout << "N for new game and P for previous game."<< endl;
            cout << "N for new game, P for previous game, R to view current ranking." << endl;
            cin >> User_choice;
        }
    }
}

//random and number and according to it choose the attaker event
//input: board
//output: random pick attack mode into the board
void Attacker(string board[][10]) // for simple mode
{
	int mode; //1 for bullet, 2 for laser
	int count = 0; //for the while loop to count the number and break
	srand(time(NULL)); //set the seed for random

    //while loop will pick at most 2 attack mode to the board
    while (count < 2)
    {
      	mode = rand() % 2 + 1; // choose laser or bullet

      	if (mode == 1)
        {
          	int row_column, position;

      	  	row_column = rand() % 2 + 1; //choose put in the row one or column one
          	position = rand() % 10; //position to put the attack

          	if (row_column == 1) //1 for bullet which from left to right
            {
                int num = 0;
                int signalB = 0; //to stop the while loop
                while (true)
                {
                    if (board[position][0] == " ") //prevent the attack overlap the position
                    {
                        break;
                    }

                    else
                    {
                        position = rand() % 10;
                        num += 1;
                    }

                    if (num == 5) // if five time still cant random a position with no attack, stop this attack to prevent looping forever
                    {
                        signalB = 1;
                        break;
                    }
                }

                if (signalB == 0) // to confirm that positon with no attack
                {
                    board[position][0] = "Bullet_Row";
                }
            }

          	if (row_column == 2) //for bullet from top to the bottom
            {
                int num = 0;
                int signalB = 0;

                while (true)
                {
                    if (board[0][position] == " ")
                    {
                        break;
                    }

                    else
                    {
                        position = rand() % 10;
                        num += 1;
                    }

                    if (num == 5)
                    {
                        signalB = 1;
                        break;
                    }
                }

                if (signalB == 0)
                {
                    board[0][position] = "Bullet_Column";
                }
            }
        }

        if (mode == 2) //for laser
        {
          	int row_column, position;

      	  	row_column = rand() % 2 + 1; //row laser or column laser
          	position = rand() % 10; //position to put laser

          	if (row_column == 1) //for row laser
            {
                while (true)
                {
                    if (board[position][0] == "Laser_Row") //prevent overlap with same laser position
                    {
                        position = rand() % 10;
                    }

                    else
                    {
                        break;
                    }
                }

              	for (int a = 0; a < 10; a++) //put the whole row be Laser_row
              	{
              	    board[position][a] = "Laser_Row";
              	}

            }

          	if (row_column == 2) //for column laser
            {
                while (true)
                {
                    if (board[0][position] == "Laser_Column")
                    {
                        position = rand() % 10;
                    }

                    else
                    {
                        break;
                    }
                }

                for (int a = 0; a < 10; a++)
              	{
              	    board[a][position] = "Laser_Column";
              	}
              	return;
            }
        }

        count += 1;
    }
}

//to let the attack mode move to the next step. e.g.bullet move to the next position, laser from prepare mode to release.
//input: board, x y position of user to check if he dead.
int checkattack(string board[][10], int xpos, int ypos) // for simple mode
{
    //to find which row have laser which is prepare and print remainder to the user
    for ( int a = 0; a < 10; a++)
    {
        for( int b = 0; b < 10; b++)
        {
            if (board[a][b] == "Laser_Row")
            {
                cout << "Watch out ! Laser is coming in row " << a + 1 << endl;
                break;
            }
        }
    }

    //to find which column have laser which is prepare and print remainder to the user
    for ( int b = 0; b < 10; b++)
    {
        for( int a = 0; a < 10; a++)
        {
            if (board[a][b] == "Laser_Column")
            {
                cout << "Watch out ! Laser is coming in column " <<  b + 1 << endl;
                break;
            }
        }
    }

    if ( (board[ypos][xpos] != " " && board[ypos][xpos] != "Laser_Row" && board[ypos][xpos] != "Laser_Column") || (overlapped(board, xpos, ypos) == true))
    {
        system("clear");
        cout << endl << "----------------------------------------" << " " << endl;
        for (int i = 0; i < 10; i++)
        {
            cout << "|" ;
            for (int j = 0; j < 10; j++)
            {
                if (i == ypos && j == xpos)
                {
                    if (board[i][j] == " " || ( board[i][j] == "Laser_Row" && overlapped(board, i, j) == false)|| (overlapped(board, i, j) == false && board[i][j] == "Laser_Column"))
                    {
                        cout << " " << "X" << " |";
                    }

                    else
                    {
                        if ( board[i][j] == "Bullet_Row" || board[i][j] == "Bullet_Column")
                        {
                            cout << " " << "B" << " |";
                        }

                        if ( board[i][j] == "CL2" || board[i][j] == "RL2" || overlapped(board, i, j) == true)
                        {
                            cout << " " << "L" << " |";
                        }
                    }
                }

                else if (board[i][j] == " ")
                {
                    cout << " " << board[i][j] << " |";
                }

                else if ( board[i][j] == "Bullet_Row" || board[i][j] == "Bullet_Column")
                {
                    cout << " " << "B" << " |";
                }

                else if ( board[i][j] == "CL2" || board[i][j] == "RL2" || overlapped(board, i, j) == true)
                {
                    cout << " " << "L" << " |";
                }

                else if ( board[i][j] == "Laser_Row" || board[i][j] == "Laser_Column")
                {
                    cout << " " << " " << " |";
                }
            }
            cout << endl << "----------------------------------------" << " " << endl;
        }

        return 5;
    }

    //change the laser from prepare mode to release mode, and deleted when finish releasing
    for (int b = 0; b < 10; b++)
    {
        for (int a = 0; a < 10; a++)
        {
            if (board[a][b] == "CL2") //delete the released laser
            {
                board[a][b] = " ";
            }

            if (board[a][b] == "Laser_Column")
            {
                board[a][b] = "CL2"; //CL2 is relase of column laser
            }

            if (board[a][b] == "RL2") //delete the released laser
            {
                board[a][b] = " ";
            }

            if (board[a][b] == "Laser_Row")
            {
                board[a][b] = "RL2"; //RL2 is relase of row laser
            }
        }
    }

    //find the bullet in the board and move one step forward.If reach the edge, deleted it.
    for(int a = 0; a < 10; a++)
    {
        for( int b = 9; b >= 0; b--)
        {
            if (board[a][b] == "Bullet_Row")
            {
                if (b == 9) //reach the edge and delete
                {
                    board[a][b] = " ";
                }

                else //other move 1 step to the right
                {
                    if (board[a][b + 1] == " ")
                    {
                        board[a][b + 1] = "Bullet_Row";
                        board[a][b] = " ";
                    }

                    else //if front is laser, remove the bullet
                    {
                        board[a][b] = " ";
                    }
                }
            }
        }
    }

    //find the bullet in the board and move one step forward.If reach the edge, deleted it.
    for (int a = 0; a < 10; a++)
    {
        for( int b = 9; b >= 0; b--)
        {
            if (board[b][a] == "Bullet_Column")
            {
                if (b == 9) //reach the edge and delete
                {
                    board[b][a] = " ";
                }

                else //other move 1 step to the bottom
                {
                    if (board[b + 1][a] == " ")
                    {
                        board[b + 1][a] = "Bullet_Column";
                        board[b][a] = " ";
                    }

                    else //if front is laser, remove the bullet
                    {
                        board[b][a] = " ";
                    }
                }
            }
        }
    }

    return 0;
}


//when user press p, tell the control part and ask if he want to continue or save the status for next time to play.
int pausebutton()
{
    system("clear");
    cout << "Instruction:" << endl;
    cout << "W to move upwards." << endl;
    cout << "A to move leftwards." << endl;
    cout << "S to move downwards." << endl;
    cout << "D to move rightwards." << endl;
    cout << "E to stand at that box" << endl;
    cout << "P to pause the game." << endl;
    cout << "C to continue the game" << endl;
    cout << "You want to save the game or keep going?" << endl;
    cout << "Enter S to save the game, C to continue the game." << endl;

    char choice;
    cin >> choice;
    while (true)
    {
        if (choice == 'S') //return 4 to save the game status
        {
            return 4;
            break;
        }

        else if (choice == 'C') //return 3 to continue the game with previous game board as input
        {
            return 3;
            break;
        }

        else //wrong input, ask user again
        {
            system("clear");
            cout << "Instruction:" << endl;
            cout << "W to move upwards." << endl;
            cout << "A to move leftwards." << endl;
            cout << "S to move downwards." << endl;
            cout << "D to move rightwards." << endl;
            cout << "E to stand at that box" << endl;
            cout << "P to pause the game." << endl;
            cout << "C to continue the game" << endl;
            cout << "You want to save the game or keep going?" << endl;
            cout << "Enter S to save the game, C to continue the game." << endl;
            cin >> choice;
        }
    }
}

// to print the rank (for simple mode)
void outputrank(int score)
{
    //first check if this time over any rank, and then print out the rank
    while (rankings.size() > 0)
    {
        rankings.pop_back();
    }
    string current = timenow();
    ranking r(score, current);
    rankings.push_back(r);
    ifstream take_rank;
    take_rank.open("rank.txt");
    for (int i = 0; i < 5; i++)
    {
      int marks;
      string date_of_game;
      take_rank >> marks >> date_of_game;
      ranking p(marks, date_of_game);
      rankings.push_back(p);
    }
    take_rank.close();
    sort(rankings.begin(), rankings.end());
    while (rankings.size() > 5)
    {
      rankings.pop_back();
    }
    cout << "Top 5 performance: " << endl;
    for (int i = 0; i < 5; i++)
    {
      cout << "No. " << i+1 << ": " << rankings[i].score << " Achieved on : " << rankings[i].Time << endl;
    }
    ofstream store_rank;
    store_rank.open("rank.txt");
    vector<ranking> :: iterator iter;
    for (iter = rankings.begin(); iter != rankings.end(); iter++)
    {
      store_rank << (*iter).score << " " << (*iter).Time << endl;
    }
    store_rank.close();
}


void temp_store(string board[][10], int xpos, int ypos, int score)
{
    // To store the data of the map into paused.txt when the game is paused
    // Then the data will be retrieved from the txt file when player continues.
    ofstream pausing;
    pausing.open("paused.txt");
    for (int i = 0; i < 10; i++)
    {
        for ( int j = 0; j < 10; j++)
        {
            if (board[i][j] != " ")
            {
                pausing << board[i][j] << endl;
            }
            else
            {
                pausing << "empty" << endl;
            }
        }
    }
    pausing << score << endl;
    pausing << xpos << endl << ypos << endl;
    pausing.close();
}

// handle user movement (for simple mode)
int System( string board[][10], int stage, int &score, int &xpos, int &ypos)
{
    system("clear");
    cout << endl << "----------------------------------------" << " " << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << "|" ;
        for (int j = 0; j < 10; j++)
        {
            if (i == ypos && j == xpos)
            {
                if (board[i][j] == " " || (board[i][j] == "Laser_Row" && overlapped(board, i, j) == false)|| (board[i][j] == "Laser_Column" && overlapped(board, i, j) == false))
                {
                    cout << " " << "X" << " |";
                }

                else
                {
                    if ( board[i][j] == "Bullet_Row" || board[i][j] == "Bullet_Column")
                    {
                        cout << " " << "B" << " |";
                    }

                    if ( board[i][j] == "CL2" || board[i][j] == "RL2" || overlapped(board, i, j) == true)
                    {
                        cout << " " << "L" << " |";
                    }
                }
            }

            else if (board[i][j] == " ")
            {
                cout << " " << board[i][j] << " |";
            }

            else if ( board[i][j] == "Bullet_Row" || board[i][j] == "Bullet_Column")
            {
                cout << " " << "B" << " |";
            }

            else if ( board[i][j] == "CL2" || board[i][j] == "RL2" || overlapped(board, i, j) == true)
            {
                cout << " " << "L" << " |";
            }

            else if ( board[i][j] == "Laser_Row" || board[i][j] == "Laser_Column")
            {
                cout << " " << " " << " |";
            }
        }
        cout << endl << "----------------------------------------" << " " << endl;
    }


    //set the attack frequency to put the attack
    int attack_freq;
  	srand(time(NULL));
  	attack_freq = rand() % 3 + 1;

    int move = 5; //for determine the score

    //this while loop is to let the user keep enter the action, print board, add attack to the board, move the attack and check if user dead.
    while (true)
    {
        char ch ;
        ch = getch(); //get user input without pressing enter

        if ( ch == 'w') //w to move up 1 unit
        {
            if (ypos != 0)
            {
                ypos = ypos - 1;
            }
        }

        else if ( ch == 'a') //a to move to the left for 1 unit
        {
            if ( xpos != 0 )
            {
                xpos = xpos - 1;
            }
        }

         else if (ch == 's') //s to move downward for 1 unit
        {
            if ( ypos != 9)
            {
                ypos = ypos + 1;
            }
        }

        else if ( ch == 'd' ) //d to move to the right for 1 unit
        {
            if (xpos != 9)
            {
                xpos = xpos + 1;
            }
        }

        else if ( ch == 'p') //pause the game and return 2 to print the pause part
        {
            return 2;
        }

        if ( ch == 'w' || ch == 'a' || ch == 's' || ch == 'd' || ch == 'e') //if the user chose the action, determine the attack mode, score and print board.
        {
            move --; //determine the user have move 1 action
            if (move == 0) //every 5 action will add 1 mark to the score
            {
              score ++;
              move = 5;
            }

            if (stage == 3) //for extra checking attack especially after pause the game.
            {
                int check = checkattack(board,xpos, ypos);
                if (check == 5) //cehckattack return 5 if user dead, and go to lose function
                {
                    return 5;
                }
                stage = 1;
            }

          	attack_freq --;
          	if (attack_freq == 0) // when attack frequency is end put attack and set the next frequency
            {
              	Attacker(board);
              	srand(time(NULL));
  				      attack_freq = rand() % 3 + 1;
            }
            system("clear");
            cout << endl << "----------------------------------------" << " " << endl;
            for (int i = 0; i < 10; i++)
            {
                cout << "|" ;
                for (int j = 0; j < 10; j++)
                {
                    if (i == ypos && j == xpos)
                    {
                        if (board[i][j] == " " || ( board[i][j] == "Laser_Row" && overlapped(board, i, j) == false) || ( overlapped(board, i, j) == false && board[i][j] == "Laser_Column"))
                        {
                            cout << " " << "X" << " |";
                        }

                        else
                        {
                            if ( board[i][j] == "Bullet_Row" || board[i][j] == "Bullet_Column")
                            {
                                cout << " " << "B" << " |";
                            }

                            if ( board[i][j] == "CL2" || board[i][j] == "RL2" || overlapped(board, i, j) == true)
                            {
                                cout << " " << "L" << " |";
                            }
                        }
                    }

                    else if (board[i][j] == " ")
                    {
                        cout << " " << board[i][j] << " |";
                    }

                    else if ( board[i][j] == "Bullet_Row" || board[i][j] == "Bullet_Column")
                    {
                        cout << " " << "B" << " |";
                    }

                    else if ( board[i][j] == "CL2" || board[i][j] == "RL2" || overlapped(board, i, j) == true)
                    {
                        cout << " " << "L" << " |";
                    }

                    else if ( board[i][j] == "Laser_Row" || board[i][j] == "Laser_Column")
                    {
                        cout << " " << " " << " |";
                    }
                }
                cout << endl << "----------------------------------------" << " " << endl;
            }
            cout << "Your Score: " << score << endl;
      }

        if ( ch == 'w' || ch == 'a' || ch == 's' || ch == 'd' || ch == 'e') //checkattack funtion if user finish action
        {
            temp_store(board, xpos, ypos, score);
            int check = checkattack(board, xpos, ypos);
            //temp_store(board, xpos, ypos, score);

            //return 5 when user dead
            if (check == 5)
            {
                return 5;
            }
        }
    }
}

//lose funtion for user when he lose and print out the score and return 4 to save the game score and time
int lose(int score)
{
    cout << "|||||                |||||           ||||||||         ||||||||||||  " << endl;
    cout << "|||||              |||||||||        |||||||||||       ||||||||||||  " << endl;
    cout << "|||||            |||       |||     ||         ||      |||           " << endl;
    cout << "|||||            |||       |||    |||                 |||           " << endl;
    cout << "|||||            |||       |||    |||                 |||           " << endl;
    cout << "|||||            |||       |||     ||||||||||||       ||||||||||||  " << endl;
    cout << "|||||            |||       |||      ||||||||||||      ||||||||||||  " << endl;
    cout << "|||||            |||       |||                |||     |||           " << endl;
    cout << "|||||            |||       |||                |||     |||           " << endl;
    cout << "|||||            |||       |||    ||        ||||      |||           " << endl;
    cout << "||||||||||||||     |||||||||       ||||||||||||       ||||||||||||  " << endl;
    cout << "||||||||||||||       |||||           |||||||||        ||||||||||||  " << endl;
    cout << "your score is " << score << '.' << endl;
    cout << "next time will be better!" << endl;
    return 4;

}

//random and number and according to it choose the attaker event (for hell mode)

void Attacker_hell(string board[][10])
{
	int mode;
	int count = 0;
	srand(time(NULL));

    while (count < 4)
    {
      	mode = rand() % 2 + 1;

      	if (mode == 1)
        {
          	int row_column, position;

      	  	row_column = rand() % 2 + 1;
          	position = rand() % 10;

          	if (row_column == 1)
            {
                int num = 0;
                int signalB = 0;
                while (true)
                {
                    if (board[position][0] == " ")
                    {
                        break;
                    }

                    else
                    {
                        position = rand() % 10;
                        num += 1;
                    }

                    if (num == 5)
                    {
                        signalB = 1;
                        break;
                    }
                }

                if (signalB == 0)
                {
                    board[position][0] = "Bullet_Row";
                }
            }

          	if (row_column == 2)
            {
                int num = 0;
                int signalB = 0;
                while (true)
                {
                    if (board[0][position] == " ")
                    {
                        break;
                    }

                    else
                    {
                        position = rand() % 10;
                        num += 1;
                    }

                    if (num == 5)
                    {
                        signalB = 1;
                        break;
                    }
                }

                if (signalB == 0)
                {
                    board[0][position] = "Bullet_Column";
                }
            }
        }

        if (mode == 2)
        {
          	int row_column, position;

      	  	row_column = rand() % 2 + 1;
          	position = rand() % 10;

          	if (row_column == 1)
            {
                while (true)
                {
                    if (board[position][0] == "Laser_Row")
                    {
                        position = rand() % 10;
                    }

                    else
                    {
                        break;
                    }
                }

              	for (int a = 0; a < 10; a++)
              	{
              	    board[position][a] = "Laser_Row";
              	}

            }

          	if (row_column == 2)
            {
                while (true)
                {
                    if (board[0][position] == "Laser_Column")
                    {
                        position = rand() % 10;
                    }

                    else
                    {
                        break;
                    }
                }

                for (int a = 0; a < 10; a++)
              	{
              	    board[a][position] = "Laser_Column";
              	}
              	return;
            }
        }

        count += 1;
    }
}

// To check the board and see if the player is hit (for hell mode)
int checkattack_hell(string board[][10], int xpos, int ypos)
{
    for ( int a = 0; a < 10; a++)
    {
        for( int b = 0; b < 10; b++)
        {
            if (board[a][b] == "Laser_Row")
            {
                cout << "Watch out ! Laser is coming in row " <<  a + 1 << endl;
                break;
            }
        }
    }

    for ( int b = 0; b < 10; b++)
    {
        for( int a = 0; a < 10; a++)
        {
            if (board[a][b] == "Laser_Column")
            {
                cout << "Watch out ! Laser is coming in column " <<  b + 1 << endl;
                break;
            }
        }
    }

    if ( (board[ypos][xpos] != " " && board[ypos][xpos] != "Laser_Row" && board[ypos][xpos] != "Laser_Column") || (overlapped(board, xpos, ypos) == true))
    {
        system("clear");
        cout << endl << "----------------------------------------" << " " << endl;
        for (int i = 0; i < 10; i++)
        {
            cout << "|" ;
            for (int j = 0; j < 10; j++)
            {
                if (i == ypos && j == xpos)
                {
                    if (board[i][j] == " " || ( board[i][j] == "Laser_Row" && overlapped(board, i, j) == false)|| (overlapped(board, i, j) == false && board[i][j] == "Laser_Column"))
                    {
                        cout << " " << "X" << " |";
                    }

                    else
                    {
                        if ( board[i][j] == "Bullet_Row" || board[i][j] == "Bullet_Column")
                        {
                            cout << " " << "B" << " |";
                        }

                        if ( board[i][j] == "CL2" || board[i][j] == "RL2" || overlapped(board, i, j) == true)
                        {
                            cout << " " << "L" << " |";
                        }
                    }
                }

                else if (board[i][j] == " ")
                {
                    cout << " " << board[i][j] << " |";
                }

                else if ( board[i][j] == "Bullet_Row" || board[i][j] == "Bullet_Column")
                {
                    cout << " " << "B" << " |";
                }

                else if ( board[i][j] == "CL2" || board[i][j] == "RL2" || overlapped(board, i, j) == true)
                {
                    cout << " " << "L" << " |";
                }

                else if ( board[i][j] == "Laser_Row" || board[i][j] == "Laser_Column")
                {
                    cout << " " << " " << " |";
                }
            }
            cout << endl << "----------------------------------------" << " " << endl;
        }

        return 5;
    }

    for (int b = 0; b < 10; b++)
    {
        for (int a = 0; a < 10; a++)
        {
            if (board[a][b] == "CL2")
            {
                board[a][b] = " ";
            }

            if (board[a][b] == "Laser_Column")
            {
                board[a][b] = "CL2";
            }

            if (board[a][b] == "RL2")
            {
                board[a][b] = " ";
            }

            if (board[a][b] == "Laser_Row")
            {
                board[a][b] = "RL2";
            }
        }
    }

    for(int a = 0; a < 10; a++)
    {
        for( int b = 9; b >= 0; b--)
        {
            if (board[a][b] == "Bullet_Row")
            {
                if (b == 9)
                {
                    board[a][b] = " ";
                }

                else
                {
                    if (board[a][b + 1] == " ")
                    {
                        board[a][b + 1] = "Bullet_Row";
                        board[a][b] = " ";
                    }

                    else
                    {
                        board[a][b] = " ";
                    }
                }
            }
        }
    }

    for (int a = 0; a < 10; a++)
    {
        for( int b = 9; b >= 0; b--)
        {
            if (board[b][a] == "Bullet_Column")
            {
                if (b == 9)
                {
                    board[b][a] = " ";
                }

                else
                {
                    if (board[b + 1][a] == " ")
                    {
                        board[b + 1][a] = "Bullet_Column";
                        board[b][a] = " ";
                    }

                    else
                    {
                        board[b][a] = " ";
                    }
                }
            }
        }
    }

    return 0;
}

// To handle user movemnet (for hell mode)
int System_hell( string board[][10], int stage, int &score, int &xpos, int &ypos)
{
    system("clear");
    cout << endl << "----------------------------------------" << " " << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << "|" ;
        for (int j = 0; j < 10; j++)
        {
            if (i == ypos && j == xpos)
            {
                if (board[i][j] == " " || (board[i][j] == "Laser_Row" && overlapped(board, i, j) == false)|| (board[i][j] == "Laser_Column" && overlapped(board, i, j) == false))
                {
                    cout << " " << "X" << " |";
                }

                else
                {
                    if ( board[i][j] == "Bullet_Row" || board[i][j] == "Bullet_Column")
                    {
                        cout << " " << "B" << " |";
                    }

                    if ( board[i][j] == "CL2" || board[i][j] == "RL2" || overlapped(board, i, j) == true)
                    {
                        cout << " " << "L" << " |";
                    }
                }
            }

            else if (board[i][j] == " ")
            {
                cout << " " << board[i][j] << " |";
            }

            else if ( board[i][j] == "Bullet_Row" || board[i][j] == "Bullet_Column")
            {
                cout << " " << "B" << " |";
            }

            else if ( board[i][j] == "CL2" || board[i][j] == "RL2" || overlapped(board, i, j) == true)
            {
                cout << " " << "L" << " |";
            }

            else if ( board[i][j] == "Laser_Row" || board[i][j] == "Laser_Column")
            {
                cout << " " << " " << " |";
            }
        }
        cout << endl << "----------------------------------------" << " " << endl;
    }

    int attack_freq;
  	srand(time(NULL));
  	attack_freq = rand() % 3 + 1;
    int timecount;

    while (true)
    {
        using namespace std::chrono ;
        // this 2 code is from http://www.cplusplus.com/forum/general/98165/
        auto start = steady_clock::now() ;

        char ch ;
        ch = getch();
        if ( ch == 'w')
        {
            if (ypos != 0)
            {
                ypos = ypos - 1;
            }
            auto end = steady_clock::now() ;
            // this 2 code is from http://www.cplusplus.com/forum/general/98165/
            timecount = duration_cast<milliseconds>(end-start).count();

            if ((timecount / 1000) > 1)
            {
                return 5;
            }

            if ((timecount / 1000) < 0.3)
            {
                score += 3;
            }

            else if ((timecount / 1000) < 0.6)
            {
                score += 2;
            }

            else if ((timecount / 1000) < 1)
            {
                score += 1;
            }
        }

        else if ( ch == 'a')
        {
            if ( xpos != 0 )
            {
                xpos = xpos - 1;
            }
            auto end = steady_clock::now() ;
            timecount = duration_cast<milliseconds>(end-start).count();
            if ((timecount / 1000) > 1)
            {
                return 5;
            }
            if ((timecount / 1000) < 0.3)
            {
                score += 3;
            }

            else if ((timecount / 1000) < 0.6)
            {
                score += 2;
            }

            else if ((timecount / 1000) < 1)
            {
                score += 1;
            }
        }

         else if (ch == 's')
        {
            if ( ypos != 9)
            {
                ypos = ypos + 1;
            }
            auto end = steady_clock::now() ;
            timecount = duration_cast<milliseconds>(end-start).count();
            if ((timecount / 1000) > 1)
            {
                return 5;
            }

            if ((timecount / 1000) < 0.3)
            {
                score += 3;
            }

            else if ((timecount / 1000) < 0.6)
            {
                score += 2;
            }

            else if ((timecount / 1000) < 1)
            {
                score += 1;
            }
        }

        else if ( ch == 'd' )
        {
            if (xpos != 9)
            {
                xpos = xpos + 1;
            }
            auto end = steady_clock::now() ;
            timecount = duration_cast<milliseconds>(end-start).count();
            if ((timecount / 1000) > 1)
            {
                return 5;
            }

            if ((timecount / 1000) < 0.3)
            {
                score += 3;
            }

            else if ((timecount / 1000) < 0.6)
            {
                score += 2;
            }

            else if ((timecount / 1000) < 1)
            {
                score += 1;
            }
        }


        if ( ch == 'w' || ch == 'a' || ch == 's' || ch == 'd' || ch == 'e')
        {
            if (stage == 3)
            {
                int check = checkattack_hell(board, xpos, ypos);
                if (check == 5)
                {
                    return 5;
                }
                stage = 1;
            }

          	attack_freq --;
          	if (attack_freq == 0)
            {
              	Attacker_hell(board);
              	srand(time(NULL));
  				      attack_freq = rand() % 3 + 1;
            }
            system("clear");
            cout << endl << "----------------------------------------" << " " << endl;
            for (int i = 0; i < 10; i++)
            {
                cout << "|" ;
                for (int j = 0; j < 10; j++)
                {
                    if (i == ypos && j == xpos)
                    {
                        if (board[i][j] == " " || ( board[i][j] == "Laser_Row" && overlapped(board, i, j) == false) || ( overlapped(board, i, j) == false && board[i][j] == "Laser_Column"))
                        {
                            cout << " " << "X" << " |";
                        }

                        else
                        {
                            if ( board[i][j] == "Bullet_Row" || board[i][j] == "Bullet_Column")
                            {
                                cout << " " << "B" << " |";
                            }

                            if ( board[i][j] == "CL2" || board[i][j] == "RL2" || overlapped(board, i, j) == true)
                            {
                                cout << " " << "L" << " |";
                            }
                        }
                    }

                    else if (board[i][j] == " ")
                    {
                        cout << " " << board[i][j] << " |";
                    }

                    else if ( board[i][j] == "Bullet_Row" || board[i][j] == "Bullet_Column")
                    {
                        cout << " " << "B" << " |";
                    }

                    else if ( board[i][j] == "CL2" || board[i][j] == "RL2" || overlapped(board, i, j) == true)
                    {
                        cout << " " << "L" << " |";
                    }

                    else if ( board[i][j] == "Laser_Row" || board[i][j] == "Laser_Column")
                    {
                        cout << " " << " " << " |";
                    }
                }
                cout << endl << "----------------------------------------" << " " << endl;
            }
            cout << "Your Score: " << score << endl;
      }

        if ( ch == 'w' || ch == 'a' || ch == 's' || ch == 'd' || ch == 'e')
        {
            int check = checkattack_hell(board, xpos, ypos);
            if (check == 5)
            {
                return 5;
            }
        }
    }
}

// print lose message (for hell mode)
void lose_hell(int score)
{
    cout << "|||||                |||||           ||||||||         ||||||||||||  " << endl;
    cout << "|||||              |||||||||        |||||||||||       ||||||||||||  " << endl;
    cout << "|||||            |||       |||     ||         ||      |||           " << endl;
    cout << "|||||            |||       |||    |||                 |||           " << endl;
    cout << "|||||            |||       |||    |||                 |||           " << endl;
    cout << "|||||            |||       |||     ||||||||||||       ||||||||||||  " << endl;
    cout << "|||||            |||       |||      ||||||||||||      ||||||||||||  " << endl;
    cout << "|||||            |||       |||                |||     |||           " << endl;
    cout << "|||||            |||       |||                |||     |||           " << endl;
    cout << "|||||            |||       |||    ||        ||||      |||           " << endl;
    cout << "||||||||||||||     |||||||||       ||||||||||||       ||||||||||||  " << endl;
    cout << "||||||||||||||       |||||           |||||||||        ||||||||||||  " << endl;
    cout << "Your score is " << score << '.' << endl;
    cout << "Try again!" << endl;
}

// print ranking (for hell mode)
void outputrank_hell(int score)
{
    //first check if this time over any rank, and then print out the rank
    while (rankings.size() > 0)
    {
        rankings.pop_back();
    }
    string current = timenow();
    ranking r(score, current);
    rankings.push_back(r);
    ifstream take_rank;
    take_rank.open("rank_hell.txt");
    for (int i = 0; i < 5; i++)
    {
      int marks;
      string date_of_game;
      take_rank >> marks >> date_of_game;
      ranking p(marks, date_of_game);
      rankings.push_back(p);
    }
    take_rank.close();
    sort(rankings.begin(), rankings.end());
    while (rankings.size() > 5)
    {
      rankings.pop_back();
    }
    cout << "Top 5 performance (Hell mode): " << endl;
    for (int i = 0; i < 5; i++)
    {
      cout << "No. " << i+1 << ": " << rankings[i].score << " Achieved on : " << rankings[i].Time << endl;
    }
    ofstream store_rank;
    store_rank.open("rank_hell.txt");
    vector<ranking> :: iterator iter;
    for (iter = rankings.begin(); iter != rankings.end(); iter++)
    {
      store_rank << (*iter).score << " " << (*iter).Time << endl;
    }
    store_rank.close();
}

int main()
{
    greet();
    guide();
    string simple_or_hell;
    cout << "Enter S for Simple Mode, H for Hell mode." << endl;
    cin >> simple_or_hell;

    if (simple_or_hell == "S")
    {
        system("clear");
        int N_or_P; //to determine what the next step of the system will do
    	  N_or_P = start(); //go to the start page first and see user choice
    	  string map[10][10]; //map for the game
        int score = 0;

        //x y position for user
        int xpos;
        int ypos;

        //the main system part for the program behind
        	while (true)
        	{
        	    if (N_or_P == 0)
                {
                    // read input from paused.txt when player want to continue the previous game
                    ifstream take_previous;
                    take_previous.open("paused.txt");
                    int player_location = 0;
                    for (int i = 0; i < 10; i++)
                    {
                        for (int j = 0; j < 10; j++)
                        {
                            string data;
                            take_previous >> data;
                            if (data != "empty")
                            {
                              map[i][j] = data;
                            } else
                            {
                              map[i][j] = " ";
                            }
                        }
                    }
                    take_previous >> score;
                    take_previous >> xpos >> ypos;
                    take_previous.close();
                    if (player_location == 1)
                    {
                      N_or_P = System(map, 1, score, xpos , ypos);
                    }

                    else
                    {
                      N_or_P = System(map , 0, score, xpos, ypos);
                    }
                }

        	    else if (N_or_P == 1)
                {
                    for (int i = 0; i < 10; i++)
                    {
                        for (int j = 0; j < 10; j++)
                        {
                            map[i][j] = " ";
                        }
                    }
                    xpos = 4;
                    ypos = 5;
                    N_or_P = System(map, 0, score, xpos, ypos);
                  }

                else  if (N_or_P == 2) //return 2 when user want to pause the game
                {
                      N_or_P = pausebutton();
                }

                else if (N_or_P == 3)
                {
                    // to read dtat from board.txt when player want to continue the paused game
                    ifstream take_temp;
                    take_temp.open("paused.txt");
                    for ( int i = 0; i < 10; i++)
                    {
                        for (int j = 0; j < 10; j++)
                        {
                            string data;
                            take_temp >> data;
                            if (data != "empty")
                            {
                                map[i][j] = data;
                            }
                            else
                            {
                                map[i][j] = " ";
                            }
                        }
                    }
                    take_temp >> score >> xpos >> ypos;
                    N_or_P = System(map, 3, score, xpos, ypos);
                }

                else if (N_or_P == 4)
                {
                    break;
                }

                else if (N_or_P == 5) //return 5 when user dead
                {
                    N_or_P = lose(score);
                    outputrank(score);
                    cout << "Enter Y to play again , L to leave" << endl;
                    string decision;
                    cin >> decision;
                    while (decision != "Y" && decision != "L")
                    {
                        system("clear");
                        cout << "Invalid input, please input again" << endl;
                        cout << "Enter Y to play again , L to leave" << endl;
                        cin >> decision;
                    }
                    if (decision == "L")
                    {
                        break;
                    }
                    else if (decision == "Y")
                    {
                        N_or_P = 1;
                    }
                }
        	}
      }
      else if ( simple_or_hell == "H")
      {
          system("clear");
          while (true)
          {
              string map[10][10];
              int score = 0;
              int xpos;
              int ypos;
              int N_or_P;

              for (int i = 0; i < 10; i++)
              {
                  for (int j = 0; j < 10; j++)
                  {
                      map[i][j] = " ";
                  }
              }
              xpos = 4;
              ypos = 5;
              N_or_P = System_hell(map, 0, score, xpos, ypos);

              if (N_or_P == 5)
              {
                  lose_hell(score);
                  outputrank_hell(score);
                  cout << "Enter Y to play again , L to leave" << endl;
                  string decision;
                  cin >> decision;
                  while (decision != "Y" && decision != "L")
                  {
                      system("clear");
                      cout << "Invalid input, please input again" << endl;
                      cout << "Enter Y to play again , L to leave" << endl;
                      cin >> decision;
                  }
                  if (decision == "L")
                  {
                      break;
                  }
              }
            }
      }
}
