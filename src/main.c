#include <fcntl.h>
#include <file.h>
#include <libft.h>
#include <md5.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <subcommand.h>
#include <unistd.h>

int run_md5(const char **argv);
int run_sha256(const char **argv);

int help()
{
	fprintf(stderr,
			"Commands:\n"
			"md5\n"
			"sha256\n"
			"Flags:\n"
			"-p -q -r -s\n");
	return 0;
}

int main(int argc, char **argv)
{
	t_subcommand *subcmd_list = NULL;
	int ret_value;

	if (argc < 2) {
		fprintf(stderr, "usage: %s command [flags] [file/string]\n", argv[0]);
		help();
		exit(EXIT_FAILURE);
	}

	subcmd_register(&subcmd_list, "help", help);
	subcmd_register(&subcmd_list, "md5", run_md5);
	subcmd_register(&subcmd_list, "sha256", run_sha256);

	ret_value = subcmd_exec(subcmd_list, (const char **)argv + 1);
	subcmd_clear(subcmd_list);

	return ret_value;
}
