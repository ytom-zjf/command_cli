#include "./inc/core_cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli_cmd.h"

int main(int argc, char **argv)
{
	init_command();
	while (1)
	{
		cli_task();
	}
	return 0;
}