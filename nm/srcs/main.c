/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 14:56:08 by hivian            #+#    #+#             */
/*   Updated: 2017/01/16 11:42:12 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		set_opts(char opt_char, t_env *e)
{
	if (opt_char == 'j')
		e->opt_j = true;
	if (opt_char == 'p')
		e->opt_p = true;
	if (opt_char == 'u')
		e->opt_u = true;
	if (opt_char == 'U')
		e->opt_big_u = true;
}

static bool		is_valid_options(int *ac, char **args, t_env *e)
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
			(*ac)--;
			while (args[i][++j])
			{
				if (args[i][j] != 'j' && args[i][j] != 'p' && \
				args[i][j] != 'u' && args[i][j] != 'U')
					return (false);
				set_opts(args[i][j], e);
			}
		}
		else
			e->is_arg = true;
	}
	return (!e->is_arg ? false : true);
}

static void		run_arg(int ac, char *arg, t_env *e)
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
	if (ac > 2)
		printf("\n%s:\n", arg);
	nm(e);
	free_array(e);
	if (munmap(e->ptr, buf.st_size) < 0)
		print_error("munmap_error");
}

int				main(int ac, char **av)
{
	t_env		*e;

	e = (t_env*)malloc(sizeof(t_env));
	if (ac == 1)
	{
		run_arg(ac, "a.out", e);
		free(e);
		return (0);
	}
	if (ac >= 2 && !is_valid_options(&ac, av, e))
		print_error("Usage: ft_nm [-jpuU] [file]");
	av++;
	while (*av)
	{
		if (*av[0] != '-')
			run_arg(ac, *av, e);
		av++;
	}
	free(e);
	return (0);
}
