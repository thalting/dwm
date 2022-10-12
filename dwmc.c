/* See LICENSE file for copyright and license details. */
/* `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "util.c"

void
usage(void)
{
    die("dwmc <signame> [<type> <value>]\n");
}

void
fsignal(char *signame, char *type, char *value)
{
    char command[256] = "";
    sprintf(command, "xsetroot -name \"fsignal:%s %s %s\"", signame, type, value);
    execl("/bin/sh", "sh", "-c", command, (char *)NULL);
}

int
main(int argc, char *argv[])
{
    switch (argc) {
    case 2:
        if (!strcmp(argv[1], "setlayout") || !strcmp(argv[1], "view") ||
            !strcmp(argv[1], "viewall") || !strcmp(argv[1], "togglebar") ||
            !strcmp(argv[1], "togglefloating") || !strcmp(argv[1], "zoom") ||
            !strcmp(argv[1], "killclient") || !strcmp(argv[1], "toggleview") ||
            !strcmp(argv[1], "quit"))
            fsignal(argv[1], "", "");
        else
            usage();
        break;
    case 3:
        if (!strcmp(argv[1], "view"))
            fsignal(argv[1], "ui", argv[2]);
        if (!strcmp(argv[1], "setmfact"))
            fsignal(argv[1], "f", argv[2]);
        if (!strcmp(argv[1], "viewex") || !strcmp(argv[1], "toggleviewex") ||
            !strcmp(argv[1], "tagex") || !strcmp(argv[1], "toggletagex") ||
            !strcmp(argv[1], "setlayoutex") || !strcmp(argv[1], "focusstack") ||
            !strcmp(argv[1], "incnmaster") || !strcmp(argv[1], "focusmon") ||
            !strcmp(argv[1], "tagmon"))
            fsignal(argv[1], "i", argv[2]);
        break;
    default:
        usage();
        break;
    }
    return EXIT_SUCCESS;
}
