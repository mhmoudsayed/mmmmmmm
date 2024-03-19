#include <iostream>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

// Structure to represent a rational number
struct Rational {
    int numerator;
    int denominator;
};

// Function to find the greatest common divisor (GCD) using Euclid's algorithm
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to simplify a rational number by dividing both numerator and denominator by their greatest common divisor
void simplifyRational(Rational& rational) {
    int divisor = gcd(rational.numerator, rational.denominator);
    rational.numerator /= divisor;
    rational.denominator /= divisor;
}

// Function to parse a string input and extract a rational number
bool parseRational(const string& input, Rational& rational) {
    stringstream ss(input);
    char slash;
    if (!(ss >> rational.numerator >> slash >> rational.denominator) || slash != '/') {
        return false;
    }
    return true;
}

// Function to add two rational numbers
Rational addRationals(const Rational& rational1, const Rational& rational2) {
    Rational result;
    result.numerator = rational1.numerator * rational2.denominator + rational2.numerator * rational1.denominator;
    result.denominator = rational1.denominator * rational2.denominator;
    simplifyRational(result);
    return result;
}

// Function to subtract two rational numbers
Rational subtractRationals(const Rational& rational1, const Rational& rational2) {
    Rational result;
    result.numerator = rational1.numerator * rational2.denominator - rational2.numerator * rational1.denominator;
    result.denominator = rational1.denominator * rational2.denominator;
    simplifyRational(result);
    return result;
}

// Function to multiply two rational numbers
Rational multiplyRationals(const Rational& rational1, const Rational& rational2) {
    Rational result;
    result.numerator = rational1.numerator * rational2.numerator;
    result.denominator = rational1.denominator * rational2.denominator;
    simplifyRational(result);
    return result;
}

// Function to divide two rational numbers
Rational divideRationals(const Rational& rational1, const Rational& rational2) {
    Rational result;
    result.numerator = rational1.numerator * rational2.denominator;
    result.denominator = rational1.denominator * rational2.numerator;
    simplifyRational(result);
    return result;
}

// Function to calculate the percentage of a rational number
double calculatePercentage(const Rational& rational) {
    return (static_cast<double>(rational.numerator) / rational.denominator) * 100;
}

// Function to print a rational number
void printRational(const Rational& rational) {
    cout << rational.numerator << "/" << rational.denominator;
}

int main() {
    string input;
    while (true) {
        cout << "Please enter a rational number operation (or exit): ";
        getline(cin, input);
        if (input == "exit") {
            cout << "Thank you for using the rational number calculator." << endl;
            break;
        }

        Rational rational1, rational2, result;
        double percentage;
        char op;

        // Parse the input string to extract rational numbers and operator
        stringstream ss(input);
        if (!(ss >> rational1.numerator >> op >> rational1.denominator >> rational2.numerator >> op >> rational2.denominator)) {
            cout << "Invalid input. Try again." << endl;
            continue;
        }

        // Check if the operator is valid
        if (op != '+' && op != '-' && op != '*' && op != '/' && op != '%') {
            cout << "Invalid operation. Try again." << endl;
            continue;
        }

        // Check if denominators are not zero
        if (rational1.denominator == 0 || rational2.denominator == 0) {
            cout << "Invalid operand. Try again." << endl;
            continue;
        }

        // Perform the specified operation
        switch (op) {
            case '+':
                result = addRationals(rational1, rational2);
                cout << "= ";
                printRational(result);
                cout << endl;
                break;
            case '-':
                result = subtractRationals(rational1, rational2);
                cout << "= ";
                printRational(result);
                cout << endl;
                break;
            case '*':
                result = multiplyRationals(rational1, rational2);
                cout << "= ";
                printRational(result);
                cout << endl;
                break;
            case '/':
                // Check for division by zero
                if (rational2.numerator == 0) {
                    cout << "Division by zero is not allowed. Try again." << endl;
                    continue;
                }
                result = divideRationals(rational1, rational2);
                cout << "= ";
                printRational(result);
                cout << endl;
                break;
            case '%':
                // Calculate the percentage of the first rational number
                percentage = calculatePercentage(rational1);
                cout << "= " << percentage << "%" << endl;
                break;
        }
    }

    return 0;
}

