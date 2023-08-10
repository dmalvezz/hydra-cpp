FROM ubuntu:20.04
ARG USERNAME=dev
ARG LOCALE=en_US.UTF-8

# Time zone
ENV TZ=Europe/Rome
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Update
ARG DEBIAN_FRONTEND=noninteractive
RUN apt update -y

# Upgrade
RUN apt upgrade -y

# Tools
RUN apt install -y zsh git git-svn subversion htop neofetch wget curl bc nano vim moreutils rsync software-properties-common locales

# Repositories
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test
RUN apt update -y

# Dev Python3
RUN apt install -y python3 python3-dev python3-pip python3-venv python3-tk

# Dev C++
RUN apt install -y build-essential gcc-11 g++-11 cmake cmake-curses-gui ninja-build gdb valgrind kcachegrind ccache cppcheck
RUN apt install -y libboost-all-dev 
RUN apt install -y libspdlog-dev libyaml-cpp-dev

# Run scripts
ADD scripts /tmp
RUN sh -c "/tmp/install_cmake.sh"

# Update libs
RUN ldconfig

# Add user
RUN useradd -m -s /bin/bash $USERNAME

# Locale
RUN locale-gen $LOCALE
RUN update-locale LANG=$LOCALE

# Make user bash history persistent
RUN BASHRC="export PROMPT_COMMAND='history -a' && export HISTFILE=/commandhistory/.bash_history" \
    && mkdir /commandhistory \
    && touch /commandhistory/.bash_history \
    && chmod 666 /commandhistory/.bash_history \
    && echo "$BASHRC" >> "/home/$USERNAME/.bashrc"

# Set working user
USER $USERNAME
RUN sh -c "/tmp/install_omb.sh"

CMD /bin/bash
