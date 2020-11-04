/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeftyr <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:00:36 by szeftyr           #+#    #+#             */
/*   Updated: 2020/11/04 19:07:30 by szeftyr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	nonprint_esc(char *str)
{
	int	len;
	int	j;

	j = -1;
	len = strlen(str);
	while (++j < len)
	{
		if (str[j] == 34 || str[j] == 39 || (str[j] == 92 && str[j + 1] == 92))
			j++;
		if (str[j] != '\0')
			ft_putchar(str[j]);
	}
}

// char		*change_tmp(char *tmp, char **newenv)
// {
// 	int		i;
// 	char	*value;
// 	int		pos;
// 	char	*key;
// 	int		len;

// 	pos = 0;
// 	while (tmp[pos] != '$')
// 		pos++;
// 	i = pos + 1;
// 	while (tmp[i] != ' ' && tmp[i] != '\t' && tmp[i] != 39 && tmp[i] != 34 && tmp[i] != '$')
// 		i++;
// 	key = ft_strsub(tmp, (pos + 1), (i - pos - 1));
// 	if (!(value = get_env_var_val(newenv, key)))
// 		value = ft_strdup("");
// 	free(key);
// 	len = ft_strlen(tmp) - i;
// 	key = ft_strnew(pos + ft_strlen(value) + len);
// 	key = ft_strncpy(key, tmp, pos);
// 	key = ft_strcat(key, value);
// 	key = ft_strcat(key, (tmp + i));
// 	free(value);
// 	free(tmp);
// 	return (key);
// }

void		print_echo(char *tmp, char *str, int *i, char **newenv)
{
	if (tmp[0] == '~')
	{
		free(tmp);
		tmp = get_env_var_val(newenv, "HOME");
	}
	// if (ft_strchr(tmp, '$'))
	// 	tmp = change_tmp(tmp, newenv);
	nonprint_esc(tmp);
	(*i)++;
	free(tmp);
	if (str)
		ft_putchar(' ');
}

int			cmd_echo(char **str, char **newenv)
{
	char	*tmp;
	int		i;
	char	*key;

	tmp = NULL;
	i = 1;
	while (str[i])
	{
		tmp = ft_strtrim(str[i]);
		if (tmp[0] != '$' || (tmp[0] == '$' && tmp[1] == '\0'))
			print_echo(tmp, str[i], &i, newenv);
		else if (tmp[0] == '$' && tmp[1] != '\0')
		{
			key = ft_strsub(tmp, 1, ft_strlen(tmp));
			free(tmp);
			if ((tmp = get_env_var_val(newenv, key)))
				print_echo(tmp, str[i], &i, newenv);
			else
				i++;
			free(key);
		}
	}
	ft_putchar('\n');
	return (0);
}

int			cmd_clear(void)
{
	const char	*clear;

	clear = " \e[1;1H\e[2J";
	write(1, clear, 12);
	return (0);
}
