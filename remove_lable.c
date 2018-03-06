/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_lable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 14:02:09 by dshevche          #+#    #+#             */
/*   Updated: 2018/03/06 14:02:12 by dshevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "asm.h"

int     ft_check_label_char(line_list *list, int n)
{
    int i;

    i = -1;
    if (list->entry.com[n][0] == '%')
        i = 0;
    while(list->entry.com[n][++i])
    {
        if (ft_strchr(LABEL_CHARS, list->entry.com[n][++i]) == 0)
        {
            ft_printf("Lexical error at [");
			ft_printf("%d:", list->entry.nbr);
			ft_printf("%d]", ft_get_pos(list->entry.raw_line, list->entry.com[n]) + i + 1);
            return (-1);
        }
    }
    return (0);

}



int 	ft_check_lables(line_list *list)
{
    int     i;


    while(list)
    {
		i = -1;
        while(list->entry.com[++i])
        {
            if (list->entry.com[i] != NULL)
			{
				if ((list->entry.com[i][0] == ':') ||
						(list->entry.com[i][0] == '%' && list->entry.com[i][1] == ':'))
					if (ft_check_label_char(list, i) == -1)
						return (-1);
			}
        }
        list = list->next;
    }
    return (0);
}


int 	ft_is_duplicate(line_list *list)
{
	line_list *tmp;

	while(list)
	{
		tmp = list->next;
		while (tmp)
		{
			if (ft_is_label(tmp->entry.com[0])
				&& ft_strequ(list->entry.com[0], tmp->entry.com[0]))
			{
				ft_putstr("error: this label defined more than one time: '");
				ft_putstr(tmp->entry.com[0]);
				ft_putstr("'\n");
				return (-1);
			}
		tmp = tmp->next;
		}
		list = list->next;
	}
	return (0);
}

char *ft_get_byte(line_list *list, line_list *tmp, int i, char *err)
{
	char *cmd;
	int 	flag;
	char *ret;
	char *tmp_1;

	flag = 0;
    if (tmp->entry.com[i][0] == ':') {
		flag = 1;
		cmd = tmp->entry.com[i] + 1;
	}
	else
        cmd = tmp->entry.com[i] + 2;
	while (list)
	{
		if (list->entry.com[0] && ft_strncmp(cmd, list->entry.com[0], ft_strlen(cmd)) == 0
			&& (list->entry.com[0][ft_strlen(cmd)] == ':'))
		{
			if (flag == 0)
			{
				tmp_1 = ft_itoa(list->entry.pos - tmp->entry.pos);
				ret = malloc(sizeof(ft_strlen(tmp_1) + 1));
				ret[0] = '%';
				ret[1] = '\0';
				ret = ft_strcat(ret,tmp_1);
				ret[ft_strlen(ret) + 1] = '\0';
				free(tmp_1);
				return (ret);
			}
			return (ft_itoa(list->entry.pos - tmp->entry.pos));
		}
		list = list->next;
	}
    ft_printf("No such label %s", err + 1);
    ft_printf(" while attempting to dereference token [TOKEN]");
    ft_printf("[%03d:", tmp->entry.nbr);
    ft_printf("%d]", ft_get_pos(tmp->entry.raw_line, err) + 1);
    err[0] == '%' ? ft_printf(" ") :ft_printf(" IN");
    ft_printf("DIRECT_LABEL %s", err);
	return (NULL);
}

int 	ft_redirect_lables(line_list *list)
{
	line_list *tmp;
	int 	i;
	char 	*error_c;

	tmp = list;
	while (tmp)
	{
		i = -1;
		while(tmp->entry.com[++i])
		{
            if (tmp->entry.com[i] && tmp->entry.com[i][0] == ':'
				&& tmp->entry.com[i][1] )
			{
				error_c = ft_strdup(tmp->entry.com[i]);
				free(tmp->entry.com[i]);
                 tmp->entry.com[i] = ft_get_byte(list, tmp, i,error_c);
				free(error_c);
				if (tmp->entry.com[i] == NULL)
                    return (-1);
			}
			else if ((tmp->entry.com[i] != NULL && tmp->entry.com[i][0] == '%'
				&& tmp->entry.com[i][1] == ':' && tmp->entry.com[i][2]))
			{
				error_c = ft_strdup(tmp->entry.com[i]);
				free(tmp->entry.com[i]);
				tmp->entry.com[i] = ft_get_byte(list, tmp, i, error_c);
				free(error_c);
				if (tmp->entry.com[i] == NULL)
					return (-1);
			}

		}
		tmp = tmp->next;
	}
	return (0);
}

int 	ft_remove_labels(line_list *list)
{

	if (ft_check_lables(list) == -1)
		return (-1);
	if (ft_is_duplicate(list) == -1)
		return (-1);
	if (ft_redirect_lables(list) == -1)
		return (-1);
	return (0);
}
