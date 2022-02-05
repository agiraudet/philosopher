/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:59:07 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/05 16:40:12 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define PICK_FORK 1
# define PUT_FORK 0
# define TIME_INIT 0
# define TIME_READ 1

typedef struct	s_rules
{
	int			nb_philo;
	long int	tm_to_die;
	long int	tm_to_eat;
	long int	tm_to_sleep;
	int			nb_eat_to_end;
}				t_rules;

typedef struct	s_locked_var
{
	pthread_mutex_t	lock;
	int				count;
}				t_lckvar;

typedef struct	s_fork_master
{
	int				nb_fork;
	int				*status;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
}				t_fm;

typedef struct	s_philo
{
	int				id;
	int				nb_meal;
	long int		last_meal;
	long int		last_sleep;
	struct s_rules	ruleset;
	int				fork_l;
	int				fork_r;
	t_lckvar		*death;
	t_fm			*forkmaster;
}				t_philo;


int			forkmaster_ask(t_philo *self);
void		forkmaster_tell(t_philo *self);
void		forkmaster_del(t_fm *forkmaster);
t_fm		*forkmaster_create(int n);
void		*philo_run(void *self_ptr);
int			room_play(t_rules *ruleset);
int			ft_atoi(const char *nptr);
int			ft_strisnb(const char *str);
long int	time_getstamp(void);

#endif
