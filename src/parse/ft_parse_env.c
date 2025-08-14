/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:57:11 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/14 13:49:42 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipe.h"
#include "ft_settings.h"
#include "libft.h"
#include "ft_utils.h"
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
	return (NULL);
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
	if (access(cmd, F_OK) == 0)
		return (ft_free_split(paths), ft_strdup(cmd));
	i = 0;
	while (paths[i])
	{
		full_path = ft_join_path(paths[i], cmd);
		if (access(full_path, F_OK) == 0)
		{
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
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
		if (!path)
			return (0);
		pipe->cmdname = path;
		current = current->next;
	}
	return (1);
}
