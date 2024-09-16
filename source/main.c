#include <stdio.h>

#include "file.h"
#include "lexer.h"
#include "lin.h"
#include "string.h"

int main(int argc, char *argv[]) {
	if (argc <= 1) {
		fprintf(stderr, "Input file is not provided.\n");
		return 1;
	}

	if (!is_source_file(argv[1])) {
		fprintf(stderr, "Input file is not a valid lin source file.\n");
		return 1;
	}
	
	File input_file = {
		.path = argv[1],
	};
	if (!read_file(&input_file)) {
		return 1;
	}

	Lexer lexer = lexer_from_file(&input_file);
	
	Token token = {0};
	for (int i = 0; i < 100 && token.kind != TOKEN_END_OF_FILE; i++) {
		token = next_token(&lexer);

		printf("#%d --- %s --- %.*s\n", i, describe_token_kind(token.kind), (int)token.length, token.source);
	}

	return 0;
}
