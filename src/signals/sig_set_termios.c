/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_set_termios.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 02:04:28 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/18 01:21:52 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sig_set_termios(t_term term_type, t_mshell *ms)
{
	if (isatty(STDIN_FILENO) && ms->is_term_set == TRUE)
	{
		if (tcsetattr(STDIN_FILENO, TCSANOW, &ms->term[term_type]) == -1)
		{
			perror("minishell: tcsetattr");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
