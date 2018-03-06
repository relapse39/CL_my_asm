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
    if (list->ent.com[n][0] == '%')
        i = 0;
    while(list->ent.com[n][++i])
    {
        if (ft_strchr(LABEL_CHARS, list->ent.com[n][++i]) == 0)
        {
            ft_printf("Lexical error at [");
			ft_printf("%d:", list->ent.nbr);
			ft_printf("%d]", ft_get_pos(list->ent.r_line, list->ent.com[n]) + i + 1);
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
        while(list->ent.com[++i])
        {
            if (list->ent.com[i] != NULL)
			{
				if ((list->ent.com[i][0] == ':') ||
						(list->ent.com[i][0] == '%' && list->ent.com[i][1] == ':'))
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
			if (ft_is_label(tmp->ent.com[0])
				&& ft_strequ(list->ent.com[0], tmp->ent.com[0]))
			{
				ft_putstr("error: this label defined more than one time: '");
				ft_putstr(tmp->ent.com[0]);
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
    if (tmp->ent.com[i][0] == ':') {
		flag = 1;
		cmd = tmp->ent.com[i] + 1;
	}
	else
        cmd = tmp->ent.com[i] + 2;
	while (list)
	{
		if (list->ent.com[0] && ft_strncmp(cmd, list->ent.com[0], ft_strlen(cmd)) == 0
			&& (list->ent.com[0][ft_strlen(cmd)] == ':'))
		{
			if (flag == 0)
			{
				tmp_1 = ft_itoa(list->ent.pos - tmp->ent.pos);
				ret = malloc(sizeof(ft_strlen(tmp_1) + 1));
				ret[0] = '%';
				ret[1] = '\0';
				ret = ft_strcat(ret,tmp_1);
				ret[ft_strlen(ret) + 1] = '\0';
				free(tmp_1);
				return (ret);
			}
			return (ft_itoa(list->ent.pos - tmp->ent.pos));
		}
		list = list->next;
	}
    ft_printf("No such label %s", err + 1);
    ft_printf(" while attempting to dereference token [TOKEN]");
    ft_printf("[%03d:", tmp->ent.nbr);
    ft_printf("%d]", ft_get_pos(tmp->ent.r_line, err) + 1);
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
		while(tmp->ent.com[++i])
		{
            if (tmp->ent.com[i] && tmp->ent.com[i][0] == ':'
				&& tmp->ent.com[i][1] )
			{
				error_c = ft_strdup(tmp->ent.com[i]);
				free(tmp->ent.com[i]);
                 tmp->ent.com[i] = ft_get_byte(list, tmp, i,error_c);
				free(error_c);
				if (tmp->ent.com[i] == NULL)
                    return (-1);
			}
			else if ((tmp->ent.com[i] != NULL && tmp->ent.com[i][0] == '%'
				&& tmp->ent.com[i][1] == ':' && tmp->ent.com[i][2]))
			{
				error_c = ft_strdup(tmp->ent.com[i]);
				free(tmp->ent.com[i]);
				tmp->ent.com[i] = ft_get_byte(list, tmp, i, error_c);
				free(error_c);
				if (tmp->ent.com[i] == NULL)
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
