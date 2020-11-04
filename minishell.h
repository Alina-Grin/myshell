/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeftyr <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:43:19 by szeftyr           #+#    #+#             */
/*   Updated: 2020/11/04 13:21:38 by szeftyr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "libft/libft.h"

void	type_promt(void);
int		cmd_echo(char **str, char **newenv);
char	**parse_input();
int		print_env(char **newenv);
char	*get_env_var_val(char **env, char *key);
int		get_env_var_pos(char **env, char *key);
void	signal_handler(int signo);
void	process_signal_handler(int signo);
int		cmd_cd(char **param, char **env);
int		env_setenv(char ***env, char *newvar);
int		env_unset(char **env, char *key);
void	env_set_new_val(char **env, char *key, int pos, char *new);
int		cmd_clear(void);
char	**env_add_new_var(char ***env, char *key, char *newval);
int		cmd_builtin(char ***newenv, char *command, char **parameters);
int		execve_cmd(char *path, char **param, char **env);
char	*check_paths(char **param, char *path_var);
char	**ft_split(char *str);

#endif
