#ifndef __PET_H
#define __PET_H

typedef struct pet_t
{
    char *name;
    signed char health;

    signed char belly;
    signed char digestion;

    signed char joy;
    signed char dirt;

    unsigned long birthday;
} pet;

// Constructor with default data
pet pet_new(char *);
void load_or_create_pet(pet *);

// Persistent data
int pet_save_to_disk(pet *);
pet pet_load_from_disk();
int available_pet_list(char ***);

#endif