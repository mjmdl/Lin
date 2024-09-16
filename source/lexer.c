#include <stdio.h>

#include "lexer.h"
#include "string.h"

static bool is_in_bounds(const Lexer *lexer) {
	return lexer->x < lexer->end && *lexer->x != '\0';
}

static void skip_whitespace(Lexer *lexer) {
	while (is_whitespace(*lexer->x) && is_in_bounds(lexer)) {
		lexer->x++;
	}
}

static bool try_identifier(Lexer *lexer, Token *token) {
	if (!is_identifier_initial(*lexer->x)) {
		return false;
	}

	token->kind = TOKEN_IDENTIFIER;
	token->source = lexer->x;

	do {
		lexer->x++;
	} while (is_in_bounds(lexer) && is_identifier(*lexer->x));

	token->length = lexer->x - token->source;
	return true;
}

static bool try_comment(Lexer *lexer, Token *token) {
	if (*lexer->x != '/') {
		return false;
	}
	
	lexer->x++;
	if (!is_in_bounds(lexer)) {
		lexer->x--;
		return false;
	}

	if (*lexer->x == '/') {
		token->kind = TOKEN_COMMENT_LINE;
		token->source = lexer->x - 1;

		do {
			lexer->x++;
		} while (is_in_bounds(lexer) && *lexer->x != '\n');

		token->length = lexer->x - token->source;
		return true;
	}

	if (*lexer->x == '*') {
		token->kind = TOKEN_COMMENT_BLOCK;
		token->source = lexer->x - 1;

		size_t level = 1;
		bool previous_star = false;
		bool previous_slash = false;
		
		do {
			lexer->x++;
			if (!is_in_bounds(lexer)) {
				break;
			}

			if (*lexer->x == '*') {
				if (previous_slash) {
					level++;
				} else {
					previous_star = true;
				}
				previous_slash = !previous_slash;
			}
			
			if (*lexer->x == '/') {
				if (previous_star) {
					level--;
				} else {
					previous_slash = true;
				}
				previous_star = !previous_star;
			}
		} while (level >= 1);

		lexer->x++;
		token->length = lexer->x - token->source;
		return true;
	}

	return false;
}

static bool try_literal_string(Lexer *lexer, Token *token) {
	if (*lexer->x != '"') {
		return false;
	}

	token->kind = TOKEN_LITERAL_STRING;
	token->source = lexer->x;
	
	bool scaped = false;
	
	do {
		lexer->x++;

		if (*lexer->x == '"') {
			if (!scaped) {
				break;
			}
			scaped = !scaped;
		}

		if (*lexer->x == '\\') {
			scaped = !scaped;
		}
	} while (*lexer->x != '\n');

	lexer->x++;
	token->length = lexer->x - token->source;
	return true;
}

Lexer lexer_from_file(File *file) {
	return (Lexer){
		.begin = file->content,
		.end = file->content + file->length,
		.x = file->content,
	};
}

Token next_token(Lexer *lexer) {
	skip_whitespace(lexer);

	if (!is_in_bounds(lexer)) {
		return (Token){
			.kind = TOKEN_END_OF_FILE,
		};
	}

	Token token = {
		.kind = TOKEN_NONE,
	};

	if (try_comment(lexer, &token)) {
		return token;
	}

	if (try_literal_string(lexer, &token)) {
		return token;
	}
	
	if (try_identifier(lexer, &token)) {
		return token;
	}

	lexer->x++;
	return token;
}
