/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:57:11 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/19 18:50:56 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse.h"
#include "ft_pipe.h"
#include "ft_printf.h"
#include "ft_settings.h"
#include "ft_utils.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	*ft_getenv(char **envp)
{
	if (!envp)
		return (NULL);
	while (*envp)
	{
		if (ft_strncmp(*envp, PATH, ft_strlen(PATH)) == 0)
			return (*envp + ft_strlen(PATH));
		envp++;
	}
	envp = ft_default_getenv();
	return (envp[0] + ft_strlen(PATH));
}

char	**ft_getenv_paths(char **envp)
{
	char	*path_value;

	path_value = ft_getenv(envp);
	if (!path_value)
		return (NULL);
	return (ft_split(path_value, PATH_DELIM));
}

static char	*ft_join_path(char *path, char *cmd)
{
	char	*full_path;
	char	*tmp;

	if (!path || !cmd)
		return (NULL);
	full_path = ft_strjoin(path, "/");
	if (!full_path)
		return (NULL);
	tmp = ft_strjoin(full_path, cmd);
	free(full_path);
	if (!tmp)
		return (NULL);
	return (tmp);
}

static char	*ft_parce_env(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (!cmd || !envp)
		return (NULL);
	paths = ft_getenv_paths(envp);
	if (!paths)
		return (NULL);
	if (cmd[0] == '.' && access(cmd, F_OK) != 0)
		return (ft_free_split(paths), NULL);
	else if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0)
		return (ft_free_split(paths), ft_strdup(cmd));
	i = 0;
	while (paths[i])
	{
		full_path = ft_join_path(paths[i], cmd);
		if (!full_path)
			return (ft_free_split(paths), NULL);
		if (access(full_path, F_OK) == 0)
			return (ft_free_split(paths), full_path);
		free(full_path);
		i++;
	}
	return (ft_free_split(paths), NULL);
}

int	ft_set_progname(t_list *cmds, char **envp)
{
	t_pipe	*pipe;
	t_list	*current;
	char	*path;

	if (!cmds || !envp)
		return (0);
	current = cmds;
	while (current)
	{
		pipe = (t_pipe *)current->content;
		path = ft_parce_env(pipe->args[0], envp);
		pipe->to_exec = 1;
		if (!path)
			pipe->to_exec = 0;
		pipe->cmdname = path;
		current = current->next;
	}
	return (1);
}
