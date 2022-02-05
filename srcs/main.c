/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:55:32 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/05 17:03:54 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_rules	*rules_set(char **argv)
{
	t_rules	*ruleset;

	ruleset = (t_rules *)malloc(sizeof(t_rules));
	if (!ruleset)
		return (0);
	ruleset->nb_philo = ft_atoi(argv[1]);
	ruleset->tm_to_die = ft_atoi(argv[2]);
	ruleset->tm_to_eat = ft_atoi(argv[3]);
	ruleset->tm_to_sleep = ft_atoi(argv[4]);
	if (!argv[5])
		ruleset->nb_eat_to_end = -1;
	else
		ruleset->nb_eat_to_end = ft_atoi(argv[5]);
	return (ruleset);
}

int	check_input(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("%s: wrong number of arguments\n", argv[0]);
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		if (!ft_strisnb(argv[i]))
		{
			printf("%s: %s: arguments must be numbers\n", argv[0], argv[i]);
			return (0);
		}
		i++;
	}
	if (ft_atoi(argv[1]) <= 0)
	{
		printf("%s: number_of_philosopher must be at leat 1\n", argv[0]);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_rules	*ruleset;
	if (!check_input(argc, argv))
		return (1);
	ruleset = rules_set(argv);
	if (!ruleset)
		return (1);
	room_play(ruleset);
	free(ruleset);
	return (0);
}
