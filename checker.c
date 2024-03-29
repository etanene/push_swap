/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afalmer- <afalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:19:19 by afalmer-          #+#    #+#             */
/*   Updated: 2019/04/27 18:23:52 by afalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		ft_reada(t_stack **a, t_stack **b, int print, char *op)
{
	if (!ft_strcmp(op, "pa"))
		ft_push_op(b, a, 'a', print);
	else if (!ft_strcmp(op, "sa"))
		ft_swap_op(a, b, 'a', print);
	else if (!ft_strcmp(op, "ra"))
		ft_rotate_op(a, b, 'a', print);
	else if (!ft_strcmp(op, "rra"))
		ft_revrotate_op(a, b, 'a', print);
	else if (!ft_strcmp(op, "ss"))
	{
		ft_swap_op(a, b, 'a', print);
		ft_swap_op(b, a, 'b', print);
	}
	else
		return (0);
	return (1);
}

static int		ft_readb(t_stack **a, t_stack **b, int print, char *op)
{
	if (!ft_strcmp(op, "pb"))
		ft_push_op(a, b, 'b', print);
	else if (!ft_strcmp(op, "sb"))
		ft_swap_op(b, a, 'b', print);
	else if (!ft_strcmp(op, "rb"))
		ft_rotate_op(b, a, 'b', print);
	else if (!ft_strcmp(op, "rrb"))
		ft_revrotate_op(b, a, 'b', print);
	else if (!ft_strcmp(op, "rr"))
	{
		ft_rotate_op(a, b, 'a', print);
		ft_rotate_op(b, a, 'b', print);
	}
	else if (!ft_strcmp(op, "rrr"))
	{
		ft_revrotate_op(a, b, 'a', print);
		ft_revrotate_op(b, a, 'b', print);
	}
	else
		return (0);
	return (1);
}

static int		ft_read_input(t_stack **a, t_stack **b, int print)
{
	char	*op;

	while (get_next_line(0, &op) > 0)
	{
		if (ft_reada(a, b, print, op))
			ft_strdel(&op);
		else if (ft_readb(a, b, print, op))
			ft_strdel(&op);
		else
		{
			ft_strdel(&op);
			return (0);
		}
	}
	return (1);
}

int				ft_read_write(t_stack **a, t_stack **b, int print)
{
	if (print == -1)
	{
		ft_printf("START\n");
		ft_print_ab(*a, *b);
	}
	if (!ft_read_input(a, b, print))
	{
		ft_printf("Error\n");
		return (0);
	}
	if (print == -1)
	{
		ft_printf("END\n");
		ft_print_ab(*a, *b);
	}
	return (1);
}

int				main(int ac, char **av)
{
	t_stack	*a;
	t_stack	*b;
	int		print;

	b = NULL;
	if (ac == 1)
		return (0);
	if ((print = ft_check_option(av[1]) ? -1 : -2) == -1)
	{
		av++;
		ac--;
	}
	if ((a = ft_set_stack(++av, ac - 1)) == NULL)
	{
		ft_printf("Error\n");
		return (ft_free_stack(a, b));
	}
	if (!ft_read_write(&a, &b, print))
		return (ft_free_stack(a, b));
	if (ft_is_sort(a, b))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	return (ft_free_stack(a, b));
}
