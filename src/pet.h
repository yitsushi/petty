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
void pet_init(pet *);
void load_or_create_pet(pet *);

// Persistent data
int pet_save_to_disk(pet *);
int pet_load_from_disk(pet *);
int available_pet_list(char ***);

#endif