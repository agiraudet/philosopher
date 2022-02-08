/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:40:30 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/08 15:16:15 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fifo.h"
#include <stdlib.h>

t_fifo	*fifo_create(int size)
{
	t_fifo	*f;

	f = (t_fifo *)malloc(sizeof(t_fifo));
	if (!f)
		return (0);
	f->buf = (char *)malloc(sizeof(char) * size);
	if (!f->buf)
	{
		free(f);
		return (0);
	}
	f->size = size;
	f->head = 0;
	f->tail = 0;
	f->stop = 0;
	return (f);
}

int	fifo_read(t_fifo *f, char *buf, int nbytes)
{
	int	i;

	i = 0;
	while (i < nbytes)
	{
		if (f->tail != f->head)
		{
			*buf++ = f->buf[f->tail++];
			if (f->tail == f->size)
				f->tail = 0;
		}
		else
			return (i);
		i++;
	}
	return (nbytes);
}

int	fifo_write(t_fifo *f, const char *buf, int nbytes)
{
	int i;

	i = 0;
	while (i < nbytes)
	{
		if (f->head + 1 == f->tail || (f->head + 1 == f->size && f->tail == 0))
			return (i);
		else
		{
			f->buf[f->head++] = *buf++;
			if (f->head == f->size)
				f->head = 0;
		}
		i++;
	}
	return (nbytes);
}
