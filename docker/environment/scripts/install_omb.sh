#!/bin/bash

bash -c "$(wget https://raw.githubusercontent.com/ohmybash/oh-my-bash/master/tools/install.sh -O -)"

# Change theme
sed -i 's/OSH_THEME="font"/OSH_THEME="mairan"/g' $HOME/.bashrc