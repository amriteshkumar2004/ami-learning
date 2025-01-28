#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void printdir(char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    // Open the directory
    if ((dp = opendir(dir)) == NULL) {
        fprintf(stderr, "cannot open directory: %s\n", dir);
        return;
    }

    // Change to the directory to process its contents
    chdir(dir);

    // Loop through the directory entries
    while ((entry = readdir(dp)) != NULL) {
        // Get the file status
        lstat(entry->d_name, &statbuf);

        // If it's a directory, and not . or .., print it and recurse
        if (S_ISDIR(statbuf.st_mode)) {
            if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
                continue;

            // Print directory name with indentation based on depth
            printf("%*s%s/\n", depth, "", entry->d_name);

            // Recursively print the subdirectory contents
            printdir(entry->d_name, depth + 4);
        }
        else {
            // Print regular file name with indentation
            printf("%*s%s\n", depth, "", entry->d_name);
        }
    }

    // Change back to the parent directory
    chdir("..");

    // Close the directory
    closedir(dp);
}

int main()
{
    printf("Directory scan of /home:\n");

    // Start the directory scan with /home and depth 0
    printdir("/home", 0);

    printf("done.\n");

    exit(0);
}

