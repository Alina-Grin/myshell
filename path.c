/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeftyr <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:22:22 by szeftyr           #+#    #+#             */
/*   Updated: 2020/11/02 21:32:50 by szeftyr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_paths(char **param, char *path_var)
{
	char	**arr_path;
	int		i;
	char	*tmp;

	arr_path = ft_strsplit(path_var, ':');
	free(path_var);
	i = -1;
	while (arr_path[++i])
	{
		tmp = ft_strjoin("/", param[0]);
		path_var = ft_strnew(ft_strlen(arr_path[i]) + ft_strlen(tmp));
		path_var = ft_strcpy(path_var, arr_path[i]);
		path_var = ft_strcat(path_var, tmp);
		free(tmp);
		if (!access(path_var, X_OK))
		{
			ft_freearray((void **)arr_path);
			return (path_var);
		}
		free(path_var);
	}
	ft_freearray((void **)arr_path);
	return (NULL);
}
