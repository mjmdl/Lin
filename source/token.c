#include "token.h"

const char *describe_token_kind(Token_Kind kind) {
	switch (kind) {
	default:
	case TOKEN_NONE:
		return "None";
	case TOKEN_END_OF_FILE:
		return "End of File";
	case TOKEN_COMMENT_LINE:
		return "Comment Line";
	case TOKEN_COMMENT_BLOCK:
		return "Comment Block";
	case TOKEN_IDENTIFIER:
		return "Identifier";
	case TOKEN_LITERAL_STRING:
		return "Literal String";
	case TOKEN_LITERAL_BOOL:
		return "Literal Bool";
	}
}
