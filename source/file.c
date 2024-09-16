#include <stdio.h>
#include <stdlib.h>

#include "file.h"

bool read_file(File *file) {
	FILE *handle = fopen(file->path, "rb");
	if (!handle) {
		fprintf(stderr, "Could not open file %s.\n", file->path);
		return false;
	}

	long length = -1;
	if (fseek(handle, 0, SEEK_END) < 0 || (length = ftell(handle)) < 0 || fseek(handle, 0, SEEK_SET) < 0) {
		fprintf(stderr, "Could not count length of file %s.\n", file->path);
		fclose(handle);
		return false;
	}

	char *buffer = (char *)malloc(sizeof(char) * length);
	if (!buffer) {
		fprintf(stderr, "Could not allocate %ld bytes for file %s.\n", length, file->path);
		fclose(handle);
		return false;
	}

	size_t bytes_read = fread(buffer, sizeof(char), length, handle);
	fclose(handle);
	if (bytes_read != length) {
		fprintf(stderr, "Could not read contents of file %s: Read %zu out of %zu bytes.\n", file->path, bytes_read, length);
		free(buffer);
		return false;
	}

	file->content = buffer;
	file->length = bytes_read;
	return true;
}

void free_file(File *file) {
	free(file->content);
	file->content = NULL;
	file->length = 0;
}
