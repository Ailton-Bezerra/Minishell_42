/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:46:28 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/23 11:47:10 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// naõ sei em que momento ele retorna com sucesso
void	ft_cd(char **cmd)
{
	const char	*path;
	t_minishell	*ms;

	ms = get_minishell();
	path = getenv("HOME");
	if (!cmd[1])
	{
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return ;
		}
	}
	else
		path = cmd[1];
	if (chdir(path) != 0)
	{
		ms->exit_status = 1;
		perror ("cd");
	}
}
