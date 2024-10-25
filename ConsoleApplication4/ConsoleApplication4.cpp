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
    int x, y;
    Node* next;
    Node* prev;

    Node(int _x, int _y) : x(_x), y(_y), next(nullptr), prev(nullptr) {};
};

class Snake {
private:
    Node* head;
    Node* tail;
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
        head = new Node(x, y);
        tail = head;
        move = END;
        f_x = rand() % (width - 2) + 1;
        f_y = rand() % (height - 2) + 1;
        score = 0;
    }

    void Move() {
        if (_kbhit()) {
            int key = _getch();
            switch (key) {
            case 'a':
            {
                if (move != RIGHT) 
                    move = LEFT;
                break;
            }
            case 's':
            {
                if (move != UP) 
                    move = DOWN;
                break;
            }
            case 'd':
            {
                if (move != LEFT) 
                    move = RIGHT;
                break;
            }
            case 'w':
            {
                if (move != DOWN) 
                    move = UP;
                break;
            }
            }
        }
    }

    void end() {
        std::cout << "Конец игры!" << std::endl;
        exit(0);
    }

    void print() {
        system("cls");

        std::cout << "Счёт: " << score << std::endl;

        for (int i = 0; i < width; i++) {
            std::cout << "#";
        }
        std::cout << std::endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0 || j == width - 1) {
                    std::cout << "#";
                }
                else if (i == f_y && j == f_x) {
                    std::cout << "*";
                }
                else {
                    bool zmeika_povtor = false;
                    Node* cur = head;
                    while (cur != nullptr) {
                        if (cur->x == j && cur->y == i) {
                            if (cur == head) {
                                std::cout << "0";
                            }
                            else {
                                std::cout << "o";
                            }
                            zmeika_povtor = true;
                            break;
                        }
                        cur = cur->next;
                    }
                    if (!zmeika_povtor) {
                        std::cout << " ";
                    }
                }
            }
            std::cout << std::endl;
        }

        for (int i = 0; i < width; i++) {
            std::cout << "#";
        }
        std::cout << std::endl;
    }

    void functional() {
        switch (move) {
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

        Node* n_head = new Node(x, y);
        n_head->next = head;
        head->prev = n_head;
        head = n_head;

        if (x != f_x || y != f_y) {
            Node* cur = head;
            while (cur->next->next != nullptr) {
                cur = cur->next;
            }
            delete cur->next;
            cur->next = nullptr;
            tail = cur;
        }
        else {
            score++;
            f_x = rand() % (width - 2) + 1;
            f_y = rand() % (height - 2) + 1;
            Node* n_tail = new Node(tail->x, tail->y);
            tail->next = n_tail;
            n_tail->prev = tail;
            tail = n_tail;
        }

        if (x < 1 || x >= width - 1 || y < 0 || y >= height) {
            end();
        }

        Node* cur = head->next;
        while (cur != nullptr) {
            if (cur->x == x && cur->y == y) {
                end();
            }
            cur = cur->next;
        }
    }
};

int main() {
    setlocale(0, "rus");
    srand(time(0));
    Snake snake;

    while (true) {
        snake.Move();
        snake.print();
        snake.functional();
        Sleep(100);
    }
}
