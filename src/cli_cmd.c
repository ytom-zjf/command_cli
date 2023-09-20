#include "cli_cmd.h"

void cmd_help(int argc, char **argv)
{
	int i = 0;

	if(argc > 1)
	{
		CLI_PRINT_LINE("command error, use command \"help\"");
		return;
	}

	CLI_PRINT_LINE("available commands:");
	for(i = 0; g_cmd_list[i].cmd != NULL; i++)
	{
		CLI_PRINT_LINE("- %s", g_cmd_list[i].cmd);
	}
}

void cmd_version(int argc, char **argv)
{
	CLI_PRINT_LINE("version 0.0.1");
}

static int cmd_get_char(char *c)
{
    *c = getchar();
    return 1;
}

static int cmd_put_char(char c)
{
    putchar(c);
    return 1;
}

void init_command()
{
	cli_init(cmd_get_char, cmd_put_char);
}


