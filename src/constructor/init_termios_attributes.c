/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termios_attributes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 23:27:57 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/17 09:51:52 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the current terminal attributes from STDIN_FILENO.
 * 
 * @note That function set common default flags in case terminal device was 
 * modified befor.
 * 
 * Input flags (c_iflag):
 * - Enable ICRNL: converts carriage returns (CR) into newlines (NL) on input.
 * - Disable INLCR: Do not map NL to CR on input.
 * - Disable IGNCR: Do not ignore carriage returns.
 * 
 * Output flags (c_oflag):
 * - Enable OPOST: Turn on output post-processing.
 * - Enable ONLCR: Map newline to carriage return + newline on output.
 * - Disable OCRNL: Do not map carriage return to newline on output.
 * 
 * Local flags (c_lflag):
 * - ECHOCTL: This stops the terminal from echoing control characters 
 *   (like Ctrl+C as "^C"). Do disabled by default and enable before executing
 *   commands.
 * 
 * @param ms Pointer to the minishell structure containing the shell state.
 * @return int Returns 0 on success, or an error code on failure.
 */
int	init_termios_attributes(t_mshell *ms)
{
	if (isatty(STDIN_FILENO))
	{
		if (tcgetattr(STDIN_FILENO, &ms->term[TERM_ORIGIN]) != 0)
		{
			perror("minishell: tcgetattr");
			exit(EXIT_FAILURE);
		}
		ms->term[TERM_ORIGIN].c_iflag |= ICRNL;
		ms->term[TERM_ORIGIN].c_iflag &= ~INLCR;
		ms->term[TERM_ORIGIN].c_iflag &= ~IGNCR;
		ms->term[TERM_ORIGIN].c_oflag |= OPOST;
		ms->term[TERM_ORIGIN].c_oflag |= ONLCR;
		ms->term[TERM_ORIGIN].c_oflag &= ~OCRNL;
		ms->term[TERM_ORIGIN].c_lflag &= ~(ECHOCTL);
		if (tcsetattr(STDIN_FILENO, TCSANOW, &ms->term[TERM_ORIGIN]) == -1)
		{
			perror("minishell: tcsetattr");
			exit(EXIT_FAILURE);
		}
		ms->term[TERM_ECHOCTL] = ms->term[TERM_ORIGIN];
		ms->term[TERM_ECHOCTL].c_lflag |= ECHOCTL;
	}
	return (EXIT_SUCCESS);
}
