/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:03:47 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/09 11:24:20 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msg_putnbr(long int n, char *buf, int *i)
{
	if (n < 0)
	{
		buf[*i] = '-';
		(*i)++;
		n *= -1;
	}
	if (n > 9)
		msg_putnbr(n / 10, buf, i);
	buf[*i] = n % 10 + '0';
	(*i)++;
}

void	msg_format(char *buf, int id, long int ms, char *msg)
{
	int	i;

	memset(buf, 0, MSG_BUF_SIZE);
	i = 0;
	msg_putnbr(ms, buf, &i);
	buf[i++] = ' ';
	msg_putnbr(id, buf, &i);
	buf[i++] = ' ';
	while (*msg)
		buf[i++] = *msg++;
	buf[i++] = '\n';
}

void	msg_put(t_philo *self, long int ms, char *msg)
{
	int		wr;
	int		buf_len;
	char	buf[MSG_BUF_SIZE];
	t_fifo	*f;

	msg_format(buf, self->id, ms, msg);
	buf_len = ft_strlen(buf);
	f = msg_fifo(0);
	if (f->stop)
		return ;
	pthread_mutex_lock(&self->ruleset->talk);
	wr = fifo_write(f, buf, buf_len);
	while (wr < buf_len)
	{
		buf_len = ft_strlen(&buf[wr + 1]);
		wr = fifo_write(f, &buf[wr + 1], buf_len);
	}
	pthread_mutex_unlock(&self->ruleset->talk);
}

int	msg_died(char *msg)
{
	char	*died;

	died = ft_strnstr(msg, "died", ft_strlen(msg));
	if (!died)
		return (0);
	died[5] = 0;
	return (1);
}

void	*msg_thread(void *lock)
{
	t_fifo	*f;
	char	buf[MSG_BUF_SIZE];

	f = msg_fifo(0);
	if (!f)
	{
		printf("fifo error\n");
		return (0);
	}
	while (!f->stop)
	{
		if (f->tail != f->head)
		{
			memset(buf, 0, MSG_BUF_SIZE);
			pthread_mutex_lock(lock);
			fifo_read(f, buf, MSG_BUF_SIZE - 1);
			pthread_mutex_unlock(lock);
			f->stop = msg_died(buf);
			printf("%s", buf);
		}
	}
	return (0);
}
