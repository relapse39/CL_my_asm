/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 13:58:58 by dshevche          #+#    #+#             */
/*   Updated: 2018/03/06 13:59:00 by dshevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "asm.h"

void        ft_print_n_err(void)
{
    ft_printf("Syntax error - unexpected end of input ");
    ft_printf("(Perhaps you forgot to end with a newline ?)");
}
