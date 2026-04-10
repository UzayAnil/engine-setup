#pragma once

const char* read_file(const char* path);

// for tinyobj obj parsing
void obj_file_read_callback(void* ctx, const char* filename, int is_mtl, const char* obj_filename, char** buf, size_t* len);

// for spv binary
typedef struct 
{
    void* ptr;
    size_t size;
} FileBlob;
FileBlob read_file_binary(const char* filename);