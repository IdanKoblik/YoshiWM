#ifndef _CONFIG_
#define _CONFIG_

#include "toml.h"

typedef struct {
    char *wallpaperPath;
} general;


typedef union  {
    general generalConfig;
} config;

int loadConfig(config *cfg);
void freeConfig(config *cfg);

#endif