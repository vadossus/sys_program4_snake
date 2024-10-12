// ConsoleApplication4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>

const int height = 10;
const int width = 20;
int x = 10;
int y = 5;
int f_x, f_y;

struct Node {
    Node* next;
    Node* prev;
    Node* data;

    Node(int value) : data(nullptr), next(nullptr), prev(nullptr) {};
};

class Snake {
private:
    Node* head;
    int score;
public:
   
    enum Dvizenie {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        END
    };

    Dvizenie move;

    Snake() {
        head = new Node(0);
        move = END;
        f_x = rand() % (width - 2) + 1;
        f_y = rand() % (height - 2) + 1;
        score = 0;
    }



    void Move()
    {
        if (_kbhit())
        {
            int key = _getch();
            switch (key)
            {
            case 'a':
            {
                move = LEFT;
                break;
            }
            case 's':
            {
                move = DOWN;
                break;
            }
            case 'd':
            {
                move = RIGHT;
                break;
            }
            case 'w':
            {
                move = UP;
                break;
            }
            }
        }
    }

    void end()
    {
        std::cout << "Конец игры!" << std::endl;
        exit(0);
    }

    void print()
    {
        system("cls");

        std::cout << "Счёт: " << score << std::endl;

        for (int i = 0; i < width; i++)
        {
            std::cout << "#";
        }
        std::cout << std::endl;


        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (j == 0 || j == width - 1)
                {
                    std::cout << "#";
                }
                else if (i == y && j == x)
                {
                    std::cout << "0";
                }
                else if (i == f_y && j == f_x)
                {
                    std::cout << "*";
                }
                else
                {
                    std::cout << " ";
                }    
            }
            std::cout << std::endl;
        }

        for (int i = 0; i < width; i++)
        {
            std::cout << "#";
        }
        std::cout << std::endl;

    }

    void functional()
    {
        switch (move)
        {
            case LEFT:
            {
                x--;
                break;
            }
            case RIGHT:
            {
                x++;
                break;
            }
            case UP:
            {
                y--;
                break;
            }
            case DOWN:
            {
                y++;
                break;
            }
        }

        Node* n_head = new Node(0);
        n_head->next = head;
        head = n_head;

        if (x != f_x || y != f_y)
        {
            Node* cur = head;
            while (cur->next->next != nullptr)
            {
                cur = cur->next;
            }
            delete cur->next;
            cur->next = nullptr;
        }


        if (x < 1 || x >= width - 1 || y < 0 || y >= height)
        {
            end();
        }

        if (x == f_x && y == f_y)
        {
            score++; 
            f_x = rand() % (width - 2) + 1; 
            f_y = rand() % (height - 2) + 1;
        }
    }
};


int main()
{
    setlocale(0, "rus");
    srand(time(0));
    Snake snake;
    
    while (true)
    {
        snake.Move();
        snake.print();
        snake.functional();
        Sleep(100);
    }
}

