AC_INIT([Anti Budgie], 1, [ikey@solus-project.com], [anti-budgie], [https://solus-project.com/])
AM_INIT_AUTOMAKE([-Wno-portability no-dist-gzip dist-xz foreign subdir-objects])
AC_PROG_CC
AC_PROG_CC_STDC
LT_PREREQ(2.2)
LT_INIT([disable-static])

AC_PREFIX_DEFAULT(/usr/local)
AM_SILENT_RULES([yes])
AC_CONFIG_MACRO_DIR([m4])

m4_define([glib_required_version], [2.48.0])
m4_define([gtk_required_version], [3.20.0])


PKG_CHECK_MODULES([GTK],
                [
                 gobject-2.0 >= glib_required_version,
                 gio-2.0 >= glib_required_version,
                 gio-unix-2.0 >= glib_required_version,
                 gtk+-3.0 >= gtk_required_version
                ]
)

# We require support for a number of GCC attributes in anti-budgie
AX_GCC_VAR_ATTRIBUTE(cleanup)
AX_GCC_VAR_ATTRIBUTE(unused)


AH_TOP([#ifndef CONFIG_H_INCLUDED
	#define CONFIG_H_INCLUDED 1])
AH_BOTTOM([#endif])
AC_CONFIG_HEADERS([config.h])


AC_CONFIG_FILES([Makefile
                src/Makefile
                src/libsolus/Makefile])

AC_OUTPUT

AC_MSG_RESULT([
        anti-budgie $VERSION
        =====================

        prefix:                 ${prefix}
        libdir:                 ${libdir}
        sysconfdir:             ${sysconfdir}
        exec_prefix:            ${exec_prefix}
        bindir:                 ${bindir}
        datarootdir:            ${datarootdir}

        compiler:               ${CC}
        cflags:                 ${CFLAGS}
        ldflags:                ${LDFLAGS}
])
