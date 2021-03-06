# Based on meta-stef by Wolfgar

DESCRIPTION = "Kodi - Media player and entertainment hub"
LICENSE = "GPLv2"

LIC_FILES_CHKSUM = "file://LICENSE.GPL;md5=930e2a5f63425d8dd72dbd7391c43c46"

DEPENDS = " \
	libfslvpuwrap \
	alsa-lib \
	python \
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
	mpeg2dec \
	boost \
	cmake \
	zlib \
	dbus \
        libass \
        mariadb \
        swig \
	libmodplug \
	yajl \
	libtinyxml \
	libcdio \
        jasper \
	libssh \
	samba \
	taglib \
	tiff \
	libmicrohttpd \
	libssh \
	rtmpdump \
	swig-native \
	libxslt \
	libplist \
	flac \
	libvorbis \
	udev \
	curl \
	lzo \
	shairplay \
	avahi \
	cairo pango fontconfig freetype \
	ffmpeg-kodi \
	libcec-imx \
"

DEPENDS_append_mx6 = " virtual/kernel virtual/libgles2 virtual/egl "

# todo: libbluray 


INC_PR = "r1"
SRC_URI = "git://github.com/xbmc/xbmc.git;branch=Helix"


S = "${WORKDIR}/git/"

inherit autotools lib_package pkgconfig gettext python-dir
EXTRA_OECONF=" --disable-debug \
	--build=${BUILD_SYS} \
	--host=${HOST_SYS} \
	--target=${TARGET_SYS} ${@append_libtool_sysroot(d)} \
	--disable-rpath \
	--prefix=/imx6/xbmc \
	--disable-pulse \
	--disable-projectm \
	--disable-x11 \
	--disable-sdl \
	--disable-libcec \
	--disable-tiff \
	--disable-xrandr \
	--disable-gl \
	--disable-vdpau \
	--disable-vaapi \
	--disable-openmax \
	--enable-gles \
	--enable-udev \
	--enable-codec=imxvpu \
	--disable-texturepacker \
	--enable-airplay \
	--enable-airtunes \
	--enable-optimizations \
	--enable-avahi \
	--disable-mid \
	--enable-rsxs \
	--enable-libcec \
	LIBS=' -llzma '"

CXXFLAGS += " -I${STAGING_KERNEL_DIR}/include/uapi -I${STAGING_KERNEL_DIR}/include "
CFLAGS += " -I${STAGING_KERNEL_DIR}/include/uapi -I${STAGING_KERNEL_DIR}/include "

FILES_${PN} += "/imx6 /usr/share/icons/hicolor"


EXTRA_OEMAKE = "'BUILDDIR=${S}/build'"


do_configure() {
   export PYTHON_EXTRA_LDFLAGS=""
   export PYTHON_EXTRA_LIBS="-lz"
   export PYTHON_VERSION="${PYTHON_BASEVERSION}"
   export PYTHON_NOVERSIONCHECK="no-check"
   export PYTHON_CPPFLAGS="-I/${STAGING_INCDIR}/${PYTHON_DIR}"
   export PYTHON_LDFLAGS="-L${STAGING_LIBDIR} -lpython${PYTHON_BASEVERSION}"
   cd ${S}
   sh bootstrap
   sh configure ${EXTRA_OECONF}
}

do_compile() {
   cd ${S}
   make -j 8 BUILDDIR=${BUILDDIR} DESTDIR=${D}
}

do_install() {
   cd ${S}
   make -j 8 BUILDDIR=${BUILDDIR} DESTDIR=${D} install
}

INHIBIT_PACKAGE_DEBUG_SPLIT = "1"
INHIBIT_PACKAGE_STRIP = "1"

PACKAGES = "${PN}"




