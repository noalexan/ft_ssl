#include <md5.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <subcommand.h>

int run_md5(char **const argv)
{
	md5(argv[1], strlen(argv[1]));
	return 0;
}

int run_sha256(char **const argv)
{
	puts("Here is sha256!");
	return 0;
}

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

	ret_value = subcmd_exec(subcmd_list, argv + 1);
	subcmd_clear(subcmd_list);

	return ret_value;
}
