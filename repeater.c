#include <stdlib.h> // system(), strtol(), exit()
#include <stdio.h> // printf()
#include <string.h> // strcmp()
#include <unistd.h> // usleep()

void print_help() {
    printf("\n");
    printf("Usage: repeater {command} [-h] [-d delay] [-m max] [-c code]\n");
    printf("Flags:\n");
    printf("  -h, --help     View this help\n");
    printf("  -d, --delay n  Set delay between runs (ms), default 10\n");
    printf("  -m, --max n    Set maximum number of runs, default 1000\n");
    printf("  -c, --code n   Set needed code to continue, default 0\n");
    printf("\n");

    exit(1);
}

int main(int argc, char* argv[]) {
    // Parse arguments
    // First arg must be command to run; the rest are flags
    if (argc < 2)
        print_help();

    char* command = argv[1];
    int delay = 10;
    int maximum = 1000;
    int retcode = 0;

    // Go through, parsing for flags
    for (int i = 2; i < argc; i++) {
        if (!strcmp(argv[i], "-d") || !strcmp(argv[i], "--delay"))
            delay = strtol(argv[i + 1], NULL, 10);
        else if (!strcmp(argv[i], "-m") || !strcmp(argv[i], "--max"))
            maximum = strtol(argv[i + 1], NULL, 10);
        else if (!strcmp(argv[i], "-c") || !strcmp(argv[i], "--code"))
            retcode = strtol(argv[i + 1], NULL, 10);
        else if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
            print_help();
    }

    // Go!
    for (int j = 0; j < maximum; j++) {
        int code = system(command);

// On some systems, system(3) and wait(2) will give an odd return value that
// is x256 and some bytes different than the real return value. Fix this.
#ifdef WEXITSTATUS
        code = WEXITSTATUS(code);
#endif

        if (code != retcode) {
            printf("! failed to get code %d, instead got %d\n", retcode, code);
            exit(2);
        }

        usleep(delay * 1000);
    }

    exit(0);
}
