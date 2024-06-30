// #include <iostream>
#include "MISTSPACE.h"
#include <time.h>
#include <cstdlib>

using namespace std;
using namespace MistSpace;

int main(int argc, char *argv[])
{

    int Num_rows, Num_cols, Num_battery, Num_wire;

    char Select;
    int Operator_power = 15;
    bool Resume = true;
    bool blncontinue = true;

    int OperatorR, OperatorC;

    srand(time(nullptr));

    if (argc != 5) // error handling for arguments.
    {
        cout << " Not enough number of arguments. " << endl;
        exit(ERR_ARGC);
    }

    Num_rows = string_to_int(argv[1]);
    Num_cols = string_to_int(argv[2]);
    Num_battery = (string_to_int(argv[3]) / 100.00) * (Num_rows * Num_cols);
    Num_wire = (string_to_int(argv[4]) / 100.00) * (Num_rows * Num_cols);

    // Range check
    if (Num_rows < minRow || Num_rows > maxRow || Num_cols < minCol || Num_cols > maxCol)
    {
        cout << "Number of rows must be less than " << minRow << " and greater than " << maxRow << "." << endl;
        cout << "Number of columns must be less than " << minCol << " and greater than " << maxCol << "." << endl;
        exit(ERR_Range);
    }

    // make the gameboard
    // Two_D_Array mist_space;
    // mist_space = alloc2D(Num_rows,Num_cols);
    // initialize_arr(mist_space,Num_rows,Num_cols);

    do
    {

        system("cls");

        cout << "Number of Rows: " << Num_rows << endl;
        cout << "Number  of columns: " << Num_cols << endl;
        cout << "Number of batteries: " << Num_battery << endl;
        cout << "Number of exposed wires: " << Num_wire << endl
             << endl;

        cout << "Welcome, Would you like to play  the game?" << endl
             << "Option A: Start the game." << endl
             << "Option X: Exit." << endl
             << endl;
        cin >> Select;

        switch (Select)
        {
        case 'a':
        case 'A':

            // make the gameboard
            Two_D_Array mist_space;
            mist_space = alloc2D(Num_rows, Num_cols);
            initialize_arr(mist_space, Num_rows, Num_cols);

            placefeature(mist_space, Num_rows, Num_cols, battery, Num_battery);
            placefeature(mist_space, Num_rows, Num_cols, Wire, Num_wire);

            OperatorR = Num_rows - 1;
            placeoperator(mist_space, Num_rows, Num_cols, Player, OperatorC);
            placeMain(mist_space, Num_rows, Num_cols, Main_switch);

            // Display(mist_space, Num_rows,Num_cols, Operator_power);
            cout << endl;

            // Display_Mist(mist_space,Num_rows,Num_cols,Operator_power,OperatorC,OperatorR);

            // Playing the game
            Play_Game(mist_space, OperatorR, OperatorC, Operator_power, Num_rows, Num_cols, Resume);

            // deallocating memory
            Dealloc(mist_space, Num_rows);

            break;

        case 'x':
        case 'X':
            cout << "Hope you had a good game, lets play again next time." << endl;
            Dealloc(mist_space, Num_rows);
            blncontinue = false;
            exit(ERR_Exit);
            break;

        default:
            cerr << "Invalid input " << endl;
            Pause();
            break;
        }
        // deallocating memory
        // Dealloc(mist_space,Num_rows);
        cout << endl;
        Pause();
    } while (blncontinue);

    // deallocating memory
    // Dealloc(mist_space,Num_rows);

    return 0;
}
