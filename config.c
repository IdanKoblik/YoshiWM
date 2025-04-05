#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "toml.h"

const char* getHomeDir() {
    const char *homeDir = getenv("HOME");
    if (!homeDir) {
        perror("Cannot get HOME directory");
        return NULL;
    }
    
    return homeDir;
}

int createConfigFile() {
    const char *homeDir = getHomeDir();
    if (!homeDir) 
        return -1;

    char mkdirCommand[1024];
    snprintf(mkdirCommand, sizeof(mkdirCommand), "mkdir -p %s/.config/yoshiwm/", homeDir);
    if (system(mkdirCommand) != 0)
        return -1;

    char touchCommand[1024];
    snprintf(touchCommand, sizeof(touchCommand), "touch %s/.config/yoshiwm/yoshi.toml", homeDir);
    if (system(touchCommand) != 0)
        return -1;

    return 0;
}

toml_table_t* readConfig() {
    const char *homeDir = getHomeDir();
    if (!homeDir) 
        return NULL;

    char configFilePath[1024];
    snprintf(configFilePath, sizeof(configFilePath), "%s/.config/yoshiwm/yoshi.toml", homeDir);

    FILE *configFile = fopen(configFilePath, "r");
    if (!configFile) {
        if (createConfigFile() != 0)
            return NULL;

        configFile = fopen(configFilePath, "r");
    }

    toml_table_t *config = toml_parse_file(configFile, NULL, 0);
    if (!config) {
        fprintf(stderr, "Error parsing file\n");
        fclose(configFile);
        return NULL;
    }

    fclose(configFile);
    return config;
}

int loadConfig(config *cfg) {
    toml_table_t* configTable = readConfig();

    if (!configTable)
        return -1;

    toml_table_t *generalTable = toml_table_in(configTable, "general");
    if (generalTable) {
        const char *wallpaperPath = toml_raw_in(generalTable, "wallpaperPath");
        cfg->generalConfig.wallpaperPath  = wallpaperPath ? strdup(wallpaperPath) : NULL;
    }

    return 0;
}