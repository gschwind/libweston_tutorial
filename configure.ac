AC_INIT([libweston_tutorial], [0.0.1])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([-Wall])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([src/config.h])

CHECK_GNU_MAKE

dnl Check for required programs

AC_PROG_CC_C99
AC_PROG_LIBTOOL

dnl Check required modules

PKG_CHECK_MODULES(X11, x11 >= 1.3.2)
AC_SUBST(X11_CFLAGS)
AC_SUBST(X11_LIBS)

PKG_CHECK_MODULES(PIXMAN, pixman-1 >= 0.32.0)
AC_SUBST(PIXMAN_CFLAGS)
AC_SUBST(PIXMAN_LIBS)

PKG_CHECK_MODULES(WESTON, [libweston-1 >= 1.8.0])
AC_SUBST(WESTON_CFLAGS)
AC_SUBST(WESTON_LIBS)

PKG_CHECK_MODULES(WAYLAND, wayland-server >= 1.9.0)
AC_SUBST(WAYLAND_CFLAGS)
AC_SUBST(WAYLAND_LIBS)

dnl check required tools

AC_PATH_PROG([wayland_scanner], [wayland-scanner], [wayland-scanner])
if test x$wayland_scanner = x; then
	PKG_CHECK_MODULES(WAYLAND_SCANNER, [wayland-scanner])
	wayland_scanner=`$PKG_CONFIG --variable=wayland_scanner wayland-scanner`
fi

AC_CONFIG_FILES([
  Makefile
  src/Makefile
  ])

AC_OUTPUT
