/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:30:06 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/23 18:04:59 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_outfile_fd(t_token *token, char *filename)
{
	int		fd;
	
	fd = -1;
	if (token->type == APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (token->type == TRUNC)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

int	get_infile_fd(t_token *token, char *filename)
{
	int		fd;
	
	fd = -1; 
	if (token->type == INPUT && ft_strncmp(filename, "error", 6))
		fd = open(filename, O_RDONLY);
	return (fd);
}

int	redirect_fds(t_command *cmd)
{
	if (cmd->infile_fd >= 0)
	{
		dup2(cmd->infile_fd, STDIN_FILENO);
		close(cmd->infile_fd);
	}
	if (cmd->outfile_fd >= 0)
	{
		dup2(cmd->outfile_fd, STDOUT_FILENO);
		close(cmd->outfile_fd);
	}
	return (1);
}

void	close_redirects(t_command *cmd)
{
	if (cmd->outfile_fd > 2)
		close(cmd->infile_fd);
	if (cmd->outfile_fd > 2)
		close(cmd->outfile_fd);
}