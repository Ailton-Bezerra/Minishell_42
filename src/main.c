/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:16:23 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/04 10:42:06 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*rl;

	while (1)
	{
		rl = readline("MINISHEL > ");
		if (!rl)
		{
			printf("exiting\n");
			break ;
		}
		if (*rl)
			add_history(rl);
		printf("%s\n", rl);
		free(rl);
	}
	rl_clear_history();
	return (0);
}
