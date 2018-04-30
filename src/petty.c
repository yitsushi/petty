#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "pet.h"

int main(int argc, char *argv[])
{
  char **pet_list = malloc(sizeof(char*));
  int pet_count = available_pet_list(&pet_list);

  printf("%d pet found.\n", pet_count);
  for (int i = 0; i < pet_count; i++)
  {
    printf(" [%d]: %s\n", i+1, pet_list[i]);
  }

  /*
  pet my_pet = pet_new("My New Pet");

  LOG_DEBUG("Name:     %s", my_pet.name);
  LOG_DEBUG("Health:   %d%%", my_pet.health);
  LOG_DEBUG("Birthday: %lu", my_pet.birthday);
  */

  /*
  int done = pet_save_to_disk(&my_pet);
  if (done < 1)
    return 1;
  */

  return 0;
}