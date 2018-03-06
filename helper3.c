//
// Created by Daniil Shevchenko on 3/6/18.
//

#include "asm.h"

int 	ft_check_lables(line_list *list)
{
	int     i;


	while(list)
	{
		i = -1;
		while(list->ent.com[++i])
		{
			if (list->ent.com[i] != NULL)
			{
				if ((list->ent.com[i][0] == ':') ||
					(list->ent.com[i][0] == '%'
					 && list->ent.com[i][1] == ':'))
					if (ft_check_label_char(list, i) == -1)
						return (-1);
			}
		}
		list = list->next;
	}
	return (0);
}