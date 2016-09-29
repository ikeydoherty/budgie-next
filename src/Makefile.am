include $(top_srcdir)/common.mk

lib_LTLIBRARIES = \
	libsolus.la

libsolus_la_SOURCES = \
	main.c \
	util.h

libsolus_la_CFLAGS = \
	$(GTK_CFLAGS) \
	$(AM_CFLAGS)

libsolus_la_LIBADD = \
	$(GTK_LIBS)
