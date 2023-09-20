#ifndef CORE_CLI_H
#define CORE_CLI_H

#include <stdio.h>
#include <stdarg.h>
#include "ring_buffer.h"
#include "cli_cmd.h"

typedef struct __cli
{
	ring_buffer_t cmd_buf;
	int num;
	int (*io_get)(char*);
	int (*io_put)(char);
}cli_t;

typedef void (*cmd_exec)(int argc, char **argv);
typedef struct __cmd
{
	char *cmd;
	cmd_exec exec;
}cmd_t;

extern cmd_t g_cmd_list[];

int cli_init(int (*io_get)(char*), int (*io_put)(char));
void cli_print(const char *fmt, ...);
void cli_task(void);

#define CLI_PRINT_LINE(...)	do{ \
								cli_print(__VA_ARGS__); \
								cli_print("\r\n"); \
							}while(0)

#endif