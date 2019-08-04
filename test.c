#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include "get_next_line.h"
#include <limits.h>
#include <dirent.h>
#include <signal.h>

#define SIGINT 2
#define HISTSIZE 100

typedef	struct	s_env
{
	char *name;
	char *value;
	char id;
	struct s_env *next;
}				t_env;

void    change_env(char *var, t_env *env, char *new)
{
    char path[FILENAME_MAX];
    if (!ft_strcmp(var, "PWD"))
    {
        getcwd(path, sizeof(path));
        new = ft_strdup(path);
    }
    while (env && ft_strcmp(env->name, var))
        env = env->next;
    if (env)
    {
        if (env->value)
            free(env->value);
        env->value = new;
    }
}

char	*pull_env(char *var, t_env *env)
{
	while (env && ft_strcmp(env->name, var) != 0)
		env = env->next;
	if (!env)
		return (0);
	return (env->value);
}

char    *makepath(char *buf, char *plus, t_env *env)
{
    char *path;
    char *tmp;

    if (plus && *plus && plus[0] == '~' && plus[1] && plus[1] == '/')
    {
        while (env && ft_strcmp("HOME", env->name))
            env = env->next;
        if (!env)
            return (NULL);
        tmp = ft_strjoin(env->value, "/");
        path = ft_strjoin(tmp, plus + 2);
        printf("path for ~ is %s\n", path);
    }
    else
    {
        tmp = ft_strjoin(buf, "/");
        path = ft_strjoin(tmp, plus);
    }
    free(tmp);
    return (path);
}

char    *search_command(char **paths, char *command)
{
    int i;
    char *full;
    char *tmp;

    i = 0;
    if (!paths)
        return (NULL);
    tmp = ft_strjoin(paths[0], "/");
    full = ft_strjoin(tmp, command);
    free(tmp);
    while (paths[i] && (access(full, 0)))
    {
        free(full);
        tmp = ft_strjoin(paths[i], "/");
        full = ft_strjoin(tmp, command);
        free(tmp);
        i++;
    }
    if (!paths[i])
    {
        free(full);
        return (NULL);
    }
    if (access(full, 1))
    {
        ft_putstr(command);
        ft_putstr(": access denied\n");
        return ("\0");
    }
    return (full);
}

//while setting variables check if 1st symbol is a letter - or throw not valid identifier mistake
char	*is_command(char **arr, t_env *env, int ind)
{
	char **paths;
	char path[PATH_MAX];
    char *p;

    if (arr[ind][0] == '.' && arr[ind][1] == '/')
    {
        getcwd(path, sizeof(path));
        p = makepath(path, arr[0], NULL);
        if (!access(p, 0)) {
            if (!access(p, 1))
                return (p);
            else {
                free(p);
                ft_putstr(arr[ind]);
                ft_putstr(": access denied\n");
                return ("\0");
            }
        }
    }
	p = pull_env("PATH", env);
	paths = ft_strsplit(p, ':');
	if ((!access(arr[ind], 0) && !access(arr[ind], 1)))
	    p = ft_strdup(arr[ind]);
	else
	    p = search_command(paths, arr[ind]);
    if (paths)
        ft_arrmemdel((void **)paths);
	return (p);
}

//int     ft_envsize(t_env *env)
//{
//    int len;
//
//    len = 0;
//    while (env) {
//        env = env->next;
//        len++;
//    }
//    return (len);
//}

//char **make_arr(t_env *env)
//{
//    char **arr;
//    int i;
//    char *tmp;
//
//    i = ft_envsize(env);
//    arr = (char **)malloc(sizeof(char *) + i + 1);
//    i = 0;
//    while (env)
//    {
//        if (env->id)
//        {
//            tmp = ft_strjoin(env->name, "=");
//            arr[i] = ft_strjoin(tmp, env->value);
//            ft_strdel(&tmp);
//        }
//        i++;
//        env = env->next;
//    }
//    arr[i] = NULL;
//    return (arr);
//}
//
//int     free_tmp(char **tmp)
//{
//    int i;
//
//    i = 0;
//    while (tmp[i])
//    {
//        ft_strdel(&tmp[i]);
//        i++;
//    }
//    free(tmp);
//    return (1);
//}

int    print_err1(char *str)
{
    ft_putstr("cd: string not in pwd: ");
    ft_putstr(str);
    ft_putchar('\n');
    return (1);
}

int     is_valid_path(char *path, char *name)
{
    DIR *dir;
    if (!path || ((dir = opendir(path)) == NULL))
    {
        if (path && name)
        {
            ft_putstr("cd: ");
            if (access(path, F_OK) == -1)
                ft_putstr("no such file or directory: ");
            else if (access(path, R_OK) == -1)
                ft_putstr("permission denied: ");
            else
                ft_putstr("not a directory: ");
            ft_putstr(name);
            ft_putchar('\n');
        }
        return (0);
    }
    closedir(dir);
    return (1);
}

t_env *is_ps1(t_env *env)
{
    while (env && ft_strcmp("PS1", env->name))
        env = env->next;
    if (!env)
        return (NULL);
    return (env);
}

int     manage_cd(char **arr, t_env *env, int i)
{
    char buf[FILENAME_MAX];
    char *path;

    if (!ft_strcmp(arr[i], "cd"))
    {
        if (!arr[i + 1] || !ft_strcmp("$HOME", arr[i + 1]) || !ft_strcmp(arr[i + 1], "~"))
        {
            change_env("OLDPWD", env, ft_strdup(getcwd(buf, sizeof(buf))));
            pull_env("HOME", env) == NULL ? ft_putstr("$HOME isn't set.\n") : chdir(pull_env("HOME", env));
        }
        else {
            if (arr[i + 2])
                return (print_err1(arr[i + 1]));
            getcwd(buf, sizeof(buf));
            if (ft_strcmp(arr[i + 1], "-"))
            {
                if (!is_valid_path(arr[i + 1], NULL))
                    path = makepath(buf, arr[i + 1], env);
                else
                    path = ft_strdup(arr[i + 1]);
                if (is_valid_path(path, arr[i + 1]))
                {
                    change_env("OLDPWD", env, ft_strdup(buf));
                    chdir(path);
                }
                else
                    ft_strdel(&path);
            } else
            {
                if (chdir(pull_env("OLDPWD", env)))
                {
                    ft_putstr("$OLDPWD isn't set.\n");
                    return (1);
                }
                path = ft_strdup(pull_env("PWD", env));
                ft_putchar('~');
                ft_putstr(pull_env("OLDPWD", env));
                ft_putchar('\n');
                change_env("OLDPWD", env, path);
            }
        }
    }
    change_env("PWD", env, NULL);
}

int    print_err4(char *str)
{
    ft_putstr(str);
    ft_putstr(": command couldn't be executed because an error occured.\n");
    return (1);
}

void     sig_handlein(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        signal(SIGINT, sig_handlein);
    }
}

void    display_prompt(t_env *home)
{
//    static char buf[sizeof(home->value + 1)];
    static char *buf;
    static char c;

    if (home != NULL)
    {
        buf = home->value;
        ft_putstr(buf);
        c = '\0';
    }
    else
    {
        if (c == '\0')
            ft_putstr(buf);
        else
            ft_putstr("$> ");
    }
}

void    sig_handleout(int sig)
{
    if (sig == SIGINT)
    {
        ft_putstr("\n");
        display_prompt(NULL);
        signal(SIGINT, sig_handleout);
    }
}


int		manage_pid(char **arr, t_env *env, int i)
{
	pid_t child_pid;
	char *path;

    if ((path = is_command(arr, env, i)) == NULL)
		return (0);
    if (!*path)
        return (1);
	child_pid = fork();
    signal(SIGINT, sig_handlein);
	if (child_pid == 0)
    {
        if ((execve(path, arr, NULL) == -1))
            exit(print_err4(arr[i]));
    }
	else if (child_pid < 0)
	    ft_putstr("Fork failure\n");
	else
	    {
        ft_strdel(&path);
        wait(&child_pid);
    }
	return (1);
}

/*int		ft_add_history(char *str, int hist)
{
	static char *buf[HISTSIZE];

	if (hist < HISTSIZE)
		buf[hist] = ft_strdup(str);
	else
	{
		hist = 0;
		free(buf[hist]);
		buf[hist] = NULL;
		while (hist + 1 != HISTSIZE)
		{
			buf[hist] = buf[hist + 1];
			hist++;
		}
		buf[hist] = ft_strdup(str);
	}
	int i = 0;
	hist++;
	return (hist);
} */

int		ft_add_history(char **hist, char *str, int i)
{
	if (!str || !*str)
	    return (i);
    if (i < HISTSIZE)
		hist[i] = ft_strdup(str);
	else
	{
		i = 0;
		free(hist[i]);
		hist[i] = NULL;
		while (i + 1 != HISTSIZE)
		{
			hist[i] = hist[i + 1];
			i++;
		}
		hist[i] = ft_strdup(str);
	}
	return (++i);
}

int		colorize(char *str)
{
	static int i;
	static int color;

	if (i == 666)
	{
		color++;
		if (color == 6)
			color = 1;
		ft_putstr("\033[");
		ft_putnbr(30 + color);
		ft_putstr("m");
		return (1);
	}
	else
	{
		i = ft_strcmp(str, "colorize");
		color = 1;
		if (!i)
		{
		    i = 666;
			ft_putstr("\033[36m");
			return (1);
		}
	}
	return (0);
}

static int		find_n_length(long long num)
{
    long long i;

    i = 1;
    while (num / 10 != 0)
    {
        num = num / 10;
        i++;
    }
    return (i);
}

void	get_history(char **history)
{
	long long i;
	long long j;
	long long max;

	i = 0;
	while (history[i])
        i++;
	max = find_n_length(i);
	i = 0;
	while (history[i])
	{
	    j = max;
	    ft_putstr("   ");
		ft_putnbr(i + 1);
		ft_putstr(":");
        if (find_n_length(i + 1) != max)
        {
            while (j--)
                ft_putstr(" ");
        }
        else
            ft_putstr(" ");
		ft_putstr(history[i]);
		write(1, "\n", 1);
		i++;
	}
}

void    list_env(t_env *env)
{
    while (env && env->id)
    {
        if (env->value)
        {
            ft_putstr(env->name);
            ft_putchar('=');
            ft_putstr(env->value);
            ft_putchar('\n');
        }
        env = env->next;
    }
}

char *parse_env(char **env, int row)
{
    int i;
    int j;
    char *str;

    i = 0;
    while (env[row][i] != '=')
        i++;
    i++;
    j = i;
    while (env[row][j] && env[row][j] != '\n')
        j++;
    str = (char *)ft_memalloc(j - i + 1);
    j = 0;
    while (env[row][i])
    {
        str[j] = env[row][i];
        j++;
        i++;
    }
    return (str);
}

char    *parse_name(char **env, int row)
{
    int i;
    int j;
    char *str;

    i = 0;
    j = 0;
    while (env[row][i] != '=')
        i++;
    str = (char *)ft_memalloc(i + 1);
    while (j != i)
    {
        str[j] = env[row][j];
        j++;
    }
    return (str);
}

int    unset_env(t_env *env, char *var)
{
    t_env *tmp1;
    t_env *tmp2;

    while (env && ft_strcmp(env->name, var))
    {
        tmp1 = env;
        env = env->next;
    }
    if (env && ft_strcmp(var, "PS1"))
    {
        tmp2 = env->next;
        free(env->name);
        if (env->value)
            free(env->value);
        free(env);
        tmp1->next = tmp2;
        return (1);
    }
    else if (env && env->id)
    {
        if (env->value)
            free(env->value);
        env->value = ft_strdup("$> ");
        env->id = 0x0;
        return (1);
    }
    return (0);
}

void    set_env(t_env *env, char **arr)
{
    int i;
    char *name;
    char *value;
    t_env *tmp;

    i = 0;
    if (!ft_strcmp("setenv", arr[0]) || !ft_strcmp("export", arr[0]) || (arr[1] && !ft_strcmp(arr[1], "PS1")))
        i = 1;
    name = parse_name(arr, i);
    value = parse_env(arr, i);
    if (!pull_env(name, env))
    {
        if (i)
        {
            while (env->next && env->next->id)
                env = env->next;
            tmp = env->next;
            env->next = (t_env *) malloc(sizeof(t_env));
            env = env->next;
            env->next = tmp;
        }
        else
        {
            while (env->next)
                env = env->next;
            env->next = (t_env *) malloc(sizeof(t_env));
            env = env->next;
            env->id = 0x0;
            env->next = NULL;
        }
        env->name = name;
    }
    else
    {
        free(name);
        while (env && ft_strcmp(env->name, name))
            env = env->next;
        ft_strdel(&env->value);
    }
    if (i)
        env->id = 0x1;
    env->value = value;
}

int is_regex(char c)
{
    if (c == '=' || c == '&' || c == '*' || c == '$' || c == '|')
    {
        if (c == '*')
            return (1);
        else
            return (2);
    }
    return (0);
}

void    print_err(int flag, char *error)
{
    if (flag == 1)
    {
        ft_putstr(": no matches found: ");
        ft_putstr(error);
        ft_putchar('\n');
    }
    else if (flag == 2)
    {
        ft_putstr(": parse error near '");
        while (*error && *error != '=')
        {
            ft_putchar(*error);
            error++;
        }
        ft_putstr("'\n");
    }
    else if (flag == 3)
    {
        while (*error && *error != '=')
            error++;
        while (*error && *error == '=')
            error++;
        while (*error)
        {
            ft_putchar(*error);
            error++;
        }
        ft_putstr(" not found\n");
    }
}

int     is_legit(char *arr, t_env *env)
{
    int flag;
    int j;

    j = 0;
    if (arr && arr[j])
    {
        if ((flag = is_regex(arr[j])) > 0)
        {
            ft_putstr(pull_env("PS1", env));
            print_err(flag, arr);
            return (1);
        }
        while (arr[j] && arr[j] != '=')
            j++;
        if (!arr[j])
            return (0);
        j++;
        if (arr[j] == '=')
        {
            ft_putstr(pull_env("PS1", env));
            print_err(3, arr);
            return (1);
        }
    }
    return (1);
}

int     wanna_set(char *str, t_env *env)
{
    if (!is_legit(str, env))
        return (0);
    return (1);
}

void    echo_var(t_env *env, char *var)
{
    char *str;

    str = var + 1;
    while (env && ft_strcmp(env->name, str))
        env = env->next;
    if (env)
        ft_putstr(env->value);
    write(1, "\n", 1);
}

void    print_err2(t_env *env, char *str)
{
    ft_putstr(pull_env("SHELL", env));
    ft_putstr(": ");
    ft_putstr(str);
    ft_putstr(": no arguments specified.\n");
}

void    print_err3(t_env *env, char *str, char *str1)
{
    ft_putstr(pull_env("SHELL", env));
    ft_putstr(": ");
    ft_putstr(str);
    ft_putstr(": no matches found: ");
    ft_putstr(str1);
    ft_putchar('\n');
}

void    echo_str(char *start, char *finish)
{
    while (start != finish)
    {
        ft_putchar(*start);
        start++;
    }
}

int     echo_that(char *str)
{
    int words;
    int brackets;
    int i;

    i = 0;
    brackets = 0;
    if (!str || !*str)
        return (0);
    words = ft_countw(str, ' ');
   while (str[i])
   {
       if (*str == '\'' || *str == '\"')
           brackets++;
       i++;
   }
   if (brackets == words * 2)
       return (0);
   while (*str)
   {
       if (*str != '\'' && *str != '\"')
           ft_putchar(*str);
       str++;
   }
   return (1);
}

void    echo_this(char **arr)
{
    int i;
    char *start;
    char *finish;

    i = 1;
    if (arr[1])
    {
        while (arr[i])
        {
            if (!echo_that(arr[i])) {
                start = NULL;
                finish = NULL;
                if ((arr[i][0] == '\'' || arr[i][0] == '\"') && arr[i][1])
                    start = &arr[i][1];
                if ((ft_strlen(arr[i]) > 2 &&
                     (arr[i][ft_strlen(arr[i]) - 1] == '\'' || arr[i][ft_strlen(arr[i]) - 1] == '\"')))
                    finish = &arr[i][ft_strlen(arr[i]) - 1];
                if (!start || !finish) {
                    start = &arr[i][0];
                    finish = &arr[i][ft_strlen(arr[i])];
                }
                echo_str(start, finish);
            }
            i++;
            if (arr[i])
                write(1, " ", 1);
        }
    }
    write(1, "\n", 1);
}

int     one_time_command(char **arr, t_env *env, char **hist)
{
    if (!ft_strcmp(arr[0], "colorize"))
        colorize(arr[0]);
    else if (!ft_strcmp(arr[0], "history"))
        get_history(hist);
    else if (!ft_strcmp(arr[0], "env"))
        list_env(env);
    else if (!ft_strcmp(arr[0], "unsetenv"))
    {
        if (!arr[1])
            print_err2(env, arr[0]);
        else if (!unset_env(env, arr[1]))
            print_err3(env, arr[0], arr[1]);
    }
    else if (!ft_strcmp(arr[0], "echo"))
    {
        if (arr[1] && arr[1][0] == '$' && arr[1][1])
            echo_var(env, arr[1]);
        else
            echo_this(arr);
    }
    else
        return (0);
    return (1);
}

void		get_command(char **arr, t_env *env, char **hist)
{
    int i;

    i = 0;
    if (one_time_command(arr, env, hist))
        return ;
    while ((arr[i] && ((!ft_strcmp(arr[i], "setenv") && arr[i + 1] && is_legit(arr[i + 1], env))
    || (!ft_strcmp(arr[i], "export") && arr[i + 1] && is_legit(arr[i + 1], env)) || wanna_set(arr[i], env))))
    {
        set_env(env, arr);
        i++;
    }
    if (arr[i] && !ft_strcmp(arr[i], "cd"))
        manage_cd(arr, env, i);
	else if (arr[i] && !manage_pid(arr, env, i))
	{
		ft_putstr("kek: command not found: ");
		ft_putstr(arr[0]);
		ft_putchar('\n');
	}
}

int     ft_counts(char **env)
{
    int i;

    i = 0;
    while (env[i])
        i++;
    return (--i);
}

void    get_nameval(t_env *start, char **env)
{
    int i;
    int ps1;
    t_env *tmp;

    i = 0;
    ps1 = 0;
    while (start)
    {
        start->name = parse_name(env, i);
        start->value = parse_env(env, i);
        start->id = (char) 0x1;
        if (!ft_strcmp(start->name, "PS1"))
            ps1 = 1;
        i++;
        tmp = start;
        start = start->next;
    }
    if (!ps1)
    {
        tmp->next = (t_env *)malloc(sizeof(t_env));
        tmp = tmp->next;
        tmp->name = ft_strdup("PS1");
        tmp->value = ft_strdup("$> ");
        tmp->id = 0x0;
        tmp->next = NULL;
    }
}

t_env   *get_envars(char **env)
{
    int rows;
    t_env *envar;
    t_env *start;

    rows = ft_counts(env);
    envar = (t_env *)malloc(sizeof(t_env));
    start = envar;
    envar->name = NULL;
    envar->value = NULL;
    envar->next = NULL;
    while (--rows)
    {
        envar->next = (t_env *)malloc(sizeof(t_env));
        envar = envar->next;
        envar->name = NULL;
        envar->value = NULL;
        envar->next = NULL;
    }
    get_nameval(start, env);
    return (start);
}

char	**create_hist(void)
{
	char **hist;
	
	hist = (char **)ft_memalloc(sizeof(char *) * HISTSIZE + 1);
	return (hist);	
}

int     not_tabs(char **arr)
{
    int i;
    int j;
    int flag;

    i = 0;
    j = 0;
    flag = 0;
    while (arr[i])
    {
        while(arr[i][j])
        {
            if (arr[i][j] != ' ' && arr[i][j] != '\t')
                flag = 1;
            j++;
        }
        i++;
        j = 0;
    }
    return (flag);
}

int     ft_cleanall(t_env *env, char **history, char *line)
{
    t_env *tmp;

    while (env)
    {
        tmp = env;
        env = env->next;
        ft_strdel(&tmp->name);
        if (tmp->value)
            ft_strdel(&tmp->value);
        free(tmp);
    }
    if (line)
        ft_strdel(&line);
    ft_arrmemdel((void **)history);
    return (0);
}

int	main(int argc, char **argv, char **env)
{
	char *str;
	char **arr;
	int hist;
	char **history;
	t_env *envr;

	hist = 0;
	envr = get_envars(env);
	history = create_hist();
	while (1)
	{
        display_prompt(is_ps1(envr));
        signal(SIGINT, sig_handleout);
        if (get_next_line(0, &str) < 0)
            write(1, "Input error\n", 12);
        hist = ft_add_history(history, str, hist);
        if (!ft_strcmp(str, "exit"))
            break ;
        colorize(str);
        if (*str)
        {
            arr = ft_strsplit(str, ' ');
            if (*arr && not_tabs(arr))
                get_command(arr, envr, history);
            ft_arrmemdel((void **) arr);
        }
        ft_strdel(&str);
    }
	return (ft_cleanall(envr, history, str));
}
