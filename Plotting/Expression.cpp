#include "Expression.h"

int Expression::priority(String& operation)
{
	if (operation == "+") return 3;
	if (operation == "-") return 3;
	if (operation == "*") return 2;
	if (operation == "/") return 2;
	if (operation == "^") return 1;
	if (operation == "sin") return 0;
	if (operation == "cos") return 0;
	if (operation == "tan") return 0;
	if (operation == "ctan") return 0;
	if (operation == "log") return 0;
	if (operation == "ln") return 0;
	if (operation == "lg") return 0;
	if (operation == "sqrt") return 0;
	return -1;
}

int Expression::growTree(Token * &curToken, int start, int end)
{
	int operation = findLastOperation(start, end);
	if (operation != -1) {
		Operation* op = new Operation(tokens[operation]);
		if (strstr("+-*/^", tokens[operation].getString())) {
			growTree(op->leftToken, start, operation);
			growTree(op->rightToken, operation + 1, end);
		}
		else if (tokens[operation] == "log") {
			int closeBracket = findPos—losingSquareBracket(operation + 1, end);
			growTree(op->leftToken, operation + 2, closeBracket);
			growTree(op->rightToken, closeBracket + 1, end);
		}
		else {
			growTree(op->rightToken, operation + 1, end);
		}
		curToken = op;
	}
	else {
		if (tokens[start] == "(") start++;
		if (tokens[start] == "x") {
			Operand* op = new Operand();
			curToken = op;
		}
		else if (tokens[start] == "e") {
			Operand* op = new Operand(M_E);
			curToken = op;
		}
		else if (tokens[start] == "pi") {
			Operand* op = new Operand(M_PI);
			curToken = op;
		}
		else {
			Operand* op = new Operand(atof(tokens[start].getString()));
			curToken = op;
		}
	}

	return 0;
}

int Expression::findLastOperation(int start, int end)
{
	int operation = -1;
	int firstBracket;
	int secondBracket = -1;

	for (int i = start; i < end; i++) {
		if (tokens[i] == "(") {
			firstBracket = i;
			secondBracket = findPos—losingBracket(i, end);
			if (secondBracket != -1) i = secondBracket;
		}
		else if (tokens[i] == "[") {
			firstBracket = i;
			secondBracket = findPos—losingSquareBracket(i, end);
			if (secondBracket != -1) i = secondBracket;
		}
		else if (operation == -1) {
			if (priority(tokens[i]) != -1) operation = i;
		}
		else if (priority(tokens[i]) > priority(tokens[operation])) operation = i;
	}
	if (operation == -1 && secondBracket != -1) operation = findLastOperation(firstBracket + 1, secondBracket);
	return operation;
}

int Expression::findPos—losingBracket(int posOpenBracket, int end)
{
	int numberBracket = 0;
	for (int i = posOpenBracket + 1; i < end; i++) {
		if (!numberBracket && tokens[i] == ")") return i;
		else if (tokens[i] == ")") numberBracket--;
		else if (tokens[i] == "(") numberBracket++;
	}
	return -1;
}

int Expression::findPos—losingSquareBracket(int posOpenBracket, int end)
{
	int numberBracket = 0;
	for (int i = posOpenBracket + 1; i < end; i++) {
		if (!numberBracket && tokens[i] == "]") return i;
		else if (tokens[i] == "]") numberBracket--;
		else if (tokens[i] == "[") numberBracket++;
	}
	return -1;
}

int Expression::breakIntoTokens(String & expression)
{
	std::regex regular("[\\[\\]()+\\-\\/^ex*]|(sin|cos|tan|ctan|log|lg|ln|pi|sqrt)|\\d+(\\.\\d{0,})?");
	auto item = std::cregex_iterator(expression.getString(), expression.getString() + expression.getSize(), regular);
	auto end = std::cregex_iterator();
	int i = 0;
	tokens[i] = item->str().c_str();
	if (tokens[i] == "-") {
		tokens[i++].pushFront('1');
		tokens[i++] = "*";
	}
	else i++;
	item++;
	for (; item != end; ++item, i++) {
		if (strstr("sin cos tan ctan log lg ln pi e x ( [", item->str().c_str()) && priority(tokens[i - 1]) == -1 && !strstr("( ) [ ]", tokens[i - 1].getString()))
			tokens[i++] = "*";
		tokens[i] = item->str().c_str();
		if (tokens[i] == "-" && tokens[i - 1] == "(") {
			tokens[i++].pushFront('1');
			tokens[i] = "*";
		}
	}

	return 0;
}

Expression::Expression(String & expression)
{
	root = nullptr;
	breakIntoTokens(expression);
	growTree(root, 0, tokens.getSize());
}

double Expression::perform(double x, bool& check)
{
	return root->perform(x, check);
}