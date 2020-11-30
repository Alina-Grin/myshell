/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeftyr <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 23:27:06 by szeftyr           #+#    #+#             */
/*   Updated: 2020/11/04 22:22:32 by szeftyr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_qoutes(char *s)
{
	int	q_count;
	int	i;

	q_count = 0;
	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == 34 || s[i] == 39)
			q_count++;
	}
	if (q_count % 2 == 0)
		return (0);
	else
	{
		ft_putstr("Check the qoutes.\n");
		return (-1);
	}
}

int		ft_count_word(char *s)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (check_qoutes(s))
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != '\t' && s[i] != '\n' && s[i] != ' ' && (s[i + 1] == '\t'
			|| s[i + 1] == 34 || s[i + 1] == 39
			|| s[i + 1] == '\n' || s[i + 1] == ' ' || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

int		ft_len_word(char *s)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while ((s[i] == '\t' || s[i] == '\n' || s[i] == ' ') && s[i] != '\0')
		i++;
	while (s[i] != '\t' && s[i] != '\n' && s[i] != ' ' && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

char	**ft_split(char *str)
{
	char	**arr;
	int		i;
	int		count_word;
	int		len_word;

	if (!(count_word = ft_count_word(str)))
		return (NULL);
	if (!(arr = (char **)malloc(sizeof(char *) * (count_word + 1))))
		return (NULL);
	i = 0;
	while (i < count_word)
	{
		len_word = ft_len_word(str);
		if (!(arr[i] = (char *)malloc(sizeof(char) * (len_word + 1))))
			return (NULL);
		while (*str == ' ' || *str == '\t' || *str == '\n')
			str++;
		ft_strncpy(arr[i], str, len_word);
		arr[i][len_word] = '\0';
		str = str + len_word;
		i++;
	}
	arr[count_word] = NULL;
	return (arr);
}
