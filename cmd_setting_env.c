/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_setting_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeftyr <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:57:15 by szeftyr           #+#    #+#             */
/*   Updated: 2020/11/01 22:57:01 by szeftyr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_add_new_var(char ***env, char *key, char *newval)
{
	char	***tmp;
	char	**envp;
	int		i;

	tmp = env;
	i = ft_arrlen((*tmp));
	envp = (char**)ft_memalloc(sizeof(char*) * (i + 2));
	i = -1;
	while ((*tmp)[++i])
		envp[i] = ft_strdup((*tmp)[i]);
	ft_freearray((void **)*env);
	envp[i] = ft_strnew(ft_strlen(key) + 1 + ft_strlen(newval));
	envp[i] = ft_strcat(envp[i], key);
	envp[i] = ft_strcat(envp[i], "=");
	envp[i] = ft_strcat(envp[i], newval);
	envp[i + 1] = NULL;
	tmp = &envp;
	return (*tmp);
}

void	env_set_new_val(char **env, char *key, int pos, char *new)
{
	free(env[pos]);
	env[pos] = ft_strnew(ft_strlen(key) + 1 + ft_strlen(new));
	env[pos] = ft_strcat(env[pos], key);
	env[pos] = ft_strcat(env[pos], "=");
	env[pos] = ft_strcat(env[pos], new);
}

int		env_setenv(char ***env, char *newvar)
{
	int		pos;
	char	*val;
	char	**tmp;
	int		i;

	tmp = ft_strsplit(newvar, '=');
	if (tmp[1] == NULL || tmp == NULL)
	{
		ft_putstr("Specify VAR=value\n");
		ft_freearray((void **)tmp);
		return (1);
	}
	i = -1;
	while (tmp[0][++i] != '\0')
		tmp[0][i] = ft_toupper(tmp[0][i]);
	pos = get_env_var_pos(*env, tmp[0]);
	val = get_env_var_val(*env, tmp[0]);
	if (pos >= 0 && ft_strcmp(val, tmp[1]) != 0)
		env_set_new_val(*env, tmp[0], pos, tmp[1]);
	else if (pos < 0)
		*env = env_add_new_var(env, tmp[0], tmp[1]);
	free(val);
	ft_freearray((void **)tmp);
	return (0);
}
