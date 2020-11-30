// blank for work with quotes

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

// void		print_echo(char *tmp, char *str, int *i, char **newenv)
// {
// 	if (tmp[0] == '~')
// 	{
// 		free(tmp);
// 		tmp = get_env_var_val(newenv, "HOME");
// 	}
// 	// if (ft_strchr(tmp, '$'))
// 	// 	tmp = change_tmp(tmp, newenv);
// 	nonprint_esc(tmp);
// 	(*i)++;
// 	free(tmp);
// 	if (str)
// 		ft_putchar(' ');
// }