#include "String.h"
#include <iostream>

String::String()
{
	this->vect[0] = '\0';
}

String::String(const char* str)
{
	this->vect = new char[strlen(str) + 1];
	for (unsigned int i = 0; i < strlen(str); i++) {
		this->pushFront(str[i]);
	}
}

bool String::operator==(const char* anotherStr)
{
	if (this->size - 1 != strlen(anotherStr)) return 0;
	return !strcmp(this->vect, anotherStr);
}

char* String::getString()
{
	return this->vect;
}

void String::toLower()
{
	for (int i = 0; i < size; i++) vect[i] = towlower(vect[i]);
}

void String::read(const char lineEnd, FILE * filestream)
{
	char ch;
	this->size = 1;
	while ((ch = getc(filestream)) != lineEnd) this->pushFront(ch);
}

void String::pushFront(char data)
{
	this->operator[](size ? size - 1 : size) = data;
	this->operator[](size) = '\0';
}

int String::getSize()
{
	return this->size - 1;
}

void String::clear()
{
	size = 0;
	this->vect[size] = '\0';
}