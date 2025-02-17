/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_set_termios.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 02:04:28 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/17 02:33:43 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sig_set_termios(struct termios *term)
{
	if (isatty(STDIN_FILENO))
	{
		if (tcsetattr(STDIN_FILENO, TCSANOW, term) == -1)
		{
			perror("minishell: tcsetattr");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
