/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeftyr <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 23:30:26 by szeftyr           #+#    #+#             */
/*   Updated: 2020/11/04 19:24:08 by szeftyr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_env_var_pos(char **env, char *key)
{
	int	i;
	int	j;

	if (env == NULL || *key == '\0' || ft_strlen(key) == 1)
		return (-1);
	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		if (j > 0)
			j--;
		if ((env[i][0] == key[0]) && ft_strstr(env[i], key)
				&& (env[i][j] == key[j]))
			return (i);
		if (env[i + 1] == '\0')
			return (-1);
	}
	return (i);
}

char	*get_env_var_val(char **env, char *key)
{
	char	*value;
	char	*tmp;
	int		pos;
	int		len;
	int		i;

	if ((pos = get_env_var_pos(env, key)) < 0)
		return (NULL);
	tmp = ft_strchr(env[pos], '=');
	if (tmp == NULL)
		return (NULL);
	tmp++;
	len = ft_strlen(env[pos]) - ft_strlen(key) - 1;
	value = ft_strnew(len);
	i = 0;
	while (*tmp != '\0')
	{
		value[i] = *tmp;
		i++;
		tmp++;
	}
	return (value);
}

int		print_env(char **newenv)
{
	int	i;

	i = 0;
	while (newenv[i] != NULL)
	{
		ft_putstr(newenv[i]);
		i++;
		if (newenv[i] == NULL)
			break ;
		ft_putchar('\n');
	}
	ft_putchar('\n');
	return (0);
}

int		env_unset(char **env, char *key)
{
	int		pos;

	if (key == NULL)
	{
		ft_putstr("You need to specify the variable name in the uppercase\n");
		return (1);
	}
	pos = get_env_var_pos(env, key);
	if (pos < 0)
	{
		ft_putstr("The specified variable does not exist\n");
		return (1);
	}
	while (env[pos] != NULL)
	{
		free(env[pos]);
		if (env[pos + 1] == NULL)
			env[pos] = NULL;
		else
		{
			env[pos] = ft_strdup(env[pos + 1]);
			pos++;
		}
	}
	return (0);
}
