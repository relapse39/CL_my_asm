//
// Created by Admin on 13.02.18.
//

#include <CoreFoundation/CoreFoundation.h>
#include "asm.h"

static line_list	*create_file(char *line, int nbr)
{
	line_list	*new;


	if ((new = (line_list*)malloc(sizeof(line_list))))
	{
		new->entry.raw_line = line;
		if ((new->entry.com = ft_split_cmd(line)) == NULL)
			return (NULL);
		new->entry.args_n = 0;
		new->entry.first_type = 0;
		new->entry.second_type = 0;
		new->entry.third_type = 0;
		new->entry.pos = 0;
		new->entry.length = 0;
		new->next = NULL;
		new->entry.nbr = nbr;
	}
	else
	{
		ft_putstr("error: malloc\n");
		return (NULL);
	}
	return (new);
}

//int check_quotes(char *s)
//{
//	int i;
//	int j;
//
//	i = 0;
//	j = 0;
//	while (s[i])
//	{
//		if (s[i] == '"')
//			j++;
//	}
//	return (j);
//}
//
#define SKIP " /t/n/v/r"
//
//int	check_endofstr(char *str)
//{
//	int i;
//	int j;
//
//	i = ft_strlen(str);
//	while (str[j])
//	{
//		if (ft_strchr(SKIP, str[j]))
//			j++;
//		else
//			break ;
//	}
//	if (i != j)
//		return (j);
//	return (0);
//}
//
//char	*dochitat(int fd, int *nbr, char *str)
//{
//	char *s;
//	char *s1;
//
//	s1 = ft_strjoin("", str);
//	while (get_next_line(fd, &s))
//	{
//		s1 = ft_strjoin(s1, s);
//		(*nbr)++;
//		if (ft_strchr(s1, 34))
//		{
//			if (!check_endofstr(ft_strchr(s1, 34) + 1))
//				return (s1);
//			break ;
//		}
//		else
//			s =
//	}
//	s = ft_strjoin(str, s);
//}
//


//char 	*cut_string(char *s, int pos, )
//{
//
//}

int 	check_eos(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t')
			i++;
		else
			return (1);
	}
	return (0);
}

int		skip_wspcs(char *s)
{
	int i;

	i = 0;
	while(s[i])
	{
		if (s[i] == ' ' || s[i] == '\t')
			i++;
		else
			break;
	}
	return (i);
}

int	check_cmd_lable(char *s, char *cmd, int pos, int *nbr)
{
	pos += skip_wspcs(s);
	if (!ft_strcmp(cmd, s + pos))
		exit(ft_printf("Syntax error on raw %d, symbol %d",
					   (*nbr), ft_strlen(cmd) + pos));
	pos += ft_strlen(cmd);
	pos += skip_wspcs(s + pos);
	if (s[pos] != 34 && s[pos] != '\0')
		exit(ft_printf("Syntax error on raw %d, symbol %d",
					   (*nbr), pos));
	else if (s[pos] == '\0')
		exit(ft_printf("Break line %d, symbol %d",
					   (*nbr) + 1, 0));
	return (pos + 1);
}



char 	*set_name(char *s, int fd, int *nbr, char *cmd)
{
	int i;
	int r;
	char *ptr;
	char *res;
	char *tmp;



	i = check_cmd_lable(s, cmd, 0, nbr);
	ptr = ft_strchr(s + i, 34);
	if (ptr == NULL)
		res = ft_strjoin(s + i, "\n");
	else
	{
		if ((r = check_eos(ptr + 1)) != 0)
			exit(ft_printf("Syntax error on raw %d, symbol %d",
						   (*nbr), i + r));
		res = ft_strsub(s + i, 0, ptr - (s + i));
		ft_strdel(&s);
		return (res);
	}
	while (ptr == NULL)
	{
		ft_strdel(&s);
		if ((r = get_next_line(fd, &s)) < 0)
			M_ERROR(-1, "Reading error");
		else if (r == 0)
			exit(ft_printf("There is no %s at all", cmd + 1));
		(*nbr)++;
		ptr = ft_strchr(s, 34);
		if (ptr == NULL)
		{
			tmp = res;
			res = ft_strjoin(res, s);
			ft_strdel(&tmp);
			tmp = res;
			res = ft_strjoin(res, "\n");
			ft_strdel(&tmp);
		}
	}
		if ((r = check_eos(ptr + 1)) != 0)
			exit(ft_printf("Syntax error on raw %d, symbol %d",
						   (*nbr), r));
		ft_strclr(ptr);
		tmp = res;
		res = ft_strjoin(res, s);
		ft_strdel(&tmp);
		ft_strdel(&s);
	return (res);
}






void 	ft_read_n_c(char *s, t_main *main, int fd, int *nbr)
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



int ft_read_file(char *name, line_list **list, t_main *main)
{
	int		fd;
	char		*str;
	line_list	*tmp;
	int 		nbr;
//	int 		flag;



	*list = NULL;
	nbr = 0;

	if ((fd = open(name, O_RDONLY)) == -1)
		return (ft_err("open", 0));
	//get_name(fd, &nbr)

	while ((get_next_line(fd, &str)))
	{
		nbr++;
		if (ft_is_empty(str) == 0)
		{
			if (main->name == NULL || main->comment == NULL)
				ft_read_n_c(str, main, fd, &nbr);
			else
			{
				tmp = *list;
				if (tmp) {
					tmp = get_last(tmp);
					if ((tmp->next = create_file(str, nbr)) == NULL)
						return (-1);
				} else if ((*list = create_file(str, nbr)) == NULL)
					return (-1);
			}
		}
	}
	close(fd);
	free(str);
	if (*list == NULL)
		return (ft_err("empty", -1));
	return (0);
}