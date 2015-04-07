#include <stdlib.h> // system(), strtol()
#include <stdio.h> // printf()
#include <string.h> // strcmp()
#include <unistd.h> // usleep()

void print_help() {
    printf("usage: repeater {command} flags...[-d delay]\n");
    printf("flags:\n");
    printf("  -d, --delay n  Set delay between runs (ms), default 10\n");
    printf("  -m, --max n    Set maximum number of runs, default 1000\n");
    printf("  -c, --code n   Set needed code to continue, default 0\n");
}

int main(int argc, char* argv[]) {
    // Parse arguments
    // First arg must be command to run; the rest are flags
    if (argc < 2) {
        print_help();

        return 1;
    }

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
    }

    // Go!
    for (int j = 0; j < maximum; j++) {
        int code = system(command);
        if (code != retcode) {
            printf("! failed to get code %d, instead got %d\n", retcode, code);
            return 2;
        }

        usleep(delay * 1000);
    }

    return 0;
}
