## GEGL Video Degradation made better.
In default the Video Degradation filter in Gimp fuses with the overlay blend mode and it does not apply on a layer above non-destructively.
My plugin allows blend mode switching and non-destructive extraction of the video line effect. It also has a chroma and enlarge effect slider.


![image](https://github.com/LinuxBeaver/Fork-of-gegl-video-degradation/assets/78667207/1797520d-c00a-48d9-aef3-111212506878)


## OS specific location to put GEGL Filter binaries 

Windows
C:\Users\USERNAME\AppData\Local\gegl-0.4\plug-ins
 
 Linux 
 /home/(USERNAME)/.local/share/gegl-0.4/plug-ins
 
 Linux (Flatpak)
 /home/(USERNAME)/.var/app/org.gimp.GIMP/data/gegl-0.4/plug-ins



## Compiling and Installing

### Linux

To compile and install you will need the GEGL header files (`libgegl-dev` on
Debian based distributions or `gegl` on Arch Linux) and meson (`meson` on
most distributions).

```bash
meson setup --buildtype=release build
ninja -C build

```

If you have an older version of gegl you may need to copy to `~/.local/share/gegl-0.3/plug-ins`
instead (on Ubuntu 18.04 for example).



### Windows

The easiest way to compile this project on Windows is by using msys2.  Download
and install it from here: https://www.msys2.org/

Open a msys2 terminal with `C:\msys64\mingw64.exe`.  Run the following to
install required build dependencies:

```bash
pacman --noconfirm -S base-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-meson mingw-w64-x86_64-gegl
```

Then build the same way you would on Linux:

```bash
meson setup --buildtype=release build
ninja -C build
```

## Screenshots of it fusing with non default blend mode (overlay).

![image](https://github.com/LinuxBeaver/Fork-of-gegl-video-degradation/assets/78667207/516c3a04-9de0-4e92-b43a-b3ccafbc9382)

![image](https://github.com/LinuxBeaver/Fork-of-gegl-video-degradation/assets/78667207/19307ebd-9afd-462c-a48f-e8979fb4ce98)

![image](https://github.com/LinuxBeaver/Fork-of-gegl-video-degradation/assets/78667207/9e0b7d35-5ab7-4a7e-bdfe-a2e048ae7280)





