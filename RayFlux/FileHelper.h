//FIXME printf !!
#pragma once

#include <stdio.h>
#include <string.h>
#include <errno.h>

// Platform-specific headers and macros
#if defined(_WIN32) || defined(_WIN64)
    #include <direct.h>
    #include <io.h>
    #define MKDIR(path) _mkdir(path)
    #define PATH_SEP '/'
    #define ALT_PATH_SEP '\\'
#else
    #include <sys/stat.h>
    #include <sys/types.h>
    #define MKDIR(path) mkdir(path, 0755)
    #define PATH_SEP '/'
    #define ALT_PATH_SEP '/' // No alternative on POSIX
#endif

namespace RayFlux::FileHelper {

// Helper function to check if a character is a path separator
int IsSeparator(char c) {
    return (c == PATH_SEP || c == ALT_PATH_SEP);
}

// Function to create a directory tree recursively
void createDirRecursive(const char *dir_path) {
    char temp_path[512];
    snprintf(temp_path, sizeof(temp_path), "%s", dir_path);
    size_t len = strlen(temp_path);

    // Skip Windows drive letters (e.g., "C:")
    size_t start_idx = 1;
    if (len > 2 && temp_path[1] == ':') {
        start_idx = 3;
    }

    // Iterate through the path string
    for (size_t i = start_idx; i < len; i++) {
        if (IsSeparator(temp_path[i])) {
            char old_char = temp_path[i];

            // Temporarily terminate the string
            temp_path[i] = '\0';

            // Create the directory and ignore "already exists" error
            if (MKDIR(temp_path) != 0 && errno != EEXIST) {
                // Double check if it exists (fixes some edge cases on Windows)
                #if defined(_WIN32) || defined(_WIN64)
                if (_access(temp_path, 0) != 0) {
                    perror("Failed to create directory");
                    return;
                }
                #else
                perror("Failed to create directory");
                return;
                #endif
            }

            // Restore the separator
            temp_path[i] = old_char;
        }
    }
}

bool createDirFromFileIfNotExits(const char* fileName) {

    char dir_path[512];

    strncpy(dir_path, fileName, sizeof(dir_path) - 1);
    dir_path[sizeof(dir_path) - 1] = '\0';

    // Find the last separator to isolate the directory part
    char *last_sep = NULL;
    for (int i = (int)strlen(dir_path) - 1; i >= 0; i--) {
        if (IsSeparator(dir_path[i])) {
            last_sep = &dir_path[i];
            break;
        }
    }

    if (last_sep != NULL) {
        // Keep the trailing separator for the recursive loop
        *(last_sep + 1) = '\0';

        printf("Creating directory: %s\n", dir_path);
        createDirRecursive(dir_path);
    } else {
        printf("Invalid path or no directory component found.\n");
        return false;
    }

    return true;
}

}
