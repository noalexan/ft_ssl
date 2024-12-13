#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <subcommand.h>

int subcmd_exec(t_subcommand *subcmd_list, char ** const argv)
{
	while (subcmd_list) {
		if (strcmp(argv[1], subcmd_list->name) == 0)
			return subcmd_list->func(argv);
		subcmd_list = subcmd_list->next;
	}

	fprintf(stderr, "%s: Error: '%s' is an invalid command.\n", argv[0], argv[1]);
	return 1;
}

void subcmd_clear(t_subcommand *subcmd_list)
{
	t_subcommand *tmp;

	while (subcmd_list) {
		tmp = subcmd_list;
		free(tmp->name);
		free(tmp);
		subcmd_list = subcmd_list->next;
	}
}

void subcmd_register(t_subcommand **subcmd_list, const char *name, int (*func)(char ** const))
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
