#pragma once

typedef struct s_subcommand {
	char *name;
	int (*func)(char ** const);
	struct s_subcommand *next;
} t_subcommand;

int subcmd_exec(t_subcommand *subcmd_list, char ** const argv);
void subcmd_register(t_subcommand **subcmd_list, const char *name, int (*func)(char ** const));
void subcmd_clear(t_subcommand *subcmd_list);
