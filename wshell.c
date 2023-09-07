/*-------------------------------------------------------------------------
 *
 * wshell.c
 *	  wshell
 *
 * Portions Copyright (c) 2023, yuesong-feng 冯岳松
 *
 *
 * IDENTIFICATION
 *	  wshell.c
 *
 *
 * NOTES
 *	  Shell
 *
 *-------------------------------------------------------------------------
 */
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>


static void ls_main();

static void ls_main() { return; }

int main(int argc, char const *argv[]) {
  char cmd[LINE_MAX] = {0};
  fputs("% ", stdout);
  while (fgets(cmd, sizeof(cmd), stdin) != NULL) {
    assert(cmd[strlen(cmd) - 1] == '\n');
    cmd[strlen(cmd) - 1] = '\0';
    if (strcmp(cmd, "ls") == 0) {
      ls_main();
    }
    fputs("% ", stdout);
  }

  return 0;
}
