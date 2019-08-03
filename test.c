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

#define HISTSIZE 50

//create a linked list (maybe two-sides)
//save all the vars there - just the ones that we have!
//check if we need to look for commands in vars other than PATH
//case in which we are given /fullpath/executable_script, check if we can just execve it
//make possible to set another PS1 and change $> to PS1 in main
//if we echo and variable isn't set or doesn't exist, we print \n only
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
	//if we're looking for PATH and there may be other path vars set, we may just find them all together and join as the whole path with ':'
	//thus we won't need to check other vars and stuff
	//but maybe no maybe better check other vars separately to preserve memory
	while (env && ft_strcmp(env->name, var) != 0)
		env = env->next;
	if (!env)
		return (0);
	return (env->value);
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
    while (paths[i] && (access(full, 0) || access(full, 1)))
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
    return (full);
}

//while setting variables check if 1st symbol is a letter - or throw not valid identifier mistake
//make sure we set variables with just var=value and export var=value (maybe execute export thing, but update your
//data structure as well
char	*is_command(char **arr, t_env *env, int ind)
{
	char **paths;
	char path[PATH_MAX];
    char *p;

    if (arr[ind][0] == '.' && arr[ind][1] == '/')
    {
        getcwd(path, sizeof(path));
        p = ft_strjoin(path, arr[0]);
        if (access(p, 0)) {
            if (access(p, 1))
                return (p);
            else {
                free(p);
                ft_putstr("kek: access denied\n");
                return (0);
            }
        }
    }
	p = pull_env("PATH", env);
	//we may also nned to search env var with path to temporary files etc
	//we may need to find some vars that we don't have in our envs but which may exist
	paths = ft_strsplit(p, ':');
	if ((!access(arr[ind], 0) && !access(arr[ind], 1)))
	    p = ft_strdup(arr[ind]);
	else
	    p = search_command(paths, arr[ind]);
//	if (!p)
//	    return ((char *)ft_arrmemdel((void **)paths));
    if (paths)
        ft_arrmemdel((void **)paths);
	return (p);
	//check each path - with opendir - readdir -closedir - stat to find command name and our executable rights
	//path could be forbidden - we must check what opendir returns. if we cant open the dir and it's the reason we can't execute command,
	//we first write that path is forbidden and then that command not found
	//don't forget to close everything
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

//char *is_home(char *str, t_env *env)
//{
//    if (!ft_strcmp("$HOME", str))
//    {
//        while (env && ft_strcmp("HOME", env->name))
//            env = env->next;
//    }
//    if (!env)
//        return (NULL);
//    return (ft_strdup(str));
//}

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
            //check if we have flag -L to get to the soft link directly, with lstat change our path
            getcwd(buf, sizeof(buf));
            //if we don't have OLDPWD set, and cd - is called, we must handle mistake right
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
                // path == NULL ? ft_putstr("$HOME isn't set.\n") : ft_strdel(&path);
            } else
            {
                path = ft_strdup(pull_env("PWD", env));
                chdir(pull_env("OLDPWD", env));
                ft_putchar('~');
                ft_putstr(pull_env("OLDPWD", env));
                ft_putchar('\n');
                change_env("OLDPWD", env, path);
            }
        }
    }
    change_env("PWD", env, NULL);
        //maybe analyze mistakes here chdir
        //change pwd only if cdir worked normally
        //save previous path always in oldpwd
        //use it with "-" arg
}

//int     get_job_done(char **arr, t_env *env, int i, char *path)
//{
//    if (!ft_strcmp(arr[i], "cd"))
//    {
//        manage_cd(arr, env, i);
//        //return (1);
//    }
//    else
//        execve(path, arr, NULL);
//}

int    print_err4(char *str)
{
    ft_putstr(str);
    ft_putstr(": couldn't be executed: permission denied.\n");
    //ft_putstr(": command couldn't be executed because an error occured.\n");
    return (1);
}

int		manage_pid(char **arr, t_env *env, int i)
{
	pid_t child_pid;
	char *path;
    //pid_t wait_result;
    int stat_loc;

	if ((path = is_command(arr, env, i)) == NULL)
		return (0);
	//higher we must check - if we found command - that it we have rights to execute this command - we can use getcwd or stat
	child_pid = fork();
	if (child_pid == 0)
    {
        if ((execve(path, arr, NULL) == -1))
            exit(print_err4(arr[i]));
    }
	    //get_job_done(arr, env, i, path);
	else if (child_pid < 0)
	    ft_putstr("Fork failure\n");
	else
	    {
        ft_strdel(&path);
        //waitpid(child_pid, &stat_loc, WUNTRACED);
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
	static int i = 2;
	static int color;

	if (!i)
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
			ft_putstr("\033[36m");
			return (1);
		}
	}
	return (0);
}

void	get_history(char **history)
{
	int i;

	i = 0;
	while (history[i])
	{
		ft_putstr("   ");
		ft_putnbr(i + 1);
		ft_putstr(":  ");
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
    if (env)
    {
        tmp2 = env->next;
        free(env->name);
        if (env->value)
            free(env->value);
        free(env);
        tmp1->next = tmp2;
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
        while (*error != '=')
        {
            ft_putchar(*error);
            error++;
        }
        ft_putstr("'\n");
    }
    else if (flag == 3)
    {
        while (*error != '=')
            error++;
        while (*error == '=')
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
            return (0);
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
            return (0);
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
    else if (!ft_strcmp(arr[0], "echo") && arr[1] && arr[1][0] == '$' && arr[1][1])
        echo_var(env, arr[1]);
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

int	main(int argc, char **argv, char **env)
{
	char *str;
	char **arr;
	int i;
	int hist;
	char **history;
	t_env *envr;

	hist = 0;
	envr = get_envars(env);
	history = create_hist();
	while (1)
	{
        ft_putstr(pull_env("PS1", envr));
        i = get_next_line(0, &str);
        hist = ft_add_history(history, str, hist);
        if (i < 0)
            write(1, "Input error\n", 12);
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
	//free everything here
	return (0);
}
