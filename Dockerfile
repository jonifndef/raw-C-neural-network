#FROM archlinux/archlinux
FROM oblique/archlinux-yay

#RUN sudo -u aur yay --noconfirm -Syy
#RUN sudo -u aur yay --noconfirm -S \
#        bc \
#        base-devel #\
RUN pacman --noconfirm -Syy
RUN yes | sudo pacman-key --init
RUN yes | sudo pacman-key --populate archlinux
RUN pacman --noconfirm -S archlinux-keyring
RUN pacman --noconfirm -S \
        bzr \
        cmake \
        cpio \
        cvs \
        git \
        rsync \ 
        shellcheck \
        subversion \
        unzip \
        wget \
        swig 
        neovim \
        python-pip \
        python-virtualenv \
        #clangd-12 \
        #clang-tidy \
        #openssh-client \
        #device-tree-compiler \
        #ninja-build \
        #gperf \
        #ccache \
        #dfu-util \
        #xz-utils \
        #gcc-multilib \
        #g++-multilib \
        #libsdl2-dev \
        #libmagic1 \
        #python3-venv \
        #bear \
        #clangd-12 \
        #check

# To be able to generate a toolchain with locales, enable one UTF-8 locale
#USER root
#RUN sed -i 's/# \(en_US.UTF-8\)/\1/' /etc/locale.gen && \
#    /usr/sbin/locale-gen
#
#RUN useradd -ms /bin/bash user && \
#    chown -R user:user /home/user
#
#USER user
#WORKDIR /home/user
#ENV HOME /home/user
#ENV LC_ALL en_US.UTF-8
