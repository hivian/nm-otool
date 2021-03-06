/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 11:40:05 by hivian            #+#    #+#             */
/*   Updated: 2017/01/13 11:22:07 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void			otool(t_env *e)
{
	e->magic_nb = *(int*)e->ptr;
	if (e->magic_nb == MH_MAGIC_64)
		handle_64(e);
	if (e->magic_nb == MH_MAGIC)
		handle_32(e);
}
