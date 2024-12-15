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

int run_md5(const char **argv)
{
	bool arg_quiet = false, arg_reverse = false, arg_stdin = false;
	t_list *strings = NULL, *tmp;
	const char **iterator = argv + 1;

	for (; *iterator && **iterator == '-'; iterator++) {
		for (const char *arg = *iterator + 1; *arg; arg++) {
			switch (*arg) {
			case 'q':
				arg_quiet = true;
				break;

			case 'r':
				arg_reverse = true;
				break;

			case 'p':
				arg_stdin = true;
				break;

			case 's':
				if (*(arg + 1) || *(++iterator) == NULL) {
					fprintf(stderr, "md5: option 's' requires an argument.\n");
					return 1;
				}
				tmp = ft_lstnew(*iterator);
				if (tmp == NULL) {
					perror("malloc");
					ft_lstclear(&strings, NULL);
					return 1;
				}
				ft_lstadd_back(&strings, tmp);
				break;

			default:
				fprintf(stderr, "md5: Unknown option or message digest: %c\n", *arg);
				return 1;
			}
		}
	}

	if (*iterator == NULL && strings == NULL) {
		puts("from stdin");
		file *f = load_file(0);
		puts(f->content);
		free(f->content);
		free(f);
	}

	for (; *iterator; iterator++) {
		int fd = open(*iterator, O_RDONLY);

		if (fd < 0) {
			perror(*iterator);
		}

		else {
			file *f = load_file(fd);
			write(1, f->content, f->length);
			free(f->content);
			free(f);
			close(fd);
		}
	}

	return 0;
}

int run_sha256(const char **argv)
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

	ret_value = subcmd_exec(subcmd_list, (const char **)argv + 1);
	subcmd_clear(subcmd_list);

	return ret_value;
}
