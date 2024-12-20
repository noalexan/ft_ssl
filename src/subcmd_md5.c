#include <fcntl.h>
#include <file.h>
#include <libft.h>
#include <md5.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int run_md5(const char **argv)
{
	bool arg_quiet = false, arg_reverse = false, arg_stdin = false;
	t_list *strings = NULL, *tmp;
	const char **iterator = argv + 1;
	uint8_t digest[MD5_DIGEST_STRING_LENGTH];
	file *f;

	digest[MD5_DIGEST_STRING_LENGTH - 1] = 0;

	// placeholder
	for (int i = 0; i < MD5_DIGEST_STRING_LENGTH - 1; i++)
		digest[i] = '-';

	// Parse given arguments
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
				tmp = ft_lstnew((char *)*iterator);
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

	// If no arguments were given, read from stdin
	if (*iterator == NULL && strings == NULL && arg_stdin == false) {
		f = load_file(0);
		md5((uint8_t *)f->content, f->length, digest);
		if (arg_quiet)
			printf("%s\n", digest);
		else if (arg_reverse)
			printf("%s *stdin\n", digest);
		else
			printf("MD5(stdin)= %s\n", digest);
		free(f->content);
		free(f);
	}

	else {
		// If '-p' were given, read from stdin
		if (arg_stdin) {
			f = load_file(0);
			md5((uint8_t *)f->content, f->length, digest);
			printf("MD5(\"%s\")= %s\n", f->content, digest);
			free(f->content);
			free(f);
		}

		// Iterate on all '-s' arguments
		for (t_list *it = strings; it; it = it->next) {
			md5((uint8_t *)it->content, ft_strlen(it->content), digest);
			printf("MD5(\"%s\")= %s\n", (char *)it->content, digest);
		}

		// Finally, iterate on all given files
		for (; *iterator; iterator++) {
			int fd = open(*iterator, O_RDONLY);

			if (fd < 0) {
				perror(*iterator);
				continue;
			}

			f = load_file(fd);
			md5((uint8_t *)f->content, f->length, digest);
			printf("MD5(%s)= %s\n", *iterator, digest);
			free(f->content);
			free(f);
			close(fd);
		}

		ft_lstclear(&strings, NULL);
	}

	return 0;
}
