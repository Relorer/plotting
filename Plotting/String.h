#pragma once
#include <iostream>
#include "Vect.h"
class String : 
	public Vect<char> 
{
public:
	String();
	String(const char* str);
	bool operator==(const char* anotherStr);
	char* getString();
	void toLower();
	void read(const char lineEnd = '\n', FILE* filestream = stdin);
	void pushFront(char data) override;
	int getSize() override;
	void clear();
};