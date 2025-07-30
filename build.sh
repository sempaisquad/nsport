#!/bin/bash

set -e

echo "Building NetSurf for Mac OS 9..."

export RETRO68=/usr/local/Retro68-build/toolchain
export PATH=$RETRO68/bin:$PATH
export TARGET=m68k-apple-macos

mkdir -p build/lib
mkdir -p build/include

echo "Building NetSurf libraries..."

if [ ! -f build/lib/libparserutils.a ]; then
    echo "Building libparserutils..."
    git clone https://github.com/netsurf-plan9/libparserutils.git temp/libparserutils
    cd temp/libparserutils
    make TARGET=m68k-apple-macos PREFIX=../../build
    make install TARGET=m68k-apple-macos PREFIX=../../build
    cd ../..
fi

if [ ! -f build/lib/libwapcaplet.a ]; then
    echo "Building libwapcaplet..."
    git clone https://github.com/netsurf-plan9/libwapcaplet.git temp/libwapcaplet
    cd temp/libwapcaplet
    make TARGET=m68k-apple-macos PREFIX=../../build
    make install TARGET=m68k-apple-macos PREFIX=../../build
    cd ../..
fi

if [ ! -f build/lib/libhubbub.a ]; then
    echo "Building libhubbub..."
    git clone https://github.com/netsurf-plan9/libhubbub.git temp/libhubbub
    cd temp/libhubbub
    make TARGET=m68k-apple-macos PREFIX=../../build
    make install TARGET=m68k-apple-macos PREFIX=../../build
    cd ../..
fi

if [ ! -f build/lib/libcss.a ]; then
    echo "Building libcss..."
    git clone https://github.com/netsurf-plan9/libcss.git temp/libcss
    cd temp/libcss
    make TARGET=m68k-apple-macos PREFIX=../../build
    make install TARGET=m68k-apple-macos PREFIX=../../build
    cd ../..
fi

if [ ! -f build/lib/libdom.a ]; then
    echo "Building libdom..."
    git clone https://github.com/netsurf-plan9/libdom.git temp/libdom
    cd temp/libdom
    make TARGET=m68k-apple-macos PREFIX=../../build
    make install TARGET=m68k-apple-macos PREFIX=../../build
    cd ../..
fi

for lib in libnsgif libnsbmp libsvgtiny; do
    if [ ! -f build/lib/${lib}.a ]; then
        echo "Building ${lib}..."
        git clone https://github.com/netsurf-plan9/${lib}.git temp/${lib}
        cd temp/${lib}
        make TARGET=m68k-apple-macos PREFIX=../../build
        make install TARGET=m68k-apple-macos PREFIX=../../build
        cd ../..
    fi
done

if [ ! -f build/lib/libnsutils.a ]; then
    echo "Building libnsutils..."
    git clone https://github.com/netsurf-plan9/libnsutils.git temp/libnsutils
    cd temp/libnsutils
    make TARGET=m68k-apple-macos PREFIX=../../build
    make install TARGET=m68k-apple-macos PREFIX=../../build
    cd ../..
fi

if [ ! -f build/lib/libnetsurf.a ]; then
    echo "Building NetSurf core..."
    git clone https://github.com/netsurf-plan9/netsurf.git temp/netsurf
    cd temp/netsurf
    make TARGET=m68k-apple-macos PREFIX=../../build libnetsurf.a
    cp libnetsurf.a ../../build/lib/
    cd ../..
fi

echo "Building NetSurf Mac OS 9 frontend..."

make clean
make CFLAGS="-Os -I./include -I./build/include -DTARGET_API_MAC_CARBON=1 -DNETSURF_MACOS9=1" \
     LDFLAGS="-L./build/lib -framework Carbon -framework ToolboxEssentials" \
     NETSURF_LIBS="-lnetsurf -lcss -ldom -lhubbub -lparserutils -lwapcaplet -lnsgif -lnsbmp -lnsutils -lsvgtiny"

echo "Build complete! NetSurf binary ready for Mac OS 9."
echo "To run on real hardware, transfer the NetSurf file to your Mac OS 9 system."
echo "To test in emulator, use: LaunchAPPL -e classic NetSurf"
