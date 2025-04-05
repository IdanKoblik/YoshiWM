#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include "toml.h"

const char* getHomeDir() {
    const char *homeDir = getenv("HOME");
    if (!homeDir) {
        perror("Cannot get HOME directory");
        return NULL;
    }
    
    return homeDir;
}

static windowAction stringToWindowAction(const char *str) {
    if (strcmp(str, "RELOAD") == 0) return ACTION_RELOAD;
    if (strcmp(str, "EXIT") == 0) return ACTION_EXIT;

    return ACTION_RELOAD;
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

void handleGeneralTable(toml_table_t *generalTable, config *cfg) {
    const char *wallpaperPath = toml_raw_in(generalTable, "wallpaperPath");
    cfg->generalConfig.wallpaperPath = wallpaperPath ? strdup(wallpaperPath) : NULL;

    const char *superKey = toml_raw_in(generalTable, "superKey");
    cfg->generalConfig.superKey = superKey ? 
        (strcmp(superKey, "ALT") == 0 ? SUPER_ALT : SUPER_WINDOW) : SUPER_WINDOW;
}

void handleShortcutsTable(toml_table_t *shortcutsTable, config *cfg) {
    toml_table_t *windowTable = toml_table_in(shortcutsTable, "window");
    if (windowTable) {
        const char *key;
        const char *raw;
        int keyCount = 0;
        
        while (toml_key_in(windowTable, keyCount) != NULL) keyCount++;
        
        cfg->windowShortcuts = malloc(sizeof(windowShortcut) * keyCount);
        cfg->windowShortcutsCount = keyCount;
        
        for (int i = 0; i < keyCount; i++) {
            key = toml_key_in(windowTable, i);
            raw = toml_raw_in(windowTable, key);
            
            if (key && raw) {
                cfg->windowShortcuts[i].shortcut = strdup(key);
                char *value = strdup(raw);
                if (value[0] == '"') {
                    value[strlen(value)-1] = '\0';
                    cfg->windowShortcuts[i].action = stringToWindowAction(value + 1);
                } else {
                    cfg->windowShortcuts[i].action = stringToWindowAction(value);
                }
                free(value);
            }
        }
    }

    toml_table_t *execTable = toml_table_in(shortcutsTable, "exec");
    if (execTable) {
        const char *key;
        const char *raw;
        int keyCount = 0;
        
        while (toml_key_in(execTable, keyCount) != NULL) keyCount++;
        cfg->execShortcuts = malloc(sizeof(execShortcut) * keyCount);
        cfg->execShortcutsCount = keyCount;
        
        for (int i = 0; i < keyCount; i++) {
            key = toml_key_in(execTable, i);
            raw = toml_raw_in(execTable, key);
            
            if (key && raw) {
                cfg->execShortcuts[i].shortcut = strdup(key);

                char *value = strdup(raw);
                if (value[0] == '"') {
                    value[strlen(value)-1] = '\0';
                    cfg->execShortcuts[i].command = strdup(value + 1);
                } else {
                    cfg->execShortcuts[i].command = strdup(value);
                }
                free(value);
            }
        }
    }
}

int loadConfig(config *cfg) {
    toml_table_t* configTable = readConfig();
    if (!configTable)
        return -1;

    toml_table_t *generalTable = toml_table_in(configTable, "general");
    handleGeneralTable(generalTable, cfg);

    toml_table_t *shortcutsTable = toml_table_in(configTable, "shortcuts");
    handleShortcutsTable(shortcutsTable, cfg);

    toml_free(configTable);
    return 0;
}

void freeConfig(config *cfg) {
    free(cfg->generalConfig.wallpaperPath);
    
    for (size_t i = 0; i < cfg->windowShortcutsCount; i++) {
        free(cfg->windowShortcuts[i].shortcut);
    }

    free(cfg->windowShortcuts);
    
    for (size_t i = 0; i < cfg->execShortcutsCount; i++) {
        free(cfg->execShortcuts[i].shortcut);
        free(cfg->execShortcuts[i].command);
    }

    free(cfg->execShortcuts);
}