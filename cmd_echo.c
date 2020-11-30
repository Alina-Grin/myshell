/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeftyr <szeftyr@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:00:36 by szeftyr           #+#    #+#             */
/*   Updated: 2020/11/05 14:25:37 by szeftyr          ###   ########.fr       */
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

void		print_echo(char *tmp, char *str, int *i, char **newenv)
{
	if (tmp[0] == '~')
	{
		free(tmp);
		tmp = get_env_var_val(newenv, "HOME");
	}
	nonprint_esc(tmp);
	(*i)++;
	if (ft_strlen(tmp) == 1 && (tmp[0] == 34 || tmp[0] == 39))
	{
		free(tmp);
		return ;
	}
	if (str)
		ft_putchar(' ');
	free(tmp);
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
		tmp = ft_strdup(str[i]);
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
