#include <stdlib.h> // system(), strtol()
#include <stdio.h> // printf()
#include <string.h> // strcmp()
#include <assert.h> // assert()

int main(int argc, char* argv[]) {
    // Parse arguments
    // First arg must be command to run; the rest are flags
    if (argc < 2) {
        printf("usage: repeater {command} flags...[-d delay]\n");
        printf("flags:\n");
        printf("  -d, --delay n  Set delay between runs (ms), default 10\n");
        printf("  -m, --max n    Set maximum number of runs, default 1000\n");

        return 1;
    }

    char* command = argv[1];
    int delay = 10;
    int maximum = 1000;

    // Go through, parsing for flags
    for (int i = 2; i < argc; i++) {
        if (!strcmp(argv[i], "-d") || !strcmp(argv[i], "--delay"))
            delay = strtol(argv[i + 1], NULL, 10);
        else if (!strcmp(argv[i], "-m") || !strcmp(argv[i], "--max"))
            maximum = strtol(argv[i + 1], NULL, 10);
    }

    printf("args: %d, delay: %d, max: %d, cmd: %s\n", argc, delay, maximum, command);

    return 0;
}
