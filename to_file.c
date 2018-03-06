//
// Created by Admin on 22.02.18.
//

#include "asm.h"




char 	*get_name(char *name)
{
	size_t 	i;
	char *new_name;
	int err_flag;
	char *new_name_free;

	i = 0;
	err_flag = 1;
	while(name[i] && name[i] != '.')
	{
		i++;
		if (name[i] == '.' && name[i + 1] == 's')
			err_flag = 0;
	}
	if (err_flag == 1)
		return (NULL);
	new_name = ft_strnew(i + 6);
	new_name_free = new_name;
	ft_strncpy(new_name, name, i);
	new_name = ft_strjoin(new_name, ".cor\0");
	free(new_name_free);
	return (new_name);

}


int		write_in_file(line_list *file, t_main *main, char *filename)
{
	char	*new_filename;
	int		size_file;
	int		fd;

	if ((new_filename = get_name(filename)) == NULL)
		return (-1);
	size_file = ft_get_max(file);
	if ((fd = open(new_filename, O_WRONLY | O_CREAT | O_TRUNC,
				   S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		return (ft_err("open", -1));
	write(fd, main->header, sizeof(*main->header));
	write(fd, main->bytes, (size_t)size_file);
	close(fd);
	ft_printf("Writing output program to %s", new_filename);
	free(new_filename);
	return (0);
}