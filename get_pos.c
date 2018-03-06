//
// Created by Admin on 14.02.18.
//

#include "asm.h"

static int 	ft_is_simple_type(char *line)
{
	if (ft_strcmp(line, "lfork") == 0
		||ft_strcmp(line, "fork") == 0
		||ft_strcmp(line, "zjmp") == 0)
		return (3);
	else if (ft_strcmp(line, "live") == 0)
		return (5);
	else
		return (0);

}

static int ft_special_params(char *str, int param)
{
	if ((param == 2 || param == 1)
		&& (ft_strcmp(str, "ldi") == 0 || ft_strcmp(str, "lldi") == 0))
		return (2);
	else if ((param == 2 || param == 3)
			 && (ft_strcmp(str, "sti") == 0))
		return (2);
	else
		return (4);

}


static int	ft_get_special_inst(char **tab, int i, int size)
{
	int param;
	int iter;

	iter = i + 1;
	param = 1;
	while (tab[iter])
	{
		if (tab[iter][0] == 'r')
			size++;
		else if (tab[iter][0] != '%')
			size += 2;
		else if (tab[iter][0] == '%')
			size += ft_special_params(tab[i], param);
		param += 1;
		iter++;
	}
	return (size);
}

static int 	ft_get_inst_pos(line_list *list, int i, int pos)
{

	list->entry.pos = pos;
	if (ft_is_simple_type(list->entry.com[i]) != 0)
	{
		pos += ft_is_simple_type(list->entry.com[i]);
		list->entry.length = pos;
		return (pos);
	}
	pos += 2;
	pos = ft_get_special_inst(list->entry.com, i, pos);
	list->entry.length = pos;
	return (pos);
}

void	ft_get_position(line_list *list)
{
	line_list *tmp;
	int 		pos;
	int 		i;

	tmp = list;
	pos = 0;
	while (tmp)
	{
		i = 0;
		if (*tmp->entry.com != NULL && tmp->entry.com[0][ft_strlen(*tmp->entry.com) - 1] == ':')
		{
			tmp->entry.length = pos;
			tmp->entry.pos = pos;
			i++;
		}
		if (tmp->entry.com[i] && ft_inst_check(tmp->entry.com[i]))
			pos = ft_get_inst_pos(tmp, i, pos);

		tmp = tmp->next;
	}

}