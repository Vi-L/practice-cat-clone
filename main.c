#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    bool showEnds = false;
    bool numberAll = false;
    int lineNumber = 0;
    int totalLines = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-E") == 0) {
                showEnds = true;
                continue;
            }
            if (strcmp(argv[i], "-n") == 0) {
                numberAll = true;
                continue;
            }
        }

        FILE* file = fopen(argv[i], "r");
        if (!file) {
            printf("%s: No such file or directory", argv[1]);
        }
        char string[1000];
        while (fgets(string, 1000, file)) {
            totalLines++;
        }
        rewind(file);
        while (fgets(string, 1000, file)) {
            lineNumber++;
            int stringLength = strlen(string);
            if (string[stringLength-1] == '\n') string[stringLength-1] = '\0';

            char line[32];
            char lineNumberStr[16];
            char totalLinesStr[16];
            sprintf(lineNumberStr, "%d", lineNumber);
            sprintf(totalLinesStr, "%d", totalLines);
            sprintf(line, "%*s%s", (int)(strlen(totalLinesStr) - strlen(lineNumberStr)), "", lineNumberStr);
            printf("%s %s%s\n", numberAll ? line : "", string, showEnds ? "$" : "");
        }
        if (i+1 < argc) printf("\n");
        fclose(file);
    }
    
    return 0;
}