/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  :
 * Student number:
 */
#include "huntWump.h"

int main()
{
    /**
    * Here's the main function. You can write the "main menu" loop/code
    * here or you can make separate functions - up to you.
    */

    startMenu();

    /* return EXIT_SUCCESS; */
    return 0;
}

void showStudentInformation()
{
    printf(
        "----------------------------------\n"
        "Name: %s\n"
        "Student ID: %s\n"
        "Email: %s\n"
        "----------------------------------\n"
        "\n",
        "Elliot Schot",
        "S3530160",
        "S3530160@student.rmit.edu.au");
}

#define INPUT_MAX_LENGTH 1
#define NEW_LINE_SPACE 1
#define NULL_SPACE 1
#define EXTRA_SPACES (NEW_LINE_SPACE + NULL_SPACE)

void showStartMenu()
{
    printf(
        "Welcome to Hunt the Wumpus\n"
        "--------------------------\n"
        "1. Play game\n"
        "2. Show student information\n"
        "3. Quit\n"
        "\n"
        "Please enter your choice: ");
}

void exitProgram()
{
    printf("Good bye! \n\n");
    exit(0);
}

void startMenu()
{
    char *inputEndPtr;
    char input;
    int inputInt;
    int readResult;
    Boolean ongoing;

    enableWindowsCompatibility();
    ongoing = TRUE;
    while (ongoing)
    {
        showStartMenu();
        readResult = readInput(&input, 1 + EXTRA_SPACES, stdin);

        putchar(10);
        if (readResult == ReadInputResultSuccess)
        {
            inputInt = strtol(&input, &inputEndPtr, 10);

            if (/* inputEndPtr == &input || *inputEndPtr  || */ inputInt <= 0 || inputInt > 3)
            {
                printInvalidInput();
            }
            else if (inputInt == 2)
            {
                showStudentInformation();
            }
            else if (inputInt == 3)
            {
                ongoing = FALSE;
            }
            else
            {
                if (inputInt != 1)
                {
                    assert(0);
                }
                /* printf("Play The Game!"); */
                game_PlayGame();
            }
        }
        else
        {
            printInvalidInput();
        }
    }
    exitProgram();
}