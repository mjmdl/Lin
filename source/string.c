#include "string.h"

const char *extension_of_file(const char *file_path) {
	const char *ext = NULL;
	while (*file_path != '\0') {
		if (*file_path == '.') {
			ext = file_path + 1;
		}
		file_path++;
	}
	return ext;
}

bool are_strings_equal(const char *first, const char *second, size_t length) {
	for (size_t i = 0; i < length; i++) {
		if (*first != *second) {
			return false;
		}
		if (*first == '\0') {
			return true;
		}
		first++;
		second++;
	}
	return true;
}

bool is_source_file(const char *file_path) {
	const char *ext = extension_of_file(file_path);
	if (!ext) {
		return false;
	}
	return are_strings_equal(ext, "lin", 3);
}

bool is_whitespace(char khar) {
	return khar == ' ' || khar == '\t' || khar == '\n' || khar == '\0';
}

bool is_identifier_initial(char khar) {
	return khar == '_' || ('a' <= khar && khar <= 'z') || ('A' <= khar && khar <= 'Z');
}

bool is_identifier(char khar) {
	return is_identifier_initial(khar) || ('0' <= khar && khar <= '9');
}
