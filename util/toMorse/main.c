#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define INPUT_SIZE  1024
#define OUTPUT_SIZE 4096 

// Take an ASCII message and encode into Morse code
void toMorse(char from[], char to[]);
char *parseInput(char a);

// Morse code arrays
char* morseAlpha[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--",
"-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
char* morseDigit[] = {"-----", ".---", "..---", "...--", "----.", ".....", "-....", "--...", "---..", "----."};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: morse [OPTIONS] MESSAGES\n");
        printf("Try 'morse --help' for more information.\n");
        return 1;
    }
    if (strcmp(argv[1], "--help") == 0) {
        printf("Usage: morse [OPTIONS] MESSAGES\n");
        printf("Encode ASCII MESSAGES into Morse code.\n");
        printf("Example: morse 'testing shit out' 'my balls are dense rn'\n");
        printf("MESSAGES can contain multiple words, but remember to use quotes.\n");
        putchar('\n');
        printf("Miscellaneous:\n");
        printf(" -i, --interactive\tprompt user for MESSAGE interactively\n");
    } else if (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--interactive") == 0) {
        char in[INPUT_SIZE], out[OUTPUT_SIZE];
        printf("Message to morse: ");
        fgets(in, INPUT_SIZE, stdin);
        toMorse(in, out);
        printf("In morse: %s\n", out);
    } else {
        char out[OUTPUT_SIZE];
        for (int i = 1; i < argc; i++) {
            out[0] = '\0';
            toMorse(argv[i], out);
            printf("Message %d: %s\n", i, out);
        }
    }

    return 0;
}

char *parseInput(char a) {
    return isalpha(a) ? morseAlpha[toupper(a) - 'A']
            : isdigit(a) ? morseDigit[a - '0']
            : a == ' ' ? " /" 
            : '\0';
}

void toMorse(char s[], char d[]) {
    for (int i = 0; s[i] != '\n' && s[i] != '\0'; i++) {
        strcat(d, parseInput(s[i]));
        strcat(d, " ");
    }
}
