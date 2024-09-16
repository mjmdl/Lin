#ifndef LIN__FILE_H
#define LIN__FILE_H

#include "lin.h"

#define FILE_FMT(FILE) (int)(FILE).length, (FILE).content

typedef struct File {
	const char *path;
	char *content;
	size_t length;
} File;

bool read_file(File *file);
void free_file(File *file);

#endif // LIN__FILE_H
