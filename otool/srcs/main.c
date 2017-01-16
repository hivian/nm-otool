/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 09:43:00 by hivian            #+#    #+#             */
/*   Updated: 2017/01/16 11:42:20 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void		set_opts(char first_char, t_env *e)
{
	if (first_char == 'h')
		e->opt_h = true;
	if (first_char == 't')
		e->opt_t = true;
}

static bool		is_valid_options(char **args, t_env *e)
{
	int			i;
	int			j;

	i = 0;
	while (args[++i])
	{
		if (args[i][0] == '-' && !args[i][1])
			return (false);
		if (args[i][0] == '-')
		{
			j = 0;
			while (args[i][++j])
			{
				if (args[i][j] != 'h' && args[i][j] != 't')
					return (false);
				set_opts(args[i][j], e);
			}
		}
		else
			e->is_arg = true;
	}
	if (!e->is_arg)
		return (false);
	return (true);
}

static void		run_arg(char *arg, t_env *e)
{
	int			fd;
	t_stat		buf;

	if ((fd = open(arg, O_RDONLY)) < 0)
		print_error("Error opening file");
	if (fstat(fd, &buf) < 0)
		print_error("stat : Error opening file");
	if ((e->ptr = mmap(0, buf.st_size, PROT_READ, \
	MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		print_error("mmap: Error");
	if (e->opt_t)
	{
		printf("%s:\n", arg);
		printf("Contents of (__TEXT,__text) section\n");
	}
	otool(e);
	if (munmap(e->ptr, buf.st_size) < 0)
		print_error("munmap_error");
}

int				main(int ac, char **av)
{
	t_env		*e;

	e = (t_env*)malloc(sizeof(t_env));
	if (ac <= 2 || (ac > 2 && !is_valid_options(av, e)))
		print_error("Usage: ft_otool [-th] [file]");
	av++;
	while (*av)
	{
		if (*av[0] != '-')
			run_arg(*av, e);
		av++;
	}
	free(e);
	return (0);
}
