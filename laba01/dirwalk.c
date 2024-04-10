#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <getopt.h>
#include <locale.h>
#include <stdbool.h>
#include <limits.h>

struct options
{
    bool show_files;
    bool show_dirs;
    bool show_links;
    bool sort;
};

static struct option long_options[] =
        {
                {"show-links", no_argument, 0, 'l'},
                {"show-dirs", no_argument, 0, 'd'},
                {"show-files", no_argument, 0, 'f'},
                {"sort", no_argument, 0, 's'},
                {0, 0, 0, 0}
        };

int compare(const struct dirent **a, const struct dirent **b)
{
    return strcoll((*a)->d_name, (*b)->d_name);
}

void scanDirectory(const char *dirPath, int tab, struct options opts)
{
    struct dirent **namelist;
    int numEntries;

    if (opts.sort == true)
    {
        numEntries = scandir(dirPath, &namelist, NULL, compare);
    }
    else
    {
        numEntries = scandir(dirPath, &namelist, NULL, NULL);
    }

    if (numEntries == -1)
    {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numEntries; i++)
    {
        struct dirent *entry = namelist[i];

        if (entry->d_type == DT_DIR)
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            {
                continue;
            }

            if (opts.show_dirs == true)
            {
                for (int j = 0; j < tab; ++j)
                {
                    printf(" ");
                }
                printf("DIR: %s\n", entry->d_name);
            }

            char sub_dir_path[PATH_MAX];

            // snprintf(sub_dir_path, PATH_MAX, "%s/%s", dirPath, entry->d_name);

            strcpy(sub_dir_path, dirPath);
            strcat(sub_dir_path, "/");
            strcat(sub_dir_path, entry->d_name);

            scanDirectory(sub_dir_path, tab + 2, opts);
        }
        else if (entry->d_type == DT_REG && opts.show_files == true)
        {
            for (int j = 0; j < tab; ++j)
            {
                printf(" ");
            }
            printf("FILE: %s\n", entry->d_name);
        }
        else if (entry->d_type == DT_LNK && opts.show_links == true)
        {
            for (int j = 0; j < tab; ++j)
            {
                printf(" ");
            }
            printf("LINK: %s\n", entry->d_name);
        }
        free(entry);
    }
    free(namelist);
}

int main(int argc, char *argv[])
{
    printf("\n\n\n");

    int option_index = 1;
    int opt;
    struct options opts = {0, 0, 0, 0};

    char *dirPath = "./";

    setlocale(LC_COLLATE, "");

    while ((opt = getopt_long(argc, argv, "ldfs", long_options, &option_index)) != -1)
    {
        switch (opt) {
            case 'l':
                opts.show_links = true;
                break;
            case 'd':
                opts.show_dirs = true;
                break;
            case 'f':
                opts.show_files = true;
                break;
            case 's':
                opts.sort = true;
                break;
            default:
                fprintf(stderr, "Usage: %s [dir] [options: -f -l -d -s]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (opts.show_files == false && opts.show_dirs == false && opts.show_links == false && opts.sort == false)
    {
        opts.show_files = true;
        opts.show_dirs = true;
        opts.show_links = true;
        opts.sort = true;
    }

    if (optind < argc)
    {
        dirPath = argv[optind];
    }

    printf("\n");

    for (int i = 0; i < argc; ++i)
    {
        printf("Argv[%d] = %s \n", i, argv[i]);
    }

    printf("\n");

    printf("show_files = %d \n", opts.show_files);
    printf("show_dirs = %d \n", opts.show_dirs);
    printf("show_links = %d \n", opts.show_links);
    printf("sort = %d \n", opts.sort);

    printf("\n");

    printf("Directoria: %s\n", dirPath);

    printf("\n");

    scanDirectory(dirPath, 0, opts);

    printf("\n\n\n");

    return 0;
}