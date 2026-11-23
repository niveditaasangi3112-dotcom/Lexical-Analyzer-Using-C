# Lexical Analyzer in C

A basic file-based lexical analyzer written in C. It reads a C source file and prints the tokens it recognizes, such as keywords, identifiers, numeric literals, string and character constants, operators, and special characters.

## Features

- Recognizes a predefined set of C keywords.
- Identifies identifiers.
- Recognizes numeric sequences containing digits and decimal points.
- Prints string and character constants.
- Recognizes selected single-character and two-character operators.
- Skips line comments (`//`) and block comments (`/* ... */`).
- Identifies common punctuation and delimiters as special characters.
- Reports unrecognized characters.

## Project files

| File | Purpose |
|---|---|
| `main.c` | Prompts for a source filename and starts the analyzer. |
| `lexer.c` | Implements token recognition and output. |
| `lexer.h` | Declares the analyzer function and defines token-related constants. |
| `test.c` | Sample C source file to analyze. |

## Requirements

- GCC or another C compiler that supports C11.
- A terminal or command prompt.

## Compile

Open a terminal in this project directory and run:

```bash
gcc -Wall -Wextra -std=c11 main.c lexer.c -o lexer
```

On Windows with GCC/MinGW, you can use:

```bash
gcc -Wall -Wextra -std=c11 main.c lexer.c -o lexer.exe
```

## Run

On Linux or macOS:

```bash
./lexer
```

On Windows:

```bash
lexer.exe
```

When prompted, enter:

```text
test.c
```

Make sure the source file you enter is in the current working directory, or provide its path.

## Example

The included `test.c` file contains a small C program with declarations, numbers, an `if` statement, an increment operator, and a return statement. The analyzer prints each recognized token on a separate line.

## Current scope and limitations

This is a basic educational lexer, not a complete implementation of the C language lexical specification. It uses a fixed keyword list and a simple character-by-character scanner. For example, it does not fully validate numeric literals, does not recognize every possible C operator as a combined token, and does not implement preprocessing or escape-sequence-aware string parsing.

## Possible future improvements

- Add the full set of C keywords and operators.
- Improve numeric literal and escape-sequence handling.
- Track line and column numbers for tokens.
- Return structured token types instead of printing directly.
- Add automated tests for valid and invalid input.

## License

No license is currently specified. Add a license file if you want to grant others explicit permission to reuse or modify this project.
