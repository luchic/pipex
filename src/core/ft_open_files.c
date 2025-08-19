/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:31:20 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/19 16:41:38 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "libft.h"
#include "ft_printf.h"
#include "ft_validate.h"
#include "ft_settings.h"

void	fd_open_files(int *fd_in, int *fd_out, char *input_file,
	char *output_file)
{
	*fd_in = open(input_file, O_RDONLY);
	if (*fd_in == -1)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s: %s\n", PIPEX, input_file,
			strerror(errno));
	}
	ft_validate_write_file(output_file);
	*fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_out == -1)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s: %s\n", PIPEX, output_file,
			strerror(errno));
		close(*fd_in);
		exit(NOT_EXIST_ERROR);
	}
}

static int	ft_is_limiter(char *line, char *del)
{
	char	*tmp;

	if (!line)
		return (1);
	if (ft_strchr(line, '\n'))
		tmp = ft_substr(line, 0, ft_strlen(line) - 1);
	else
		tmp = ft_strdup(line);
	if (!tmp)
		return (1);
	if (del[0] != '\0' && !ft_strcmp(tmp, del))
		return (free(tmp), 1);
	if (del[0] == '\0' && (!ft_strcmp(tmp, "\n") || !ft_strcmp(tmp, "")))
		return (free(tmp), 1);
	free(tmp);
	return (0);
}

static void	ft_write_data_to_std(char *del, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (ft_is_limiter(line, del))
			break ;
		ft_printf_fd(fd, "%s", line);
		free(line);
	}
	free(line);
}

void	ft_open_here_doc(char *delimiter, char *output_file, int *fd_in,
	int *fd_out)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", PIPEX, PIPE_ERROR);
		exit(EXIT_FAILURE);
	}
	ft_write_data_to_std(delimiter, fd[1]);
	*fd_in = fd[0];
	close(fd[1]);
	*fd_out = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd_out == -1)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s: %s\n", PIPEX, output_file,
			strerror(errno));
		close(*fd_in);
		exit(NOT_EXIST_ERROR);
	}
}
