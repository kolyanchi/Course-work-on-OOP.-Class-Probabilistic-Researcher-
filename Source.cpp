#define _USE_MATH_DEFINES
#include <graphics.h>
#include <iostream>
#include <cmath>
using namespace std;

class ProbabilisticResearcher
{
private:
	int* ptr; // указатель на  первый массив случайных чисел 
	int* ptr1; // указатель на  второй массив случайных чисел 
	int* rasp;
	int size1; //кол-во случайных чисел/размер массиваз
	int size2; //
	float P; // Плотность
	float M; // Мат. ож. первого массива
	float M1; // Мат. ож. второго массива
	float D; // Дисперсия 
	float K; // Корреляционная ф-я
	float MS; //Среднеквадратическое отклонениt
public:
	ProbabilisticResearcher(int,int);
	void PutMass(); // Заполнение массивов случайными цифрами 
	float Density(); 
	float MathExp();
	float MathExp1();
	float Dispersion();
	float MeanSquareDeviation();
	float CorrFunction();
	void Gist();
};

ProbabilisticResearcher::ProbabilisticResearcher(int size1,int size2)
{
	this->size1 = size1;
	ptr = new int[size1]; 
	for (int ix = 0; ix < size1; ix++)
		ptr[ix] = 0;
	ptr1 = new int[size1]; 
	for (int ix = 0; ix < size1; ix++)
		ptr1[ix] = 0;
	this->size2 = size2;
	rasp = new int[size2]; 
	for (int ix = 0; ix < size2; ix++) 
		rasp[ix] = 0;
}

void  ProbabilisticResearcher::PutMass()
{
	for (int ix = 0; ix < size1; ix++)
	{
		ptr[ix] = rand() % 100 + 0;
		ptr1[ix] = rand() % 100 + 0;
		if (ptr[ix] > 0 && ptr[ix] <= 10) rasp[0]++;
		if (ptr[ix] > 10 && ptr[ix] <= 20) rasp[1]++;
		if (ptr[ix] > 20 && ptr[ix] <= 30) rasp[2]++;
		if (ptr[ix] > 30 && ptr[ix] <= 40) rasp[3]++;
		if (ptr[ix] > 40 && ptr[ix] <= 50) rasp[4]++;
		if (ptr[ix] > 50 && ptr[ix] <= 60) rasp[5]++;
		if (ptr[ix] > 60 && ptr[ix] <= 70) rasp[6]++;
		if (ptr[ix] > 70 && ptr[ix] <= 80) rasp[7]++;
		if (ptr[ix] > 80 && ptr[ix] <= 90) rasp[8]++;
		if (ptr[ix] > 90 && ptr[ix] <= 100) rasp[9]++;
	}
}
float  ProbabilisticResearcher::Density()
{
	P = (float)1 / (size2 - 0);
	return P;
}
float  ProbabilisticResearcher::MathExp()
{
	for (int ix = 0; ix < size1; ix++)
		M = M + ptr[ix];
	M = M / size1;
	return M;
}
float  ProbabilisticResearcher::MathExp1()
{
	for (int ix = 0; ix < size1; ix++)
		M1 = M1 + ptr1[ix];
	M1 = M1 / size1;
	return M1;
}
float  ProbabilisticResearcher::Dispersion()
{
	for (int ix = 0; ix < size1; ix++)
		D = D + ((ptr[ix] - MathExp()) * (ptr[ix] - MathExp()));
	D = D / (size1 - 1);
	return D;
}
float  ProbabilisticResearcher::CorrFunction()
{
	for (int ix = 0; ix < size1; ix++) {
		K = K + ((ptr[ix] - M) * (ptr1[ix] - M1));
	}
	K = K / (size1 - 1);
	return K;
}

float ProbabilisticResearcher::MeanSquareDeviation()
{
	for (int ix = 0; ix < size1; ix++)
		MS = MS + pow(ptr[ix] - MathExp(), 2);
	MS = pow(MS / size1,0.5);
	return MS;
}
void ProbabilisticResearcher::Gist()
{
	int TempColor;
	TempColor = getcolor();
	setcolor(8);
	line(50, 0, 50, getmaxy());
	line(0,400, getmaxx(), 400);
	setfillstyle(1, BLACK);
	for (int i = 0, j = 50 ; i < 10; i++, j+=50) {
		rectangle(j, 400, j + 50, 400 - rasp[i]*2 );
		//j++;
	}
	char x[] = "0        10         20         30         40         50        60       70        80        90         100          x";
	char p[] = "p(x)";     
	setcolor(8);
	outtextxy(50 + 2, 410, x);
	outtextxy(20, 5, p);
	for (int i = 400, j = 0; i > 0; i-=100, j+=50) {
		line(45, i, 55, i);
	}
	char y[] = "50"; char y1[] = "100"; char y2[] = "150";
	outtextxy(25, 90, y2);
	outtextxy(25, 190, y1);
	outtextxy(25, 290, y);

	setcolor(TempColor);
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int gdriver = DETECT, gmode, errorcode;
	char path[] = "";
	initgraph(&gdriver, &gmode, path);
	errorcode = graphresult();
	if (errorcode != grOk)
	{
		cout << "Ошибка графики: " << grapherrormsg(errorcode) << endl;
		cout << "Нажмите любую клавишу для прерывания:" << endl;
		getch(); return(1);
	}
	setcolor(15);
	bar(0, 0, getmaxx(), getmaxy());
	setbkcolor(15);
	ProbabilisticResearcher one(1000,10);
	one.PutMass();
	float P = one.Density();
	float M = one.MathExp();
	float D = one.Dispersion();
	float MS = one.MeanSquareDeviation();
	float K = one.CorrFunction();
	cout <<"Плотность = " << P << endl;
	cout <<"Математическое ожидание = " << M << endl;
	cout <<"Дисперсия = " << D << endl;
	cout <<"Среднеквадратическое отклонение = " << MS << endl;
	cout << "Корреляционная функция = " << K << endl;
	one.Gist();
	getch();
	closegraph();
	return 0;
}
