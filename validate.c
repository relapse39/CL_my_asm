//
// Created by Admin on 20.02.18.
//

#include "asm.h"

int 	ft_find_inst(char *inst)
{
	int i;

	i = 0;
	while (g_op_tab[i].name && ft_strequ(g_op_tab[i].name, inst) != 1)
		i++;
	if (i > 15)
		return (-1);
	else
		return (i);
}



int		ft_check_args_n(line_list *list)
{
	int par;

	par = ft_find_inst(list->entry.com[0]);
		if (par == -1)
		{
			ft_printf("Invalid instruction at token [TOKEN]");
			ft_printf("[%03d",list->entry.nbr);
			ft_printf(":%03d]",ft_get_pos(list->entry.raw_line, list->entry.com[0]) + 1);
			ft_printf(" %s \"%s\"",ft_get_l_i_str(list->entry.com[0]), list->entry.com[0]);
			return (-1);
		}
		if (g_op_tab[par].arg_num != list->entry.args_n)
		{
			ft_printf("Invalid parameter %d type ",g_op_tab[par].arg_num - 1);
			ft_printf("register for instruction %s ",g_op_tab[par].name);
			//ft_printf("bad nbr. of args in line: %s", list->entry.raw_line);
			return (-1);
		}
	return (0);
}

int 	ft_print_err_inst(line_list *list, int n)
{
	ft_printf("Syntax error in token [TOKEN]");
	ft_printf("[%03d:",list->entry.nbr);
	ft_printf("%03d", ft_get_pos(list->entry.raw_line,list->entry.com[n]) + 1);
	ft_printf("] INSTRUCTION \"%s\"",list->entry.com[n]);
	return (-1);
}

int 	ft_print_err_lexical(line_list *list, int n)
{
	ft_printf("Lexical error at ");
	ft_printf("[%d:",list->entry.nbr);
	ft_printf("%d]", ft_get_pos(list->entry.raw_line,list->entry.com[n]) + 1);
	return (-1);
}

int 	ft_check_arg(line_list *list, int n)
{
	int i;
	int type;

	type = -1;
	n == 1 ? type = list->entry.first_type : (0);
	n == 2 ? type = list->entry.second_type : (0);
	n == 3 ? type = list->entry.third_type : (0);
	i = ft_find_inst(list->entry.com[0]);
	if (type != T_DIR && type != T_REG && type != T_IND && type != INST)
		return(ft_print_err_lexical(list, n));
	if (type == INST)
		return (ft_print_err_inst(list, n));




	if ((g_op_tab[i].args[n - 1] & type) == 0)
	{
		ft_printf("Invalid parameter %d type register",n - 1);
		ft_printf(" for instruction %s",g_op_tab[i].name);
		return (-1);
	}
	if(type == T_REG)
	{
		if(ft_atoi(list->entry.com[n] + 1) > REG_NUMBER)
		{
			ft_printf("Syntax error in token [TOKEN]");
			ft_printf("[%03d:",list->entry.nbr);
			ft_printf("%03d", ft_get_pos(list->entry.raw_line,list->entry.com[n]) + 1);
			ft_printf("] INSTRUCTION \"%s\"",list->entry.com[n]);
			return (-1);
		}
	}

//	if (ft_atoi(arg + 1) == 0 || ft_atoi(arg + 1) > REG_NUMBER)
//	{
//		//ft_printf("r is too big at line %s", line);
//		return (-1);
//	}
	return (0);
}

//int 	ft_check_dir(char *arg, line_list *list, int n)
//{
//	int	i;
//
//	if (arg[1] == '-')
//		i = 2;
//	else
//		i = 1;
//	while (arg[i])
//	{
//		if (!ft_isdigit(arg[i]))
//		{
//			//ft_printf("bad dir arg '%s' in line: %s",arg[i], line);
//			return (-1);
//		}
//		i++;
//	}
//	if (ft_strlen(arg + 1) > 10 )
//	{
//		//ft_printf("dir is to big at line %s", line);
//	}
//	return (0);
//}
//
//int ft_check_indir(char *arg, line_list *list, int n)
//{
//	int i;
//
//	if (arg[0] == '-')
//		i = 1;
//	else
//		i = 0;
//	while (arg[i])
//	{
//		if (!ft_isdigit(arg[i]))
//		{
//			//ft_printf("bad indir arg in line%s", line);
//			return (-1);
//		}
//		i++;
//	}
//	if ((ft_atoi(arg) > IDX_MOD))
//	{
//		//ft_printf("too big indir arg in line%s , %d", line, ft_atoi(arg));
//		return (-1);
//	}
//	return (0);
//}


//int 	ft_check_args_1(line_list *list, int type, int n)
//{
//	type = 0;
//		return (ft_check_reg( list, n));
//	else if (type == 2)
//		return(ft_check_dir(arg, list, n));
//	else if (type == 3)
//		return (ft_check_indir(arg, list, n));
//	return (0);
//}

int 	ft_cycle_body(line_list *list)
{
	int res;

	res = 0;
	if (list->entry.first_type != 0)
		res = ft_check_arg(list, 1);
	if (list->entry.second_type != 0)
		res += ft_check_arg(list, 2);
	if (list->entry.third_type != 0)
		res += ft_check_arg(list, 3);
	if (res < 0)
		return (-1);
	return (0);
}



int 	ft_is_valid(line_list *list)
{
	line_list *tmp;

	tmp = list;
	while(tmp)
	{
		if (ft_check_args_n(tmp) == -1)
			return (-1);
		if (ft_cycle_body(tmp) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}