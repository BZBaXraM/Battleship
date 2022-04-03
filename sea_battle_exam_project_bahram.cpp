#include <iostream>
#include <ctime>
#include <Windows.h>
#include <iomanip>

using namespace std;
//FILE* file;

bool active_player = false;

int** createdArr(int n, int m); // Создаю динамический массив n на m

int** fiil_null(int** arr, int n, int m); // Нолики для массива

int testUP(int** arr, int n, int m, int tmp1, int tmp2,
    int numOfdecks); // Функ проверяет, можно ли расставлять корабли вверх от случайно определенной базовой координаты?

int testDown(int** arr, int n, int m, int tmp1, int tmp2,
    int numOfdecks); // Функ проверяет, можно ли расставлять корабли вниз от случайно определенной базовой координаты?

int testLeft(int** arr, int n, int m, int tmp1, int tmp2,
    int numOfdecks); // Функ проверяет, можно ли расставлять корабли влево от случайно определенной базовой координаты?

int testRight(int** arr, int n, int m, int tmp1, int tmp2,
    int numOfdecks); // Функ проверяет. можно ли расставлять корабли вправо от случайно определенной базовой координаты?

void rAnd(int** arr, int n, int m); // Установка кораблей рандомом

void attackComp(int** arr, int n, int m, int& attack_n_save, int& attack_m_save, bool& repeat,
    int& win); // Функ для стрелбы по корабл€м (ходит комп)

void attackPlayer(int** arr, int n, int m, int& win); // Функ для стрелбы по кораблям (хожу Я, то есть пользователь)

void bufferDeckHor(int** arr, int n, int m, int ii, int jj,
    int number_of_decks); // Функ для расстановки выстрелов вокруг уничтоженного корабля (по горизонтали)

void bufferDeckVer(int** arr, int n, int m, int ii, int jj,
    int number_of_decks); // Функ для расстановки выстрелов вокруг уничтоженного корабля (по вертикали)

int testKillHor(int** arr, int n, int m, int ii, int jj,
    int number_of_decks); // Функ для проверки по горизонтали, все ли палубы одного корабля уничтожены?

int testKillVer(int** arr, int n, int m, int ii, int jj,
    int number_of_decks); // Функ для расстановки выстрелов вокруг уничтоженного корабля (по вертикали)

void printPlayer(int** arr, int n, int m); // Функ для вывода поля игрока

void printComp(int** arr, int n, int m); // Функ для вывода пол€ компа

int testWin(int** arr, int n, int m);  // Функ для проверки на проигришь

void delArrMem(int** arr, int n); // Удаление динамического массива после игры

//void save(int** arr) {
//    fopen_s(&file, "data.dat", "wb");
//    fwrite((char*)arr, sizeof(int), 16, file);
//}
//
//void load(int** arr, int n, int m){
//    fopen_s(&file, "data.dat", "rb");
//    fread((char*)arr, sizeof(int), 16, file);
//}

int main() {
    srand(time(NULL));
    int n = 10;
    int m = 10;
    int win = 0;
    bool repeat = false;

    int select;
    int attack_n_save, attack_m_save;
    int** Player = createdArr(n, m);
    fiil_null(Player, 10, 10);
    rAnd(Player, n, m);
    int** Comp = createdArr(n, m);
    fiil_null(Comp, 10, 10);
    rAnd(Comp, n, m);

    cout << "\033[0;34m" << "\t\tSea Battle by Bahram Bayramzade \n";

    /*select = rand() % 2;*/
    select = 0;
    do {
        if (select == 0) {
            if (win == 0 && !active_player) {
                attackComp(Player, n, m, attack_n_save, attack_m_save, repeat, win);
            }
            if (win == 0 && active_player) {
                attackPlayer(Comp, n, m, win);
            }
            /*  else {
                  if (win == 0) {
                      attackPlayer(Comp, n, m, win);
                  }
                  if (win == 0) {
                      attackComp(Player, n, m, attack_n_save, attack_m_save, repeat, win);
                  }
              }*/
            if (win == 1) {
                cout << "\033[0;34m" << "Computer is win!\n";
            }
            if (win == 2) {
                cout << "\033[0;34m" << "Player is win!\n";
            }
        }
    } while (win == 0);
    delArrMem(Player, n);
    delArrMem(Comp, n);
    system("pause");



    return 0;
}

int** createdArr(int n, int m) {
    int** arr = new int* [n];
    for (int i = 0; i < n; ++i) {
        arr[i] = new int[m];
    }
    return arr;

} // создаю динамический массив n на m

int** fiil_null(int** arr, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; j++)
        {
            arr[i][j] = 0;

        }
    }
    return arr;

} // вывожу основной массив 

void rAnd(int** arr, int n, int m) {
    int number_of_ships = 1; //переменная для определения нужного количества кораблей
    int number_of_decks = 4; //переменная для определения нужного количества палуб
    while (number_of_decks != 0) {
        for (int ships = 0; ships < number_of_ships;) {
            int tmp1 = rand() % 10;
            int tmp2 = rand() % 10;
            int down = testDown(arr, n, m, tmp1, tmp2, number_of_decks);
            int up = testUP(arr, n, m, tmp1, tmp2, number_of_decks);
            int left = testLeft(arr, n, m, tmp1, tmp2, number_of_decks);
            int right = testRight(arr, n, m, tmp1, tmp2, number_of_decks);
            if ((up == 1 && down == 1) || (left == 1 && right == 1)) {
                bool test = false; // false
                int select;
                while (test != 1) {
                    select = rand() % 2;
                    if (select == 0 && right == 1 && left == 1) {
                        test = true;
                    }
                    if (select == 1 && up == 1 && down == 1) {
                        test = true;
                    }
                }
                if (select == 0) {
                    int k = 0; //переменная для хранения количества кораблей
                    for (int j = tmp2; j < (tmp2 + number_of_decks) && j < m; j++)  //цикл для построения палуб
                    {
                        arr[tmp1][j] = number_of_decks;
                        k++;
                    }
                    if (k !=
                        number_of_decks)  //если построены не все необходимые палубы - начинаем строить в обратном направлении до тех пор...
                    {
                        for (int j = tmp2; k != number_of_decks;) {
                            j--;
                            arr[tmp1][j] = number_of_decks;
                            k++;
                        }
                    }
                }
                else {
                    int k = 0;
                    for (int i = tmp1; i < (tmp1 + number_of_decks) && i < n; i++) {
                        arr[i][tmp2] = number_of_decks;
                        k++;
                    }
                    if (k != number_of_decks) {
                        for (int i = tmp1; k != number_of_decks;) {
                            i--;
                            arr[i][tmp2] = number_of_decks;
                            k++;
                        }
                    }
                }
                ships++;
            }
        }
        number_of_ships++;
        number_of_decks--;
    }
} // Установка кораблей рандомом

int testUP(int** arr, int n, int m, int tmp1, int tmp2, int numOfdecks) {
    int test = 1;
    int i, j;
    for (tmp1 == (n - 1) ? i = tmp1 : i = (tmp1 + 1); i >= (tmp1 - numOfdecks) && i >= 0; i--) {
        for (tmp2 == 0 ? j = tmp2 : j = (tmp2 - 1); j <= (tmp2 + 1) && j >= 0 && j < m; j++) {
            if (arr[i][j] == 1 || arr[i][j] == 2 || arr[i][j] == 3 || arr[i][j] == 4) {
                test = 0;
                break;
            }
        }
    }
    return test;
} // Функ проверяет, можно ли расставлять корабли вверх от случайно определенной базовой координаты?

int testDown(int** arr, int n, int m, int tmp1, int tmp2, int numOfdecks) {
    int test = 1;
    int i, j;
    for (tmp1 == 0 ? i = tmp1 : i = (tmp1 - 1); i <= (tmp1 + numOfdecks) && i < n; i++) {
        for (tmp2 == 0 ? j = tmp2 : j = (tmp2 - 1); j <= (tmp2 + 1) && j >= 0 && j < m; j++) {
            if (arr[i][j] == 1 || arr[i][j] == 2 || arr[i][j] == 3 || arr[i][j] == 4) {
                test = 0;
                break;
            }
        }
    }
    return test;
} // Функ проверет, можно ли расставлять корабли вниз от случайно определенной базовой координаты?

int testLeft(int** arr, int n, int m, int tmp1, int tmp2, int numOfdecks) {
    int test = 1;
    int i, j;
    for (tmp1 == 0 ? i = tmp1 : i = (tmp1 - 1); i <= (tmp1 + 1) && i >= 0 && i < n; i++)
        for (tmp2 == (m - 1) ? j = tmp2 : j = (tmp2 + 1); j >= (tmp2 - numOfdecks) && j >= 0; j--) {
            if (arr[i][j] == 1 || arr[i][j] == 2 || arr[i][j] == 3 || arr[i][j] == 4) {
                test = 0;
                break;
            }
        }
    return test;
} // Функ проверяет, можно ли расставлять корабли влево от случайно определенной базовой координаты?

int testRight(int** arr, int n, int m, int tmp1, int tmp2, int numOfdecks) {
    int test = 1;
    int i, j;
    for (tmp1 == 0 ? i = tmp1 : i = (tmp1 - 1); i <= (tmp1 + 1) && i >= 0 && i < n; i++) {
        for (tmp2 == 0 ? j = tmp2 : j = (tmp2 - 1); j <= (tmp2 + numOfdecks) && j < m; j++) {
            if (arr[i][j] == 1 || arr[i][j] == 2 || arr[i][j] == 3 || arr[i][j] == 4) {
                test = 0;
                break;
            }
        }
    }
    return test;
} // Функ проверяет. можно ли расставлять корабли вправо от случайно определенной базовой координаты?

void attackComp(int** arr, int n, int m, int& attack_n_save, int& attack_m_save, bool& repeat, int& win) {

    int attack_n, attack_m;
    bool test = true; // true

    do {
        //system("cls");
        cout << "\033[0;34m" << "   Computer motion\n\n";
        printPlayer(arr, n, m);
        cout << "\n";
        bool control = false; //переменная для хранение нашего хода (false - туда уже ранее стреляли, true - стреляем туда впервые)
        do {
            if (repeat == 1) {
                if (attack_m_save > 0 && attack_m_save < (m - 1) && arr[attack_n_save][attack_m_save + 1] >= 0 &&
                    arr[attack_n_save][attack_m_save + 1] < 5 && arr[attack_n_save][attack_m_save - 1] < 0) {
                    attack_n = attack_n_save;
                    attack_m = attack_m_save + 1;
                }
                else if (attack_n_save < (n - 1) && attack_n_save > 0 && arr[attack_n_save - 1][attack_m_save] >= 0 &&
                    arr[attack_n_save - 1][attack_m_save] < 5 && arr[attack_n_save + 1][attack_m_save] < 0) {
                    attack_n = attack_n_save - 1;
                    attack_m = attack_m_save;
                }
                else if (attack_m_save > 0 && attack_m_save < (m - 1) && arr[attack_n_save][attack_m_save - 1] >= 0 &&
                    arr[attack_n_save][attack_m_save - 1] < 5 && arr[attack_n_save][attack_m_save + 1] < 0) {
                    attack_n = attack_n_save;
                    attack_m = attack_m_save - 1;
                }
                else if (attack_n_save < (n - 1) && attack_n_save > 0 && arr[attack_n_save + 1][attack_m_save] >= 0 &&
                    arr[attack_n_save + 1][attack_m_save] < 5 && arr[attack_n_save - 1][attack_m_save] < 0) {
                    attack_n = attack_n_save + 1;
                    attack_m = attack_m_save;
                }
                else if (attack_m_save > 1 && attack_m_save < (m - 1) && arr[attack_n_save][attack_m_save + 1] == 5 &&
                    arr[attack_n_save][attack_m_save - 1] < 0) {
                    attack_n = attack_n_save;
                    attack_m = attack_m_save - 2;
                }
                else if (attack_n_save < (n - 2) && attack_n_save > 0 && arr[attack_n_save - 1][attack_m_save] == 5 &&
                    arr[attack_n_save + 1][attack_m_save] < 0) {
                    attack_n = attack_n_save + 2;
                    attack_m = attack_m_save;
                }
                else if (attack_m_save > 0 && attack_m_save < (m - 2) && arr[attack_n_save][attack_m_save - 1] == 5 &&
                    arr[attack_n_save][attack_m_save + 1] < 0) {
                    attack_n = attack_n_save;
                    attack_m = attack_m_save + 2;
                }
                else if (attack_n_save < (n - 1) && attack_n_save > 1 && arr[attack_n_save + 1][attack_m_save] == 5 &&
                    arr[attack_n_save - 1][attack_m_save] < 0) {
                    attack_n = attack_n_save - 2;
                    attack_m = attack_m_save;
                }
                else if (attack_m_save < (m - 1) && arr[attack_n_save][attack_m_save + 1] >= 0 &&
                    arr[attack_n_save][attack_m_save + 1] < 5) {
                    attack_n = attack_n_save;
                    attack_m = attack_m_save + 1;
                }
                else if (attack_n_save > 0 && arr[attack_n_save - 1][attack_m_save] >= 0 &&
                    arr[attack_n_save - 1][attack_m_save] < 5) {
                    attack_n = attack_n_save - 1;
                    attack_m = attack_m_save;
                }
                else if (attack_m_save > 0 && arr[attack_n_save][attack_m_save - 1] >= 0 &&
                    arr[attack_n_save][attack_m_save - 1] < 5) {
                    attack_n = attack_n_save;
                    attack_m = attack_m_save - 1;
                }
                else if (attack_n_save < (n - 1) && arr[attack_n_save + 1][attack_m_save] >= 0 &&
                    arr[attack_n_save + 1][attack_m_save] < 5) {
                    attack_n = attack_n_save + 1;
                    attack_m = attack_m_save;
                }
                else {
                    attack_n = rand() % n; // 10 (размер самого массива)
                    attack_m = rand() % m; // 10 (размер самого массива)
                    repeat = false; // false
                }
            }
            else {

                attack_n = rand() % n; // 10 (размер самого массива)
                attack_m = rand() % m; // 10 (размер самого массива)
            }
            if (arr[attack_n][attack_m] >= 0 &&
                arr[attack_n][attack_m] < 5) //если компьютер туда еще не стрелял - производим выстрел и...
            {
                control = true; // true
            }

        } while (control != 1); //цикл для отслеживание хода (чтобы два раза не стрелять в одно и то же место)
        switch (attack_m) //...озвучиваем ход
        {
        case 0:
            cout << "A" << attack_n + 1 << "\n";
            break;
        case 1:
            cout << "B" << attack_n + 1 << "\n";
            break;
        case 2:
            cout << "C" << attack_n + 1 << "\n";
            break;
        case 3:
            cout << "D" << attack_n + 1 << "\n";
            break;
        case 4:
            cout << "E" << attack_n + 1 << "\n";
            break;
        case 5:
            cout << "F" << attack_n + 1 << "\n";
            break;
        case 6:
            cout << "G" << attack_n + 1 << "\n";
            break;
        case 7:
            cout << "H" << attack_n + 1 << "\n";
            break;
        case 8:
            cout << "I" << attack_n + 1 << "\n";
            break;
        case 9:
            cout << "J" << attack_n + 1 << "\n";
            break;
        }
        if (arr[attack_n][attack_m] == 0) //если поле пустое (на нем нет кораблей)...
        {
            cout << "\033[0;34m" << "Slip!\n"; //...выводим сообщение "ѕромах",...
            arr[attack_n][attack_m] = 5; //записываем ход и...
            test = false; //...пропускаем ход
            active_player = true;
        }
        if (arr[attack_n][attack_m] > 0 && arr[attack_n][attack_m] < 5) //если мы попали в корабль - ...
        {
            int tmp = arr[attack_n][attack_m]; //запоминаем палубность корабля,
            arr[attack_n][attack_m] *= -1; //меняем значение убитого корабля на противоложное и проверяем уничтожен ли он.
            if (testKillHor(arr, n, m, attack_n, attack_m, tmp) == tmp ||
                testKillVer(arr, n, m, attack_n, attack_m, tmp) == tmp) //если уничтожен,...
            {
                cout << "\033[0;34m" << "Killed!\n"; //..выводим сообщение убит,...
                if (testKillHor(arr, n, m, attack_n, attack_m, tmp) == tmp) {
                    bufferDeckHor
                    (arr, n, m, attack_n, attack_m,
                        tmp); //заменяем граничащие с убитым кораблем поля на "5", чтобы повторно туда не стрелять,...
                    repeat = false;
                }
                else {
                    bufferDeckVer(arr, n, m, attack_n, attack_m, tmp);
                    repeat = false;
                }
                if (testWin(arr, n, m) == 0) //проверяем остались ли еще корабли и...
                {
                    test = false; //...если нет - пропускаем ход
                    win = 1; //...завершаем игру
                }
                else {
                    test = true; //...если остались - повторяем ход
                }

            }
            else //если корабль не уничтожен,...
            {
                attack_n_save = attack_n; // «апоминаем текущую атаку (удачный выстрел),...
                attack_m_save = attack_m;
                repeat = true;
                cout << "\033[0;34m" << "Hitting!\n";//...выводим сообщещие попал и ...
                test = true; //повтор€ем ход

            }
        }
        Sleep(50);
    } while (test != 0);
} // Функ для стрелбы по кораблям (ходит комп)

void attackPlayer(int** arr, int n, int m, int& win) {
    int attack_n, attack_m, attack_n_enter;
    char attack_m_enter;
    bool test = true; // true

    do {
        //system("cls");
        cout << "\033[0;34m" << "   Motion of player\n\n";
        printComp(arr, n, m);
        cout << "\n";
        bool control = true; // (true) переменная для контроля праильности ввода координат
        while (control != 0) {
            cout << "\033[0;34m" << "Enter the coordinates for the attack:\n";
            cout << "\033[0;34m" << "- Horizontal - ";
            cin >> attack_m_enter;

            if ((attack_m_enter > 64 && attack_m_enter < 75) || (attack_m_enter > 96 && attack_m_enter < 107)) {
                control = false; // false
            }
        }
        control = true; // true
        while (control != 0) {
            cout << "\033[0;34m" << "- Vertical - ";
            cin >> attack_n_enter;
            if (attack_n_enter > 0 && attack_n_enter < 11) {
                control = false; // false
            }
        }
        attack_n = attack_n_enter - 1;
        switch (attack_m_enter) {
        case 'A':
            attack_m = 0;
            break;
        case 'B':
            attack_m = 1;
            break;
        case 'C':
            attack_m = 2;
            break;
        case 'D':
            attack_m = 3;
            break;
        case 'E':
            attack_m = 4;
            break;
        case 'F':
            attack_m = 5;
            break;
        case 'G':
            attack_m = 6;
            break;
        case 'H':
            attack_m = 7;
            break;
        case 'I':
            attack_m = 8;
            break;
        case 'J':
            attack_m = 9;
            break;
        case 'a':
            attack_m = 0;
            break;
        case 'b':
            attack_m = 1;
            break;
        case 'c':
            attack_m = 2;
            break;
        case 'd':
            attack_m = 3;
            break;
        case 'e':
            attack_m = 4;
            break;
        case 'f':
            attack_m = 5;
            break;
        case 'g':
            attack_m = 6;
            break;
        case 'h':
            attack_m = 7;
            break;
        case 'i':
            attack_m = 8;
            break;
        case 'j':
            attack_m = 9;
            break;
        }

        if (arr[attack_n][attack_m] == 0) //если поле пустое (на нем нет кораблей)-...
        {
            cout << "\033[0;34m" << "Slip!\n"; //...выводим сообщение "промах",...
            arr[attack_n][attack_m] = 5; //записываем ход и...
            test = 0; //...пропускаем ход
            active_player = false;
        }
        if (arr[attack_n][attack_m] > 0 && arr[attack_n][attack_m] < 5) //если мы попали в корабль - ...
        {
            int tmp = arr[attack_n][attack_m]; //запоминаем палубность корабля,
            arr[attack_n][attack_m] *= -1; //меняем значение убитого корабля на противоложное и проверяем уничтожен ли он.
            if (testKillHor(arr, n, m, attack_n, attack_m, tmp) == tmp ||
                testKillVer(arr, n, m, attack_n, attack_m, tmp) == tmp) //если уничтожен,...
            {
                cout << "\033[0;34m" << "Killed!\n"; //..выводим сообщение убит,...
                if (testKillHor(arr, n, m, attack_n, attack_m, tmp) == tmp) {
                    bufferDeckHor
                    (arr, n, m, attack_n, attack_m,
                        tmp); // «аменяем граничащие с уничтоженным кораблем поля на "5", чтобы повторно туда не стрелять,...
                }
                else {
                    bufferDeckVer(arr, n, m, attack_n, attack_m, tmp);
                }
                if (testWin(arr, n, m) == 0) // проверяем, остались ли еще корабли ?
                {
                    test = false; // Еесли нет - пропускаем ход
                    win = 2; // завершаем игру
                }
                else {
                    test = true; // если остались - повторяем ход
                }

            }
            else // если корабль не уничтожен,...
            {
                cout << "\033[0;34m" << "Hitting!\n";// выводим сообщещие попал и...
                test = true; // повторяем ход!
            }
        }
        system("cls");
    } while (test != 0);
} // функ для стрелбы по кораблям (хожу я, то есть пользователь)

int testKillHor(int** arr, int n, int m, int ii, int jj, int number_of_decks) {

    int test = 0;
    int i = ii;
    int j;
    for ((jj - number_of_decks + 1) <= 0 ? j = 0 : j = (jj - number_of_decks + 1);
        j < (jj + number_of_decks) && j < m; j++) {
        if (arr[i][j] == (-number_of_decks)) {
            test++;
        }
    }
    return test;
} // функ для проверки по горизонтали, все ли палубы одного корабля уничтожены?

int testKillVer(int** arr, int n, int m, int ii, int jj, int number_of_decks) {

    int test = 0;
    int i;
    int j = jj;
    for ((ii - number_of_decks + 1) <= 0 ? i = 0 : i = (ii - number_of_decks + 1);
        i < (ii + number_of_decks) && i < n; i++) {
        if (arr[i][j] == (-number_of_decks)) {
            test++;
        }
    }
    return test;
} // функ для проверки по вертикали, все ли палубы одного корабля уничтожены?

void bufferDeckHor(int** arr, int n, int m, int ii, int jj, int number_of_decks) {

    int i = ii;
    int j;
    for ((jj - number_of_decks + 1) <= 0 ? j = 0 : j = (jj - number_of_decks + 1);
        j < (jj + number_of_decks) && j < m; j++) {
        if (arr[i][j] == -number_of_decks) {
            if (j > 0 && arr[i][j - 1] != -number_of_decks) {
                arr[i][j - 1] = 5;
                if (i > 0) {
                    arr[i - 1][j - 1] = 5;
                }
                if (i < (n - 1)) {
                    arr[i + 1][j - 1] = 5;
                }
            }
            if (j < (m - 1) && arr[i][j + 1] != -number_of_decks) {
                arr[i][j + 1] = 5;
                if (i > 0) {
                    arr[i - 1][j + 1] = 5;
                }
                if (i < (n - 1)) {
                    arr[i + 1][j + 1] = 5;
                }
            }
            if (i > 0) {
                arr[i - 1][j] = 5;
            }
            if (i < (n - 1)) {
                arr[i + 1][j] = 5;
            }
        }
    }
} // функ для расстановки выстрелов вокруг уничтоженного корабля (по горизонтали)

void bufferDeckVer(int** arr, int n, int m, int ii, int jj, int number_of_decks) {

    int i;
    int j = jj;
    for ((ii - number_of_decks + 1) <= 0 ? i = 0 : i = (ii - number_of_decks + 1);
        i < (ii + number_of_decks) && i < m; i++) {
        if (arr[i][j] == -number_of_decks) {
            if (i > 0 && arr[i - 1][j] != -number_of_decks) {
                arr[i - 1][j] = 5;
                if (j > 0) {
                    arr[i - 1][j - 1] = 5;
                }
                if (j < (m - 1)) {
                    arr[i - 1][j + 1] = 5;
                }
            }
            if (i < (n - 1) && arr[i + 1][j] != -number_of_decks) {
                arr[i + 1][j] = 5;
                if (j > 0) {
                    arr[i + 1][j - 1] = 5;
                }
                if (j < (n - 1)) {
                    arr[i + 1][j + 1] = 5;
                }
            }
            if (j > 0) {
                arr[i][j - 1] = 5;
            }
            if (j < (m - 1)) {
                arr[i][j + 1] = 5;
            }
        }
    }
} // функ для расстановки выстрелов вокруг уничтоженного корабля (по вертикали)

int testWin(int** arr, int n, int m) {
    int win = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] > 0 && arr[i][j] < 5) {
                win++;
            }
        }
    }
    return win;
} // функ для проверки на проигришь

void printPlayer(int** arr, int n, int m) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int num = 0;

    cout << "\033[0;34m   " << "A " << "B " << "C " << "D " << "E " << "F " << "G " << "H " << "I " << "J "
        << " \033[m\n";
    for (int i = 0; i < n; i++) {
        cout << setw(2) << left << num++;
        if (i < 9) {
            cout << i + 1 << "  ";
        }
        else {
            cout << i + 1 << " ";
        }
        for (int j = 0; j < m; j++) {
            Sleep(5);
            if (arr[i][j] == 0) {
                SetConsoleTextAttribute(h, (0 << 4) | 8);
                cout << char(176) << char(176);
            }
            if (arr[i][j] == 5) {
                SetConsoleTextAttribute(h, (0 << 4) | 6);
                cout << char(219) << char(219);
            }
            if (arr[i][j] > 0 && arr[i][j] < 5) {
                 SetConsoleTextAttribute(h, (0 << 4) | 4);
                 cout << char(177) << char(177);
            }
            SetConsoleTextAttribute(h, (0 << 4) | 15);

            if (arr[i][j] < 0) {
                SetConsoleTextAttribute(h, (0 << 4) | 15);
                cout << char(127) << char(127);
            }


        }
        cout << "\n";
    }
} // функ для вывода поля компа 

void printComp(int** arr, int n, int m) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int num = 0;
    //char shot = 120;
    //char killed_ship = 127;
    cout << "\033[0;34m   " << "A " << "B " << "C " << "D " << "E " << "F " << "G " << "H " << "I " << "J "
        << " \033[m\n";
    for (int i = 0; i < n; i++) {
        cout << setw(2) << left << num++;
        if (i < 9) {
            cout << i + 1 << "\033[0;34m" << "  ";
        }
        else {
            cout << i + 1 << "\033[0;34m" << " ";
        }
        for (int j = 0; j < m; j++) {
            if (arr[i][j] >= 0 && arr[i][j] < 5) {
                cout << "\033[0;34m" << "- ";
            }
            if (arr[i][j] == 5) {
                SetConsoleTextAttribute(h, (0 << 4) | 6);
                cout << char(176) << char(176);
            }
            if (arr[i][j] < 0) {
                SetConsoleTextAttribute(h, (0 << 4) | 6);
                cout << char(176) << char(176);
            }
        }
        cout << "\n";
    }
} // ‘унк дл€ вывода пол€ компа // printPlayer

void delArrMem(int** arr, int n) {

    for (int i = 0; i < n; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
} // ”даление динамического массива после игры