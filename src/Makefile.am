bin_PROGRAMS = libweston_tutorial 

AM_CFLAGS =  \
	-std=c99 \
	-rdynamic \
	$(X11_CFLAGS) \
	$(PIXMAN_CFLAGS) \
	$(WESTON_CFLAGS) \
	$(WAYLAND_CFLAGS) \
	-fno-strict-aliasing


BUILT_SOURCES = \
	xdg-shell-protocol.c \
	xdg-shell-server-protocol.h

libweston_tutorial_SOURCES = \
	main.c \
	compositor.c \
	compositor.h \
	xdg_shell.c \
	xdg_shell.h \
	xdg-shell-protocol.c
	
libweston_tutorial_LDADD = \
	$(X11_LIBS) \
	$(PIXMAN_LIBS) \
	$(WESTON_LIBS) \
	$(WAYLAND_LIBS) 

%-protocol.c : $(top_srcdir)/protocol/%.xml
	$(wayland_scanner) code < $< > $@

%-server-protocol.h : $(top_srcdir)/protocol/%.xml
	$(wayland_scanner) server-header < $< > $@

%-client-protocol.h : $(top_srcdir)/protocol/%.xml
	$(wayland_scanner) client-header < $< > $@

