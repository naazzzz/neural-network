﻿#include <iostream>
#include <math.h>
#include <cstdlib>
#include <fstream>
using namespace std;
void wwf(double p[5][3], double* x1, double* a, double* t, int* u) {
    ifstream fin;
    fin.open("NS.txt");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            fin >> p[i][j];
        }
    }
    *x1 = p[*u][0];
    *a = p[*u][1];
    *t = p[*u][2];
    *u += 1;
    fin.close();
}
void write(double w[3][2], string name)
{

    ofstream fout;
    fout.open(name);
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 2; i++) {
            fout << w[j][i] << endl;
        }
    }
    fout.close();
}
void education(double* a, double* x1, double* Y1, double* d, double* t, double* Y, double* d1, double* d2, double* d3, double* d4, double* d5, double* d6, double* f1, double* f2, double* f3, double w[3][2]) {



    (*d) = (*t) - (*Y1);//вычисление ошибки
    (*d4) = (*d) * w[1][1];
    (*d6) = (*d) * w[2][1];
    (*d5) = (*d) * w[2][0];
    (*d1) = (*d4) * w[0][0];
    (*d2) = (*d5) * w[0][1];
    (*d3) = (*d6) * w[1][0];


    w[0][0] = w[0][0] + (*d1) * (*f1) * (1 - (*f1)) * (*x1) * (*a);
    w[0][1] = w[0][1] + (*d2) * (*f2) * (1 - (*f2)) * (*x1) * (*a);
    w[1][0] = w[1][0] + (*d3) * (*f3) * (1 - (*f3)) * (*x1) * (*a);
    w[1][1] = w[1][1] + (*d4) * (*Y1) * (1 - (*Y1)) * (*x1) * (*a);
    w[2][0] = w[2][0] + (*d6) * (*Y1) * (1 - (*Y1)) * (*x1) * (*a);
    w[2][1] = w[2][1] + (*d5) * (*Y1) * (1 - (*Y1)) * (*x1) * (*a);

    cout << "Значения Иcправленных Весов: " << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            cout << "Число " << i << j << " " << w[i][j] << "   ";
            cout << endl;

        }
    }
    cout << endl;

}
void work(double* Y, double* F1, double* F2, double* F3, double* Y1) {

    (*Y) = ((*F1) + (*F2) + (*F3));
    (*Y1) = 1 / (1 + exp(-*Y));

}

void work1(double* y1, double* x1, double w[3][2], double* f1, double* F1) {

    (*y1) = (*x1) * (w[0][0]);
    (*f1) = 1 / (1 + exp(-*y1));//полный расчет 1 нейрона
    (*F1) = (*f1) * (w[0][1]);
}

void work2(double* y2, double* x1, double w[3][2], double* f2, double* F2) {

    (*y2) = (*x1) * (w[2][0]);
    (*f2) = 1 / (1 + exp(-*y2));//полный расчет 2 нейрона
    (*F2) = (*f2) * (w[2][1]);

}

void work3(double* y3, double* x1, double w[3][2], double* f3, double* F3) {

    (*y3) = (*x1) * (w[1][0]);
    (*f3) = 1 / (1 + exp(-*y3));//полный расчет 3 нейрона
    (*F3) = (*f3) * (w[1][1]);

}

int main() {

    setlocale(LC_ALL, "ru");
    double p[5][3];//массив для обучающей выборки
    const int ROWS = 3;//строка массива
    const int COL = 2;//столбец массива
    int R; int N = 1; int N1 = 1; int O = 0; int N2 = 0;   int u = 0;//переменные для циклов
    string name;//ввод-вывод
    double x1, w[ROWS][COL], y1, y2, y3, f1, f2, f3, F1, F2, F3, Y, Y1, t, d, d1, d2, d3, d4, d5, d6, a;//переменные для обучения

    cout << "Обучать сеть или работать с обученной?(1-Обучать, 2- Работать с обученной)" << endl;
    cin >> R;
    if (R == 1) {
        cout << "Желаете обучать набором из файла или по одному?(1-набором/2-по одному)" << endl;
        cin >> N2;
    }
    while (R == 1) {
        if (N2 == 2) {
            cout << "ВВедите входное значение нейрона" << endl; cin >> x1;
            cout << "Введите скорость обучения(от 0.1 до 0.9)" << endl; cin >> a;
            cout << "Введите правильный ответ" << endl; cin >> t;
        }
        if (N2 == 1) {
            wwf(p, &x1, &a, &t, &u);
        }
        cout << "Введите название обучающего файла для записи нейронной сети " << endl;
        cin >> name;
        if (O == 0) {
            cout << "Значения Исходных Весов: " << endl;
            cout << endl;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 2; j++) {
                    w[i][j] = (rand() % 70) * 0.01;
                    cout << "Число " << w[i][j] << "   ";
                }
            }
        }
        cout << endl << endl;



        for (int i = 0; i < 200; i++)
        {
            work1(&y1, &x1, w, &f1, &F1);
            work2(&y2, &x1, w, &f2, &F2);
            work3(&y3, &x1, w, &f3, &F3);
            work(&Y, &F1, &F2, &F3, &Y1);


            education(&a, &x1, &Y1, &d, &t, &Y, &d1, &d2, &d3, &d4, &d5, &d6, &f1, &f2, &f3, w);
            write(w, name);
            cout << "Ответ сети " << Y1 << endl << endl;

        }
        cout << "Сеть обучена на данном примере!" << endl << endl;

        cout << "Обучить на другом примере?(1-Да/2-Нет)" << endl;
        cin >> N;
        if (N == 1) {
            O = 1;
        }

        while (N == 1) {
            if (N2 == 2) {
                cout << "ВВедите входное значение нейрона" << endl; cin >> x1;
                cout << "Введите скорость обучения(от 0.1 до 0.9)" << endl; cin >> a;
                cout << "Введите правильный ответ" << endl; cin >> t;
            }
            if (N2 == 1) {
                wwf(p, &x1, &a, &t, &u);
            }
            for (int i = 0; i < 200; i++)
            {
                work1(&y1, &x1, w, &f1, &F1);
                work2(&y2, &x1, w, &f2, &F2);
                work3(&y3, &x1, w, &f3, &F3);
                work(&Y, &F1, &F2, &F3, &Y1);


                education(&a, &x1, &Y1, &d, &t, &Y, &d1, &d2, &d3, &d4, &d5, &d6, &f1, &f2, &f3, w);
                write(w, name);
                cout << "Ответ сети " << Y1 << endl << endl;
            }
            cout << "Сеть обучена на данном примере!" << endl << endl;
            cout << "Обучить на другом примере?(1-Да/2-Нет)" << endl;
            cin >> N;

        }
        cout << "Желаете рабоать с сетью?(1-Да/2-Нет)" << endl;
        cin >> R;
        if (R == 1) {
            R = 2;
        }
        else {
            exit(1);
        }
    }
    while (R == 2) {
        cout << "ВВедите входное значение " << endl;
        cin >> x1;
        cout << "ВВедите название файла с весами  " << endl;
        cin >> name;
        ifstream fin;
        fin.open(name);
        int k = 0;
        int p = 0;
        while (!fin.eof()) {

            fin >> w[k][p];
            if (p == 0) {
                p = p + 1;
            }
            else {
                p = p - 1;
                k = k + 1;

            }
            fin.close();
            work1(&y1, &x1, w, &f1, &F1);
            work2(&y2, &x1, w, &f2, &F2);
            work3(&y3, &x1, w, &f3, &F3);
            work(&Y, &F1, &F2, &F3, &Y1);
            cout << "Ответ сети " << Y1 << endl << endl;
            cout << "Желаете еще раз порабоать с сетью?(1-Да/2-Нет)" << endl;
            cin >> R;
            if (R == 1) {
                R = 2;
            }
            else {
                cout << "Желаете обучить сеть?(1-Да/2-Нет)" << endl;
                cin >> N;
                while (N == 1) {
                    cout << "ВВедите входное значение нейрона" << endl; cin >> x1;
                    cout << "Введите скорость обучения(от 0.1 до 0.9)" << endl; cin >> a;
                    cout << "Введите правильный ответ" << endl; cin >> t;

                    for (int i = 0; i < 200; i++)
                    {
                        work1(&y1, &x1, w, &f1, &F1);
                        work2(&y2, &x1, w, &f2, &F2);
                        work3(&y3, &x1, w, &f3, &F3);
                        work(&Y, &F1, &F2, &F3, &Y1);


                        education(&a, &x1, &Y1, &d, &t, &Y, &d1, &d2, &d3, &d4, &d5, &d6, &f1, &f2, &f3, w);
                        write(w, name);
                        cout << "Ответ сети " << Y1 << endl << endl;

                    }
                    cout << "Сеть обучена на данном примере!" << endl << endl;
                    cout << "Желаете обучить сеть еще раз?(1-Да/2-Нет)" << endl;
                    cin >> N1;
                    if (N1 == 2) {
                        cout << "Желаете работать с сетью?(1-Да/2-Нет)" << endl;
                        cin >> R;
                        if (R == 1) {
                            R = 2;
                        }
                        else {
                            exit(1);
                        }
                    }
                }
                if (N == 2) {
                    exit(1);
                }
            }
        }

        return 0;
    }

}