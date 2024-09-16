#ifndef LIN__STRING_H
#define LIN__STRING_H

#include "lin.h"

const char *extension_of_file(const char *file_path);
bool are_strings_equal(const char *first, const char *second, size_t length);
bool is_source_file(const char *file_path);
bool is_whitespace(char khar);
bool is_identifier_initial(char khar);
bool is_identifier(char khar);

#endif // LIN__STRING_H
