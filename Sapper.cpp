#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <conio.h>

using namespace sf;
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    int Answer = 0; //хранит выбор пользователя в меню
    int AnswerComplexity = 0; //хранит выбор пользователя в выборе сложности
    int Return;

tryAgain:
    cout << "САПЕР" << endl;
    cout << "Что бы начать игру выберите сложность" << endl;

    cout << "1 - Выбрать сложность" << endl; 
    cout << "2 - Справка" << endl;
    cout << "3 - Разработчик" << endl; // можно немного вальнуть дурака
    /*cout << "4 - Рекорды" << endl;*/
    cout << "5 - Выйти из игры" << endl << endl;

    cin >> Answer;
    system("cls");
    while (true)
    {
        if (Answer == 1)// Сложности
        {
        ChoiceComplexity:
            system("cls");
            cout << "1    | Легко | " << endl; //поле 10х10
            cout << "2  | Любитель |" << endl; //поле 16х16 
            cout << "3 | Профессионал |" << endl; //поле 16х30 
            cout << "4  Вернуться в меню " << endl;
            cin >> AnswerComplexity;
            goto PlayComplexity;
        }
        else if (Answer == 2)// Справка
        {
            cout << "Сапер - это игра головоломка, где игроку нужно разминировать минное поле, помечая флажками ячейки, на которых могут быть мины, для их обнаружения на соседних пустых клетках есть подсказки в виде чисел." << endl;
            cout << "Числа в Сапере - это наши подсказки, они нам говорят сколько и где расположено мин." << endl;
            cout << "Когда обнаружили мину, помете ее флажком, для этого нужно нажать ПКМ (правую кнопку мыши) на ячейку где предположительно может быть мина." << endl;
            system("pause");
            system("cls");
            goto tryAgain;
        }
        else if (Answer == 3)// Идиотизм...(Разработчик(Адаптатор))
        {
            cout << "Руководитель проекта: CLINlQUE" << endl;
            cout << "Программист: CLINlQUE" << endl;
            cout << "Главный дизайнер: CLINlQUE" << endl;
            system("pause");
            system("cls");
            goto tryAgain;
            //юморнуть
        }
        /*else if (Answer == 4)
        {
            ifstream file("Record.txt");
        }*/
        else if (Answer == 5)// Выход из игры
        {
            return 0;
        }
        else if (Answer <= 0 || Answer >= 6)// Ловушка для "самых" одаренных
        {
            cout << "Варианта с таким номером " << Answer << " Нет! ";
            cout << "Сделайте правильный выбор (от 1 до 5): " << endl;
            system("pause");
            system("cls");
            goto tryAgain;
        }
    }

PlayComplexity:

    if (AnswerComplexity == 1)//код легкого варианта игры
    {
        system("cls");
        srand(time(0));

        RenderWindow app(VideoMode(400, 400), "Sapper");

        // Ширина клетки
        int w = 32;
        int gridLogic[12][12];
        int gridView[12][12];

        // Загрузка текстуры и создание спрайта
        Texture t;
        t.loadFromFile("C:\\soft\\images\\tiles.jpg");
        Sprite s(t);

        for (int i = 1; i <= 10; i++)
            for (int j = 1; j <= 10; j++)
            {
                gridView[i][j] = 10;
                if (rand() % 5 == 0)  gridLogic[i][j] = 9;
                else gridLogic[i][j] = 0;
            }


        // Подсчет мин вокруг каждой клетки
        for (int i = 1; i <= 10; i++)
            for (int j = 1; j <= 10; j++)
            {
                int n = 0;
                if (gridLogic[i][j] == 9) continue;
                if (gridLogic[i + 1][j] == 9) n++;
                if (gridLogic[i][j + 1] == 9) n++;
                if (gridLogic[i - 1][j] == 9) n++;
                if (gridLogic[i][j - 1] == 9) n++;
                if (gridLogic[i + 1][j + 1] == 9) n++;
                if (gridLogic[i - 1][j - 1] == 9) n++;
                if (gridLogic[i - 1][j + 1] == 9) n++;
                if (gridLogic[i + 1][j - 1] == 9) n++;
                gridLogic[i][j] = n;
            }

        while (app.isOpen())
        {
            // Получаем координаты мышки относительно окна нашего приложения
            Vector2i pos = Mouse::getPosition(app);
            int x = pos.x / w;
            int y = pos.y / w;

            Event e;
            while (app.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    app.close();

                // Была нажата кнопка мыши…?
                if (e.type == Event::MouseButtonPressed)
                    // Если это - левая кнопка мыши, то открываем клетку
                    if (e.key.code == Mouse::Left) gridView[x][y] = gridLogic[x][y];
                // Если это – правая кнопка мыши, то отображаем флажок
                    else if (e.key.code == Mouse::Right) gridView[x][y] = 11;
            }


            // Устанавливаем белый фон
            app.clear(Color::White);

            for (int i = 1; i <= 10; i++)
                for (int j = 1; j <= 10; j++)
                {
                    if (gridView[x][y] == 9) gridView[i][j] = gridLogic[i][j];

                    // Вырезаем из спрайта нужный нам квадратик текстуры
                    s.setTextureRect(IntRect(gridView[i][j] * w, 0, w, w));

                    // Устанавливаем его заданную позицию
                    s.setPosition(i * w, j * w);

                    // Отрисовываем
                    app.draw(s);
                }
            // Отображаем всю композицию на экране
            app.display();
            system("cls");
        }
    }
    else if (AnswerComplexity == 2)//код любительского варианта игры
    {
        system("cls");
        srand(time(0));

        RenderWindow app(VideoMode(600, 600), "Sapper");

        // Ширина клетки
        int w = 32;
        int gridLogic[18][18];
        int gridView[18][18];

        // Загрузка текстуры и создание спрайта
        Texture t;
        t.loadFromFile("C:\\soft\\images\\tiles.jpg");
        Sprite s(t);

        for (int i = 1; i <= 16; i++)
            for (int j = 1; j <= 16; j++)
            {
                gridView[i][j] = 10;
                if (rand() % 5 == 0)  gridLogic[i][j] = 9;
                else gridLogic[i][j] = 0;
            }


        // Подсчет мин вокруг каждой клетки
        for (int i = 1; i <= 16; i++)
            for (int j = 1; j <= 16; j++)
            {
                int n = 0;
                if (gridLogic[i][j] == 9) continue;
                if (gridLogic[i + 1][j] == 9) n++;
                if (gridLogic[i][j + 1] == 9) n++;
                if (gridLogic[i - 1][j] == 9) n++;
                if (gridLogic[i][j - 1] == 9) n++;
                if (gridLogic[i + 1][j + 1] == 9) n++;
                if (gridLogic[i - 1][j - 1] == 9) n++;
                if (gridLogic[i - 1][j + 1] == 9) n++;
                if (gridLogic[i + 1][j - 1] == 9) n++;
                gridLogic[i][j] = n;
            }

        while (app.isOpen())
        {
            // Получаем координаты мышки относительно окна нашего приложения
            Vector2i pos = Mouse::getPosition(app);
            int x = pos.x / w;
            int y = pos.y / w;

            Event e;
            while (app.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    app.close();

                // Была ли нажата кнопка мыши
                if (e.type == Event::MouseButtonPressed)
                    // Если это - левая кнопка мыши, то открываем клетку
                    if (e.key.code == Mouse::Left) gridView[x][y] = gridLogic[x][y];
                // Если это – правая кнопка мыши, то отображаем флажок
                    else if (e.key.code == Mouse::Right) gridView[x][y] = 11;
            }


            // Устанавливаем белый фон
            app.clear(Color::White);

            for (int i = 1; i <= 16; i++)
                for (int j = 1; j <= 16; j++)
                {
                    if (gridView[x][y] == 9) gridView[i][j] = gridLogic[i][j];

                    // Вырезаем из спрайта нужный нам квадратик текстуры
                    s.setTextureRect(IntRect(gridView[i][j] * w, 0, w, w));

                    // Устанавливаем его заданную позицию
                    s.setPosition(i * w, j * w);

                    // Отрисовываем
                    app.draw(s);
                }
            // Отображаем всю композицию на экране
            app.display();
            system("cls");
        }
        //setlocale(LC_ALL, "RUSSIAN");
        //cout << "Пожалуйста запишите своё имя и результаты (Пример: 'Артём - проигрыш'): ";
        //ofstream file("Record.txt");
        //char one[100];
        //cin >> one;
        //if (file << one)
        //    cout << "COMLEPTE" << endl;
        //else
        //    cout << "ERROR" << endl;
        //file.close();
        //system("pause");
    }
    else if (AnswerComplexity == 3)//код профессионального варианта игры
    {
        system("cls");
        srand(time(0));

        RenderWindow app(VideoMode(1030, 600), "Sapper");

        // Ширина клетки
        int w = 32;
        int gridLogic[32][18];
        int gridView[32][18];

        // Загрузка текстуры и создание спрайта
        Texture t;
        t.loadFromFile("C:\\soft\\images\\tiles.jpg");
        Sprite s(t);

        for (int i = 1; i <= 30; i++)
            for (int j = 1; j <= 16; j++)
            {
                gridView[i][j] = 10;
                if (rand() % 5 == 0)  gridLogic[i][j] = 9;
                else gridLogic[i][j] = 0;
            }


        // Подсчет мин вокруг каждой клетки
        for (int i = 1; i <= 30; i++)
            for (int j = 1; j <= 16; j++)
            {
                int n = 0;
                if (gridLogic[i][j] == 9) continue;
                if (gridLogic[i + 1][j] == 9) n++;
                if (gridLogic[i][j + 1] == 9) n++;
                if (gridLogic[i - 1][j] == 9) n++;
                if (gridLogic[i][j - 1] == 9) n++;
                if (gridLogic[i + 1][j + 1] == 9) n++;
                if (gridLogic[i - 1][j - 1] == 9) n++;
                if (gridLogic[i - 1][j + 1] == 9) n++;
                if (gridLogic[i + 1][j - 1] == 9) n++;
                gridLogic[i][j] = n;
            }

        while (app.isOpen())
        {
            // Получаем координаты мышки относительно окна нашего приложения
            Vector2i pos = Mouse::getPosition(app);
            int x = pos.x / w;
            int y = pos.y / w;

            Event e;
            while (app.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    app.close();

                // Была нажата кнопка мыши…?
                if (e.type == Event::MouseButtonPressed)
                    // Если это - левая кнопка мыши, то открываем клетку
                    if (e.key.code == Mouse::Left) gridView[x][y] = gridLogic[x][y];
                // Если это – правая кнопка мыши, то отображаем флажок
                    else if (e.key.code == Mouse::Right) gridView[x][y] = 11;
            }


            // Устанавливаем белый фон
            app.clear(Color::White);

            for (int i = 1; i <= 30; i++)
                for (int j = 1; j <= 16; j++)
                {
                    if (gridView[x][y] == 9) gridView[i][j] = gridLogic[i][j];

                    // Вырезаем из спрайта нужный нам квадратик текстуры
                    s.setTextureRect(IntRect(gridView[i][j] * w, 0, w, w));

                    // Устанавливаем его заданную позицию
                    s.setPosition(i * w, j * w);

                    // Отрисовываем
                    app.draw(s);
                }
            // Отображаем всю композицию на экране
            app.display();
            system("cls");
        }
    }
    else if (AnswerComplexity == 4)// Возвращение в меню
        goto tryAgain;
    else if (AnswerComplexity <= 0 || AnswerComplexity >= 5)// Ловушка для идиотов
    {
        cout << "Варианта с таким номером " << AnswerComplexity << " Нет! ";
        cout << "Сделайте правильный выбор (от 1 до 4): " << endl;
        system("pause");
        system("cls");
        goto ChoiceComplexity;
    }
    return 0;
}
