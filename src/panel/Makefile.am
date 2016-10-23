include $(top_srcdir)/common.mk

bin_PROGRAMS = \
	budgie-next-panel

budgie_next_panel_SOURCES = \
	main.c \
	panel-window.h \
	panel-window.c \
	x11/panel-window-x11.h \
	x11/panel-window-x11.c

budgie_next_panel_CFLAGS = \
	$(GTK_CFLAGS) \
	$(AM_CFLAGS)

budgie_next_panel_LDADD = \
	$(GTK_LIBS)
