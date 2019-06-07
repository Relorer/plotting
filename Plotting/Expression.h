#pragma once
#define _USE_MATH_DEFINES
#include <regex>
#include <math.h>
#include "Vect.h"
#include "String.h"

class Expression
{
private:
	class Token {
	public:
		virtual double perform(double argument, bool& check) = 0;
	};

	class Operation : public Token {
	public:
		String operation;
		Token* leftToken;
		Token* rightToken;
		Operation(String operation) {
			this->operation = operation;
			leftToken = nullptr;
			rightToken = nullptr;
		}
		double perform(double argument, bool& check) override {
			if (!strcmp(operation.getString(), "+")) return leftToken->perform(argument, check) + rightToken->perform(argument, check);
			if (!strcmp(operation.getString(), "-")) return leftToken->perform(argument, check) - rightToken->perform(argument, check);
			if (!strcmp(operation.getString(), "*")) return leftToken->perform(argument, check)* rightToken->perform(argument, check);
			if (!strcmp(operation.getString(), "/")) {
				double rightValue = rightToken->perform(argument, check);
				if ((int)(rightValue * 1000) % 1000 != 0) return leftToken->perform(argument, check) / rightValue; // 0
			}
			if (!strcmp(operation.getString(), "^")) {
				double rightValue = rightToken->perform(argument, check);
				double leftValue = leftToken->perform(argument, check);
				if (leftValue >= 0 || (double)(int)rightValue == rightValue)
					return pow(leftToken->perform(argument, check), rightToken->perform(argument, check));
			}
			if (!strcmp(operation.getString(), "sin")) return sin(rightToken->perform(argument, check));
			if (!strcmp(operation.getString(), "cos")) return cos(rightToken->perform(argument, check));
			if (!strcmp(operation.getString(), "tan")) {
				double rightValue = rightToken->perform(argument, check);
				if ((int)(cos(rightValue) * 1000) % 1000 != 0) return tan(rightValue); // pi / 2 
			}
			if (!strcmp(operation.getString(), "ctan")) {
				double rightValue = rightToken->perform(argument, check);
				if ((int)(sin(rightValue) * 1000) % 1000 != 0) return 1 / tan(rightValue); // 0 pi
			}
			if (!strcmp(operation.getString(), "log")) {
				double rightValue = rightToken->perform(argument, check);
				double leftValue = leftToken->perform(argument, check);
				if (rightValue > 0 && leftValue != 1 && leftValue > 0)
					return log2(rightValue) / log2(leftValue); // bas: 0 1 arg: >= 1 
			}
			if (!strcmp(operation.getString(), "ln")) {
				double rightValue = rightToken->perform(argument, check);
				if (rightValue > 0) return log(rightValue); //arg: >= 1
			}
			if (!strcmp(operation.getString(), "lg")) {
				double rightValue = rightToken->perform(argument, check);
				if (rightValue > 0) return log10(rightValue); //arg: >= 1
			}
			if (!strcmp(operation.getString(), "sqrt")) {
				double rightValue = rightToken->perform(argument, check);
				if (rightValue >= 0) return sqrt(rightValue); //arg: >= 0
			}
			check = false;
			return 0;
		}
	};

	class Operand : public Token {
	public:
		bool isArgument;
		double value;
		Operand() {
			this->value = 0;
			this->isArgument = true;
		}
		Operand(double value) {
			this->value = value;
			this->isArgument = false;
		}
		double perform(double argument, bool& check) override {
			if (isArgument) return argument;
			return value;
		}
	};

	Token* root;
	Vect<String> tokens;

	int priority(String& operation);

	int growTree(Token*& curToken, int start, int end);

	int findLastOperation(int start, int end);

	int findPos—losingBracket(int posOpenBracket, int end);

	int findPos—losingSquareBracket(int posOpenBracket, int end);

	int breakIntoTokens(String& expression);

public:
	Expression(String& expression);

	double perform(double x, bool& check);
};