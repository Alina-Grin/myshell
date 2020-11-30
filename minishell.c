/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeftyr <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:57:39 by szeftyr           #+#    #+#             */
/*   Updated: 2020/11/04 23:48:50 by szeftyr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	type_promt(void)
{
	char	*location;

	location = getcwd(NULL, 0);
	ft_putstr(location);
	ft_putstr(" $>");
	free(location);
}

int		read_command(char **cmd, char ***par)
{
	char	**arr;
	int		j;
	int		len;
	int		i;
	char	**tmp;

	arr = parse_input();
	if (arr == NULL)
		return (1);
	*cmd = ft_strjoin("", arr[0]);
	j = 0;
	i = 0;
	len = (int)ft_arrlen(arr);
	tmp = (char **)malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		tmp[j] = ft_strdup(arr[i]);
		i++;
		j++;
	}
	tmp[j] = NULL;
	*par = tmp;
	ft_freearray((void **)arr);
	return (0);
}

int		execve_cmd(char *path, char **param, char **env)
{
	pid_t	pid;

	if (path == NULL)
		return (-1);
	pid = fork();
	signal(SIGINT, process_signal_handler);
	if (pid == 0)
	{
		if (execve(path, param, env) == -1)
		{
			ft_putstr("Command not found\n");
			free(path);
			ft_freearray((void **)param);
			exit(0);
		}
		ft_freearray((void **)param);
	}
	else if (pid < 0)
	{
		free(path);
		ft_putstr("Fork failed to create a new process.\n");
		return (-1);
	}
	wait(&pid);
	return (1);
}

void	run_exec(char *command, char **param, char **newenv)
{
	char	*cmdpath;
	char	*path_var;

	path_var = get_env_var_val(newenv, "PATH");
	if (path_var == NULL && param[0][0] != '/')
	{
		ft_putstr("Command not found\n");
		return ;
	}
	if (param[0][0] == '/')
	{
		free(path_var);
		execve_cmd(command, param, newenv);
	}
	else
	{
		cmdpath = check_paths(param, path_var);
		if (execve_cmd(cmdpath, param, newenv) == -1)
			ft_putstr("Command not found\n");
		free(cmdpath);
	}
}

int		main(void)
{
	char		*command;
	char		**parameters;
	extern char	**environ;
	char		**newenv;

	newenv = ft_arrdup(environ);
	while (1)
	{
		type_promt();
		signal(SIGINT, signal_handler);
		if (read_command(&command, &parameters))
			continue ;
		if ((cmd_builtin(&newenv, command, parameters) == -1)
			&& command != NULL)
			run_exec(command, parameters, newenv);
		free(command);
		ft_freearray((void **)parameters);
	}
	ft_freearray((void **)newenv);
	return (0);
}
