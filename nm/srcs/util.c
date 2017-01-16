/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:06:42 by hivian            #+#    #+#             */
/*   Updated: 2017/01/13 11:42:07 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

long long int		llatoi(const char *str)
{
	int				sign;
	long long int	nb;

	sign = 1;
	nb = 0;
	while (*str == ' ' || *str == '\n' || *str == '\v'
			|| *str == '\t' || *str == '\r' || *str == '\f')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - '0');
		str++;
	}
	return (sign * nb);
}

void				free_array(t_env *e)
{
	size_t			i;

	i = 0;
	while (i < e->sym->nsyms)
	{
		ft_strdel(&e->output_arr[i][0]);
		ft_strdel(&e->output_arr[i][1]);
		ft_strdel(&e->output_arr[i][2]);
		ft_strdel(&e->output_arr[i][3]);
		ft_strdel(&e->output_arr[i][4]);
		free(e->output_arr[i]);
		i++;
	}
	free(e->output_arr);
}
