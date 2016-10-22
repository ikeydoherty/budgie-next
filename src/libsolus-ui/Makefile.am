include $(top_srcdir)/common.mk

lib_LTLIBRARIES = \
	libsolus-ui.la

libsolus_ui_la_SOURCES = \
	main.c \
	util.h \
	radial-progress.h \
	radial-progress.c

libsolus_ui_la_CFLAGS = \
	$(GTK_CFLAGS) \
	$(AM_CFLAGS)

libsolus_ui_la_LIBADD = \
	$(GTK_LIBS)
