#include "pet.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <dirent.h>

#include "common.h"

pet pet_new(char *name)
{
    pet p = (pet){
        .name = name,
        .health = 80,
        .belly = 80,
        .digestion = 0,
        .joy = 80,
        .dirt = 0,
        .birthday = time(0)};
    return p;
}

void load_or_create_pet(pet *p)
{
}

static const char *homedir()
{
    struct passwd *pw = getpwuid(getuid());
    return pw->pw_dir;
}

char *_config_dir = "";
static char *config_dir()
{
    if (strlen(_config_dir) > 0)
    {
        return _config_dir;
    }
    _config_dir = concat(homedir(), "/.config/petty");
    return _config_dir;
}

static char *pet_file(char *name)
{
    return concat(concat(concat(config_dir(), "/"), name), ".dat");
}

static void check_and_create_config_directory()
{
    char *dirname = config_dir();
    struct stat st = {0};
    if (stat(dirname, &st) == -1)
    {
        mkdir(dirname, 0700);
    }
}

static int save_data(void *data, size_t size, int count, FILE *file)
{
    int written = fwrite(data, size, count, file);
    if (!written)
    {
        LOG_ERROR("Cannot write health data.");
    }
    return written;
}

int pet_save_to_disk(pet *p)
{
    check_and_create_config_directory();

    int written = 0;
    FILE *file;

    file = fopen(pet_file(p->name), "wb");

    if (file == 0)
    {
        LOG_ERROR("Cannot open pet file for writing.");
        return 0;
    }

    written += save_data(&(p->health), sizeof(p->health), 1, file);
    written += save_data(&(p->belly), sizeof(p->belly), 1, file);
    written += save_data(&(p->digestion), sizeof(p->digestion), 1, file);
    written += save_data(&(p->joy), sizeof(p->joy), 1, file);
    written += save_data(&(p->dirt), sizeof(p->dirt), 1, file);
    written += save_data(&(p->birthday), sizeof(p->birthday), 1, file);

    fclose(file);

    return written;
}

pet pet_load_from_disk()
{
    check_and_create_config_directory();

    LOG_ERROR("Not implemented yet!");

    return pet_new("test");
}

int available_pet_list(char ***list)
{
    check_and_create_config_directory();

    DIR *dir_handler;
    struct dirent *dir;
    dir_handler = opendir(config_dir());
    int count = 0;
    if (dir_handler)
    {
        while ((dir = readdir(dir_handler)) != 0)
        {
            if (dir->d_type != DT_REG)
                continue;
            if (strncmp(dir->d_name + strlen(dir->d_name) - 4, ".dat", 4) != 0)
                continue;

            char *pet_name = malloc(sizeof(char) * (strlen(dir->d_name) - 3));
            strncpy(pet_name, dir->d_name, strlen(dir->d_name) - 4);
            LOG_DEBUG("%20s -> %s", dir->d_name, pet_name);

            *list = realloc(*list, (count + 1) * sizeof(char *));
            (*list)[count] = malloc(strlen(pet_name) + 1);
            strncpy((*list)[count], pet_name, strlen(pet_name) + 1);
            free(pet_name);
            count++;
        }
        closedir(dir_handler);
    }

    return count;
}