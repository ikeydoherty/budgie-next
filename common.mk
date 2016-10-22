AM_CFLAGS = -fstack-protector -Wall -pedantic \
        -Wstrict-prototypes -Wundef -fno-common \
        -Werror-implicit-function-declaration \
        -Wformat -Wformat-security -Werror=format-security \
        -Wno-conversion -Wunused-variable -Wunreachable-code \
        -Wall -W -D_FORTIFY_SOURCE=2 \
        -std=c11 -Wno-error

AM_CPPFLAGS = \
	-I $(top_srcdir)/src \
	-I $(top_srcdir)/src/libsolus \
	-I $(top_srcdir)/src/libsolus-ui

GTK_VERSIONING_FLAGS =						\
        -DGDK_VERSION_MAX_ALLOWED=GDK_VERSION_3_20              \
        -DGDK_VERSION_MIN_REQUIRED=GDK_VERSION_3_20             \
        -DGLIB_VERSION_MAX_ALLOWED=GLIB_VERSION_2_48            \
        -DGLIB_VERSION_MIN_REQUIRED=GLIB_VERSION_2_48
