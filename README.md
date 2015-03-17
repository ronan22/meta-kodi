# meta-kodi
# Description
# How to test meta-kodi
The easy way to test the meta-kodi is to use the poky distribution.

A good point to start yocto :
 http://www.yoctoproject.org/docs/current/ref-manual/ref-manual.html

Note:
```text
> WORKINGDIR="~/WORKING"
> mkdir -p ${WORKINGDIR}
> cd ${WORKINGDIR}
```
## get poky, clone with Git (preferred)
* from dizzy revision
```text
> git clone -b dizzy git://git.yoctoproject.org/poky.git
```
* from master
```text
> git clone git://git.yoctoproject.org/poky.git
```
For more information:
 https://www.yoctoproject.org/downloads
 
## get meta-oe, clone with Git (preferred)
* from dizzy revision
```text
> git clone -b dizzy git@github.com:openembedded/meta-oe.git
```
* from master
```text
> git clone git@github.com:openembedded/meta-oe.git
```

## get meta-kodi:
```text
> git clone git@github.com:ronan22/meta-kodi.git
```

## init your project:
```text
> cd poky
> . oe-init-build-env build-kodi
```
## add your meta:
```text
> vi conf/bblayers.conf 
```
* Add meta-kodi path to BBLAYERS variable
* Add meta-oe path to BBLAYERS variable
 
## add your meta-kodi:
add LICENSE_FLAGS_WHITELIST
```text
> vi conf/local.conf
```
 LICENSE_FLAGS_WHITELIST += "commercial"

## Build your image:
```text
> bitbake kodi-image 
```
## Test your image:
On a terminal
```text
> runqemu qemux86 kodi-image
```

On a web navigator such as firefox, go to

http://192.168.7.2 and enjoy.

192.168.7.2 should be the address given to qemu machine by default

You should see a HTML Menu with file manager & Transmission (Torrent Client)


