include $(top_srcdir)/common.mk

if HAVE_DEMOS

noinst_PROGRAMS = \
	radial-progress-demo

radial_progress_demo_SOURCES = \
	radial-progress-demo.c

radial_progress_demo_CFLAGS = \
	$(GTK_CFLAGS) \
	$(AM_CFLAGS)

radial_progress_demo_LDADD = \
  ../src/libsolus-ui/libsolus-ui.la \
  $(GTK_LIBS)


# Demos
endif
