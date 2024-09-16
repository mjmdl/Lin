#ifndef LIN__TOKEN_H
#define LIN__TOKEN_H

#include "lin.h"

typedef enum Token_Kind {
	TOKEN_NONE = 0,
	TOKEN_END_OF_FILE,
	TOKEN_COMMENT_LINE,
	TOKEN_COMMENT_BLOCK,
	TOKEN_IDENTIFIER,
	TOKEN_LITERAL_STRING,
	TOKEN_LITERAL_BOOL,
} Token_Kind;

typedef struct Token {
	Token_Kind kind;
	const char *source;
	size_t length;
} Token;

const char *describe_token_kind(Token_Kind kind);

#endif // LIN__TOKEN_H
