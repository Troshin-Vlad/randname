#include "const.h"

void version( void );
void help( void );

// version: print version program and last changes in programs
void version(){
    printf("Version program randname(generation name): %0.2f\n",VERSION);
    printf(" [%s+%s] Change parser option(getopt_long)\n",GREEN,DEFAULT);
    printf(" [%s+%s] Rename verialable and function\n",GREEN,DEFAULT);
    exit(1);
}

// help: print help page on use option program
void help(){
    printf("Usage: randname [-w|-m] [options]:\n");
    printf("  --women, -w:      generate female names\n");
    printf("  --male, -m:       generate male names\n");
    printf("  --count, -c:      specify the number of generated names\n");
    printf("  --separate, -s:   specify the separating symbol\n");
    printf("  --num-style, -i:  line numbering (numeric style 1,2,3)\n");
    printf("  --all-names, -a:  print all names\n");
    printf("  --line, -l:       separate lines\n");
    printf("  --rare, -r:       on rare names\n");
    printf("  --eng, -e:        generation english names\n");
    printf("  --help, -h:       print this help\n");
    printf("  --version, -v:    print version program\n");
    exit(1);
}
