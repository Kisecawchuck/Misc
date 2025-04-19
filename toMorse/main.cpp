#include <cctype>
#include <cstdio>
#include <iostream>

#define INPUT_SIZE 128

using namespace std;

string morse[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--",
"-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

int main() {
    char input[INPUT_SIZE];
    cout << "Message to morse: ";
    fgets(input, INPUT_SIZE, stdin);
    cout << input << '\n';

    cout << "In morse: ";
    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            cout << morse[toupper(input[i]) - 'A'] << ' ';
        }
    }
    cout << '\n';

    return 0;
}
