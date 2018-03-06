/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 14:01:51 by dshevche          #+#    #+#             */
/*   Updated: 2018/03/06 14:01:52 by dshevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "asm.h"

int 	ft_skip_spaces(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

static int		ft_get_name(line_list *list, t_main *main)
{
	int 		i;
	int 		j;

	j = 0;
	i = 1;
	if ((main->name = (char*)malloc((int)ft_strlen(list->entry.com[1]) + 1)) == NULL)
		return (ft_err("malloc", -1));
	while(i < (int)ft_strlen(list->entry.com[1]) - 1)
	{
		main->name[j] = list->entry.com[1][i];
		i++;
		j++;
	}
	main->name[i] = '\0';
	return (0);
//	int i;
//
//	i = 5;
//	i = ft_skip_spaces(line, i);
//	if (line[i] == 0 || line[i++] != '"')
//		return (-1);
//	line = line + i;
//	i = -1;
//	while (line[++i] != '"' && line[i])
//		;
//	if ((main->name = (char*)malloc(i + 1)) == NULL)
//		return (ft_err("malloc", -1));
//	i = -1;
//	while (line[++i] && line[i] != '"')
//		main->name[i] = line[i];
//	main->name[i] = 0;
//	while (line[++i])
//		if (line[i] != '\t' && line[i] != ' ')
//			return (ft_err("name", -1));
//	return (0);
}


static int		ft_get_comment(line_list *list, t_main *main)
{
	int 		i;
	int 		j;

	j = 0;
	i = 1;
	if ((main->comment = (char*)malloc((int)ft_strlen(list->entry.com[1]) + 1)) == NULL)
		return (ft_err("malloc", -1));
	while(i < (int)ft_strlen(list->entry.com[1]) - 1)
	{
		main->comment[j] = list->entry.com[1][i];
		i++;
		j++;
	}
	main->comment[i] = '\0';
	return (0);
}



int 	ft_read_comment(line_list *list, t_main *main)
{
	line_list *tmp;

	tmp = list;
	while(tmp && tmp->entry.com[0] && ft_strcmp(tmp->entry.com[0], ".comment") != 0)
		tmp = tmp->next;
	if (tmp && tmp->entry.com[0] && tmp->entry.com[1])
		if (ft_get_comment(tmp, main) == -1)
			return (-1);
	return (0);
}



int 	ft_is_got_name_commnet(line_list *list)
{
	int 		is_err;
	line_list 	*tmp;

	tmp = list;
	is_err = 0;
	while(list)
	{
		if (list->entry.com[0] && ft_strcmp(list->entry.com[0], ".comment") == 0)
			is_err++;
		if (list->entry.com[0] && ft_strcmp(list->entry.com[0], ".name") == 0)
			is_err++;
		list = list->next;
	}
	if (is_err < 2)
	{
		while(tmp->entry.com[0] == NULL || tmp->entry.com[0][0] == '.')
			tmp = tmp->next;
		ft_printf("Syntax error at token [TOKEN][%03d", tmp->entry.nbr);
		ft_printf(":%03d",ft_get_pos(tmp->entry.raw_line, tmp->entry.com[0]) + 1);
		ft_printf("] %s \"%s\"", ft_get_l_i_str(tmp->entry.com[0]), tmp->entry.com[0]);
		return (-1);
	}
	return (0);
}

int 	is_space(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (1);
	while(str[i])
	{
		if(str[i] != ' ')
			return (-1);
		i++;
	}
	return (1);
}


int 	ft_put_nc_error(int n1, int n2)
{
	ft_printf("Syntax error at token [TOKEN]");
	ft_printf("[%03d:", n1);
	ft_printf("%03d] ENDLINE", n2 + 1);
	return (-1);
}

int 	ft_is_no_name_comment(line_list *list)
{
	int 	tmp;

	tmp = 0;
	while(list)
	{
		if ((list->entry.com[0] && ft_strcmp(list->entry.com[0], ".comment") == 0)
				||(list->entry.com[0] && ft_strcmp(list->entry.com[0], ".name") == 0))
		{
			if (list->entry.com[1] == NULL)
			{
				if (is_space(list->next->entry.raw_line) == 1)
				{
					list=list->next;
					while(is_space(list->next->entry.raw_line) == 1)
						list = list->next;
					return(ft_put_nc_error(list->entry.nbr,(int)ft_strlen(list->entry.raw_line)));
				}
				else
					return(ft_put_nc_error(list->entry.nbr,(int)ft_strlen(list->entry.raw_line)));

//				while(list)
//				{
//
//					if (is_space(list->entry.raw_line) != 1)
//					{
//						ft_printf("Syntax error at token [TOKEN]");
//						ft_printf("[%03d:", list->entry.nbr);
//						ft_printf("%03d] ENDLINE", ft_strlen(list->entry.raw_line));
//						return (-1);
//					}
//					tmp = (int)ft_strlen(list->entry.raw_line);
//					list = list->next;
//				}
			}
		}
		list = list->next;
	}
	return (0);
}

int 	ft_check_dot(line_list *list)
{
	while(list)
	{
		if (list->entry.com[0] && ft_strcmp(list->entry.com[0], ".comment") != 0 &&
			ft_strcmp(list->entry.com[0], ".name") != 0 &&
			list->entry.com[0][0] == '.')
		{
			ft_printf("Lexical error at [%d:",list->entry.nbr);
			ft_printf("%d]", ft_get_pos(list->entry.raw_line,list->entry.com[0]) + 1);
			return (-1);
		}
		list = list->next;
	}
	return (0);
}

int 	ft_check_quotes(line_list *list)
{
	while(list)
	{
		if (list->entry.com[0] && (ft_strcmp(list->entry.com[0], ".comment") == 0 ||
				ft_strcmp(list->entry.com[0], ".name") == 0))
		{
			if (list->entry.com[1] && list->entry.com[1][0] != '"')
			{
				ft_printf("Lexical error at [%d:",list->entry.nbr);
				ft_printf("%d]", ft_get_pos(list->entry.raw_line,list->entry.com[1]) + 1);
				return (-1);
			}
			if (list->entry.com[1] && list->entry.com[1][ft_strlen(list->entry.com[1]) - 1] != '"')
			{
				ft_printf("Syntax error at token [TOKEN]");
				ft_printf("[%03d:", list->entry.nbr);
				ft_printf("%03d] END \"(null)\"", ft_strlen(list->entry.raw_line));
				return (-1);
			}
		}
		list = list->next;
	}
	return (0);
}

char 	*ft_get_type(char *str)
{
	int 	i;
	int 	err;

	i = 0;
	err = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			err++;
		i++;
	}
	if (err == 0)
		return ("INDIRECT");
	if (str[0] == 'r')
		return("REGISTER");
	else if (str[0] == ':')
		return ("INDIRECT_LABEL");
	else if (str[0] == '%')
		return ("DIRECT");
	else if (ft_strcmp(str, COMMENT_CMD_STRING) == 0)
		return ("COMMAND_COMMENT");
	else if (ft_strcmp(str, NAME_CMD_STRING) == 0)
		return ("COMMAND_NAME");
	else
		return ("INSTRUCTION");

//	else if(ft_isalnum(str))
//		return ("INDIRECT");
//	else
//		return ("INSTRUCTION");

}

int 	ft_check_quotes_two(line_list *list)
{
	while(list)
	{
		if (list->entry.com[0] && (ft_strcmp(list->entry.com[0], ".comment") == 0 ||
								   ft_strcmp(list->entry.com[0], ".name") == 0))
		{
			if (list->entry.com[1] && list->entry.com[1][0] != '"' &&
					list->entry.com[1] &&
					list->entry.com[1][ft_strlen(list->entry.com[1]) - 1] != '"')
			{
				ft_printf("Syntax error at token [TOKEN]");
				ft_printf("[%03d:", list->entry.nbr);
				ft_printf("%03d]", ft_get_pos(list->entry.raw_line, list->entry.com[1]) + 1);
				ft_printf(" %s \"%s\"", ft_get_type(list->entry.com[1]),list->entry.com[1]);

				return (-1);
			}
		}

		list = list->next;
	}
	return (0);
}

int 	ft_two_n_c(line_list *list)
{
	int 	i;
	int 	j;

	i = 0;
	j = 0;
	while(list)
	{
		if (list->entry.com[0] && (ft_strcmp(list->entry.com[0], ".name") == 0))
			i++;
		if (list->entry.com[0] && (ft_strcmp(list->entry.com[0], ".comment") == 0))
			j++;
		if (i > 1 || j > 1)
		{
			ft_printf("Syntax error at token [TOKEN]");
			ft_printf("[%03d:", list->entry.nbr);
			ft_printf("%03d]", ft_get_pos(list->entry.raw_line, list->entry.com[0]) + 1);
			ft_printf(" %s %s", ft_get_type(list->entry.com[0]),list->entry.com[1]);
			return (-1);
		}


		list= list->next;
	}
	return (0);
}

int 	ft_read_name(line_list *list, t_main *main)
{
	line_list *tmp;

	tmp = list;
	if (ft_is_no_name_comment(list) == -1)
		return (-1);
	if (ft_check_quotes_two(list) == -1)
		return (-1);
	if (ft_check_quotes(list) == -1)
		return (-1);
	if(ft_check_dot(list) == -1)
		return (-1);
	if(ft_is_got_name_commnet(list) == -1)
		return (-1);
	if(ft_two_n_c(list) == -1)
		return (-1);
	while(tmp && ft_strcmp(tmp->entry.com[0], ".name") != 0)
		tmp = tmp->next;
	if (tmp && tmp->entry.com[0] && tmp->entry.com[1])
		if(ft_get_name(list, main) == -1)
			return (-1);
	return (0);
}
