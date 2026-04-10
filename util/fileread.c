#include <stdio.h>
#include <stdlib.h>
#include "include/fileread.h"

const char* read_file(const char* filename) 
{
    FILE* file_ptr;
    char* buffer;
    long file_size;
    size_t bytes_read;

    file_ptr = fopen(filename, "rb");
    if (file_ptr == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file_ptr, 0L, SEEK_END);
    file_size = ftell(file_ptr);
    if (file_size == -1) {
        perror("Error getting file size");
        fclose(file_ptr);
        return NULL;
    }

    rewind(file_ptr); // or fseek(file_ptr, 0L, SEEK_SET);

    buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        perror("Error allocating memory");
        fclose(file_ptr);
        return NULL;
    }

    bytes_read = fread(buffer, 1, file_size, file_ptr);
    if (bytes_read != file_size) {
        perror("Error reading file content");
        free(buffer);
        fclose(file_ptr);
        return NULL;
    }

    buffer[file_size] = '\0';

    fclose(file_ptr);
    return buffer;
}

// for tinyobj obj loading
void obj_file_read_callback(void* ctx, const char* filename, int is_mtl, const char* obj_filename, char** buf, size_t* len) 
{
    FILE* f = fopen(filename, "rb");
    if (!f) {
        *buf = NULL;
        *len = 0;
        return;
    }

    fseek(f, 0, SEEK_END);
    size_t size = (size_t)ftell(f);
    rewind(f);

    char* data = (char*)malloc(size + 1);
    if (!data) {
        fclose(f);
        *buf = NULL;
        *len = 0;
        return;
    }

    size_t bytes_read = fread(data, 1, size, f);
    data[size] = '\0';
    fclose(f);

    *buf = data;
    *len = size;
}

// for spv binary
FileBlob read_file_binary(const char* filename) 
{
    FILE* f = fopen(filename, "rb");
    if (!f) {
        perror("Error opening binary file");
        return (FileBlob){0};
    }

    fseek(f, 0, SEEK_END);
    size_t size = (size_t)ftell(f);
    rewind(f);

    void* buffer = malloc(size);
    if (!buffer) {
        perror("Error allocating binary buffer");
        fclose(f);
        return (FileBlob){0};
    }

    size_t bytes_read = fread(buffer, 1, size, f);
    fclose(f);

    if (bytes_read != size) {
        perror("Error reading binary content");
        free(buffer);
        return (FileBlob){0};
    }

    return (FileBlob){ .ptr = buffer, .size = size };
}