/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:50:26 by hiono             #+#    #+#             */
/*   Updated: 2024/04/16 22:45:59 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

// double slash does not clash
char	*ft_strdirjoin(char	*s1, char *s2)
{
	char	*res;
	char	*tmp;

	tmp = ft_strjoin(s1, "/");
	res = ft_strjoin(tmp, s2);
	free(tmp);
	return (res);
}	

char	**get_evnp_path(char **envp)
{
	char	*envp_path_str;
	char	**envp_path;

	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
			envp_path_str = *envp + 5;
		envp++;
	}
	envp_path = ft_split(envp_path_str, ':');
	return (envp_path);	
}

int	cnt_args(char *cmd)
{
	int	i;

	i = 0;
	while (*cmd)
	{
		while (*cmd == ' ')
			cmd++;
		if (*cmd && *cmd != ' ')
			i++;
		while (*cmd && *cmd != ' ')
		{
			if (*cmd == '\'')
				cmd = ft_strchr(cmd + 1, '\'');
			else if (*cmd == '\"')
				cmd = ft_strchr(cmd + 1, '\"');
			cmd++;
		}
	}
	return (i);
}

char	*trim_quotes(char *str)
{
	int		len;
	char	*res;

	len = ft_strlen(str);
	res = str;
	if (str[0] == '\'' && str[len - 1] == '\'')
	{
		res = ft_strtrim(str, "\'");
		free(str);
	}
	else if (str[0] == '\"' && str[len - 1] == '\"')
	{
		res = ft_strtrim(str, "\"");
		free(str);
	}
	return (res);
}

char	**split_cmd(char *cmd)
{
	int		i;
	int		len;
	char	*str;
	char	**strs;
	char	*wstart;

	len = cnt_args(cmd);
	strs = malloc((len + 1) * sizeof(char *));
	i = 0;
	while (i < len)
	{
		while (*cmd == ' ')
			cmd++;
		wstart = cmd;
		while (*cmd && *cmd != ' ')
		{
			if (*cmd == '\'')
				cmd = ft_strchr(cmd + 1, '\'');
			else if (*cmd == '\"')
				cmd = ft_strchr(cmd + 1, '\"');
			cmd++;
		}
		str = ft_substr(wstart, 0, cmd - wstart);
		strs[i] = trim_quotes(str);
		i++;
	}
	strs[i] = NULL;
	return (strs);
}

