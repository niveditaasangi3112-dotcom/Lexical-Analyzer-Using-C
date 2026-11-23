#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

static const char *keywords[MAX_KEYWORDS] = {
    "int", "float", "return", "if", "else", "while", "for", "do",
    "break", "continue", "char", "double", "void", "switch",
    "case", "default", "const", "static", "sizeof", "struct"
};

static const char *operators = "+-*/%*=!<>|&";
static const char *specialCharacters = ",;{}()[]";

static int is_keyword(const char *word)
{
    for (int i = 0; i < MAX_KEYWORDS; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

static int is_operator(char ch)
{
    return strchr(operators, ch) != NULL;
}

static int is_special_character(char ch)
{
    return strchr(specialCharacters, ch) != NULL;
}

void lexical_analyzer(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    int ch;

    if (fp == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return;
    }

    while ((ch = fgetc(fp)) != EOF) {
        if (isspace((unsigned char)ch))
            continue;

        /* Identifier or keyword */
        if (isalpha((unsigned char)ch) || ch == '_') {
            char token[MAX_TOKEN_SIZE];
            int i = 0;

            token[i++] = (char)ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isalnum((unsigned char)ch) || ch == '_')) {
                if (i < MAX_TOKEN_SIZE - 1)
                    token[i++] = (char)ch;
            }

            token[i] = '\0';

            if (is_keyword(token))
                printf("Keyword       : %s\n", token);
            else
                printf("Identifier    : %s\n", token);

            if (ch != EOF)
                ungetc(ch, fp);
        }
        /* Number */
        else if (isdigit((unsigned char)ch)) {
            char token[MAX_TOKEN_SIZE];
            int i = 0;

            token[i++] = (char)ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isdigit((unsigned char)ch) || ch == '.')) {
                if (i < MAX_TOKEN_SIZE - 1)
                    token[i++] = (char)ch;
            }

            token[i] = '\0';
            printf("Number        : %s\n", token);

            if (ch != EOF)
                ungetc(ch, fp);
        }
        /* String constant */
        else if (ch == '"') {
            char token[MAX_TOKEN_SIZE];
            int i = 0;

            token[i++] = (char)ch;

            while ((ch = fgetc(fp)) != EOF) {
                if (i < MAX_TOKEN_SIZE - 1)
                    token[i++] = (char)ch;

                if (ch == '"')
                    break;
            }

            token[i] = '\0';
            printf("String        : %s\n", token);
        }
        /* Character constant */
        else if (ch == '\'') {
            char token[MAX_TOKEN_SIZE];
            int i = 0;

            token[i++] = (char)ch;

            while ((ch = fgetc(fp)) != EOF) {
                if (i < MAX_TOKEN_SIZE - 1)
                    token[i++] = (char)ch;

                if (ch == '\'')
                    break;
            }

            token[i] = '\0';
            printf("Character     : %s\n", token);
        }
        /* Comments or division operator */
        else if (ch == '/') {
            int next = fgetc(fp);

            if (next == '/') {
                while ((ch = fgetc(fp)) != EOF && ch != '\n')
                    ;
            } else if (next == '*') {
                int prev = 0;
                while ((ch = fgetc(fp)) != EOF) {
                    if (prev == '*' && ch == '/')
                        break;
                    prev = ch;
                }
            } else {
                printf("Operator      : /\n");
                if (next != EOF)
                    ungetc(next, fp);
            }
        }
        /* Operators */
        else if (is_operator((char)ch)) {
            int next = fgetc(fp);

            if ((ch == '=' && next == '=') ||
                (ch == '!' && next == '=') ||
                (ch == '<' && next == '=') ||
                (ch == '>' && next == '=') ||
                (ch == '&' && next == '&') ||
                (ch == '|' && next == '|') ||
                (ch == '+' && next == '+') ||
                (ch == '-' && next == '-') ||
                (ch == '+' && next == '=') ||
                (ch == '-' && next == '=') ||
                (ch == '*' && next == '=') ||
                (ch == '/' && next == '=')) {
                printf("Operator      : %c%c\n", ch, next);
            } else {
                printf("Operator      : %c\n", ch);
                if (next != EOF)
                    ungetc(next, fp);
            }
        }
        /* Special characters */
        else if (is_special_character((char)ch)) {
            printf("Special       : %c\n", ch);
        }
        /* Preprocessor marker */
        else if (ch == '#') {
            printf("Special       : #\n");
        }
        else {
            printf("Unknown       : %c\n", ch);
        }
    }

    fclose(fp);
}
