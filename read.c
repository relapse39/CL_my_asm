/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 13:59:22 by dshevche          #+#    #+#             */
/*   Updated: 2018/03/06 16:33:56 by dshevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					check_cmd_lable(char *s, char *cmd, int pos, int *nbr)
{
	pos += skip_wspcs(s);
	if (!ft_strcmp(cmd, s + pos))
		exit(ft_printf("Syntax error on raw %d, symbol %d\n",
							(*nbr), ft_strlen(cmd) + pos));
	pos += ft_strlen(cmd);
	pos += skip_wspcs(s + pos);
	if (s[pos] != 34 && s[pos] != '\0')
		exit(ft_printf("Syntax error on raw %d, symbol %d\n",
					(*nbr), pos));
	else if (s[pos] == '\0')
		exit(ft_printf("Break line %d, symbol %d\n",
				(*nbr) + 1, 0));
	return (pos + 1);
}

static char			*get_the_fucking_ptr(char *s, int i, int *nbr, char **res)
{
	char			*ptr;
	int				r;

	ptr = ft_strchr(s + i, 34);
	if (ptr == NULL)
		(*res) = ft_strjoin(s + i, "\n");
	else
	{
		if ((r = check_eos(ptr + 1)) != 0)
			exit(ft_printf("Syntax error on raw %d, symbol %d\n",
					(*nbr), i + r));
		(*res) = ft_strsub(s + i, 0, ptr - (s + i));
		ft_strdel(&s);
		return (ptr);
	}
	return (ptr);
}

char				*set_name(char *s, int fd, int *nbr, char *cmd)
{
	int				r;
	char			*ptr;
	char			*res;

	if ((ptr = get_the_fucking_ptr(s,
					check_cmd_lable(s, cmd, 0, nbr), nbr, &res)))
		return (res);
	while (ptr == NULL)
	{
		ft_strdel(&s);
		if ((r = get_next_line(fd, &s)) < 0)
			M_ERROR(-1, "Reading error\n");
		else if (r == 0)
			exit(ft_printf("There is no %s at all\n", cmd + 1));
		(*nbr)++;
		ptr = some_modifying(&res, s);
	}
	if ((r = check_eos(ptr + 1)) != 0)
		exit(ft_printf("Syntax error on raw %d, symbol %d\n",
					(*nbr), r));
	some_modifying_two(s, ptr, &res);
	return (res);
}

void				ft_read_n_c(char *s, t_main *main, int fd, int *nbr)
{
	if (ft_strstr(s, ".name") && main->name == NULL)
		main->name = set_name(s, fd, nbr, ".name");
	else if (ft_strstr(s, ".name"))
		M_ERROR(-1, "a name already exist");
	else if (ft_strstr(s, ".comment") && main->comment == NULL)
		main->comment = set_name(s, fd, nbr, ".comment");
	else if (ft_strstr(s, ".comment"))
		M_ERROR(-1, "a comment already exist");
	else
		M_ERROR(-1, "Not a valid sequence");
}


void			ft_add_space3(char **str)
{
	int 		i;
	int 		j;
	char		*res;

	i = 0;
	res = ft_strnew(ft_strlen(*str) + 2);
	while((*str)[i] != ':' && (*str)[i] != '%')
	{
		res[i] = (*str)[i];
		i++;
	}
	res[i] = ' ';
	j = i;
	i++;
	while((*str)[j])
	{
		res[i] = (*str)[j];
		i++;
		j++;
	}
	res[i] = '\0';
	free(*str);
	*str = res;
}

void 			ft_skip_stuff(int *i, int *j, int *k, char **str)
{
	*i = 0;
	*k = 0;
	while((*str)[*i] != 0 && ((*str)[*i] == '\t' || (*str)[*i] == ' '))
		(*i)++;
	*j = *i;
	while((*str)[*i] != '%' && (*str)[*i] != 0)
		(*i)++;
}

void			ft_add_space2(char **str)
{
	int 		i;
	int 		j;
	char 		*tmp;
	int 		k;

	ft_skip_stuff(&i, &j, &k, str);
	if ((*str)[i] == ' ' || (*str)[i] == '\t')
		return;
	if (i < (int)ft_strlen(*str) - 1)
	{
		tmp = ft_strnew(i + 2);
		while (j < i)
			tmp[k++] = (*str)[j++];
		tmp[k] = '\0';
		i = 0;
		while(g_op_tab[i].name)
			if (ft_strequ(tmp, g_op_tab[i++].name))
			{
				ft_add_space3(str);
				free(tmp);
				return;
			}
		free(tmp);
	}
}

void			ft_add_space(char **str)
{
	char 		*tmp;
	int 		i;

	i = 0;
	if(ft_is_label(*str))
	{
		tmp = ft_strnew(ft_strlen(*str) + 2);
		while((*str)[i])
		{
			tmp[i] = (*str)[i];
			i++;
		}
		tmp[i] = ' ';
		tmp[i + 1] = '\0';
		free(*str);
		*str = tmp;
	}
	else
		ft_add_space2(str);
}

int					ft_check_len(t_main *main)
{
	if (ft_strlen(main->comment) > COMMENT_LENGTH)
	{
		ft_printf("Champion comment too long (Max length 2048)\n");
		return (-1);
	}
	else if (ft_strlen(main->name) > PROG_NAME_LENGTH)
	{
		ft_printf("Champion name too long (Max length 128)\n");
		return (-1);
	}
	return (0);
}

int					ft_read_file(char *name, t_line_list **list, t_main *main)
{
	int			fd;
	char		*str;
	int			nbr;

	*list = NULL;
	nbr = 0;
	if ((fd = open(name, O_RDONLY)) == -1)
		return (ft_err("open", -1));
	while ((get_next_line(fd, &str)))
	{
		nbr++;
		if (ft_is_empty(str) == 0)
		{
			if (main->name == NULL || main->comment == NULL)
				ft_read_n_c(str, main, fd, &nbr);
			else if (read_helper(list, &str, &nbr) == -1)
				return (-1);
		}
	}
	close(fd);
	free(str);
	if (*list == NULL)
		return (ft_err("empty", -1));
	return (ft_check_len(main));
}


