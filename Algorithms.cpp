#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    NUMBER, OPERATOR, FUNCTION, PARENTHESIS, END
} TokenType;

typedef struct {
    TokenType type;
    union {
        int value; // For numbers
        char op; // For operators and parentheses
        char func[10]; // Increased size for longer function names
    };
} Token;

// Function to determine if a string is a function name
int isFunctionName(char* str) {
    const char* functions[] = { "MIN", "MAX", "IF", "N" };
    for (int i = 0; i < sizeof(functions) / sizeof(functions[0]); ++i) {
        if (strcmp(str, functions[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to read the next token from the input
Token getNextToken(FILE* input) {
    Token token;
    char ch = fgetc(input);

    // Skip whitespace
    while (isspace(ch)) ch = fgetc(input);

    if (isdigit(ch) || ch == '-') { // Handle numbers (and negative numbers, if they appear without N)
        ungetc(ch, input); // Put back the character to read the whole number
        fscanf_s(input, "%d", &token.value);
        token.type = NUMBER;
    }
    else if (ch == '.' || ch == EOF) { // End of an expression or file
        token.type = END;
    }
    else if (strchr("+-*/", ch)) { // Operators
        token.op = ch;
        token.type = OPERATOR;
    }
    else if (ch == '(' || ch == ')') { // Parentheses
        token.op = ch;
        token.type = PARENTHESIS;
    }
    else if (isalpha(ch)) { // Potential function name
        char funcName[10] = { ch, '\0' }; // Start building the function name
        while (isalpha(ch = fgetc(input))) { // Read the rest of the function name
            strncat_s(funcName, &ch, 1);
        }
        ungetc(ch, input); // The last character read is not part of the function name
        if (isFunctionName(funcName)) {
            strcpy_s(token.func, funcName);
            token.type = FUNCTION;   
        }
    }
    else {
        // Handle unknown character/token
        fprintf(stderr, "Unknown token encountered: %c\n", ch);
        exit(EXIT_FAILURE);
    }

    return token;
}

int main() {
    printf("Enter an expression (end with a dot): \n");
    printf("what the hack is this (Osamah) \n");
    printf("aaaaa magic");

    Token token;
    do {
        token = getNextToken(stdin);
        switch (token.type) {
        case NUMBER:
            printf("Number: %d\n", token.value);
            break;
        case OPERATOR:
            printf("Operator: %c\n", token.op);
            break;
        case FUNCTION:
            printf("Function: %s\n", token.func);
            break;
        case PARENTHESIS:
            printf("Parenthesis: %c\n", token.op);
            break;
        case END:
            printf("End of expression.\n");
            break;
        default:
            break;
        }
    } while (token.type != END);

    return 0;
}
