#include "core_cli.h"

cli_t g_cli;

cmd_t g_cmd_list[] = 
{
	{"help",cmd_help},
	{"version", cmd_version},
};


int cli_init(int (*io_get)(char*), int (*io_put)(char))
{
	if(io_get != NULL && io_put != NULL)
	{
		g_cli.io_get = io_get;
		g_cli.io_put = io_put;
		g_cli.num = 0;
		ring_buffer_init(&g_cli.cmd_buf);
		return 0;
	}
	else
	{
		return -1;
	}
}

void cli_print(const char *fmt, ...)
{
	va_list list;
	int i = 0;;
	char buf[128] = {0};
	va_start(list, fmt);
	vsnprintf(buf,sizeof(buf), fmt, list);
	va_end(list);
	for(i = 0; buf[i]; i++)
	{
		g_cli.io_put(buf[i]);
	}
}

static void cli_find_and_exec_cmd(char *buf)
{
	int argc = 0;
	char* argv[10] = {0};
	int cmd_list_len = sizeof(g_cmd_list)/sizeof(cmd_t);
	int i = 0;
	char *cmd = buf;
	argv[argc] = strtok(cmd, " ");
	for(i = 0; i < cmd_list_len; i++)
	{
		int cmd_len = strlen(g_cmd_list[i].cmd);
		if(0 == strncmp(g_cmd_list[i].cmd, argv[argc], cmd_len))
		{
			while(argv[argc] != NULL)
			{
				argc++;
				if(argc >= 10)
				{
					CLI_PRINT_LINE("this command is too long.");
					return;
				}
				argv[argc] = strtok(NULL, " ");
			}
			g_cmd_list[i].exec(argc, argv);
			return;
		}
	}
	CLI_PRINT_LINE("this command can't found.");
}

static void cli_parser(char c)
{
	char buf[RING_BUFFER_MAX_SIZE] = {0};
	int i = 0;
	if(c >= 0x20 && c <= 0x7e)
	{
		ring_buffer_write(c, &g_cli.cmd_buf);
		g_cli.num++;
	}
	else
	{
		for(i = 0 ; i < g_cli.num; i++)
		{
			ring_buffer_read(&buf[i], &g_cli.cmd_buf);
		}
		g_cli.num = 0;
		cli_find_and_exec_cmd(buf);
	}
}

void cli_task(void)
{
	char c;
	if(g_cli.io_get(&c))
	{
		cli_parser(c);
	}
}