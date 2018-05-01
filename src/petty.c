#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "pet.h"

#define PS1 "petty >"

void prompt(char **response, int max_length, char *ps)
{
    size_t size = sizeof(char) * max_length;

    if (ps == 0)
        ps = PS1;

    *response = malloc(size);
    printf("%s ", ps);
    char *r = fgets(*response, size + 1, stdin);

    LOG_DEBUG("%lu -> %lu", strlen(r), size);
    if (strlen(r) >= size)
    {
        char ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
    }
}

pet select_pet_menu()
{
    char **pet_list = malloc(sizeof(char *));
    int pet_count = available_pet_list(&pet_list);

    printf("%d pet found.\n", pet_count);
    for (int i = 0; i < pet_count; i++)
    {
        printf(" [%d]: %s\n", i + 1, pet_list[i]);
    }
    printf("\n [c]: Craft a new pet\n");

    printf("Choose one...\n");

    int answer = 0;

    while (1)
    {
        char *response = {0};
        prompt(&response, 10, 0);

        sscanf(response, "%d", &answer);
        LOG_DEBUG("%d", answer);

        if (answer > 0 && answer <= pet_count)
            break;

        if (strncmp(response, "c", 1) == 0)
            break;

        printf("Try again...\n");
        fflush(stdin);
    }

    if (answer)
    {
        return (pet){.name = pet_list[answer - 1]};
    }

    free(pet_list);

    char *name = "";
    if (!answer)
    {
        printf("One of the main ingredients is the name...\n");
        while (1)
        {
            char *response = {0};
            prompt(&response, 20, "Name of your new fiend?");

            printf("\n >>> %s\n", response);
            response[strlen(response) - 1] = '\0';

            char *yn = {0};
            prompt(&yn, 1, "Are you sure? (y/n)");

            if ((yn[0] - 0x59) % 0x20 == 0)
            {
                name = response;
                break;
            }
        }
    }

    return (pet){.name = name};
}

int main(int argc, char *argv[])
{
    pet my_pet = select_pet_menu();

    printf("Summoning '%s'...\n", my_pet.name);
    load_or_create_pet(&my_pet);

    LOG_DEBUG("Name:     %s", my_pet.name);
    LOG_DEBUG("Health:   %d%%", my_pet.health);
    LOG_DEBUG("Birthday: %lu seconds old", time(0) - my_pet.birthday);

    printf("Now go and sleep wel '%s'\n", my_pet.name);
    int done = pet_save_to_disk(&my_pet);
    if (done < 1)
        return 1;

    return 0;
}