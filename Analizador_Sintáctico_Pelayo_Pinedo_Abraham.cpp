#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Función para representar un token
struct Token {
    char type;
    int value;
};

class Parser {
public:
    Parser(const string& input) : input_(input), pos_(0) {}

    // Método para analizar una expresión
    int parseExpression() {
        int result = parseTerm();
        while (pos_ < input_.length()) {
            char op = input_[pos_++];
            if (op == '+') {
                result += parseTerm();
            } else if (op == '-') {
                result -= parseTerm();
            } else {
                throw runtime_error("Error de sintaxis");
            }
        }
        return result;
    }

private:
    string input_;
    size_t pos_;

    // Método para analizar un término
    int parseTerm() {
        int result = parseFactor();
        while (pos_ < input_.length()) {
            char op = input_[pos_++];
            if (op == '*') {
                result *= parseFactor();
            } else if (op == '/') {
                int divisor = parseFactor();
                if (divisor == 0) {
                    throw runtime_error("División por cero");
                }
                result /= divisor;
            } else {
                pos_--;
                break;
            }
        }
        return result;
    }

    // Método para analizar un factor (número o paréntesis)
    int parseFactor() {
        if (isdigit(input_[pos_])) {
            int number = 0;
            while (pos_ < input_.length() && isdigit(input_[pos_])) {
                number = number * 10 + (input_[pos_] - '0');
                pos_++;
            }
            return number;
        } else if (input_[pos_] == '(') {
            pos_++;
            int result = parseExpression();
            if (pos_ < input_.length() && input_[pos_] == ')') {
                pos_++;
                return result;
            } else {
                throw runtime_error("Error de sintaxis: paréntesis no cerrado");
            }
        } else {
            throw runtime_error("Error de sintaxis: factor no reconocido");
        }
    }
};

int main() {
    string input = "3 + 4 * (5 - 2) / 2";

    try {
        Parser parser(input);
        int result = parser.parseExpression();
        cout << "Resultado: " << result << endl;
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}

