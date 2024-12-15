#pragma once

typedef struct s_subcommand {
	char *name;
	int (*func)(const char **);
	struct s_subcommand *next;
} t_subcommand;

int subcmd_exec(t_subcommand *subcmd_list, const char **argv);
void subcmd_register(t_subcommand **subcmd_list, const char *name, int (*func)(const char **));
void subcmd_clear(t_subcommand *subcmd_list);
