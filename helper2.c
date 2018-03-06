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


int ft_is_label(char *str)
{

	int i;
	if (str == NULL)
		return (0);
	i = -1;
	while (str[++i])
		;
	if (str[i - 1] == ':')
		return (1);
	else
		return (0);
}

int 	ft_atoi_ret( int neg)
{
	if (neg)
		return (0);
	else
		return (2147483647);
}

int		ft_atoi_1(const char *str)
{
	int i;
	uintmax_t   nbr;
	int negative;

	nbr = 0;
	negative = 0;
	i = 0;
	while ((str[i] == '\t') || (str[i] == ' '))
		i++;
	if (str[i] == '-')
		negative = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && (str[i] >= '0') && (str[i] <= '9'))
	{
		nbr *= 10;
		nbr += (int)str[i] - '0';
		if (nbr > MY_LONG_MAX)
			return (ft_atoi_ret(negative));
		i++;
	}
	if (negative == 1)
		return (int)(-nbr);
	else
		return (int)(nbr);
}