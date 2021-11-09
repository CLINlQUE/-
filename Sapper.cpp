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
    int Answer = 0; //������ ����� ������������ � ����
    int AnswerComplexity = 0; //������ ����� ������������ � ������ ���������
    int Return;

tryAgain:
    cout << "�����" << endl;
    cout << "��� �� ������ ���� �������� ���������" << endl;

    cout << "1 - ������� ���������" << endl; 
    cout << "2 - �������" << endl;
    cout << "3 - �����������" << endl; // ����� ������� �������� ������
    /*cout << "4 - �������" << endl;*/
    cout << "5 - ����� �� ����" << endl << endl;

    cin >> Answer;
    system("cls");
    while (true)
    {
        if (Answer == 1)// ���������
        {
        ChoiceComplexity:
            system("cls");
            cout << "1    | ����� | " << endl; //���� 10�10
            cout << "2  | �������� |" << endl; //���� 16�16 
            cout << "3 | ������������ |" << endl; //���� 16�30 
            cout << "4  ��������� � ���� " << endl;
            cin >> AnswerComplexity;
            goto PlayComplexity;
        }
        else if (Answer == 2)// �������
        {
            cout << "����� - ��� ���� �����������, ��� ������ ����� ������������� ������ ����, ������� �������� ������, �� ������� ����� ���� ����, ��� �� ����������� �� �������� ������ ������� ���� ��������� � ���� �����." << endl;
            cout << "����� � ������ - ��� ���� ���������, ��� ��� ������� ������� � ��� ����������� ���." << endl;
            cout << "����� ���������� ����, ������ �� �������, ��� ����� ����� ������ ��� (������ ������ ����) �� ������ ��� ���������������� ����� ���� ����." << endl;
            system("pause");
            system("cls");
            goto tryAgain;
        }
        else if (Answer == 3)// ��������...(�����������(���������))
        {
            cout << "������������ �������: CLINlQUE" << endl;
            cout << "�����������: CLINlQUE" << endl;
            cout << "������� ��������: CLINlQUE" << endl;
            system("pause");
            system("cls");
            goto tryAgain;
            //��������
        }
        /*else if (Answer == 4)
        {
            ifstream file("Record.txt");
        }*/
        else if (Answer == 5)// ����� �� ����
        {
            return 0;
        }
        else if (Answer <= 0 || Answer >= 6)// ������� ��� "�����" ���������
        {
            cout << "�������� � ����� ������� " << Answer << " ���! ";
            cout << "�������� ���������� ����� (�� 1 �� 5): " << endl;
            system("pause");
            system("cls");
            goto tryAgain;
        }
    }

PlayComplexity:

    if (AnswerComplexity == 1)//��� ������� �������� ����
    {
        system("cls");
        srand(time(0));

        RenderWindow app(VideoMode(400, 400), "Sapper");

        // ������ ������
        int w = 32;
        int gridLogic[12][12];
        int gridView[12][12];

        // �������� �������� � �������� �������
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


        // ������� ��� ������ ������ ������
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
            // �������� ���������� ����� ������������ ���� ������ ����������
            Vector2i pos = Mouse::getPosition(app);
            int x = pos.x / w;
            int y = pos.y / w;

            Event e;
            while (app.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    app.close();

                // ���� ������ ������ ����?
                if (e.type == Event::MouseButtonPressed)
                    // ���� ��� - ����� ������ ����, �� ��������� ������
                    if (e.key.code == Mouse::Left) gridView[x][y] = gridLogic[x][y];
                // ���� ��� � ������ ������ ����, �� ���������� ������
                    else if (e.key.code == Mouse::Right) gridView[x][y] = 11;
            }


            // ������������� ����� ���
            app.clear(Color::White);

            for (int i = 1; i <= 10; i++)
                for (int j = 1; j <= 10; j++)
                {
                    if (gridView[x][y] == 9) gridView[i][j] = gridLogic[i][j];

                    // �������� �� ������� ������ ��� ��������� ��������
                    s.setTextureRect(IntRect(gridView[i][j] * w, 0, w, w));

                    // ������������� ��� �������� �������
                    s.setPosition(i * w, j * w);

                    // ������������
                    app.draw(s);
                }
            // ���������� ��� ���������� �� ������
            app.display();
            system("cls");
        }
    }
    else if (AnswerComplexity == 2)//��� ������������� �������� ����
    {
        system("cls");
        srand(time(0));

        RenderWindow app(VideoMode(600, 600), "Sapper");

        // ������ ������
        int w = 32;
        int gridLogic[18][18];
        int gridView[18][18];

        // �������� �������� � �������� �������
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


        // ������� ��� ������ ������ ������
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
            // �������� ���������� ����� ������������ ���� ������ ����������
            Vector2i pos = Mouse::getPosition(app);
            int x = pos.x / w;
            int y = pos.y / w;

            Event e;
            while (app.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    app.close();

                // ���� �� ������ ������ ����
                if (e.type == Event::MouseButtonPressed)
                    // ���� ��� - ����� ������ ����, �� ��������� ������
                    if (e.key.code == Mouse::Left) gridView[x][y] = gridLogic[x][y];
                // ���� ��� � ������ ������ ����, �� ���������� ������
                    else if (e.key.code == Mouse::Right) gridView[x][y] = 11;
            }


            // ������������� ����� ���
            app.clear(Color::White);

            for (int i = 1; i <= 16; i++)
                for (int j = 1; j <= 16; j++)
                {
                    if (gridView[x][y] == 9) gridView[i][j] = gridLogic[i][j];

                    // �������� �� ������� ������ ��� ��������� ��������
                    s.setTextureRect(IntRect(gridView[i][j] * w, 0, w, w));

                    // ������������� ��� �������� �������
                    s.setPosition(i * w, j * w);

                    // ������������
                    app.draw(s);
                }
            // ���������� ��� ���������� �� ������
            app.display();
            system("cls");
        }
        //setlocale(LC_ALL, "RUSSIAN");
        //cout << "���������� �������� ��� ��� � ���������� (������: '���� - ��������'): ";
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
    else if (AnswerComplexity == 3)//��� ����������������� �������� ����
    {
        system("cls");
        srand(time(0));

        RenderWindow app(VideoMode(1030, 600), "Sapper");

        // ������ ������
        int w = 32;
        int gridLogic[32][18];
        int gridView[32][18];

        // �������� �������� � �������� �������
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


        // ������� ��� ������ ������ ������
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
            // �������� ���������� ����� ������������ ���� ������ ����������
            Vector2i pos = Mouse::getPosition(app);
            int x = pos.x / w;
            int y = pos.y / w;

            Event e;
            while (app.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    app.close();

                // ���� ������ ������ ����?
                if (e.type == Event::MouseButtonPressed)
                    // ���� ��� - ����� ������ ����, �� ��������� ������
                    if (e.key.code == Mouse::Left) gridView[x][y] = gridLogic[x][y];
                // ���� ��� � ������ ������ ����, �� ���������� ������
                    else if (e.key.code == Mouse::Right) gridView[x][y] = 11;
            }


            // ������������� ����� ���
            app.clear(Color::White);

            for (int i = 1; i <= 30; i++)
                for (int j = 1; j <= 16; j++)
                {
                    if (gridView[x][y] == 9) gridView[i][j] = gridLogic[i][j];

                    // �������� �� ������� ������ ��� ��������� ��������
                    s.setTextureRect(IntRect(gridView[i][j] * w, 0, w, w));

                    // ������������� ��� �������� �������
                    s.setPosition(i * w, j * w);

                    // ������������
                    app.draw(s);
                }
            // ���������� ��� ���������� �� ������
            app.display();
            system("cls");
        }
    }
    else if (AnswerComplexity == 4)// ����������� � ����
        goto tryAgain;
    else if (AnswerComplexity <= 0 || AnswerComplexity >= 5)// ������� ��� �������
    {
        cout << "�������� � ����� ������� " << AnswerComplexity << " ���! ";
        cout << "�������� ���������� ����� (�� 1 �� 4): " << endl;
        system("pause");
        system("cls");
        goto ChoiceComplexity;
    }
    return 0;
}
