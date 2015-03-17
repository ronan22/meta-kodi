include recipes-core/images/core-image-base.bb
#include recipes-graphics/images/core-image-weston.bb
#include recipes-graphics/images/core-image-x11.bb
#Based on meta-stef by Wolfgar

LICENSE = "MIT"


IMAGE_FEATURES += "debug-tweaks"

# Add extra image features
EXTRA_IMAGE_FEATURES += " \
    nfs-server \
    tools-debug \
    tools-profile \
    ssh-server-openssh \
"

IMAGE_INSTALL += " \
    mpeg2dec \
    openssh-sftp-server \
    kodi \
    procps \
    util-linux-mount \
    util-linux \
    packagegroup-core-sdk \
    joe \
    nano \
    rsync \
    ethtool \
    samba \
    curl \
    python-distutils \
    python-textutils \
    python-sqlite3 \
    python-pickle \
    python-logging \
    python-elementtree \
    python-curses \
    python-compile \
    python-compiler \
    python-fcntl \
    python-shell \
    python-multiprocessing \
    python-subprocess \
    python-xmlrpc \
    python-netclient \
    python-netserver \
    python-unixadmin \
    python-compression \
    python-json \
    python-unittest \
    python-mmap \
    python-difflib \
    python-pprint \
    python-git \
    python-pkgutil \
    python-pycairo \
    python-mako \
    gettext \
    glibc-gconv-ibm850 \
    glibc-gconv-cp1252 \
    glibc-gconv-utf-32 \
    alsa-tools alsa-state alsa-utils-alsaconf \
    pulseaudio \
    transmission \
"
ENABLE_BINARY_LOCALE_GENERATION = "1"

export IMAGE_BASENAME = "kodi-image"

#     TODO:     tvheadend
