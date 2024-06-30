#include "MISTSPACE.h"

using namespace std;

namespace MistSpace
{
    int string_to_int(string str) // Function for converting string to integer
    {
        int num;
        stringstream ss(str);
        ss >> num;

        if (ss.fail())
        {
            cout << "Invalid arguments." << endl;
        }
        return num;
    }

    int gen_rand(int low, int high) // function for generating random number
    {
        int result;
        result = low + (rand() % (high - low));
        return result;
    }

    void Pause() // Pause function
    {
        cin.ignore(100, '\n');
        cout << "Press Enter to continue." << endl;
        cin.get();
    }

    void Display(Two_D_Array &arr, int row, int col, int operatorP) // function for displaying the 3d array
    {
        for (int r = 0; r < row; r++)
        {
            for (int c = 0; c < col; c++)
            {
                cout << arr[r][c] << " ";
            }
            cout << endl;
        }
        cout << endl
             << "Operator battery life: " << operatorP << " units." << endl;
    }

    void Display_Mist(Two_D_Array &arr, int row, int col, int operatorP, int Op_col, int &Op_row) // function for displaying the 3d array
    {
        for (int r = 0; r < row; r++)
        {
            for (int c = 0; c < col; c++)
            {
                if ((r >= Op_row - 1 && r <= Op_row + 1) && (c >= Op_col - 1 && c <= Op_col + 1))
                {
                    cout << arr[r][c] << " ";
                }
                else
                    cout << blank << " ";
            }
            cout << endl;
        }
        cout << endl
             << "Operator battery life: " << operatorP << " units." << endl;
    }

    Two_D_Array alloc2D(int row, int col) // function for allocating memory into a 2d array
    {
        Two_D_Array newArray;
        newArray = new One_D_Array[row];
        for (int r = 0; r < row; r++)
        {
            newArray[r] = new char(col);
        }
        return newArray;
    }

    void Dealloc(Two_D_Array &arr, int row) // function for deallocating memory into a 2d array
    {
        for (int r = 0; r < row; r++)
        {
            delete[] arr[r];
        }
        delete[] arr;
        arr = nullptr;
    }

    void initialize_arr(Two_D_Array &arr, int row, int col) // function for intitialising the array
    {
        for (int r = 0; r < row; r++)
        {
            for (int c = 0; c < col; c++)
            {
                arr[r][c] = Space;
            }
        }
    }

    void placefeature(Two_D_Array &arr, int row, int col, const char feature, int num) // function for randomly placing the pieces on the board(2d array)
    {
        int ROW, COL;
        int temp = 0;
        while (temp < num)
        {
            ROW = gen_rand(0, row);
            COL = gen_rand(0, col);
            while (arr[ROW][COL] == Space)
            {
                arr[ROW][COL] = feature;
                temp += 1;
            }
        }
    }

    void placeoperator(Two_D_Array &arr, int row, int col, char feature, int &pCol) // functiion for randomly placing the player piece on the board
    {
        int ROW, COL;
        int temp = 0;
        while (temp < 1)
        {
            ROW = row - 1;
            COL = gen_rand(0, col);
            while (arr[ROW][COL] == Space)
            {
                arr[ROW][COL] = feature;
                pCol = COL;
                temp += 1;
            }
        }
    }

    void placeMain(Two_D_Array &arr, int row, int col, char feature) // functiion for randomly placing the player piece on the board
    {
        int ROW, COL;
        int temp = 0;
        while (temp < 1)
        {
            ROW = 0;
            COL = gen_rand(0, col);
            while (arr[ROW][COL] == Space)
            {
                arr[ROW][COL] = feature;
                temp += 1;
            }
        }
    }

    void Play_Game(Two_D_Array &arr, int &pRow, int &pCol, int pEnergy, int r, int c, bool Gamecontinue) // function for playing the gae
    {
        bool Main_Switch = false;
        char Movement;
        cout << endl;

        do
        {
            if (Main_Switch == false)
            {
            system("cls");
            Display_Mist(arr, r, c, pEnergy, pCol, pRow);
            cout << "Press to move: " << endl
                 << "W is up" << endl
                 << "S is down" << endl
                 << "A is left" << endl
                 << "D is right" << endl
                 << "Q is North East" << endl
                 << "E is North West" << endl
                 << "Z is South East" << endl
                 << "C is South West" << endl
                 << "K to quit" << endl
                 << endl;

            if (pEnergy < 1) // checking if the play has energy to continue with game.
            {
                cout << "You have lost,Player is out of Energy." << endl << endl;
                Pause();
                Gamecontinue = false;
            }
            else
            {

                cin >> Movement;

                switch (Movement) // switch case for moving the players peice
                {
                case 'w': // moving the player the up
                case 'W':
                    if (pRow - 1 < 0)
                    {
                        cout << "Operator may not move outside of Utopian city" << endl;
                        Pause();
                    }
                    else if (arr[pRow - 1][pCol] == Space) // checking if the play move up
                    {
                        arr[pRow][pCol] = Space;
                        arr[pRow - 1][pCol] = Player;
                        pRow -= 1;
                        pEnergy -= 1;
                        break;
                    }
                    else if (arr[pRow - 1][pCol] == battery) // checking if there is an energy unit to increase the players energy
                    {
                        arr[pRow - 1][pCol] = Player;
                        arr[pRow][pCol] = Space;
                        pRow -= 1;
                        pEnergy -= 1;
                        pEnergy += 5;
                        break;
                    }
                    else if (arr[pRow - 1][pCol] == Wire) ////checking if there is mine
                    {
                        cout << "Player lost, Operator touched an exposed wire at Row " << pRow - 1 << " ,column " << pCol << "." << endl;
                        Gamecontinue = false;
                        break;
                    }
                    else if (arr[pRow - 1][pCol] == Main_switch)
                    {
                        Main_Switch = true;
                        //Gamecontinue = false;
                        break;
                    }
                    break;

                case 's': // Moving the player piece down
                case 'S':

                    if (pRow + 1 >= r)
                    {
                        cout << "Operator may not move outside of Utopian city" << endl;
                        Pause();
                    }
                    else
                    {
                        if (arr[pRow + 1][pCol] == Space) // empty space
                        {
                            arr[pRow][pCol] = Space;
                            arr[pRow + 1][pCol] = Player;
                            pRow += 1;
                            pEnergy -= 1;
                            break;
                        }
                        else if (arr[pRow + 1][pCol] == battery) // energy unit
                        {
                            arr[pRow + 1][pCol] = Player;
                            arr[pRow][pCol] = Space;
                            pRow += 1;
                            pEnergy -= 1;
                            pEnergy += 5;
                            break;
                        }
                        else if (arr[pRow + 1][pCol] == Wire) // Mines
                        {
                            cout << "Player lost, Operator touched an exposed wire at Row " << pRow + 1 << " ,column " << pCol << "." << endl;
                            Gamecontinue = false;
                            break;
                        }
                    }
                    break;

                case 'a': // Moving the player piece left
                case 'A':
                    if (pCol - 1 < 0)
                    {
                        cout << "Operator may not move outside of Utopian city" << endl;
                        Pause();
                    }
                    else
                    {
                        if (arr[pRow][pCol - 1] == Space) // empty space
                        {
                            arr[pRow][pCol] = Space;
                            arr[pRow][pCol - 1] = Player;
                            pCol -= 1;
                            pEnergy -= 1;
                            break;
                        }
                        else if (arr[pRow][pCol - 1] == battery) // energy unit
                        {
                            arr[pRow][pCol - 1] = Player;
                            arr[pRow][pCol] = Space;
                            pCol -= 1;
                            pEnergy -= 1;
                            pEnergy += 5;
                            break;
                        }
                        else if (arr[pRow][pCol - 1] == Wire) // Mines
                        {
                            cout << "Player lost, Operator touched an exposed wire at Row " << pRow << " ,column " << pCol - 1 << "." << endl;
                            Gamecontinue = false;
                            break;
                        }
                        else if (arr[pRow][pCol - 1] == Main_switch)
                        {
                            Main_Switch = true;
                            break;
                        }
                    }
                    break;

                case 'd': // Moving the player piece right
                case 'D':

                    if (pCol + 1 > r)
                    {
                        cout << "Operator may not move outside of Utopian city" << endl;
                        Pause();
                        break;
                    }
                    else
                    {
                        if (arr[pRow][pCol + 1] == Space) // empty space
                        {
                            arr[pRow][pCol] = Space;
                            arr[pRow][pCol + 1] = Player;
                            pCol += 1;
                            pEnergy -= 1;
                            break;
                        }
                        else if (arr[pRow][pCol + 1] == battery) // energy unit
                        {
                            arr[pRow][pCol + 1] = Player;
                            arr[pRow][pCol] = Space;
                            pCol += 1;
                            pEnergy -= 1;
                            pEnergy += 5;
                            break;
                        }
                        else if (arr[pRow][pCol + 1] == Wire) // Mines
                        {
                            cout << "Player lost, Operator touched an exposed wire at Row " << pRow << " ,column " << pCol + 1 << "." << endl;
                            Gamecontinue = false;
                            break;
                        }
                        else if (arr[pRow][pCol + 1] == Main_switch)
                        {
                            Main_Switch = true;
                            break;
                        }
                    }
                    break;

                case 'e': // moving the player the North west
                case 'E':
                    if (pRow - 1 < 0 || pCol + 1 > r)
                    {
                        cout << "Operator may not move outside of Utopian city" << endl;
                        Pause();
                    }
                    else if (arr[pRow - 1][pCol + 1] == Space) // checking if the play move up
                    {
                        arr[pRow][pCol] = Space;
                        arr[pRow - 1][pCol + 1] = Player;
                        pRow -= 1;
                        pCol += 1;
                        pEnergy -= 1;
                        break;
                    }
                    else if (arr[pRow - 1][pCol + 1] == battery) // checking if there is an energy unit to increase the players energy
                    {
                        arr[pRow - 1][pCol + 1] = Player;
                        arr[pRow][pCol] = Space;
                        pRow -= 1;
                        pCol += 1;
                        pEnergy -= 1;
                        pEnergy += 5;
                        break;
                    }
                    else if (arr[pRow - 1][pCol + 1] == Wire) ////checking if there is mine
                    {
                        cout << "Player lost, Operator touched an exposed wire at Row " << pRow - 1 << " ,column " << pCol + 1 << "." << endl;
                        Gamecontinue = false;
                        break;
                    }
                    else if (arr[pRow - 1][pCol + 1] == Main_switch)
                    {
                        Main_Switch = true;
                        break;
                    }
                    break;

                case 'c': // moving the player the South west
                case 'C':
                    if (pRow + 1 > r || pCol + 1 > r)
                    {
                        cout << "Operator may not move outside of Utopian city" << endl;
                        Pause();
                    }
                    else if (arr[pRow + 1][pCol + 1] == Space) // checking if the play move up
                    {
                        arr[pRow][pCol] = Space;
                        arr[pRow + 1][pCol + 1] = Player;
                        pRow += 1;
                        pCol += 1;
                        pEnergy -= 1;
                        break;
                    }
                    else if (arr[pRow + 1][pCol + 1] == battery) // checking if there is an energy unit to increase the players energy
                    {
                        arr[pRow + 1][pCol + 1] = Player;
                        arr[pRow][pCol] = Space;
                        pRow += 1;
                        pCol += 1;
                        pEnergy -= 1;
                        pEnergy += 5;
                        break;
                    }
                    else if (arr[pRow + 1][pCol + 1] == Wire) ////checking if there is mine
                    {
                        cout << "Player lost, Operator touched an exposed wire at Row " << pRow + 1 << " ,column " << pCol + 1 << "." << endl;
                        Gamecontinue = false;
                        break;
                    }
                    break;

                case 'q': // moving the player the North East
                case 'Q':
                    if (pRow - 1 < 0 || pCol - 1 < 0)
                    {
                        cout << "Operator may not move outside of Utopian city" << endl;
                        Pause();
                    }
                    else if (arr[pRow - 1][pCol - 1] == Space) // checking if the play move up
                    {
                        arr[pRow][pCol] = Space;
                        arr[pRow - 1][pCol - 1] = Player;
                        pRow -= 1;
                        pCol -= 1;
                        pEnergy -= 1;
                        break;
                    }
                    else if (arr[pRow - 1][pCol - 1] == battery) // checking if there is an energy unit to increase the players energy
                    {
                        arr[pRow - 1][pCol - 1] = Player;
                        arr[pRow][pCol] = Space;
                        pRow -= 1;
                        pCol -= 1;
                        pEnergy -= 1;
                        pEnergy += 5;
                        break;
                    }
                    else if (arr[pRow - 1][pCol - 1] == Wire) ////checking if there is mine
                    {
                        cout << "Player lost, Operator touched an exposed wire at Row " << pRow - 1 << " ,column " << pCol - 1 << "." << endl;
                        Gamecontinue = false;
                        break;
                    }
                    else if (arr[pRow - 1][pCol - 1] == Main_switch)
                    {
                        Main_Switch = true;
                        break;
                    }
                    break;

                case 'z': // moving the player the South East
                case 'Z':
                    if (pRow + 1 > r || pCol - 1 < 0)
                    {

                        cout << "Operator may not move outside of Utopian city" << endl;
                        Pause();
                    }
                    else if (arr[pRow + 1][pCol - 1] == Space) // checking if the play move up
                    {
                        arr[pRow][pCol] = Space;
                        arr[pRow + 1][pCol - 1] = Player;
                        pRow += 1;
                        pCol -= 1;
                        pEnergy -= 1;
                        break;
                    }
                    else if (arr[pRow + 1][pCol - 1] == battery) // checking if there is an energy unit to increase the players energy
                    {
                        arr[pRow + 1][pCol - 1] = Player;
                        arr[pRow][pCol] = Space;
                        pRow += 1;
                        pCol -= 1;
                        pEnergy -= 1;
                        pEnergy += 5;
                        break;
                    }
                    else if (arr[pRow + 1][pCol - 1] == Wire) ////checking if there is mine
                    {
                        cout << "Player lost, Operator touched an exposed wire at Row " << pRow + 1 << " ,column " << pCol - 1 << "." << endl;
                        Gamecontinue = false;
                        break;
                    }
                    break;

                case 'k': // option for player to quit the game.
                case 'K':
                    cout << "You quit the game, better luck next time" << endl;
                    Pause();
                    Gamecontinue = false;
                    break;

                default:
                    cerr << "Invalid input. " << endl;
                    Pause();
                }
            }
            }
             else
            {
                cout << "Congratulations, you have WON, you reached your destination!!!" << endl << endl;
                Display(arr, r, c, pEnergy);
                Gamecontinue = false;
                Pause();
            }
        } while (Gamecontinue);
    }
}
