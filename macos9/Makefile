TARGET = NetSurf
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)

CC = m68k-apple-macos-gcc
CFLAGS = -Os -I./include -DTARGET_API_MAC_CARBON=1 -DNETSURF_MACOS9=1
LDFLAGS = -framework Carbon -framework ToolboxEssentials
NETSURF_LIBS = -lnetsurf -lcss -ldom -lhubbub -lparserutils -lwapcaplet \
               -lnsgif -lnsbmp -lnsutils -lsvgtiny

all: $(TARGET)

$(TARGET): $(OBJECTS)
$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(NETSURF_LIBS)

%.o: %.c
$(CC) $(CFLAGS) -c $< -o $@

clean:
rm -f $(OBJECTS) $(TARGET)
