#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

// Definición de la estructura Token
struct Token {
	string type;
	string value;
};

// Función para analizar la entrada y generar tokens
vector<Token> tokenize(const string& input) {
	vector<Token> tokens;
	string currentToken = "";
	
	for (char c : input) {
		if (isdigit(c)) {
			currentToken += c;
		} else {
			if (!currentToken.empty()) {
				tokens.push_back({ "Number", currentToken });
				currentToken = "";
			}
		}
	}
	
	if (!currentToken.empty()) {
		tokens.push_back({ "Number", currentToken });
	}
	
	return tokens;
}

int main() {
	string input = "123 is a number, and 456 is another.";
	
	vector<Token> tokens = tokenize(input);
	
	cout << "Tokens:" << endl;
	for (const Token& token : tokens) {
		cout << "Type: " << token.type << ", Value: " << token.value << endl;
	}
	
	return 0;
}
