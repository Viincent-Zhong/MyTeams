/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** unit_test_client.c
*/

#include <criterion/criterion.h>
#include "client.h"

Test(client, wrong_number_of_argument_one)
{
    int ac = 0;
    char *av[] = {NULL};
    const int result = client(ac, av);

    cr_assert_eq(result, -1);
}

Test(client, wrong_number_of_argument_two)
{
    int ac = 10;
    char *av[] = {NULL};
    const int result = client(ac, av);

    cr_assert_eq(result, -1);
}

Test(client, ip_is_string)
{
    int ac = 2;
    char *av[] = {"epitech", "1234", NULL};
    const int result = client(ac, av);

    cr_assert_eq(result, -1);
}

Test(client, ip_is_negative)
{
    int ac = 2;
    char *av[] = {"-124", "1234", NULL};
    const int result = client(ac, av);

    cr_assert_eq(result, -1);
}

Test(client, port_is_string)
{
    int ac = 2;
    char *av[] = {"127.0.0.1", "abcdefu", NULL};
    const int result = client(ac, av);

    cr_assert_eq(result, -1);
}

Test(client, port_is_string_and_number)
{
    int ac = 2;
    char *av[] = {"127.0.0.1", "-4°", NULL};
    const int result = client(ac, av);

    cr_assert_eq(result, -1);
}

Test(client, port_is_negative)
{
    int ac = 2;
    char *av[] = {"127.0.0.1", "-42", NULL};
    const int result = client(ac, av);

    cr_assert_eq(result, -1);
}

Test(client, cant_connect_server)
{
    int ac = 2;
    char *av[] = {"127.0.0.1", "1", NULL};
    const int result = client(ac, av);

    cr_assert_eq(result, -1);
}

Test(init_user, ini_and_connect_server)
{
    int ac = 2;
    char *av[] = {"127.0.0.1", "1", NULL};
    user_info_t user;

    cr_assert_eq(init_client(ac, av, &user), -1);
}
