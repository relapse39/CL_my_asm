//
// Created by Admin on 06.12.17.
//

#ifndef ASM_H
#define ASM_H

#include "libft/includes/libft.h"
#include "op.h"
#include <stdio.h>


# define REG	(1)
# define DIR	(2)
# define IND	(3)
# define INST   (12)
#define LABEL_CHARS_1				"abcdefghijklmnopqrstuvwxyz_0123456789:"
#define REG_MASK_1 0b01000000
#define REG_MASK_2 0b00010000
#define REG_MASK_3 0b00000100
#define IND_MASK_1 0b11000000
#define IND_MASK_2 0b00110000
#define IND_MASK_3 0b00001100
#define DIR_MASK_1 0b10000000
#define DIR_MASK_2 0b00100000
#define DIR_MASK_3 0b00001000
#define TWO_BYTE_MASK 0b11111111
#define FOUR_BYTE_MASK_1 0b00000000111111110000000000000000
#define FOUR_BYTE_MASK_2 0b00000000000000001111111100000000
#define FULL_BYTE 0b11111111
#define MY_LONG_MAX 9223372036854775807



typedef struct line_t line;
typedef struct line_list_t line_list;

struct 			line_t {
    char 		*r_line;
    char 		**com;
    int 		f_type;
    int 		s_type;
    int 		t_type;
    int		    args_n;
    int 		pos;
    int 		length;
    int 		nbr;
};

struct line_list_t {
    line ent;
    line_list *next;
};

typedef struct	s_main
{
    char			*name;
    char			*comment;
    t_header		*header;
    unsigned char	*bytes;
    int 			name_c;
}				t_main;

char				*some_modifying(char **res, char *s);
void				some_modifying_two(char *s, char *ptr, char **res);
int					read_helper(line_list **list, char *str, int *nbr);
int					skip_wspcs(char *s);
int					check_eos(char *s);
line_list			*create_file(char *line, int nbr);
int					ft_print_err_arg(line_list *list, int n);
int					ft_print_err_lexical(line_list *list, int n);
int					ft_print_err_inst(line_list *list, int n);
int					ft_is_reg(char *str);
void				ft_ad_t(line_list *line, int com_n, int type);
int					ft_got_thresh(line_list *list);
int					ft_is_delete(char **com);
int 				ft_check_lables(line_list *list);
int     			ft_check_label_char(line_list *list, int n);
int					ft_atoi_1(const char *str);
int 				ft_atoi_ret( int neg);
void                ft_print_n_err(void);
int 	            ft_find_inst(char *inst);
char 				*ft_get_l_i_str(char *str);
int					ft_get_pos(const char *big, const char *little);
int					ft_spec_case(char *inst, int n);
int 				ft_is_need_arg_code(char *inst);
int					write_in_file(line_list *file, t_main *main, char *filename);
int					ft_get_max(line_list *list);
int					ft_bytecode(line_list *list, t_main *main);
int 				ft_is_valid(line_list *list);
void				ft_clear_list(line_list **list);
int 				ft_is_label(char *str);
int 				ft_remove_labels(line_list *list);
int					ft_get_type_param(line_list *line);
void				ft_get_position(line_list *list);
int					ft_inst_check(char *str);
int 				ft_read_file(char *name, line_list **list,t_main *main);
char				**ft_split_cmd(char *str);
line_list  			*get_last(line_list *list);
int 				ft_is_empty(char *str);
int 				ft_err(char *err, int ret);
int					get_header(t_main *main,int size);

#endif
