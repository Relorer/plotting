#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Expression.h"


int validatorBracket(String& expression, int start)
{
	int count = 0;
	for (int i = start + 1; i < expression.getSize(); i++) {
		if (expression[i] == ')' && !count) return i;
		else if (expression[i] == ')') count--;
		else if (expression[i] == '(') count++;
	}
	return -1;
}

int validatorSquareBracket(String & expression, int start)
{
	int count = 0;
	for (int i = start + 1; i < expression.getSize(); i++) {
		if (expression[i] == ']' && !count) return i;
		else if (expression[i] == ']') count--;
		else if (expression[i] == '[') count++;
	}
	return -1;
}

int validator(String & expression, HANDLE hConsole)
{
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	if (expression.getSize() == 0) {
		printf("Функция не может быть пустой, попробуйте еще\n");
		return 1;
	}

	for (int i = 0; i < expression.getSize(); i++) {
		if (expression[i] >= 'А' && expression[i] <= 'я' || expression[i] == 'ё' || expression[i] == 'Ё') {
			printf("Функция не может содержать кириллицу, попробуйте еще\n");
			return 1;
		}
	}

	std::cmatch result_1;
	std::regex regular_1("\\b(?!(?:(([()+\\-\\/^ex*]|(\\d*))?(sin|cos|tan|ctan|log|lg|ln|pi|e|x|sqrt)\\s*([ex\\(\\+\\-\\*\\/\\^\\[]|\\d+.?\\d*|sin|cos|tan|ctan|log|lg|ln|pi|sqrt)*|\\d+(\\.\\d*)?))\\b)\\w+\\b|[\\,\\=!@#$%&`~:\\=\\{\\}\\\\]");
	if (std::regex_search(expression.getString(), result_1, regular_1)) {
		printf("Функция введена некорректно: %s\n", result_1[0].str().c_str());
		printf("попробуйте еще\n");
		return 1;
	}

	std::cmatch result_2;
	std::regex regular_2("\\D{1,}\\.|\\.\\D{1,}");
	if (std::regex_search(expression.getString(), result_2, regular_2)) {
		printf("Точка должна быть заключена в число: %s\n", result_2[0].str().c_str());
		printf("попробуйте еще\n");
		return 1;
	}

	std::cmatch result_3;
	std::regex regular_3("(sin|cos|tan|ctan|log\\s*\\[.+\\]|lg|ln|sqrt)((\\s*[+\\.\\-\\/^*)\\]])|\\s*$)");
	if (std::regex_search(expression.getString(), result_3, regular_3)) {
		printf("У функции должен быть аргумент: %s\n", result_3[0].str().c_str());
		printf("попробуйте еще\n");
		return 1;
	}

	std::cmatch result_4;
	std::regex regular_4("(\\d+\\.\\d*\\.\\d*)");
	if (std::regex_search(expression.getString(), result_4, regular_4)) {
		printf("Число не может содержать больше олной точки: %s\n", result_4[0].str().c_str());
		printf("попробуйте еще\n");
		return 1;
	}

	std::cmatch result_5;
	std::regex regular_5("[+\\-\\/^*]\\s*[+\\-\\/^*)]|[(]\\s*[+\\/^*]|[+\\-\\/^*]\\s*$|^\\s*[\\+\\/\\*\\^]");
	if (std::regex_search(expression.getString(), result_5, regular_5)) {
		printf("Арифметический знак должен иметь два операнда: %s\n", result_5[0].str().c_str());
		printf("попробуйте еще\n");
		return 1;
	}

	std::cmatch result_6;
	std::regex regular_6("\\b(?!(?:log\\s*\\[)\\B)(\\w+\\s*\\[)\\B\\s*|^\\[");
	if (std::regex_search(expression.getString(), result_6, regular_6)) {
		printf("Квадратные скобки должны стоять только после log: %s\n", result_6[0].str().c_str());
		printf("попробуйте еще\n");
		return 1;
	}

	std::cmatch result_7;
	std::regex regular_7("\\[\\]");
	if (std::regex_search(expression.getString(), result_7, regular_7)) {
		printf("Основание логарифма не может быть пустым: %s\n", result_7[0].str().c_str());
		printf("попробуйте еще\n");
		return 1;
	}

	std::cmatch result_8;
	std::regex regular_8("(log((?!\\s*\\[).)+)|log\\s*$");
	if (std::regex_search(expression.getString(), result_8, regular_8)) {
		printf("Логарифм (log) должен иметь основание: %s\n", result_8[0].str().c_str());
		printf("попробуйте еще\n");
		return 1;
	}

	std::cmatch result_9;
	std::regex regular_9("^\\s*[\\.\\)\\]]");
	if (std::regex_search(expression.getString(), result_9, regular_9)) {
		printf("Функция не может начинаться с %s\n", result_9[0].str().c_str());
		printf("попробуйте еще\n");
		return 1;
	}

	std::cmatch result_10;
	std::regex regular_10("[(]\\s*[)]");
	if (std::regex_search(expression.getString(), result_10, regular_10)) {
		printf("Скобки не могут быть пустыми: %s\n", result_10[0].str().c_str());
		printf("попробуйте еще\n");
		return 1;
	}

	std::cmatch result_11;
	std::regex regular_11("\\)\\s*((\\d+\\.?\\d*)|sin|cos|tan|ctan|log|lg|ln|pi|e|x|sqrt)");
	if (std::regex_search(expression.getString(), result_11, regular_11)) {
		printf("После закрывающей скобки могут идти только арифметические знаки: %s\n", result_11[0].str().c_str());
		printf("попробуйте еще\n");
		return 1;
	}

	for (int i = 0; i < expression.getSize(); i++) {
		if (expression[i] == '(' && validatorBracket(expression, i) == -1) {
			printf("Не все скобки имеют пару, попробуйте еще\n");
			return 1;
		}
		else if (expression[i] == '(') break;
	}

	for (int i = 0; i < expression.getSize(); i++) {
		if (expression[i] == '[' && validatorSquareBracket(expression, i) == -1) {
			printf("Не все скобки имеют пару, попробуйте еще\n");
			return 1;
		}
		else if (expression[i] == '[') break;
	}

	return 0;
}

void drawTheBorder(HDC hdc, HPEN pen, int posX, int posY, double sizeX, double sizeY){
	SelectObject(hdc, pen);
	MoveToEx(hdc, posX, posY, NULL);
	LineTo(hdc, posX + sizeX, posY);
	LineTo(hdc, posX + sizeX, posY + sizeY);
	LineTo(hdc, posX, posY + sizeY);
	LineTo(hdc, posX, posY);
}

int countNum(int num) {
	int result = 0;
	while (num > 0) {
		result++;
		num /= 10;
	}
	return result;
}

double calculateStep(double num) {
	const int digitsAfterPoint = 15;
	double whole = floor(num);
	double fractional = (num - whole) * pow(10, digitsAfterPoint);
	double result = 0;
	int count = countNum((int)whole);
	if (count > 0) return pow(10, count - 2);
	for (int i = 1; i < digitsAfterPoint; i++) {
		if (floor(fractional / pow(10, digitsAfterPoint - i)) != 0) return pow(10, -i - 1);
	}
}

void draw(HANDLE hConsole, HWND hcon)
{
	system("cls");
	int posX, posY;
	int sizeX, sizeY;
	double minX, maxX;
	double minY = 0, maxY = 0;
	String expression;

	do { 
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
		printf("Введите функцию: y = ");
		expression.read();
		expression.toLower();
	} while (validator(expression, hConsole));

	Expression treeExpression(expression);

	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);

	do {
		printf("Введите координаты верхнего левого угла окна графика (x, y): ");
		scanf("%d%d", &posX, &posY);
		if (posX >= 0 && posY >= 0) {
			posY += 26;
			break;
		}
		else {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			printf("Координаты не могут быть отрицательными, попробуйте еще\n");
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
		}
	} while (true);

	do {
		printf("Введите размеры окна графика (ширина, высота): ");
		scanf("%d%d", &sizeX, &sizeY);
		if (sizeX >= 0 && sizeY >= 0) break;
		else {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			printf("Ширина и высота должны быть положительными, попробуйте еще\n");
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
		}
	} while (true);

	do {
		printf("Введите интервал изменения аргумента функции (min, max): ");
		scanf("%lf%lf", &minX, &maxX);
		if (maxX < minX) {
			double buff = minX;
			minX = maxX;
			maxX = buff;
		}
		if (minX != maxX) break;
		else {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			printf("Диапазон должен содержать больше одной точки, попробуйте еще\n");
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
		}
	} while (true);

	getchar();

	HDC hdc = GetDC(hcon);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(0, 0, 0));
	do {
		String answer;
		printf("Вывести функцию рядом с графиком: ");
		answer.read();
		answer.toLower();
		if (answer == "да" || answer == "д" || answer == "yes" || answer == "y") {
			wchar_t wchar[26];
			mbstowcs_s(NULL, wchar, sizeof(wchar) / 2, expression.getString(), sizeof(wchar));
			TextOut(hdc, posX + sizeX / 2 - (lstrlen(wchar) / 2 - 2) * 5 - 24, posY + sizeY + 20, L"y =", 3);
			TextOut(hdc, posX + sizeX / 2 - (lstrlen(wchar) / 2 - 2) * 5, posY + sizeY + 20, wchar, lstrlen(wchar));
			break;
		}
		else if (answer == "нет" || answer == "н" || answer == "no" || answer == "n") {
			break;
		}
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		printf("Введен некореектный ответ, попробуйте еще\n");
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	} while (true);

	system("cls");
	HPEN whitePen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	HPEN bluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	HPEN palePen = CreatePen(PS_SOLID, 1, RGB(100, 100, 100));


	const double periodicity = 0.0001;

	double stepX = calculateStep(abs(maxX) > abs(minX) ? abs(maxX) : abs(minX));
	if (maxX - minX < 3 * stepX) stepX /= 10;
	while (((maxX - minX) / stepX) > sizeX / 20) stepX *= 10;
	minX -= minX - stepX * floor(minX / stepX);
	maxX += maxX - stepX * floor(maxX / stepX);
	int sizeGridX = sizeX / ((maxX - minX) / stepX);
	sizeX -= sizeX % sizeGridX;
	double unitPerPixelX = (maxX - minX) / (double)sizeX;


	int i = 0;
	for (; i < sizeX; i++) {
		bool check = true;
		double result = treeExpression.perform(minX + i * unitPerPixelX, check);
		if (check) {
			minY = maxY = result;
			break;
		}
	}

	for (; i < sizeX; i++) {
		bool check = true;
		double result = treeExpression.perform(minX + i * unitPerPixelX, check);
		if (check) {
			if (result > maxY) maxY = result;
			else if (result < minY) minY = result;
		}
	}


	double stepY = calculateStep(abs(maxY) > abs(minY) ? abs(maxY) : abs(minY));
	if (maxY - minY < 3 * stepY) stepY /= 10;
	while (((maxY - minY) / stepY) > sizeY / 20) stepY *= 10;
	minY -= minY - stepY * floor(minY / stepY);
	maxY += maxY - stepY * floor(maxY / stepY);
	int sizeGridY = sizeY / ((maxY - minY) / stepY);
	sizeY -= sizeY % sizeGridY;
	double unitPerPixelY = (maxY - minY) / (double)sizeY;


	// draw the grid
	SelectObject(hdc, palePen);

	int posAxisX = -minX / unitPerPixelX;
	if (posAxisX < 0) posAxisX = 0;
	if (posAxisX > sizeX) posAxisX = sizeX;
	int posAxisY = maxY / unitPerPixelY;
	if (posAxisY < 0) posAxisY = 0;
	if (posAxisY > sizeY) posAxisY = sizeY;

	for (int i = 0; i <= sizeX; i += sizeGridX) { // grid x
		MoveToEx(hdc, posX + i, posY, NULL);
		LineTo(hdc, posX + i, posY + sizeY);

		double num = minX + i * unitPerPixelX;
		char numChar[26];
		sprintf(numChar, "%.2lf", num);
		wchar_t numWchar[26];
		mbstowcs_s(NULL, numWchar, sizeof(numWchar) / 2, numChar, sizeof(numChar));

		TextOut(hdc, posX + i, posY + posAxisY, numWchar, lstrlen(numWchar));

	}

	for (int i = 0; i <= sizeY; i += sizeGridY) { // grid y
		MoveToEx(hdc, posX, posY + i, NULL);
		LineTo(hdc, posX + sizeX, posY + i);

		double num = maxY - i * unitPerPixelY;
		char numChar[26];
		sprintf(numChar, "%.2lf", num);
		wchar_t numWchar[26];
		mbstowcs_s(NULL, numWchar, sizeof(numWchar) / 2, numChar, sizeof(numChar));

		TextOut(hdc, posX + posAxisX, posY + i, numWchar, lstrlen(numWchar));
	}

	SelectObject(hdc, whitePen);

	drawTheBorder(hdc, whitePen, posX, posY, sizeX, sizeY);


	MoveToEx(hdc, posX + posAxisX, posY, NULL);
	LineTo(hdc, posX + posAxisX, posY + sizeY);
	MoveToEx(hdc, posX, posY + posAxisY, NULL);
	LineTo(hdc, posX + sizeX, posY + posAxisY);

	// draw a graph
	SelectObject(hdc, bluePen);

	bool previousPoint = false;

	for (int i = 0; i < sizeX; i++) {
		for (double j = 0; j < unitPerPixelX; j += periodicity) {

			bool check = true;

			double result = treeExpression.perform(minX + i * unitPerPixelX + j, check);

			if (result > maxY) result = maxY;
			else if (result < minY) result = minY;

			if (check && previousPoint) {
				LineTo(hdc, posX + i, posY + sizeY - (int)((result - minY) / unitPerPixelY));
			}
			else if (check) {
				previousPoint = true;
				MoveToEx(hdc, posX + i, posY + sizeY - (int)((result - minY) / unitPerPixelY), NULL);
			}
			else previousPoint = false;
		}
	}

	drawTheBorder(hdc, whitePen, posX, posY, sizeX, sizeY);

	printf("Нажмите любую клавишу, чтобы выйти ");
	_getch();

	DeleteObject(whitePen);
	DeleteObject(bluePen);
	DeleteObject(palePen);
}

void help() {
	system("cls");
	printf("x      – аргумент функции\n");
	printf("+      – сложение\n");
	printf("-      – вычитание\n");
	printf("*      – умножение\n");
	printf("/      – деление\n");
	printf("^      – возведение в степень\n");
	printf("sqrt   – квадратный корень\n");
	printf("sin    – синус\n");
	printf("cos    – косинус\n");
	printf("tan    – тангенс\n");
	printf("ctan   – котангенс\n");
	printf("ln     – натуральный логарифм\n");
	printf("lg     – десятичный логарифм\n");
	printf("log[a] – логарифм по основанию a\n");
	printf("\nНажмите любую клавишу, чтобы выйти ");
	_getch();
}

int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hcon = GetConsoleWindow();

	CONSOLE_FONT_INFO cfi;
	GetCurrentConsoleFont(hConsole, false, &cfi);
	COORD fs = GetConsoleFontSize(hConsole, cfi.nFont);
	PCONSOLE_FONT_INFOEX ccf = new CONSOLE_FONT_INFOEX;
	(*ccf).dwFontSize.X = 12;
	(*ccf).dwFontSize.Y = 20;
	(*ccf).nFont = 11;
	(*ccf).cbSize = sizeof(CONSOLE_FONT_INFOEX);
	ccf->FontWeight = 400;
	lstrcpyW((*ccf).FaceName, L"Lucida Console");
	(*ccf).FontFamily = FF_DONTCARE;
	bool b = SetCurrentConsoleFontEx(hConsole, false, ccf);
	fs = GetConsoleFontSize(hConsole, cfi.nFont);

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	PCONSOLE_SCREEN_BUFFER_INFO pwi = new CONSOLE_SCREEN_BUFFER_INFO;
	PWINDOWINFO pgwi = new WINDOWINFO;

	const int n = 3;
	COORD positionMenuItem[n];
	int punkt = 0;
	char names[n][25] = { "Построить график", "Справка", "Выход" };
	do
	{
		int xmax, ymax;

		GetConsoleScreenBufferInfo(hConsole, pwi);
		GetWindowInfo(hcon, pgwi);
		xmax = pwi->dwSize.X;
		ymax = pwi->dwSize.Y;

		int y0 = 7;
		for (int i = 0; i < n; i++)
		{
			positionMenuItem[i].X = (xmax - strlen(names[i])) / 2;
			positionMenuItem[i].Y = y0 + i;
		}
		system("cls");
		char title[] = "Построение графиков";
		COORD pos;
		pos.X = (xmax - strlen(title)) / 2;
		pos.Y = n;
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
		SetConsoleCursorPosition(hConsole, pos);
		puts(title);
		for (int i = 0; i < n; i++)
		{
			SetConsoleCursorPosition(hConsole, positionMenuItem[i]);
			puts(names[i]);
		}
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		SetConsoleCursorPosition(hConsole, positionMenuItem[punkt]);
		puts(names[punkt]);
		unsigned char ch;
		do
		{
			ch = _getch();
			if (ch == 224)
			{
				ch = _getch();
				switch (ch)
				{
				case 72:
					SetConsoleCursorPosition(hConsole, positionMenuItem[punkt]);
					SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
					puts(names[punkt]);
					punkt--;
					if (punkt < 0) punkt = n - 1;
					SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					SetConsoleCursorPosition(hConsole, positionMenuItem[punkt]);
					puts(names[punkt]); break;
				case 80:
					SetConsoleCursorPosition(hConsole, positionMenuItem[punkt]);
					SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
					puts(names[punkt]);
					punkt++;
					if (punkt > n - 1) punkt = 0;
					SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					SetConsoleCursorPosition(hConsole, positionMenuItem[punkt]);
					puts(names[punkt]); break;
				}
			}
		} while (ch != 13);	// enter - выбор пункта меню
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
		switch (punkt)
		{
		case 0:
			draw(hConsole, hcon);
			break;
		case 1:
			help();
			break;
		}
	} while (punkt != n - 1);
	return 0;
}