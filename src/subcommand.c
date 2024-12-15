#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <subcommand.h>

int subcmd_exec(t_subcommand *subcmd_list, const char **argv)
{
	for (; subcmd_list; subcmd_list = subcmd_list->next)
		if (strcmp(argv[0], subcmd_list->name) == 0)
			return subcmd_list->func(argv);

	fprintf(stderr, "%s: Error: '%s' is an invalid command.\n", argv[0], argv[1]);
	return 1;
}

void subcmd_clear(t_subcommand *subcmd_list)
{
	t_subcommand *tmp;

	for (; subcmd_list; subcmd_list = subcmd_list->next) {
		tmp = subcmd_list;
		free(tmp->name);
		free(tmp);
	}
}

void subcmd_register(t_subcommand **subcmd_list, const char *name, int (*func)(const char **))
{
	t_subcommand *new;

	if ((new = malloc(sizeof(t_subcommand))) == NULL) {
		perror("malloc");
		return;
	}

	new->name = strdup(name);
	new->func = func;
	new->next = *subcmd_list;
	*subcmd_list = new;
}
