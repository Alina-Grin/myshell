/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeftyr <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:25:49 by szeftyr           #+#    #+#             */
/*   Updated: 2020/10/27 12:44:32 by szeftyr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrdup(char **arr)
{
	char	**dup;
	int		len;
	int		i;
	int		j;
	int		len_str;

	if (arr == NULL)
		return (NULL);
	len = (int)ft_arrlen(arr);
	if ((dup = (char **)malloc((sizeof(char *) * (len + 1)))) == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		j = -1;
		len_str = ft_strlen(arr[i]);
		if (!(dup[i] = (char *)malloc(sizeof(char) * (len_str + 1))))
			return (NULL);
		while (++j < len_str)
			dup[i][j] = arr[i][j];
		dup[i][j] = '\0';
	}
	dup[len] = NULL;
	return (dup);
}
