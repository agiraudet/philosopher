/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:39:38 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/08 15:16:32 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIFO_H
# define FIFO_H

# include <stdlib.h>

# define FIFO_SIZE 1000

typedef struct	s_fifo
{
	char	*buf;
	int		head;
	int		tail;
	int		size;
	int		stop;
}				t_fifo;

t_fifo	*fifo_create(int size);
int		fifo_read(t_fifo *f, char *buf, int nbytes);
int		fifo_write(t_fifo *f, const char *buf, int nbytes);

#endif
