#ifndef LIN__LEXER_H
#define LIN__LEXER_H

#include "file.h"
#include "lin.h"
#include "token.h"

typedef struct Lexer {
	const char *begin;
	const char *end;
	const char *x;
} Lexer;

Lexer lexer_from_file(File *file);
Token next_token(Lexer *lexer);

#endif // LIN__LEXER_H
