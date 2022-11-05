#include <iostream>
#include <cstdlib> // rand function
#include <ctime> // sleep
#include <Windows.h> // gotoxy
#include <conio.h> // kb hit

using namespace std;
const int height = 40; // fix dont want to change
const int width = 100;
int snake_size = 1; // snake starting length
int score = 0;
int fruitx = 15; // starting fruit display
int fruity = 15; //
bool gameover = false; // game end

struct point // snake
{
    int x;
    int y;
};

void gotoxy(int x, int y)
{

    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void boundary()
{

    for (int x = 10; x <= width; x++) // top wall
    {
        gotoxy(x, 5);
        cout << "=";
        Sleep(10);
    }

    for (int y = 6; y <= height - 2; y++) // right wall
    {
        gotoxy(width, y);
        cout << "|";
        Sleep(10);
    }

    for (int x = width; x >= 11; x--)  // bottom wall
    {
        gotoxy(x, height - 2);
        cout << "=";
        Sleep(10);
    }
    for (int y = height - 2; y >= 6; y--) // left wall
    {
        gotoxy(10, y);
        cout << "|";
        Sleep(15);
    }


    gotoxy(fruitx, fruity); // first time print
    cout << "X";

}

void Displaysnake(point p[])
{
    gotoxy(p[0].x, p[0].y);
    cout << "O";

    int i;
    for (i = 1; i < snake_size; i++)
    {
        gotoxy(p[i].x, p[i].y);
        cout << "o";

    }

}

void removesnake(point p[])
{
    for (int index = 0; index < snake_size; index++)
    {
        gotoxy(p[index].x, p[index].y);
        cout << " ";
    }

}

void Moveup(point p[])
{
    int index;

    for (index = snake_size; index > 0; index--)
    {
        p[index].x = p[index - 1].x;
        p[index].y = p[index - 1].y;

    }
    p[index].y = p[index].y - 1;
}

void Movedown(point p[])
{
    int index;
    for (index = snake_size; index > 0; index--)
    {
        p[index].x = p[index - 1].x;
        p[index].y = p[index - 1].y;

    }
    p[index].y = p[index].y + 1;
}

void Moveright(point p[])
{
    int index;
    for (index = snake_size; index > 0; index--)
    {
        p[index].x = p[index - 1].x;
        p[index].y = p[index - 1].y;

    }
    p[index].x = p[index].x + 1;
}

void Moveleft(point p[])
{
    int index;
    for (index = snake_size; index > 0; index--)
    {
        p[index].x = p[index - 1].x;
        p[index].y = p[index - 1].y;

    }
    p[index].x = p[index].x - 1;
}

void snake_movement(point p[], char input)
{

    if (input == 72)
    {
        Moveup(p);
    }
    else if (input == 80)
    {
        Movedown(p);
    }
    else if (input == 77)
    {
        Moveright(p);
    }
    else if (input == 75)
    {
        Moveleft(p);
    }

}

void boundary_check(point p[], int &score)
{

    if (p[0].y <= 5) // top wall
    {
        gameover = true;

        gotoxy(10, height);
        cout << "Game over!";
        gotoxy(10, height + 1);
        cout << "Your Score is: " << score;
        gotoxy(10, height + 3);
        system("PAUSE");

    }

    if (p[0].x > width - 1) // right wall

    {
        gameover = true;

        gotoxy(0, height);
        cout << "Game over!";
        gotoxy(10, height + 1);
        cout << "Your Score is: " << score;
        gotoxy(10, height + 3);
        system("PAUSE");

    }

    if (p[0].y > height - 3) // bottom wall

    {
        gameover = true;

        gotoxy(10, height);
        cout << "Game over!";
        gotoxy(10, height + 1);
        cout << "Your Score is: " << score;
        gotoxy(10, height + 3);
        system("PAUSE");

    }

    if (p[0].x < 11) // left wall
    {
        gameover = true;

        gotoxy(10, height);
        cout << "Game over!";
        gotoxy(10, height + 1);
        cout << "Your Score is: " << score;
        gotoxy(10, height + 3);
        system("PAUSE");

    }


    for (int index = 1; index < snake_size; index++) // snake touch itself
    {
        if (p[0].x == p[index].x && p[0].y == p[index].y)
        {
            gameover = true;

            gotoxy(10, height);
            cout << "Game over!";
            gotoxy(10, height + 1);
            cout << "Your Score is: " << score;
            gotoxy(10, height + 3);
            system("PAUSE");
        }
    }

}

void fruit(point p[], int& speed, int& score)
{
    if (p[0].x == fruitx && p[0].y == fruity)
    {

        fruitx = 10 + rand() % (width - 25);
        fruity = 10 + rand() % (height - 25);

        for (int i = 0; i < snake_size; i++)
        {
            if (fruitx == p[i].x && fruity == p[i].y)
            {
                fruitx = 10 + rand() % (width - 25);
                fruity = 10 + rand() % (height - 25);
            }
        }

        gotoxy(fruitx, fruity);

        cout << "X";
        score = score + 10;
        snake_size++;

        if (speed > 50)
        {
            speed = speed - 50;
        }
    }

}

void hurdles()
{
    int y = 17, x = 74;

    for (int h = 0; h < 8; h++)
    {
        gotoxy(x, y);
        cout << "*";
        x++;
    }

    x = 26;
    y = 27;


    for (int h = 0; h < 8; h++)
    {
        gotoxy(x, y);
        cout << "*";
        x++;
    }

}

int hurdle_End(point p[])
{
    if (p[0].y >= 17 && p[0].x >= 75)
    {
        if (p[0].y <= 21 && p[0].x <= 78)
            return 0;
    }
    else if (p[0].y >= 23 && p[0].x >= 26)
    {
        if (p[0].y <= 26 && p[0].x <= 31)
            return 0;
    }
    else
        return 1;
}

int hurdle1_end(point p[])
{
    if (p[0].x >= 74 && p[0].x <= 81 && p[0].y == 17)
    {
        return 0;
    }
}

int hurdle2_end(point p[])
{
    if (p[0].x >= 26 && p[0].x <= 33 && p[0].y == 27)
    {
        return 0;
	}
}
void game_setup()
{

    system("Color 80");
    int x;
    cout << endl << endl;
    cout << "\t\t\t\t\tSNAKE GAME" << endl << endl;
    cout << "\tInstructions" << endl << endl << endl;
    cout << "\tUSE Arrow KEYS TO MOVE SNAKE" << endl << endl << endl;
    cout << "\tPress 1 and Enter to Start Game: ";
    cin >> x;

    system("cls");

}

int main()
{
    game_setup();
    char input;
    char lastinput;
    int score = 0;
    int speed = 200;
    point p[300]; // snake size
    p[0].x = width / 2; // snake first time display
    p[0].y = height / 2;
    boundary();
    hurdles();

    while (gameover != true)
    {

        if (_kbhit())
        {
            lastinput = input;
            input = _getch();// 77745
            input = _getch();// 45
            //check_snake_movement_keys(p, lastinput, input);
        }


        Sleep(speed);
        removesnake(p);
        snake_movement(p, input);
        Displaysnake(p);

        gotoxy(10, height - 1);
        cout << "Score: " << score;

        fruit(p, speed, score);
        boundary_check(p, score);

        int snake_end = hurdle1_end(p);
        if (snake_end == 0)
        {
            break;
            system("pause");
        }
        int snake_end1 = hurdle2_end(p);
        if (snake_end1 == 0)
        {
            break;
            system("pause");
        }
    }

}

