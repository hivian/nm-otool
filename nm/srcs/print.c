/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 15:39:26 by hivian            #+#    #+#             */
/*   Updated: 2017/01/16 11:50:02 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		print_type(t_env *e)
{
	if (e->n_type == N_UNDF)
		(e->n_value != 0) ? printf("C ") : printf("U ");
	else if (e->n_type == N_ABS)
		printf("A ");
	else if (e->n_type == N_SECT)
	{
		if (e->n_sect == e->text_nsect)
			(e->is_lsym == true) ? printf("t ") : printf("T ");
		else if (e->n_sect == e->data_nsect)
			(e->is_lsym == true) ? printf("d ") : printf("D ");
		else if (e->n_sect == e->bss_nsect)
			(e->is_lsym == true) ? printf("b ") : printf("B ");
		else
			printf("S ");
	}
	else if (e->n_type == N_INDR)
		printf("I ");
	else
		printf("? ");
}

static void		print_value(t_env *e)
{
	if ((void*)e->n_value != 0x0 || e->n_type == N_SECT)
	{
		if (e->magic_nb == MH_MAGIC_64)
			printf("%016llx ", e->n_value);
		else
			printf("%08llx ", e->n_value);
	}
	else
	{
		if (e->magic_nb == MH_MAGIC_64)
			printf("%16c ", ' ');
		else
			printf("%8c ", ' ');
	}
}

static void		print_all(t_env *e)
{
	if (!e->opt_j)
	{
		print_value(e);
		print_type(e);
	}
	printf("%s\n", e->str_symbol);
}

void			print_output(t_env *e)
{
	size_t		i;

	i = 0;
	while (i < e->sym->nsyms)
	{
		if (e->opt_u && e->opt_big_u)
			break ;
		e->n_value = llatoi(e->output_arr[i][0]);
		e->n_type = ft_atoi(e->output_arr[i][1]);
		e->n_sect = ft_atoi(e->output_arr[i][3]);
		e->str_symbol = e->output_arr[i][2];
		e->is_lsym = !ft_strcmp(e->output_arr[i][4], "LSYM_OK") ? true : false;
		if (e->n_type != N_PBUD)
		{
			if (!e->opt_big_u && !e->opt_u)
				print_all(e);
			else if (e->n_type == N_UNDF && e->opt_u)
				printf("%s\n", e->str_symbol);
			else if (e->n_type != N_UNDF && e->opt_big_u)
				print_all(e);
		}
		i++;
	}
}
