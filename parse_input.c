/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeftyr <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:57:29 by szeftyr           #+#    #+#             */
/*   Updated: 2020/11/04 22:45:22 by szeftyr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_strappend(char *s1, char c)
{
	char	*result;
	int		len;
	int		i;

	if (!c)
		return (NULL);
	len = ft_strlen((char *)s1) + 1;
	if (!(result = (char *)malloc(len + 1)))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	result[i++] = c;
	result[i] = '\0';
	free(s1);
	return (result);
}

static void	read_input(char **input)
{
	char	buf;
	int		res;
	char	*tmp;

	*input = ft_strnew(1);
	while ((res = read(0, &buf, 1) > 0) && buf != '\n')
	{
		tmp = ft_strappend(*input, buf);
		*input = tmp;
	}
	if (!res)
	{
		free(*input);
		return ;
	}
}

char		**parse_input(void)
{
	char	*input;
	char	**arr;

	read_input(&input);
	arr = ft_split(input);
	free(input);
	return (arr);
}

int			cmd_builtin(char ***newenv, char *command, char **parameters)
{
	int	ret;

	ret = -1;
	if (ft_strequ(command, "cd"))
		ret = cmd_cd(parameters, *newenv);
	else if (ft_strequ(command, "echo"))
		ret = cmd_echo(parameters, *newenv);
	else if (ft_strequ(command, "exit"))
	{
		free(command);
		ft_freearray((void **)parameters);
		ft_freearray((void **)*newenv);
		exit(0);
	}
	else if (ft_strequ(command, "env"))
		ret = print_env(*newenv);
	else if (ft_strequ(command, "setenv"))
		ret = env_setenv(newenv, parameters[1]);
	else if (ft_strequ(command, "unsetenv"))
		ret = env_unset(*newenv, parameters[1]);
	else if (ft_strequ(command, "clear"))
		ret = cmd_clear();
	return (ret);
}
