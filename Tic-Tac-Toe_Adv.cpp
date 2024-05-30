#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <windows.h>
#include <vector>
#include <climits>
#include <map>
using namespace std;
// +-----+-----+-----+
// |  O  |  X  |  X  |
// +-----+-----+-----+
// |  O  |  X  |  X  |
// +-----+-----+-----+
// |  O  |  O  |  O  |
// +-----+-----+-----+
map <char, int> m = {{'X', 1}, {'O', -1}, {'T', 0}};
void intro()
{
    HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("Copyright (c) 2024 ");
    SetConsoleTextAttribute(hc, 0x0A);
    printf("Kushanava Ghosh");
    SetConsoleTextAttribute(hc, 0x07);
    printf(". All Rights Reserved.\n");
    printf("========================================================\n");
    printf("                      TIC-TAC-TOE\n");
    printf("========================================================\n");
}
void setRowCol(int row, int col)
{
    HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
    int x = col, y = row;
    COORD screen;
    HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
    screen.X = x;
    screen.Y = y;
    SetConsoleCursorPosition(hd, screen);
}
char checkWinner(char a[3][3])
{
    if((a[0][0] == 'O' && a[0][1] == 'O' && a[0][2] == 'O')||
       (a[1][0] == 'O' && a[1][1] == 'O' && a[1][2] == 'O')||
       (a[2][0] == 'O' && a[2][1] == 'O' && a[2][2] == 'O')||
       (a[0][0] == 'O' && a[1][0] == 'O' && a[2][0] == 'O')||
       (a[0][1] == 'O' && a[1][1] == 'O' && a[2][1] == 'O')||
       (a[0][2] == 'O' && a[1][2] == 'O' && a[2][2] == 'O')||
       (a[0][0] == 'O' && a[1][1] == 'O' && a[2][2] == 'O')||
       (a[0][2] == 'O' && a[1][1] == 'O' && a[2][0] == 'O'))
    return 'O';
    else if((a[0][0] == 'X' && a[0][1] == 'X' && a[0][2] == 'X')||
            (a[1][0] == 'X' && a[1][1] == 'X' && a[1][2] == 'X')||
            (a[2][0] == 'X' && a[2][1] == 'X' && a[2][2] == 'X')||
            (a[0][0] == 'X' && a[1][0] == 'X' && a[2][0] == 'X')||
            (a[0][1] == 'X' && a[1][1] == 'X' && a[2][1] == 'X')||
            (a[0][2] == 'X' && a[1][2] == 'X' && a[2][2] == 'X')||
            (a[0][0] == 'X' && a[1][1] == 'X' && a[2][2] == 'X')||
            (a[0][2] == 'X' && a[1][1] == 'X' && a[2][0] == 'X'))
    return 'X';
    else
    {
        int t = 0;
        for(int i = 0; i<3; i++)
        {
            for(int j = 0; j<3; j++)
            {
                if(a[i][j] != '.')
                t++;
            }
        }
        if(t == 9)
        return 'T';
    }
    return 'C';
}
int minimax(char a[3][3], int depth, bool isMaximizing)
{
    char result = checkWinner(a);
    int bestScore;
    if(result != 'C')
    return m[result];
    if(isMaximizing)
    {
        int bestScore = INT_MIN;
        for(int i = 0; i<3; i++)
        {
            for(int j = 0; j<3; j++)
            {
                if(a[i][j] == '.')
                {
                    a[i][j] = 'X';
                    int score = minimax(a, depth+1, false);
                    a[i][j] = '.';
                    bestScore = max(score, bestScore);
                }
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = INT_MAX;
        for(int i = 0; i<3; i++)
        {
            for(int j = 0; j<3; j++)
            {
                if(a[i][j] == '.')
                {
                    a[i][j] = 'O';
                    int score = minimax(a, depth+1, true);
                    a[i][j] = '.';
                    bestScore = min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}
void optimalMove(char a[3][3])
{
    int bestScore = INT_MIN;
    pair<int,int> bestMove;
    if((a[0][0] == 'X' && a[1][1] == 'X' && a[2][2] == '.')||
        (a[0][2] == 'X' && a[1][2] == 'X' && a[2][2] == '.')||
        (a[2][0] == 'X' && a[2][1] == 'X' && a[2][2] == '.'))
        {
            a[2][2] = 'X';
            return;
        }
        else if((a[0][0] == 'X' && a[1][1] == '.' && a[2][2] == 'X')||
                (a[2][0] == 'X' && a[1][1] == '.' && a[0][2] == 'X')||
                (a[1][0] == 'X' && a[1][1] == '.' && a[1][2] == 'X')||
                (a[0][1] == 'X' && a[1][1] == '.' && a[2][1] == 'X'))
        {
            a[1][1] = 'X';
            return;
        }
        else if((a[0][0] == '.' && a[1][1] == 'X' && a[2][2] == 'X')||
                (a[0][0] == '.' && a[1][0] == 'X' && a[2][0] == 'X')||
                (a[0][0] == '.' && a[0][1] == 'X' && a[0][2] == 'X'))
        {
            a[0][0] = 'X';
        }
        else if((a[2][0] == 'X' && a[1][1] == 'X' && a[0][2] == '.')||
                (a[0][0] == 'X' && a[0][1] == 'X' && a[0][2] == '.')||
                (a[0][2] == '.' && a[1][2] == 'X' && a[2][2] == 'X'))
        {
            a[0][2] = 'X';
            return;
        }
        else if((a[2][0] == '.' && a[1][1] == 'X' && a[0][2] == 'X')||
                (a[0][0] == 'X' && a[1][0] == 'X' && a[2][0] == '.')||
                (a[2][0] == '.' && a[2][1] == 'X' && a[2][2] == 'X'))
        {
            a[2][0] = 'X';
            return;
        }
        else if((a[0][0] == 'X' && a[1][0] == '.' && a[2][0] == 'X')||
                (a[1][0] == '.' && a[1][1] == 'X' && a[1][2] == 'X'))
        {
            a[1][0] = 'X';
            return;
        }
        else if((a[0][0] == 'X' && a[0][1] == '.' && a[0][2] == 'X')||
                (a[0][1] == '.' && a[1][1] == 'X' && a[2][1] == 'X'))
        {
            a[0][1] = 'X';
            return;
        }
        else if((a[0][2] == 'X' && a[1][2] == '.' && a[2][2] == 'X')||
                (a[1][0] == 'X' && a[1][1] == 'X' && a[1][2] == '.'))
        {
            a[1][2] = 'X';
            return;
        }
        else if((a[2][0] == 'X' && a[2][1] == '.' && a[2][2] == 'X')||
                (a[0][1] == 'X' && a[1][1] == 'X' && a[2][1] == '.'))
        {
            a[2][1] = 'X';
            return;
        }
    for(int i = 0; i<3; i++)
    {
        for(int j = 0; j<3; j++)
        {
            if(a[i][j] == '.')
            {
                a[i][j] = 'X';
                int score = minimax(a, 0, false);
                a[i][j] = '.';
                if(score > bestScore)
                {
                    bestScore = score;
                    bestMove = {i,j};
                }
            }
        }
    }
    a[bestMove.first][bestMove.second] = 'X';
}
void dev()
{
    intro();
    printf("--> About Developer :- \n");
    printf(" This game is developed by Mr. Kushanava Ghosh who is\n");
    printf(" currently pursuing B.Tech in Mathematics and Computing at\n");
    printf(" Indian Institute of Technology Guwahati (2022-2026).\n");
    printf(" I belong from Kolkata, West Bengal but completed my \n");
    printf(" education in Ahmedabad, Gujarat. I have a keen\n");
    printf(" interest in Computer Programming. I know C, C++, Java,\n");
    printf(" Python well. I love to develop games.\n");
    printf("--------------------------------------------------------\n");
}
void version()
{
    HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
    intro();
    printf("              TIC-TAC-TOE Release Notes\n");
    printf("--------------------------------------------------------\n");
    printf("--> TIC-TAC-TOE Version 7.0 <--> To be decided\n");
    printf("1. New :- Introducing Elite Level.\n");
    printf("------ Currently Under Development ------\n\n");
    SetConsoleTextAttribute(hc, 0x02);
    printf("--> TIC-TAC-TOE Version 6.0 <--> 29-May-2024\n");
    printf("1. Introducing an Advanced Algorithm for Hard Level.\n");
    printf("2. Minor Bug Fixes.\n\n");
    SetConsoleTextAttribute(hc, 0x07);
    printf("--> TIC-TAC-TOE Version 5.0 <--> 29-Feb-2024\n");
    printf("1. New :- Introducing User Login Authentication Portal.\n");
    printf("-- Players can now Register and Login to play with Computer\n");
    printf("2. New :- Introducing Score History.\n");
    printf("-- Players can now view their score history which they played\n   since registration.\n");
    // printf("--> TIC-TAC-TOE Version 5.0 <--> 25-Dec-2022\n");
    // printf("1. New :- Introducing Token Choice.\n");
    // printf("-- Player can choose for 'O' or 'X' before starting the\n   round.\n");
    // printf("2. Minor Bug Fixes.\n\n");
    printf("--> TIC-TAC-TOE Version 4.0 <--> 27-Sept-2022\n");
    printf("1. New :- Introducing Versus Mode.\n");
    printf("-- Players can play on a 2 vs 2 mode.\n");
    printf("2. New :- Revised Scoring Pattern for 2 vs 2 mode.\n");
    printf("3. Minor Bug Fixes.\n\n");
    printf("--> TIC-TAC-TOE Version 3.0 <--> 04-Apr-2022\n");
    printf("1. New :- Introducing Level Mode.\n");
    printf("-- Player can now play choosing a level i.e Easy, Medium,\n   Hard against Computer.\n");
    printf("2. New :- Introducing Score Analysis.\n");
    printf("-- Player can now see their scores of each round at the\n   end of game.\n");
    printf("3. Improved Scoring Pattern.\n\n");
    printf("--> TIC-TAC-TOE Version 2.1 <--> 24-Mar-2022\n");
    printf("1. Improved Game Interface.\n");
    printf("2. Minor Bug Fixes.\n");
    printf("-- Crashing of game due to wrong input by user has been\n   resolved.\n\n");
    printf("--> TIC-TAC-TOE Version 2.0 <--> 15-Mar-2022\n");
    printf("1. New :- Introducing Scores.\n");
    printf("-- Player can now see their scores on the dashboard after\n   each round.\n");
    printf("2. Minor Bug Fixes.\n\n");
    printf("--> TIC-TAC-TOE Version 1.1 <--> 10-Feb-2022\n");
    printf("1. Minor Bug Fixes.\n");
    printf("-- More Time Consumption to play a move by Computer is\n   resolved.\n");
    printf("-- Some User Input Issues has been resolved.\n\n");
    printf("--> TIC-TAC-TOE Version 1.0 <--> 06-Feb-2022\n");
    printf("1. Worldwide Release !!!\n");
    printf("2. Ensured Smooth Running of Game.\n");
    printf("--------------------------------------------------------\n");
}
void cmode(char q)
{
    HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
    printf(" Mode :- ");
    SetConsoleTextAttribute(hc, 0x09);
    printf("vs COMPUTER");
    SetConsoleTextAttribute(hc, 0x07);
    printf("   v6.0   Difficulty Level :- ");
    if(q == 'E')
    {
        SetConsoleTextAttribute(hc, 0x02);
        printf("Easy\n");
        SetConsoleTextAttribute(hc, 0x07);
    }
    else if(q == 'M')
    {
        SetConsoleTextAttribute(hc, 0x06);
        printf("Medium\n");
        SetConsoleTextAttribute(hc, 0x07);
    }
    else if(q == 'H')
    {
        SetConsoleTextAttribute(hc, 0x0C);
        printf("Hard\n");
        SetConsoleTextAttribute(hc, 0x07);
    }
    printf("========================================================\n");
}
void show_score(char time[], char diff, int round, int sum, int score[])
{
    HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("\n Played On: ");
    SetConsoleTextAttribute(hc, 0x09);
    printf("%s\n",time);
    SetConsoleTextAttribute(hc, 0x07);
    printf("--------------------------------------------------------\n");
    printf(" Difficulty Level: ");
    if(diff == 'E')
    {
        SetConsoleTextAttribute(hc, 0x02);
        printf("Easy\n");
        SetConsoleTextAttribute(hc, 0x07);
    }
    else if(diff == 'M')
    {
        SetConsoleTextAttribute(hc, 0x06);
        printf("Medium\n");
        SetConsoleTextAttribute(hc, 0x07);
    }
    else if(diff == 'H')
    {
        SetConsoleTextAttribute(hc, 0x0C);
        printf("Hard\n");
        SetConsoleTextAttribute(hc, 0x07);
    }
    printf("--------------------------------------------------------\n");
    printf(" Round\t\t\tPoints\t\t\tStatus\n");
    printf("--------------------------------------------------------\n");
    for(int i = 0; i<round; i++)
    {
        printf("  %d\t\t\t  %d\t\t\t",i+1,score[i]*10);
        if(score[i] == 1)
        printf(" Win\n");
        else if(score[i] == -1)
        printf(" Lose\n");
        else
        printf(" Tie\n");
    }
    printf("--------------------------------------------------------\n");
    printf(" Final Score : %d\n",sum*10);
    printf("--------------------------------------------------------\n");
}
// Encryption function
void encrypt()
{
    FILE *fptr, *fptr1;
    char ch;
    fptr = fopen("Account.txt", "r");
    fptr1 = fopen("temp.txt", "w");
    ch = fgetc(fptr);
    while(ch != EOF)
    {   
        fprintf(fptr1, "%c", ch+311);
        ch = fgetc(fptr);
    }
    fclose(fptr);
    fclose(fptr1);
    remove("Account.txt");
    rename("temp.txt", "Account.txt");
}
// Decryption function
void decrypt()
{
    FILE *fptr, *fptr1;
    char ch;
    fptr = fopen("Account.txt", "r");
    fptr1 = fopen("temp.txt", "w");
    ch = fgetc(fptr);
    while(ch != EOF)
    {   
        fprintf(fptr1, "%c", ch-311);
        ch = fgetc(fptr);
    }
    fclose(fptr);
    fclose(fptr1);
    remove("Account.txt");
    rename("temp.txt", "Account.txt");
}
//Encryption for Scores
void encrypt_(char* user)
{
    FILE *fptr, *fptr1;
    char ch;
    fptr = fopen(user, "r");
    fptr1 = fopen("temp.txt", "w");
    ch = fgetc(fptr);
    while(ch != EOF)
    {   
        fprintf(fptr1, "%c", ch+127);
        ch = fgetc(fptr);
    }
    fclose(fptr);
    fclose(fptr1);
    remove(user);
    rename("temp.txt", user);
}
// Decryption for Scores
void decrypt_(char* user)
{
    FILE *fptr, *fptr1;
    char ch;
    fptr = fopen(user, "r");
    fptr1 = fopen("temp.txt", "w");
    ch = fgetc(fptr);
    while(ch != EOF)
    {   
        fprintf(fptr1, "%c", ch-127);
        ch = fgetc(fptr);
    }
    fclose(fptr);
    fclose(fptr1);
    remove(user);
    rename("temp.txt", user);
}
// User Authentication function
char* authenticate(int m)
{
    FILE *fptr, *fptr1;
    HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
    char user[100], pwd[100], ch, buf[100];
    int i, n, flag, count, count1;
    for(int i = 0; i<100; i++)
    {
        user[i] = '.';
        pwd[i] = '.';
    }
    char* USER = user;
    while(1)
    {
        intro();
        printf("\tWelcome to User Authentication Portal\n");
        printf("--------------------------------------------------------\n");
        SetConsoleTextAttribute(hc, 0x0D);
        printf("--> Press 1 to Login\n");
        SetConsoleTextAttribute(hc, 0x07);
        if(m == 1)
        {
            SetConsoleTextAttribute(hc, 0x0B);
            printf("--> Press 2 to Register\n");
            SetConsoleTextAttribute(hc, 0x04);
            printf("--> Press 3 to Manage Accounts\n");
            SetConsoleTextAttribute(hc, 0x07);
        }
        SetConsoleTextAttribute(hc, 0x06);
        printf("--> Press 4 to Return to Main Menu\n");
        SetConsoleTextAttribute(hc, 0x07);
        printf("--------------------------------------------------------\n");
        scanf("%d",&n);
        if(n == 4)
        {
            strcpy(USER, "4");
            return USER;
        }
        else if(n == 1)
        {
            system("cls");
            intro();
            flag = 0;
            decrypt();
            fptr = fopen("Account.txt","r");
            ch = fgetc(fptr);
            if(ch == EOF)
            {
                system("cls");
                intro();
                SetConsoleTextAttribute(hc, 0x09);
                printf("\t\t    No Account Exists.\n\t     Register to have one account.\n");
                SetConsoleTextAttribute(hc, 0x07);
                printf("--------------------------------------------------------\n");
                sleep(1);
                printf(" Redirecting to User Authentication Portal.....\n");
                fclose(fptr);
                encrypt();
                sleep(2);
                system("cls");
                continue;
            }
            fclose(fptr);
            encrypt();
            printf("\t\tWelcome to Login Portal\n");
            printf("--------------------------------------------------------\n");
            printf(" NOTE: All characters of username are treated as\n");
            printf("       lowercase letters.\n");
            printf("--------------------------------------------------------\n");
            printf(" Enter username: ");
            scanf("%s",user);
            for(int l = 0; l<strlen(user); l++)
            {
                if(user[l] >= 'A' && user[l] <= 'Z')
                user[l] += 32;
            }
            decrypt();
            fptr = fopen("Account.txt","r");
            count = 1;
            while(fscanf(fptr, "%s %*s ", buf) == 1)
            {
                if(!strcmp(buf, user))
                {
                    flag = 1;
                    break;
                }
                count++;
            }
            fclose(fptr);
            encrypt();
            if(!flag)
            {
                printf("--------------------------------------------------------\n");
                SetConsoleTextAttribute(hc, 0x0C);
                printf("\t\tUsername does not exist.\n\t\t     Login Failed.\n");
                SetConsoleTextAttribute(hc, 0x07);
                printf("--------------------------------------------------------\n");
                sleep(1);
                printf(" Redirecting to User Authentication Portal.....\n");
                sleep(2);
                system("cls");
                continue;
            }
            i = 0;
            printf(" Enter Password: ");
            while((ch = _getch()) != 13)
            {
                if(i == 0 && ch == '\b')
                continue;
                if(ch == '\t' || ch == ' ')
                pwd[i++] = '_';
                else
                pwd[i++] = ch;
                if(ch == '\b')
                {
                    if(i>0)
                    {
                        i--;
                        pwd[i--] = '.';
                        printf("\b \b");
                    }
                }
                else
                printf("*");
            }
            pwd[i] = '\0';
            printf("\n");
            getchar();
            flag = 0;
            decrypt();
            fptr = fopen("Account.txt","r");
            while(fscanf(fptr, "%*s %s ", buf) == 1)
            {
                if(!strcmp(buf, pwd) && count == 1)
                {
                    printf("--------------------------------------------------------\n");
                    SetConsoleTextAttribute(hc, 0x02);
                    printf("\t\t   Login Successful\n");
                    SetConsoleTextAttribute(hc, 0x07);
                    printf("--------------------------------------------------------\n");
                    fclose(fptr);
                    encrypt();
                    flag = 1;
                    sleep(2);
                    system("cls");
                    return USER;
                }
                count--;
            }
            if(!flag)
            {
                printf("--------------------------------------------------------\n");
                SetConsoleTextAttribute(hc, 0x04);
                printf("\t\t   Incorrect Password.\n");
                SetConsoleTextAttribute(hc, 0x07);
                printf("--------------------------------------------------------\n");
                fclose(fptr);
                encrypt();
                sleep(1);
                printf(" Redirecting to User Authentication Portal.....\n");
                sleep(3);
                system("cls");
                continue;
            }
        }
        else if(n == 2 && m == 1)
        {
            flag = 0;
            system("cls");
            intro();
            printf("\t     Welcome to Registration Portal\n");
            printf("--------------------------------------------------------\n");
            printf("\t      USERNAME AND PASSWORD POLICY\n");
            printf("--------------------------------------------------------\n");
            printf(" 1. Username should not start with a number.\n");
            printf(" 2. Password Length should contain atleast 5 characters.\n");
            printf(" 3. Space and Tab are equivalent to _ for passwords.\n");
            printf(" 4. Username must be lowercase letters if uppercase\n");
            printf(" letters are used than it will be converted automatically\n");
            printf(" to lowercase letters.\n");
            printf("--------------------------------------------------------\n");
            printf(" Enter Username: ");
            scanf("%s",user);
            for(int l = 0; l<strlen(user); l++)
            {
                if(user[l] >= 'A' && user[l] <= 'Z')
                user[l] += 32;
            }
            if(user[0] >= 48 && user[0] <= 57)
            {
                printf("--------------------------------------------------------\n");
                SetConsoleTextAttribute(hc, 0x04);
                printf("\t\t   Invalid Username\n");
                SetConsoleTextAttribute(hc, 0x07);
                printf("--------------------------------------------------------\n");
                sleep(1);
                printf(" Redirecting to User Authentication Portal.....\n");
                sleep(2);
                system("cls");
                continue;
            }
            decrypt();
            fptr = fopen("Account.txt","r");
            while(fscanf(fptr, "%s %*s ", buf) == 1)
            {
                if(!strcmp(buf, user))
                {
                    printf("--------------------------------------------------------\n");
                    SetConsoleTextAttribute(hc, 0x0C);
                    printf("\t\tUsername already exist.\n\t\t  Registration Failed.\n");
                    SetConsoleTextAttribute(hc, 0x07);
                    printf("--------------------------------------------------------\n");
                    sleep(1);
                    printf(" Redirecting to User Authentication Portal.....\n");
                    sleep(2);
                    system("cls");
                    flag = 1;
                    break;
                }
            }
            fclose(fptr);
            encrypt();
            if(flag)
            continue;
            i = 0;
            printf(" Enter Password: ");
            while((ch = _getch()) != 13)
            {
                if(i == 0 && ch == '\b')
                continue;
                if(ch == '\t' || ch == ' ')
                pwd[i++] = '_';
                else
                pwd[i++] = ch;
                if(ch == '\b')
                {
                    if(i>0)
                    {
                        i--;
                        pwd[i--] = '.';
                        printf("\b \b");
                    }
                }
                else
                printf("*");
            }
            pwd[i] = '\0';
            if(strlen(pwd) < 5)
            {
                printf("\n--------------------------------------------------------\n");
                SetConsoleTextAttribute(hc, 0x0C);
                printf("\t     Password Length is less than 5.\n");
                SetConsoleTextAttribute(hc, 0x07);
                printf("--------------------------------------------------------\n");
                sleep(1);
                printf(" Redirecting to User Authentication Portal.....\n");
                sleep(2);
                system("cls");
                continue;
            }
            printf("\n--------------------------------------------------------\n");
            SetConsoleTextAttribute(hc, 0x03);
            printf("\t\tRegistered Successfully\n");
            SetConsoleTextAttribute(hc, 0x07);
            printf("--------------------------------------------------------\n");
            sleep(1);
            printf(" Redirecting to User Authentication Portal.....\n");
            sleep(2);
            system("cls");
            decrypt();
            fptr = fopen("Account.txt","a");
            fprintf(fptr, "%s %s\n",user,pwd);
            fclose(fptr);
            encrypt();
            strcat(user, ".txt");
            fptr = fopen(user, "w");
            fclose(fptr);
        }
        else if(n == 3 && m == 1)
        {
            system("cls");
            intro();
            flag = 0;
            decrypt();
            fptr = fopen("Account.txt","r");
            ch = fgetc(fptr);
            if(ch == EOF)
            {
                system("cls");
                intro();
                SetConsoleTextAttribute(hc, 0x0C);
                printf("\t\t    No Account Exists.\n\t     Register to have one account.\n");
                SetConsoleTextAttribute(hc, 0x07);
                printf("--------------------------------------------------------\n");
                sleep(1);
                printf(" Redirecting to User Authentication Portal.....\n");
                fclose(fptr);
                encrypt();
                sleep(2);
                system("cls");
                continue;
            }
            fclose(fptr);
            encrypt();
            printf("\t\t    Manage Accounts\n");
            printf("--------------------------------------------------------\n");
            SetConsoleTextAttribute(hc, 0x04);
            printf("--> Press 1 to Delete Account\n");
            SetConsoleTextAttribute(hc, 0x09);
            printf("--> Press 2 to go back\n");
            SetConsoleTextAttribute(hc, 0x07);
            printf("--------------------------------------------------------\n");
            scanf("%d",&n);
            if(n == 1)
            {
                system("cls");
                intro();
                printf("\t\t     Delete Account\n");
                printf("--------------------------------------------------------\n");
                SetConsoleTextAttribute(hc, 0x04);
                printf(" Caution : Deleting Account will lead to loss of data.\n");
                SetConsoleTextAttribute(hc, 0x07);
                printf("--------------------------------------------------------\n");
                decrypt();
                fptr = fopen("Account.txt","r");
                ch = fgetc(fptr);
                if(ch == EOF)
                {
                    system("cls");
                    intro();
                    SetConsoleTextAttribute(hc, 0x0C);
                    printf("\t\t    No Account Exists.\n\t\t     Deletion failed.\n");
                    SetConsoleTextAttribute(hc, 0x07);
                    printf("--------------------------------------------------------\n");
                    sleep(1);
                    printf(" Redirecting to User Authentication Portal.....\n");
                    fclose(fptr);
                    encrypt();
                    sleep(2);
                    continue;
                }
                fclose(fptr);
                encrypt();
                printf(" Enter Username: ");
                scanf("%s",user);
                for(int l = 0; l<strlen(user); l++)
                {
                    if(user[l] >= 'A' && user[l] <= 'Z')
                    user[l] += 32;
                }
                decrypt();
                fptr = fopen("Account.txt","r");
                count = 1;
                while(fscanf(fptr, "%s %*s ", buf) == 1)
                {
                    if(!strcmp(buf, user))
                    {
                        flag = 1;
                        break;
                    }
                    count++;
                }
                fclose(fptr);
                encrypt();
                if(!flag)
                {
                    printf("--------------------------------------------------------\n");
                    SetConsoleTextAttribute(hc, 0x0C);
                    printf("\t\tUsername does not exist.\n\t\t   Deletion Failed.\n");
                    SetConsoleTextAttribute(hc, 0x07);
                    printf("--------------------------------------------------------\n");
                    sleep(1);
                    printf(" Redirecting to User Authentication Portal.....\n");
                    sleep(2);
                    system("cls");
                    continue;
                }
                i = 0;
                printf(" Enter Password: ");
                while((ch = _getch()) != 13)
                {
                    if(i == 0 && ch == '\b')
                    continue;
                    if(ch == '\t' || ch == ' ')
                    pwd[i++] = '_';
                    else
                    pwd[i++] = ch;
                    if(ch == '\b')
                    {
                        if(i>0)
                        {
                            i--;
                            pwd[i--] = '.';
                            printf("\b \b");
                        }
                    }
                    else
                    printf("*");
                }
                pwd[i] = '\0';
                printf("\n");
                getchar();
                flag = 0;
                decrypt();
                fptr = fopen("Account.txt","r");
                while(fscanf(fptr, "%*s %s ", buf) == 1)
                {
                    if(!strcmp(buf, pwd) && count == 1)
                    {
                        printf("--------------------------------------------------------\n");
                        SetConsoleTextAttribute(hc, 0x02);
                        printf("\t     Account Deleted Successfully\n");
                        SetConsoleTextAttribute(hc, 0x07);
                        printf("--------------------------------------------------------\n");
                        fclose(fptr);
                        encrypt();
                        sleep(1);
                        flag = 1;
                        printf(" Redirecting to User Authentication Portal.....\n");
                        sleep(2);
                        system("cls");
                        decrypt();
                        fptr = fopen("Account.txt","r");
                        count1 = 1;
                        while(fscanf(fptr, "%s %*s ", buf) == 1)
                        {
                            if(!strcmp(buf, user))
                            {
                                flag = 1;
                                break;
                            }
                            count1++;
                        }
                        fclose(fptr);
                        fptr = fopen("Account.txt", "r");
                        fptr1 = fopen("temp.txt", "w");
                        while((ch = fgetc(fptr)) != EOF)
                        {
                            if(count1 != 1)
                            fprintf(fptr1, "%c",ch);
                            if(ch == '\n')
                            count1--;
                        }
                        fprintf(fptr, "\b");
                        strcat(user, ".txt");
                        remove(user);
                        fclose(fptr);
                        fclose(fptr1);
                        remove("Account.txt");
                        rename("temp.txt", "Account.txt");
                        encrypt();
                        break;
                    }
                    count--;
                }
                if(!flag)
                {
                    printf("--------------------------------------------------------\n");
                    SetConsoleTextAttribute(hc, 0x04);
                    printf("\t\t   Incorrect Password.\n");
                    SetConsoleTextAttribute(hc, 0x07);
                    printf("--------------------------------------------------------\n");
                    fclose(fptr);
                    encrypt();
                    sleep(1);
                    printf(" Redirecting to User Authentication Portal.....\n");
                    sleep(3);
                    system("cls");
                    continue;
                }
                continue;
            }
            else if(n == 2)
            {
                system("cls");
                continue;
            }
        }
    }
}
int main()
{
    char a[3][3], c, h, ch;
    FILE* fptr;
    char* USER = (char*)malloc(100*sizeof(char));
    int x, y, z, w, k, t, flag, sum = 0, sum1 = 0, n = 1, m, v = -1, b[10000], d[10000], it, r, first = 0;
    vector <pair<int, int>> move, move_h;
    time_t T = time(NULL);
    struct tm date = *localtime(&T);
    HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
    // Introduction
    printf(" Introducing the first ever Tic-Tac-Toe game in C environment.\n");
    sleep(5);
    printf("\t\tDeveloped & Created by Mr.Kushanava Ghosh\n");
    sleep(3);
    system("cls");
    printf(" Initiallizing database......\n");
    sleep(1.75);
    system("cls");
    printf(" Downloading data......\n");
    sleep(2);
    system("cls");
    printf(" Setting up Environment Variables......\n");
    sleep(1.75);
    system("cls");
    printf(" Creating interface......\n");
    sleep(1.75);
    system("cls");
    for(int i = 5; i>=0; i--)
    {
        system("cls");
        printf(" Game is starting in %d sec\n",i);
        sleep(1);
    }
    I:
    system("cls");
    intro();
    SetConsoleTextAttribute(hc, 0x09);
    printf("--> Press 1 to Play\n");
    SetConsoleTextAttribute(hc, 0x0D);
    printf("--> Press 2 to read Instructions\n");
    SetConsoleTextAttribute(hc, 0x06);
    printf("--> Press 3 to read Release Notes\n");
    SetConsoleTextAttribute(hc, 0x02);
    printf("--> Press 4 to read about Developer\n");
    SetConsoleTextAttribute(hc, 0x0B);
    printf("--> Press 5 to view Scores (only for Computer Mode)\n");
    SetConsoleTextAttribute(hc, 0x0C);
    printf("--> Press 6 to exit\n");
    SetConsoleTextAttribute(hc, 0x07);
    printf("========================================================\n");
    printf("                     Version 6.0\n");
    printf("========================================================\n");
    scanf("%d",&m);
    for(int i = 0; i>=0; i++)
    {
        if(m == 1)
        goto G;
        else if(m == 2)
        goto Y;
        else if(m == 3)
        {
            system("cls");
            version();
            printf("Press any key to return to Main Menu\n");
            getchar();
            scanf("%c",&h);
            goto I;
        }
        else if(m == 4)
        {
            system("cls");
            dev();
            printf("Press any key to return to Main Menu\n");
            getchar();
            scanf("%c",&h);
            goto I;
        }
        else if(m == 5)
        {
            system("cls");
            strcpy(USER, authenticate(2));
            if(!strcmp(USER, "4"))
            goto I;
            intro();
            printf(" Logged in as : ");
            SetConsoleTextAttribute(hc, 0x06);
            printf("%s\n", USER);
            SetConsoleTextAttribute(hc, 0x07);
            printf("========================================================\n");
            printf("--> PLAY HISTORY\n");
            printf("========================================================\n");
            strcat(USER, ".txt");
            decrypt_(USER);
            fptr = fopen(USER, "r");
            ch = fgetc(fptr);
            if(ch == EOF)
            {
                printf("\tPlay atleast 1 game to view scores.\n");
                fclose(fptr);
                sleep(2);
                goto I;
            }
            int lines = 0;
            while(ch != EOF)
            {
                if(ch == '\n')
                lines++;
                ch = fgetc(fptr);
            }
            fclose(fptr);
            fptr = fopen(USER, "r");
            for(int i = 0; i<lines; i++)
            {
                char timestamp[100];
                char diff;
                int round, sum;
                fscanf(fptr, "%100[^,],%c,%d,",timestamp, &diff, &round);
                int score[round];
                for(int j = 0; j<round; j++)
                fscanf(fptr, "%d,",&score[j]);
                fscanf(fptr, "%d\n",&sum);
                show_score(timestamp, diff, round, sum, score);
            }
            fclose(fptr);
            encrypt_(USER);
            printf("Press any key to return to Main Menu\n");
            scanf("%c",&h);
            goto I;
        }
        else
        goto Z;
    }
    // Instructions
    Y:
    system("cls");
    printf("Copyright (c) 2024 ");
    SetConsoleTextAttribute(hc, 0x0A);
    printf("Kushanava Ghosh");
    SetConsoleTextAttribute(hc, 0x07);
    printf(". All Rights Reserved. Version 6.0\n");
    printf("===================================================================================\n");
    printf("                           Instructions on how to play.\n");
    printf("===================================================================================\n");
    printf("1) You have been provided a 3x3 grid to play Tic-Tac-Toe game in which\n");
    printf("   the vacant spaces are denoted by '.'(dots).\n");
    printf("2) By default you (player) are assigned 'O'(Noughts) as the token whereas\n");
    printf("   Computer is assigned 'X'(Crosses) as the token. (for vs Computer Mode)\n");
    printf("2A) By default Player 1 is assigned 'O'(Noughts) as the token whereas\n");
    printf("   Player 2 is assigned 'X'(Crosses) as the token. (for vs Friend Mode)\n");
    printf("3) After each round of the game, the first move of the player & computer\n");
    printf("   get switched.\n");
    printf("3A) After each round of the game, the first move of the Player 1 & Player 2\n");
    printf("   get switched.\n");
    printf("4) For assigning the token you are required to enter the Row - coordinate \n");
    printf("   as well as the Column - coordinate of the point as per the grid system\n");
    printf("   given in the game.\n");
    printf(" For example:- \n");
    printf("    0 1 2                                      0 1 2\n");
    printf("  0 . . .                  Output            0 . . .\n");
    printf("  1 . . .                    =>              1 . . .\n");
    printf("  2 . . .                                    2 . O .\n\n");
    printf(" Enter Row - coordinate :- 2\n");
    printf(" Enter Column - coordinate :- 1\n\n");
    printf("5) The Scores is shown on the top left corner and the Round is shown on the\n");
    printf("   top right corner.\n\n");
    printf("----------------------------------- SCORES ---------------------------------\n");
    printf("                             --> vs COMPUTER <--\n");
    printf("-->If the player wins against Computer then he/she will be awarded 10 points.\n");
    printf("-->If the player loses against Computer then 10 points will be deducted as a\n");
    printf("   as a penalty.\n");
    printf("-->If the game ends in a tie then 0 points will be awarded to a player.\n");
    printf("                             --> vs FRIEND <--\n");
    printf("-->On winning, 20 points will be awarded to the respective player.\n");
    printf("-->On losing, 10 points will be deducted as a penalty from the respective player.\n");
    printf("-->If the game ends in a tie then 0 points will be awarded to each player.\n");
    printf("----------------------------------------------------------------------------\n\n");
    printf("6) To win the game either the player/Player 1 have to make symmetric figures in the\n");
    printf("   game or else the computer/Player 2 may win or the game may end in tie.\n");
    printf(" For Example :-\n");
    printf(" The player/Player 1 wins if \n");
    printf("    0 1 2           0 1 2           0 1 2\n");
    printf("  0 O X X         0 O X .         0 O O O\n");
    printf("  1 . O .         1 O X .         1 . X .\n");
    printf("  2 . . O         2 O . .         2 . . X\n");
    printf("\n The computer/Player 2 wins if \n");
    printf("    0 1 2           0 1 2           0 1 2\n");
    printf("  0 X X X         0 O X .         0 X O O\n");
    printf("  1 . O .         1 O X .         1 . X .\n");
    printf("  2 . . O         2 . X .         2 . . X\n");
    printf("\n The game ends in a tie in the following sequence \n");
    printf("    0 1 2\n");
    printf("  0 X X O\n");
    printf("  1 O O X\n");
    printf("  2 X O O\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("--> Press Enter to play (or) Press any other key to return to Main Menu.\n");
    getchar();
    scanf("%c",&c);
    if(c == 10)
    goto G;
    else
    goto I;
    // Selection of Mode
    G:
    system("cls");
    intro();
    printf("                       Select Mode\n");
    printf("--------------------------------------------------------\n");
    SetConsoleTextAttribute(hc, 0x0B);
    printf("--> Press 1 to play against Computer (Login Required)\n");
    SetConsoleTextAttribute(hc, 0x0D);
    printf("--> Press 2 to play against Friend\n");
    SetConsoleTextAttribute(hc, 0x07);
    printf("--------------------------------------------------------\n");
    getchar();
    scanf("%d",&m);
    if(m == 1)
    goto W;
    else if(m == 2)
    goto S;
    else
    goto G;
    //Pickup the difficulty level
    W:
    system("cls");
    strcpy(USER, authenticate(1));
    if(!strcmp(USER, "4"))
    goto I;
    setRowCol(0,0);
    intro();
    printf(" Mode : ");
    SetConsoleTextAttribute(hc, 0x09);
    printf("vs COMPUTER");
    SetConsoleTextAttribute(hc, 0x07);
    printf("\t\t\t\t   v6.0\n");
    printf("========================================================\n");
    printf(" Logged in as : ");
    SetConsoleTextAttribute(hc, 0x06);
    printf("%s\n", USER);
    SetConsoleTextAttribute(hc, 0x07);
    printf("========================================================\n");
    printf("                 Select Difficulty Level\n");
    printf("--------------------------------------------------------\n");
    SetConsoleTextAttribute(hc, 0x02);
    printf("--> Press E for Easy Level.\n");
    SetConsoleTextAttribute(hc, 0x06);
    printf("--> Press M for Medium Level.\n");
    SetConsoleTextAttribute(hc, 0x0C);
    printf("--> Press H for Hard Level.\n");
    SetConsoleTextAttribute(hc, 0x08);
    printf("--> Press A for Elite Level. (Coming Soon)\n");
    SetConsoleTextAttribute(hc, 0x07);
    printf("--------------------------------------------------------\n");
    while(1)
    {
        scanf("%c",&h);
        if(h == 'E' || h == 'M' || h == 'H')
        break;
        else
        goto W;
    }
    // Initialising the character array and the set of possible moves
    S:
    if(n%2 == 0)
    flag = 0;
    else
    flag = 1;
    move = {{0,0}, {0,1}, {0,2}, {1,0}, {1,1}, {1,2}, {2,0}, {2,1}, {2,2}};
    for(int i = 0; i<3; i++)
    {
        for(int j = 0; j<3; j++)
        {
            *(*(a+i)+j) = '.';
        }
    }
    // Displaying the moves
    A:
    system("cls");
    // b[2*n-1] = n;
    intro();
    if(m == 1)
    {
        cmode(h);
        printf(" Logged in as : ");
        SetConsoleTextAttribute(hc, 0x06);
        printf("%s\n", USER);
        SetConsoleTextAttribute(hc, 0x07);
        printf("========================================================\n");
        if(flag == 1 && v<0)
        printf("                     Player's Turn\n");
        else if(flag == 0 && v<0)
        printf("                   Computer's Turn\n");
        else if(v == 0 || v == 1 || v == 2)
        printf("                       Game Over\n");
        printf("--------------------------------------------------------\n");
        printf(" Score = %d                                  Round : %d\n",sum,n);
    }
    else if(m == 2)
    {
        printf(" Mode : ");
        SetConsoleTextAttribute(hc, 0x06);
        printf("vs FRIEND");
        SetConsoleTextAttribute(hc, 0x07);
        printf("\t\t\t\t   v6.0\n");
        printf("========================================================\n");
        if(flag == 1 && v<0)
        printf("                    Player 1's Turn\n");
        else if(flag == 0 && v<0)
        printf("                    Player 2's Turn\n");
        else if(v == 0 || v == 1 || v == 2)
        printf("                       Game Over\n");
        printf("--------------------------------------------------------\n");
        printf("                      ROUND : %d\n",n);
        printf("--------------------------------------------------------\n");
        printf(" Player 1's Score = %d              Player 2's Score = %d\n",sum,sum1);
    }
    printf("\t      +-----+-----+-----+-----+\n");
    printf("\t      |  *  |  0  |  1  |  2  |\n");
    printf("\t      +-----+-----+-----+-----+\n");
    for(int i = 0; i<3; i++)
    {
        printf("\t      |  %d  |  %c  |  %c  |  %c  |\n",i,*(*(a+i)+0), *(*(a+i)+1), *(*(a+i)+2));
        printf("\t      +-----+-----+-----+-----+\n");
    }
    printf("\n");
    if(v == 0 && m == 1)
    {
        printf("--------------------------------------------------------\n");
        SetConsoleTextAttribute(hc, 0x02);
        printf("\t\tCongratulations!!! You won :)\n");
        SetConsoleTextAttribute(hc, 0x07);
        printf("--------------------------------------------------------\n");
        v = -1;
        goto C;
    }
    else if(v == 1 && m == 1)
    {
        printf("--------------------------------------------------------\n");
        SetConsoleTextAttribute(hc, 0x0C);
        printf("\t\tUnfortunately, You Lose :(\n");
        SetConsoleTextAttribute(hc, 0x07);
        printf("--------------------------------------------------------\n");
        v = -1;
        goto C;
    }
    else if(v == 2 && m == 1)
    {
        printf("--------------------------------------------------------\n");
        SetConsoleTextAttribute(hc, 0x06);
        printf("\t\tThe game ended in a tie.\n");
        SetConsoleTextAttribute(hc, 0x07);
        printf("--------------------------------------------------------\n");
        v = -1;
        goto C;
    }
    else if(v == 0 && m == 2)
    {
        printf("Verdict :- Player 1 Won\n\n");
        v = -1;
        goto C;
    }
    else if(v == 1 && m == 2)
    {
        printf("Verdict :- Player 2 Won\n\n");
        v = -1;
        goto C;
    }
    else if(v == 2 && m == 2)
    {
        printf("Verdict :- Tie\n\n");
        v = -1;
        goto C;
    }
    // Checking the moves
    B:
    if((a[0][0] == 'O' && a[0][1] == 'O' && a[0][2] == 'O')||
       (a[1][0] == 'O' && a[1][1] == 'O' && a[1][2] == 'O')||
       (a[2][0] == 'O' && a[2][1] == 'O' && a[2][2] == 'O')||
       (a[0][0] == 'O' && a[1][0] == 'O' && a[2][0] == 'O')||
       (a[0][1] == 'O' && a[1][1] == 'O' && a[2][1] == 'O')||
       (a[0][2] == 'O' && a[1][2] == 'O' && a[2][2] == 'O')||
       (a[0][0] == 'O' && a[1][1] == 'O' && a[2][2] == 'O')||
       (a[0][2] == 'O' && a[1][1] == 'O' && a[2][0] == 'O'))
    {
        if(m == 1)
        {
            sum+=10;
            b[n-1] = 10;
            v = 0;
            goto A;
        }
        else if(m == 2)
        {
            sum+=20;
            sum1-=10;
            b[n-1] = 20;
            d[n-1] = -10;
            v = 0;
            goto A;
        }
    }
    else if((a[0][0] == 'X' && a[0][1] == 'X' && a[0][2] == 'X')||
            (a[1][0] == 'X' && a[1][1] == 'X' && a[1][2] == 'X')||
            (a[2][0] == 'X' && a[2][1] == 'X' && a[2][2] == 'X')||
            (a[0][0] == 'X' && a[1][0] == 'X' && a[2][0] == 'X')||
            (a[0][1] == 'X' && a[1][1] == 'X' && a[2][1] == 'X')||
            (a[0][2] == 'X' && a[1][2] == 'X' && a[2][2] == 'X')||
            (a[0][0] == 'X' && a[1][1] == 'X' && a[2][2] == 'X')||
            (a[0][2] == 'X' && a[1][1] == 'X' && a[2][0] == 'X'))
    {
        if(m == 1)
        {
            sum-=10;
            b[n-1] = -10;
            v = 1;
            goto A;
        }
        else if(m == 2)
        {
            sum1+=20;
            sum-=10;
            b[n-1] = -10;
            d[n-1] = 20;
            v = 1;
            goto A;
        }
    }
    else
    {
        t = 0;
        for(int i = 0; i<3; i++)
        {
            for(int j = 0; j<3; j++)
            {
                if(a[i][j] != '.')
                t++;
            }
        }
        if(t == 9)
        {
            b[n-1] = 0;
            v = 2;
            goto A;
        }
    }
    if(m == 1)
    {
        if(flag == 1)
        goto D;
        else
        goto E;
    }
    else if(m == 2)
    {
        if(flag == 1)
        goto D;
        else
        goto F;
    }
    // Player Makes a Move
    D:
    k = 0;
    printf("Enter Row-Coordinate :- ");
    scanf("%d",&x);
    printf("Enter Column-Coordinate :- ");
    scanf("%d",&y);
    if(x >= 0 && y >= 0 && x < 3 && y < 3 && a[x][y] == '.')
    {
        a[x][y] = 'O';
        int it = 0;
        for(auto j:move)
        {
            if(j.first == x && j.second == y)
            {
                move.erase(move.begin()+it);
                break;
            }
            else
            it++;
        }
        flag = 0;
        goto A;
    }
    else
    goto A;
    // Player 2 makes a move
    F:
    k = 0;
    printf("Enter Row-Coordinate :- ");
    scanf("%d",&x);
    printf("Enter Column-Coordinate :- ");
    scanf("%d",&y);
    
    if(x >= 0 && y >= 0 && x < 3 && y < 3 && a[x][y] == '.')
    {
        a[x][y] = 'X';
        flag = 1;
        goto A;
    }
    else
    goto A;
    // Computer makes a move
    E:
    if(h == 'H')
    {
        int count = 0;
        for(int i = 0; i<3; i++)
        for(int j = 0; j<3; j++)
        if(a[i][j] == '.')
        count++;
        if(count == 9)
        first = 1;
        else
        first = 0;
        if(first)
        {
            move_h = {{0,0},{0,2},{2,0},{2,2}};
            srand(time(0));
            int t_h = rand()%(move_h.size());
            z = move_h[t_h].first;
            w = move_h[t_h].second;
            a[z][w] = 'X';
        }
        else
        optimalMove(a);
    }
    else
    {
        while(1)
        {
            // Favor of Computer
            if(((a[0][0] == 'X' && a[1][1] == 'X' && a[2][2] == '.')||
            (a[0][2] == 'X' && a[1][2] == 'X' && a[2][2] == '.')||
            (a[2][0] == 'X' && a[2][1] == 'X' && a[2][2] == '.')) && (h == 'E' || h == 'M'))
            {
                z = 2;
                w = 2;
            }
            else if(((a[0][0] == 'X' && a[1][1] == '.' && a[2][2] == 'X')||
                    (a[2][0] == 'X' && a[1][1] == '.' && a[0][2] == 'X')||
                    (a[1][0] == 'X' && a[1][1] == '.' && a[1][2] == 'X')||
                    (a[0][1] == 'X' && a[1][1] == '.' && a[2][1] == 'X')) && (h == 'E' || h == 'M'))
            {
                z = 1;
                w = 1;
            }
            else if(((a[0][0] == '.' && a[1][1] == 'X' && a[2][2] == 'X')||
                    (a[0][0] == '.' && a[1][0] == 'X' && a[2][0] == 'X')||
                    (a[0][0] == '.' && a[0][1] == 'X' && a[0][2] == 'X')) && (h == 'E' || h == 'M'))
            {
                z = 0;
                w = 0;
            }
            else if(((a[2][0] == 'X' && a[1][1] == 'X' && a[0][2] == '.')||
                    (a[0][0] == 'X' && a[0][1] == 'X' && a[0][2] == '.')||
                    (a[0][2] == '.' && a[1][2] == 'X' && a[2][2] == 'X')) && (h == 'E' || h == 'M'))
            {
                z = 0;
                w = 2;
            }
            else if(((a[2][0] == '.' && a[1][1] == 'X' && a[0][2] == 'X')||
                    (a[0][0] == 'X' && a[1][0] == 'X' && a[2][0] == '.')||
                    (a[2][0] == '.' && a[2][1] == 'X' && a[2][2] == 'X')) && (h == 'E' || h == 'M'))
            {
                z = 2;
                w = 0;
            }
            else if(((a[0][0] == 'X' && a[1][0] == '.' && a[2][0] == 'X')||
                    (a[1][0] == '.' && a[1][1] == 'X' && a[1][2] == 'X')) && (h == 'E' || h == 'M'))
            {
                z = 1;
                w = 0;
            }
            else if(((a[0][0] == 'X' && a[0][1] == '.' && a[0][2] == 'X')||
                    (a[0][1] == '.' && a[1][1] == 'X' && a[2][1] == 'X')) && (h == 'E' || h == 'M'))
            {
                z = 0;
                w = 1;
            }
            else if(((a[0][2] == 'X' && a[1][2] == '.' && a[2][2] == 'X')||
                    (a[1][0] == 'X' && a[1][1] == 'X' && a[1][2] == '.')) && (h == 'E' || h == 'M'))
            {
                z = 1;
                w = 2;
            }
            else if(((a[2][0] == 'X' && a[2][1] == '.' && a[2][2] == 'X')||
                    (a[0][1] == 'X' && a[1][1] == 'X' && a[2][1] == '.')) && (h == 'E' || h == 'M'))
            {
                z = 2;
                w = 1;
            }
            
            // Against Player
            else if(((a[0][0] == 'O' && a[1][1] == 'O' && a[2][2] == '.')||
                    (a[0][2] == 'O' && a[1][2] == 'O' && a[2][2] == '.')||
                    (a[2][0] == 'O' && a[2][1] == 'O' && a[2][2] == '.'))
                    && h == 'M')
            {
                z = 2;
                w = 2;
            }
            else if(((a[0][0] == 'O' && a[1][1] == '.' && a[2][2] == 'O')||
                    (a[2][0] == 'O' && a[1][1] == '.' && a[0][2] == 'O')||
                    (a[1][0] == 'O' && a[1][1] == '.' && a[1][2] == 'O')||
                    (a[0][1] == 'O' && a[1][1] == '.' && a[2][1] == 'O'))
                    && h == 'M')
            {
                z = 1;
                w = 1;
            }
            else if(((a[0][0] == '.' && a[1][1] == 'O' && a[2][2] == 'O')||
                    (a[0][0] == '.' && a[1][0] == 'O' && a[2][0] == 'O')||
                    (a[0][0] == '.' && a[0][1] == 'O' && a[0][2] == 'O'))
                    && h == 'M')
            {
                z = 0;
                w = 0;
            }
            else if(((a[2][0] == 'O' && a[1][1] == 'O' && a[0][2] == '.')||
                    (a[0][0] == 'O' && a[0][1] == 'O' && a[0][2] == '.')||
                    (a[0][2] == '.' && a[1][2] == 'O' && a[2][2] == 'O'))
                    && h == 'M')
            {
                z = 0;
                w = 2;
            }
            else if(((a[2][0] == '.' && a[1][1] == 'O' && a[0][2] == 'O')||
                    (a[0][0] == 'O' && a[1][0] == 'O' && a[2][0] == '.')||
                    (a[2][0] == '.' && a[2][1] == 'O' && a[2][2] == 'O'))
                    && h == 'M')
            {
                z = 2;
                w = 0;
            }
            else if(((a[0][0] == 'O' && a[1][0] == '.' && a[2][0] == 'O')||
                    (a[1][0] == '.' && a[1][1] == 'O' && a[1][2] == 'O'))
                    && h == 'M')
            {
                z = 1;
                w = 0;
            }
            else if(((a[0][0] == 'O' && a[0][1] == '.' && a[0][2] == 'O')||
                    (a[0][1] == '.' && a[1][1] == 'O' && a[2][1] == 'O'))
                    && h == 'M')
            {
                z = 0;
                w = 1;
            }
            else if(((a[0][2] == 'O' && a[1][2] == '.' && a[2][2] == 'O')||
                    (a[1][0] == 'O' && a[1][1] == 'O' && a[1][2] == '.'))
                    && h == 'M')
            {
                z = 1;
                w = 2;
            }
            else if(((a[2][0] == 'O' && a[2][1] == '.' && a[2][2] == 'O')||
                    (a[0][1] == 'O' && a[1][1] == 'O' && a[2][1] == '.'))
                    && h == 'M')
            {
                z = 2;
                w = 1;
            }
            else
            {
                srand(time(0));
                r = rand()%(move.size());
                z = move[r].first;
                w = move[r].second;
            }
            if(a[z][w] == '.')
            {
                a[z][w] = 'X';
                it = 0;
                for(auto j:move)
                {
                    if(j.first == z && j.second == w)
                    {
                        move.erase(move.begin()+it);
                        break;
                    }
                    else
                    it++;
                }
                break;
            }
        }
    }
    flag = 1;
    goto A;
    C:
    printf("Do you want to play again?\n--> Press Enter to Play (or)\n");
    printf("--> Press any other key to View Final Scores.\n");
    getchar();
    scanf("%c",&c);
    if(c == 10)
    {
        n++;
        goto S;
    }
    else
    {
        system("cls");
        intro();
        if(m == 1)
        {
            cmode(h);
            printf(" Logged in as : ");
            SetConsoleTextAttribute(hc, 0x06);
            printf("%s\n", USER);
            SetConsoleTextAttribute(hc, 0x07);
            printf("========================================================\n");
            printf(" Final Score : %d\n",sum);
            printf("--------------------------------------------------------\n");
            strcat(USER, ".txt");
            decrypt_(USER);
            fptr = fopen(USER, "a");
            fprintf(fptr, "%02d-%02d-%d %02d:%02d:%02d,%c,%d,", date.tm_mday, date.tm_mon+1, date.tm_year+1900, date.tm_hour, date.tm_min, date.tm_sec, h, n);
            for(int i = 0; i<n; i++)
            fprintf(fptr, "%d,",b[i]/10);
            fprintf(fptr, "%d\n",sum/10);
            fclose(fptr);
            encrypt_(USER);
        }
        else if(m == 2)
        {
            printf("Mode :- ");
            SetConsoleTextAttribute(hc, 0x06);
            printf("vs FRIEND\n");
            SetConsoleTextAttribute(hc, 0x07);
            printf("========================================================\n");
            printf("                     FINAL SCORES\n");
            printf("========================================================\n");
            printf(" Player 1 : %d                          Player 2 : %d\n\n",sum,sum1);
        }
        printf("--> Press Enter to view the Score Analysis (or) \n--> Press any other key to exit.\n");
        getchar();
        scanf("%c",&c);
        if(c == 10)
        goto X;
        else
        goto Z;
    }
    X:
    system("cls");
    intro();
    printf("                     Score Analysis\n");
    printf("========================================================\n");
    if(m == 1)
    {
        cmode(h);
        printf(" Logged in as : ");
        SetConsoleTextAttribute(hc, 0x06);
        printf("%.*s\n", (int)(strchr(USER, '.')-USER), USER);
        SetConsoleTextAttribute(hc, 0x07);
        printf("========================================================\n");
        printf("Round\t\t\tPoints\t\t\tStatus\n");
        printf("--------------------------------------------------------\n");
        for(int i = 0; i<n; i++)
        {
            printf("  %d\t\t\t  %d\t\t\t",i+1,b[i]);
            if(b[i] == 10)
            printf(" Win\n");
            else if(b[i] == -10)
            printf(" Lose\n");
            else
            printf(" Tie\n");
        }
        printf("--------------------------------------------------------\n");
        printf(" Final Score :- %d\n",sum);
        printf("--------------------------------------------------------\n");
    }
    else if(m == 2)
    {
        printf("Mode : ");
        SetConsoleTextAttribute(hc, 0x06);
        printf("vs FRIEND\n");
        SetConsoleTextAttribute(hc, 0x07);
        printf("========================================================\n");
        printf("Round\t\t\t\t\tWin Status\n");
        printf("--------------------------------------------------------\n");
        for(int i = 0; i<n; i+=2)
        {
            printf("  %d\t\t\t\t\t",i+1);
            if(b[i] == 20)
            printf(" Player 1\n");
            else if(b[i] == -10)
            printf(" Player 2\n");
            else
            printf(" Tie\n");
        }
        printf("========================================================\n");
        printf("                     FINAL SCORES\n");
        printf("========================================================\n");
        printf(" Player 1 : %d                          Player 2 : %d\n\n",sum,sum1);
    }
    printf("Press Enter or any other key to exit.\n");
    scanf("%c",&c);
    Z:
    system("cls");
    printf("The game is exited.\n");
    return 0;
}