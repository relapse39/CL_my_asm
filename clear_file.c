/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 14:00:58 by dshevche          #+#    #+#             */
/*   Updated: 2018/03/06 14:00:59 by dshevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "asm.h"

int			ft_is_delete(char **com)
{
	if (com[0] == NULL)
		return (1);
	if (com[0] != NULL  && (ft_strcmp(com[0], NAME_CMD_STRING) == 0
							|| ft_strcmp(com[0], COMMENT_CMD_STRING) == 0
							|| ft_is_label(com[0])))
		return (1);
	else
		return (0);
}

line_list   	*ft_remove(line_list *list)
{
	int 	i;

	i = -1;
	if (list == NULL)
		return (NULL);
	if (ft_is_delete(list->ent.com))
	{
		line_list *tmp;
		tmp = list->next;
		free(list->ent.r_line);
		while(list->ent.com[++i])
			free(list->ent.com[i]);
		free(list->ent.com[i]);
		free(list->ent.com);
		free(list);
		return (tmp);
	}
	list->next = ft_remove(list->next);
	return (list);

}

int 		ft_got_thresh(line_list *list)
{
	while(list)
	{
		if (ft_is_delete((list->ent.com)))
			return (1);
		list = list->next;
	}
	return (-1);
}



void		ft_clear(line_list *list)
{
	int i;
	int j;
	int k;
	char *new_s = NULL;
	while (list)
	{
		i = 0;
		j = 0;
		if (ft_is_label(list->ent.com[0]) &&
				list->ent.com[1] != NULL)
		{
			while(list->ent.com[i] != NULL)
			{
				while(list->ent.com[i][j] != 0)
					j++;
				i++;
			}
			new_s = malloc(sizeof(j + i));
			i = 1;
			k = 0;
			while(list->ent.com[i] != NULL)
			{
				j = 0;
				while(list->ent.com[i][j] != 0)
				{
					new_s[k] = list->ent.com[i][j];
					j++;
					k++;
				}
				new_s[k] = ' ';
				k++;
				i++;
			}
			new_s[k] = '\0';
			i = 0;
			while(list->ent.com[i])
			{
				free(list->ent.com[i]);
				i++;
			}
			free(list->ent.com[i]);
			free(list->ent.com);
			list->ent.com = ft_strsplit(new_s, ' ');
			free(new_s);


		}
		list = list->next;
	}
}

void		ft_clear_list(line_list **list)
{
//	int 	i;
//	line_list *tmp;
//
//	tmp = *list;
//	while (tmp)
//	{
//		i = -1;
//		if (ft_is_label(tmp->ent.com[0]) &&
//			tmp->ent.com[1] != NULL)
//		{
//			while(tmp->ent.com[++i] && tmp->ent.com[i + 1])
//			{
//				ft_strdel(&tmp->ent.com[i]);
//				tmp->ent.com[i] = ft_strdup(tmp->ent.com[i + 1]);
//
//			}
//			ft_strdel(&tmp->ent.com[i]);
//		}
//		tmp = tmp->next;
//	}
	ft_clear(*list);
	while (ft_got_thresh(*list) == 1)
		*list = ft_remove(*list);

}
