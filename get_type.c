/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 14:01:22 by dshevche          #+#    #+#             */
/*   Updated: 2018/03/06 14:01:23 by dshevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "asm.h"




void	ft_add_type(line_list *line,  int com_n, int type)
{
	if (com_n == 0)
		line->ent.first_type = type;
	else if (com_n == 1)
		line->ent.second_type = type;
	else if (com_n == 2)
		line->ent.third_type = type;
}


int 	ft_is_reg(char *str)
{
	int 	i;

	i = 0;
	if (str[0] != 'r')
		return (-1);
	str++;
	while(str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (1);
}

int 	ft_is_dir(char *str)
{
	int i;

	i = 0;
	if (str[0] != '%')
		return (-1);
	str++;
	if (str[0] == ':')
		return (1);
	if (str[0] == '-')
		str++;
	while(str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (1);
}

int 	ft_is_ind(char *str)
{
	int 	i;

	i = 0;
	if(str[0] == ':')
		return (1);
	if (str[0] == '-')
		str++;
	while(str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (1);
}

int 	ft_is_inst(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (!ft_isalnum(str[i]))
			return (-1);
		i++;
	}
	return (1);
}

int		ft_get_type_param(line_list *line)
{
	int		i;
	int		com_n;

	while (line)
	{
		com_n = 0;
		i = 0;
		if (line->ent.com[0]!= NULL && line->ent.com[0][ft_strlen(line->ent.com[0]) - 1] == ':')
			i++;
		i++;
		while (line->ent.com[i - 1] && line->ent.com[i])
		{
			if (ft_is_reg(line->ent.com[i]) == 1)
				ft_add_type(line, com_n, T_REG);
			else if (ft_is_dir(line->ent.com[i]) == 1)
				ft_add_type(line, com_n, T_DIR);
			else if (ft_is_ind(line->ent.com[i]) == 1)
				ft_add_type(line, com_n, T_IND);
			else if (ft_is_inst(line->ent.com[i]) == 1)
				ft_add_type(line, com_n, INST);
			else
				ft_add_type(line, com_n, 10);
			i++;
			com_n++;
		}
		line->ent.args_n = com_n;
		line = line->next;
	}
	return (0);
}
