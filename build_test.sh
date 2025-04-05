#!/bin/bash

set -e

make

config_file="$HOME/.config/yoshiwm/yoshi.toml"

if [ ! -f "$config_file" ]; then
  mkdir -p ~/.config/yoshiwm

  cat <<EOF > "$config_file"
# General settings for the window manager
[general]

# Keyboard shortcuts
[shortcuts]

# Window-related shortcuts
[shortcuts.window]


# Exec-related shortcuts
[shortcuts.exec]
EOF
  echo "Configuration file created at $config_file"
else
  echo "Configuration file already exists at $config_file"
fi


XEPHYR=$(whereis -b Xephyr | cut -f2 -d' ')
xinit ./xinitrc -- \
    "$XEPHYR" \
        :2 \
        -ac \
        -screen 800x600 \
        -host-cursor
