#include <stdio.h>
#include <stdlib.h>
#include <subcommand.h>
#include <md5.h>

int run_md5(char ** const argv)
{
	printf("Here is md5!\n");
	return 0;
}

int run_sha256(char ** const argv)
{
	printf("Here is sha256!\n");
	return 0;
}

int main(int argc, char **argv)
{
	t_subcommand *subcmd_list = NULL;
	int ret_value;

	if (argc < 2) {
		fprintf(stderr, "usage: %s command [flags] [file/string]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	subcmd_register(&subcmd_list, "md5", run_md5);
	subcmd_register(&subcmd_list, "sha256", run_sha256);

	ret_value = subcmd_exec(subcmd_list, argv);
	subcmd_clear(subcmd_list);

	return ret_value;
}
