/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** unit_test_server.c
*/

#include <criterion/criterion.h>
#include "server.h"

Test(server, wrong_number_of_arguments_one)
{
    int ac = 2;
    char *av[] = {NULL};
    const int result = server(ac, av);

    cr_assert_eq(result, -1);
}

Test(server, wrong_number_of_arguments_two)
{
    int ac = 0;
    char *av[] = {NULL};
    const int result = server(ac, av);

    cr_assert_eq(result, -1);
}

Test(server, port_is_str_one)
{
    int ac = 1;
    char *av[] = {"epitech", NULL};
    const int result = server(ac, av);

    cr_assert_eq(result, -1);
}

Test(server, port_is_str_two)
{
    int ac = 1;
    char *av[] = {"-4°", NULL};
    const int result = server(ac, av);

    cr_assert_eq(result, -1);
}

Test(server, port_is_negative)
{
    int ac = 1;
    char *av[] = {"-42", NULL};
    const int result = server(ac, av);

    cr_assert_eq(result, -1);
}

Test(server, port_need_super_user)
{
    int ac = 1;
    char *av[] = {"42", NULL};
    const int result = server(ac, av);

    cr_assert_eq(result, -1);
}
