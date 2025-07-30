# NetSurf Mac OS 9 Port Makefile
# For use with Retro68 toolchain

TARGET = NetSurf
SOURCES = src/main.c src/gui.c src/window.c src/bitmap.c src/fetch.c \
          src/schedule.c src/misc.c src/layout.c src/utf8.c src/file.c \
          src/download.c src/clipboard.c src/search.c src/local_history.c \
          src/plotters.c src/font.c

OBJECTS = $(SOURCES:.c=.o)
RESOURCES = Resources/NetSurf.r

CC = m68k-apple-macos-gcc
REZ = Rez
CFLAGS = -Os -I./include -DTARGET_API_MAC_CARBON=1 -DNETSURF_MACOS9=1
LDFLAGS = -framework Carbon -framework ToolboxEssentials

NETSURF_LIBS = -lnetsurf -lcss -ldom -lhubbub -lparserutils -lwapcaplet \
               -lnsgif -lnsbmp -lnsutils -lsvgtiny

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS) $(TARGET).rsrc
$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(NETSURF_LIBS)
DeRez $(TARGET).rsrc > $(TARGET).r
Rez $(TARGET).r -o $(TARGET) -append

$(TARGET).rsrc: $(RESOURCES)
$(REZ) $(RESOURCES) -o $@

%.o: %.c
$(CC) $(CFLAGS) -c $< -o $@

clean:
rm -f $(OBJECTS) $(TARGET) $(TARGET).rsrc $(TARGET).r

src/main.o: include/macos9_gui.h
src/gui.o: include/macos9_gui.h  
src/window.o: include/macos9_gui.h
src/bitmap.o: include/macos9_gui.h
src/fetch.o: include/macos9_gui.h
src/schedule.o: include/macos9_gui.h
src/misc.o: include/macos9_gui.h
src/layout.o: include/macos9_gui.h
src/utf8.o: include/macos9_gui.h
src/file.o: include/macos9_gui.h
src/download.o: include/macos9_gui.h
src/clipboard.o: include/macos9_gui.h
src/search.o: include/macos9_gui.h
src/local_history.o: include/macos9_gui.h
src/plotters.o: include/macos9_gui.h
src/font.o: include/macos9_gui.h
