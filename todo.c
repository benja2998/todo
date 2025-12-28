#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

//Clears the terminal or console screen.
void clear_console(void) {
    printf("\e[1;1H\e[2J");
}

//Entry point for program.
int main(void) {
    int exists;
    int status;

    struct stat buf;
    exists = stat("db", &buf);
    if (exists == -1) {
        status = mkdir("db", 0755);
        if (status == -1) {
            perror("mkdir error");
        }
    }

    while (1) {
        clear_console();
        printf(
                "options\n"
                "-------\n"
                "1) new todo\n"
                "2) list todos\n"
                "3) remove todo\n"
                "4) exit\n"
                "\n"
                "enter option and press enter: "
              );

        char opt[4];
        if (fgets(opt, 4, stdin) == NULL) {
            return EXIT_FAILURE;
        }

        switch (atoi(opt)) {
            case 1:
                printf("\nenter todo name and press enter: ");
                char filename[4096];
                if (fgets(filename, 4096, stdin) == NULL) {
                    return EXIT_FAILURE;
                }
                filename[strcspn(filename, "\n")] = 0;
                char filepath[4100];
                snprintf(filepath, 4100, "db/%s", filename);
                FILE *file = fopen(filepath, "w");
                if (file == NULL) {
                    //Oh no!
                    perror("Error creating file");
                    return EXIT_FAILURE;
                }
                fclose(file);
                break;
            case 2:
                status = system("ls -lt --color db/");
                printf("press enter to continue\n");
                getchar();
                break;
            case 3:
                printf("\nenter todo name and press enter: ");
                char filename_2[4096];
                if (fgets(filename_2, 4096, stdin) == NULL) {
                    return EXIT_FAILURE;
                }
                filename_2[strcspn(filename_2, "\n")] = 0;
                char filepath_2[4100];
                snprintf(filepath_2, 4100, "db/%s", filename_2);
                if (remove(filepath_2) == 0) {
                    printf("deleted %s\n", filename_2);
                }
                else {
                    printf("unable to delete %s\n", filename_2);
                }
                break;
            case 4:
                clear_console();
                exit(EXIT_SUCCESS);
                break;
            default:
                fprintf(stderr, "Invalid option\n");
        }
    }

    return EXIT_SUCCESS;
}
