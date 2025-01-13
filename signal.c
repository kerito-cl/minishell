/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:49:11 by mquero            #+#    #+#             */
/*   Updated: 2025/01/13 18:52:28 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

sig_atomic_t g_signal = 0;

void slash_signal(int sig)
{
    sig = 0;
    g_signal = 3;

}

void continue_signal(int sig)
{
    sig = 0;
    g_signal = 1;

}

int hook_signal(void)
{
    if (g_signal == 1)
    {
        write (1, "\n", 1);
        rl_on_new_line();  
        rl_redisplay();
        g_signal = 0;
    }
    if (g_signal == 3)
    {
        g_signal = 0;
        return 0;
    }
    return 0;

}