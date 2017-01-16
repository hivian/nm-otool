/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:13:41 by hivian            #+#    #+#             */
/*   Updated: 2017/01/16 11:37:24 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void				print_t_64(t_section_64 *sect_text, t_env *e)
{
	size_t			j;
	size_t			k;
	size_t			l;
	unsigned char	*offset;

	j = 0;
	l = 16;
	offset = (unsigned char*)e->ptr + sect_text->offset;
	while (j < sect_text->size)
	{
		k = j - 1;
		printf("%016llx\t", sect_text->addr + j);
		while (++k < l && k < sect_text->size)
			printf("%02x ", offset[k]);
		printf("\n");
		j += 16;
		l += 16;
	}
}

void				print_h_64(t_env *e)
{
	char			str_cpusub[16];
	char			str_cpucaps[16];

	sprintf(str_cpusub, "%x", e->header->cpusubtype);
	sprintf(str_cpucaps, "%02x", e->header->cpusubtype & CPU_SUBTYPE_MASK);
	printf("Mach header\n");
	printf("      magic cputype cpusubtype  caps");
	printf("    filetype ncmds sizeofcmds      flags\n");
	printf("%#11x %7d %10s  0x%.2s %11u %5u %10u 0x%08x\n", \
		e->header->magic, e->header->cputype, \
		str_cpusub + ft_strlen(str_cpusub) - 1, \
		str_cpucaps, e->header->filetype, \
		e->header->ncmds, e->header->sizeofcmds, e->header->flags);
}

void				print_t_32(t_section *sect_text, t_env *e)
{
	size_t			j;
	size_t			k;
	size_t			l;
	unsigned char	*offset;

	j = 0;
	l = 16;
	offset = (unsigned char*)e->ptr + sect_text->offset;
	while (j < sect_text->size)
	{
		k = j - 1;
		printf("%08lx\t", sect_text->addr + j);
		while (++k < l && k < sect_text->size)
			printf("%02x ", offset[k]);
		printf("\n");
		j += 16;
		l += 16;
	}
}

void				print_h_32(t_env *e)
{
	char			str_cpusub[16];
	char			str_cpucaps[16];

	sprintf(str_cpusub, "%x", e->header_32->cpusubtype);
	sprintf(str_cpucaps, "%02x", e->header_32->cpusubtype & CPU_SUBTYPE_MASK);
	printf("Mach header\n");
	printf("      magic cputype cpusubtype  caps");
	printf("    filetype ncmds sizeofcmds      flags\n");
	printf("%#11x %7d %10s  0x%.2s %11u %5u %10u 0x%08x\n", \
		e->header_32->magic, e->header_32->cputype, \
		str_cpusub + ft_strlen(str_cpusub) - 1, \
		str_cpucaps, e->header_32->filetype, \
		e->header_32->ncmds, e->header_32->sizeofcmds, e->header_32->flags);
}
