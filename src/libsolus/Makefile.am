include $(top_srcdir)/common.mk

lib_LTLIBRARIES = \
	libsolus.la

libsolus_la_SOURCES = \
	main.c \
	util.h \
	radial-progress.h \
	radial-progress.c

libsolus_la_CFLAGS = \
	$(GTK_CFLAGS) \
	$(AM_CFLAGS)

libsolus_la_LIBADD = \
	$(GTK_LIBS)
