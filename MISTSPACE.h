#ifndef MISTSPACE_H
#define MISTSAPCE_H

#include <iostream>
#include <sstream>
#include <random>
#include <cstdlib>

using namespace std;

namespace MistSpace
{
    // Rangechecking
    const int minRow = 2, maxRow = 12, minCol = 2, maxCol = 12;

    // Error codes.
    const int ERR_ARGC = -1;
    const int ERR_Range = -2;
    const int ERR_Exit = -3;
    const int Quit = -4;

    int string_to_int(string str);
    int gen_rand(int low, int high);

    // Game pieces
    const int num_main = 1;
    const char blank = ' ';
    const char Space = '.';
    const char Player = 'O';
    const char battery = 'B';
    const char Wire = 'W';
    const char Main_switch = 'M';

    typedef char *One_D_Array;
    typedef char **Two_D_Array;

    // setting up the game world
    Two_D_Array alloc2D(int row, int col);
    void Dealloc(Two_D_Array &arr, int row);
    void Display(Two_D_Array &arr, int row, int col, int playerE);
    void Display_Mist(Two_D_Array &arr, int row, int col, int operatorP, int Op_col, int &Op_row);
    void initialize_arr(Two_D_Array &arr, int row, int col);
    void placefeature(Two_D_Array &arr, int row, int col, const char feature, int num);
    void placeoperator(Two_D_Array &arr, int row, int col, char feature, int &pCol);
    void placeMain(Two_D_Array &arr, int row, int col, char feature);

    // Play the game.
    void Play_Game(Two_D_Array &arr, int &pRow, int &pCol, int pEnergy, int r, int c, bool Gamecontinue);
    void Pause();
    void check_Energy(int energy, bool resume);
}

#endif // MISTSPACE_H
