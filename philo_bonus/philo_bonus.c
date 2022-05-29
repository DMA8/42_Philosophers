/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syolando <syolando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 23:31:54 by syolando          #+#    #+#             */
/*   Updated: 2022/05/30 01:46:18 by syolando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_overall	*all;

	if (!validate_inputs(argc, argv))
	{
		write(2, "bad input\n", 10);
		exit(1);
	}
	all = init_overall(argv, argc);
	if (!all)
	{
		write(2, "init failure\n", 13);
		exit(1);
	}
	all->start_time = get_time();
	start_philo(all);
	return (0);
}