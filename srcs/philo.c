/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 16:25:27 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/09 11:19:29 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_are_fat(t_rules *ruleset)
{
	int	i;

	i = 0;
	while (i < ruleset->nb_philo)
		if (ruleset->nb_eat_to_end != -1
			&& ruleset->meals[i++] < ruleset->nb_eat_to_end)
			return (0);
	return (1);
}

void	philo_letgo(t_philo *self)
{
	if (self->hold[0] == 1)
		philo_use_fork(self, self->fork_l, PUT_FORK);
	if (self->hold[1] == 1)
		philo_use_fork(self, self->fork_r, PUT_FORK);
}

int	philo_is_alive(t_philo *self)
{
	long int	ms;

	ms = time_getstamp();
	if (self->ruleset->tm_to_die < ms - self->last_meal)
	{
		pthread_mutex_lock(&self->death->lock);
		self->death->dead = 1;
		pthread_mutex_unlock(&self->death->lock);
		msg_put(self, ms, "died");
	}
	if (self->death->dead || philo_are_fat(self->ruleset))
	{
		philo_letgo(self);
		return (0);
	}
	return (1);
}

void	philo_wait(t_philo *self, long int tm_to_wait)
{
	long int	ms;
	long int	life;

	if (self->death->dead)
		return ;
	ms = time_getstamp();
	if (ms + tm_to_wait > self->last_meal + self->ruleset->tm_to_die)
	{
		life = (self->last_meal + self->ruleset->tm_to_die) - ms;
		life++;
		usleep(life * 1000);
		philo_is_alive(self);
	}
	else
		usleep(tm_to_wait * 1000);
}

void	*philo_run(void *self_ptr)
{
	t_philo	*self;

	if (!self_ptr)
		return (0);
	self = (t_philo *)self_ptr;
	self->last_meal = time_getstamp();
	self->last_sleep = time_getstamp();
	philo_loop(self);
	free(self);
	return (0);
}
