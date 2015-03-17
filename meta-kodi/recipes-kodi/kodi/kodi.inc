# Based on meta-stef by Wolfgar

DESCRIPTION = "Kodi - Media player and entertainment hub"
LICENSE = "GPLv2"

LIC_FILES_CHKSUM = "file://LICENSE.GPL;md5=930e2a5f63425d8dd72dbd7391c43c46"

DEPENDS = " \
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
"

DEPENDS_append = " virtual/kernel \
                   virtual/libgles2 \
                   virtual/egl \
                 "

DEPENDS_append_mx6 = " libfslvpuwrap \
                       libcec-imx \
                     "
# todo: libbluray 

RDEPENDS_${PN} = "lsb \
                  ${PN}-bin \
                 "

INC_PR = "r1"
SRC_URI = "git://github.com/xbmc/xbmc.git;branch=Helix"
SRC_URI += "file://Fix_JsonSchemaBuilder_build.patch"

S = "${WORKDIR}/git/"

inherit autotools lib_package pkgconfig gettext python-dir
EXTRA_OECONF=" --disable-debug \
	--build=${BUILD_SYS} \
	--host=${HOST_SYS} \
	--target=${TARGET_SYS} ${@append_libtool_sysroot(d)} \
	--disable-rpath \
	--disable-pulse \
	--disable-projectm \
	--disable-x11 \
	--disable-libcec \
	--disable-tiff \
	--disable-xrandr \
	--disable-gl \
	--disable-vdpau \
	--disable-vaapi \
	--disable-openmax \
	--enable-gles \
	--enable-udev \
	--disable-texturepacker \
	--enable-airplay \
	--enable-airtunes \
	--enable-optimizations \
	--enable-avahi \
	--disable-mid \
	--enable-rsxs \
	LIBS=' -llzma ' \
           "

EXTRA_OECONF_append = "${@bb.utils.contains('MACHINE', 'mx6', ' --prefix=/imx6/xbmc', ' --prefix=/usr', d)}"

#With no sdl, they will have no joystick ...
EXTRA_OECONF_append=" --disable-sdl \
	              --disable-joystick \
	            "


CXXFLAGS += " -I${STAGING_KERNEL_DIR}/include/uapi -I${STAGING_KERNEL_DIR}/include "
CFLAGS += " -I${STAGING_KERNEL_DIR}/include/uapi -I${STAGING_KERNEL_DIR}/include "

FILES_${PN} += "/usr/share/icons/hicolor"
FILES_${PN}_mx6 += " /imx6"


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
   rm -fr   ${D}/usr/lib/xbmc
   rm -fr   ${D}/usr/share/xbmc
   rm -f   ${D}/usr/share/xsessions/xbmc.desktop
}

INHIBIT_PACKAGE_DEBUG_SPLIT = "1"
INHIBIT_PACKAGE_STRIP = "1"

FILES_${PN} += "/usr/share/xsessions/kodi.desktop"
