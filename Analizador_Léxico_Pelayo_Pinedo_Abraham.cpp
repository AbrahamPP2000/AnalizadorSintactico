#include <iostream>
#include <string>
#include <vector>
#include <cctype>

// Definición de la estructura Token
struct Token {
	std::string type;
	std::string value;
};

// Función para comprobar si una cadena es una palabra clave
bool isKeyword(const std::string& str) {
	std::vector<std::string> keywords = { "if", "else", "while", "int", "return" };
	return std::find(keywords.begin(), keywords.end(), str) != keywords.end();
}

// Función para analizar la entrada y generar tokens
std::vector<Token> tokenize(const std::string& input) {
	std::vector<Token> tokens;
	std::string currentToken = "";
	bool inWord = false;
	
	for (char c : input) {
		if (std::isalpha(c) || c == '_') {
			currentToken += c;
			inWord = true;
		} else {
			if (inWord) {
				if (isKeyword(currentToken)) {
					tokens.push_back({ "Keyword", currentToken });
				} else {
					tokens.push_back({ "Identifier", currentToken });
				}
				currentToken = "";
				inWord = false;
			}
			
			if (std::isdigit(c)) {
				currentToken += c;
			} else if (c != ' ') {
				tokens.push_back({ "Operator", std::string(1, c) });
			}
		}
	}
	
	if (!currentToken.empty()) {
		if (inWord) {
			if (isKeyword(currentToken)) {
				tokens.push_back({ "Keyword", currentToken });
			} else {
				tokens.push_back({ "Identifier", currentToken });
			}
		} else if (std::isdigit(currentToken[0])) {
			tokens.push_back({ "Number", currentToken });
		}
	}
	
	return tokens;
}

int main() {
	std::string input = "if (x > 0) { return 42; }";
	
	std::vector<Token> tokens = tokenize(input);
	
	std::cout << "Tokens:" << std::endl;
	for (const Token& token : tokens) {
		std::cout << "Type: " << token.type << ", Value: " << token.value << std::endl;
	}
	
	return 0;
}
