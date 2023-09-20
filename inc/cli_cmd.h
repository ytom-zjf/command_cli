#ifndef CLI_CMD_H
#define CLI_CMD_H

#include "core_cli.h"

void init_command();
void cmd_help(int argc, char **argv);
void cmd_version(int argc, char **argv);

#endif