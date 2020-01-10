/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 07:58:39 by bomanyte          #+#    #+#             */
/*   Updated: 2019/08/05 10:46:16 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/syslimits.h>

# define SIGINT 2
# define HISTSIZE 100

typedef	struct		s_env
{
	char			*name;
	char			*value;
	char			id;
	struct s_env	*next;
}					t_env;

void				subst_comm(char **comm, int i, int j);
int					count_commands(char **arr);
int					exec_many(char **arr, t_env *env, char **hist);
int					is_first_num(char *str);
void				not_found_err(char *command);
int					manage_global(t_env *env, char **arr, int i);
int					manage_local(t_env *env, char **arr, int i);
void				parse_error(char *error);
void				no_matches_err(char *error);
void				clear_env(t_env *tmp1, t_env *env);
t_env				*sort_global(t_env *env);
t_env				*sort_local(t_env *env);
int					check_ps1(char **arr);
void				set_ps1(t_env *tmp);
int					ft_counts(char **env);
char				*get_start(char **arr, int i);
char				*get_finish(char **arr, int i);
char				*access_err(char *command);
void				change_env(char *var, t_env *env, char *new);
char				*pull_env(char *var, t_env *env);
char				*makepath(char *buf, char *plus, t_env *env);
char				*is_command(char **arr, t_env *env, int ind);
void				print_err1(char *str);
int					is_valid_path(char *path, char *name);
t_env				*is_ps1(t_env *env);
void				manage_cd(char **arr, t_env *env, int i);
int					print_err4(char *str);
void				sig_handlein(int sig);
void				display_prompt(t_env *home);
void				sig_handleout(int sig);
int					manage_pid(char **arr, t_env *env, int i);
int					colorize(char *str);
int					ft_add_history(char **hist, char *str, int i);
void				get_history(char **history);
void				list_env(t_env *env);
char				*parse_env(char **env, int row);
char				*parse_name(char **env, int row);
int					unset_env(t_env *env, char *var);
void				set_env(t_env *env, char **arr, int ind);
void				print_err(int flag, char *error);
int					is_legit(char *arr, t_env *env);
int					wanna_set(char *str);
void				echo_var(t_env *env, char *var);
void				print_err2(char *str);
void				print_err3(char *str, char *str1);
void				echo_this(char **arr);
int					one_time_command(char **arr, t_env *env, char **hist);
void				get_command(char **arr, t_env *env, char **hist);
void				get_nameval(t_env *start, char **env);
t_env				*get_envars(char **env);
char				**create_hist(void);

#endif
