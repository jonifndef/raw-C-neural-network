FROM oblique/archlinux-yay

RUN pacman --noconfirm -Syy
RUN yes | sudo pacman-key --init
RUN yes | sudo pacman-key --populate archlinux
RUN pacman --noconfirm -S archlinux-keyring
RUN pacman --noconfirm -Su
RUN pacman --noconfirm -S \
        base-devel \
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
        swig \
        python-pip \
        python-virtualenv \
        bear \
        openssh \
        check \
        clang \
        compiler-rt
        #neovim \

# To be able to generate a toolchain with locales, enable one UTF-8 locale
USER root
RUN sed -i 's/# \(en_US.UTF-8\)/\1/' /etc/locale.gen && \
    /usr/sbin/locale-gen
#
RUN useradd -ms /bin/bash user && \
    chown -R user:user /home/user
#
USER user
WORKDIR /home/user
ENV HOME /home/user
ENV LC_ALL en_US.UTF-8
