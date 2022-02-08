/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkmaster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:33:35 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/08 14:58:47 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		forkmaster_ask(t_philo *self)
{
	t_fm	*forkmaster;
	int		ok;

	forkmaster = self->forkmaster;
	ok = 0;
	if (self->fork_l == self->fork_r)
		return (0);
	pthread_mutex_lock(&(forkmaster->lock));
	if (forkmaster->status[self->fork_l] && forkmaster->status[self->fork_r])
	{
		forkmaster->status[self->fork_l] = 0;
		forkmaster->status[self->fork_r] = 0;
		ok = 1;
	}
	pthread_mutex_unlock(&(forkmaster->lock));
	return (ok);
}

void	forkmaster_tell(t_philo *self, int fork_id)
{
	t_fm	*forkmaster;

	forkmaster = self->forkmaster;
	pthread_mutex_lock(&(forkmaster->lock));
	forkmaster->status[fork_id] = 1;
	pthread_mutex_unlock(&(forkmaster->lock));
}

void	forkmaster_del(t_fm *forkmaster)
{
	int	i;

	i = 0;
	while (i != forkmaster->nb_fork)
		pthread_mutex_destroy(&(forkmaster->forks[i++]));
	free(forkmaster->forks);
	free(forkmaster->status);
	free(forkmaster);
}

int	forkmaster_init(t_fm *forkmaster, int n)
{
	int	i;

	forkmaster->nb_fork = 0;
	if (pthread_mutex_init(&(forkmaster->lock), NULL) != 0)
		return (0);
	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&(forkmaster->forks[i]), NULL) != 0)
			return (0);
		forkmaster->nb_fork += 1;
		forkmaster->status[i] = 1;
		i++;
	}
	return (1);
}

t_fm	*forkmaster_create(int n)
{
	t_fm	*forkmaster;

	forkmaster = (t_fm *)malloc(sizeof(t_fm));
	if (!forkmaster)
		return (0);
	forkmaster->status = (int *)malloc(sizeof(int) * n);
	if (!forkmaster->status)
	{
		free(forkmaster);
		return (0);
	}
	forkmaster->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n);
	if (!forkmaster->forks)
	{
		free(forkmaster->status);
		free(forkmaster);
		return (0);
	}
	if (!forkmaster_init(forkmaster, n))
	{
		forkmaster_del(forkmaster);
		return (0);
	}
	return (forkmaster);
}
