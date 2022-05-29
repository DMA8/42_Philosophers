/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_inputs_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syolando <syolando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:04:34 by syolando          #+#    #+#             */
/*   Updated: 2022/05/30 00:04:40 by syolando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../philo_bonus.h"

static int	is_numeric(char *inp)
{
	int	i;

	i = 0;
	while (inp[i])
	{
		if (!(inp[i] >= '0' && inp[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

static int	validate_parameter(char *inp)
{
	if (is_numeric(inp) && !not_int_limits(inp))
		return (1);
	return (0);
}

int	validate_inputs(int argc, char **argv)
{
	int	i;
	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	while (argv[i])
	{
		if (!validate_parameter(argv[i]))
			return (0);
		i++;
	}
	return (1);
}