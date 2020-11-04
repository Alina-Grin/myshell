/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeftyr <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 22:15:10 by szeftyr           #+#    #+#             */
/*   Updated: 2020/11/01 23:33:33 by szeftyr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_cderror(char *fullpath)
{
	ft_putstr("cd: ");
	if (access(fullpath, F_OK) == -1)
		ft_putstr("no such file or directory: ");
	else if (access(fullpath, R_OK) == -1)
		ft_putstr("permission denied: ");
	else
		ft_putstr("not a directory: ");
	ft_putstr(fullpath);
	ft_putchar('\n');
	return (1);
}

int		cmd_cd_other(char **env, char *path)
{
	int		ret;
	char	*currentwd;
	char	*tmp;
	int		r;

	currentwd = getcwd(NULL, 0);
	tmp = ft_strjoin("OLDPWD=", currentwd);
	env_setenv(&env, tmp);
	ret = chdir(path);
	r = 0;
	if (ret)
		r = print_cderror(path);
	free(currentwd);
	free(tmp);
	return (r);
}

int		cmd_cd_home_prev(char **env, char *keydest)
{
	char	*path;
	int		ret;
	char	*currentwd;
	char	*tmp;
	int		r;

	currentwd = getcwd(NULL, 0);
	tmp = ft_strjoin("OLDPWD=", currentwd);
	r = 0;
	if ((path = get_env_var_val(env, keydest)))
	{
		env_setenv(&env, tmp);
		ret = chdir(path);
		if (ret)
			r = print_cderror(path);
		free(path);
	}
	else
	{
		ft_putstr("HOME directory is undefined\n");
		r = 1;
	}
	free(currentwd);
	free(tmp);
	return (r);
}

int		cmd_cd(char **param, char **env)
{
	char	*path;
	int		ret;

	if (param[1] == NULL || ft_strequ(param[1], "~"))
		return (cmd_cd_home_prev(env, "HOME"));
	else if (ft_strequ(param[1], "-"))
		return (cmd_cd_home_prev(env, "OLDPWD"));
	else
	{
		path = ft_strdup(param[1]);
		ret = cmd_cd_other(env, path);
		free(path);
		return (ret);
	}
}
