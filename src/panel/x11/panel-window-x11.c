/*
 * This file is part of budgie-next
 *
 * Copyright © 2016 Ikey Doherty <ikey@solus-project.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */

#define _GNU_SOURCE

#include "util.h"

SOLUS_BEGIN_PEDANTIC
#include "panel-window-private.h"
#include "panel-window-x11.h"
SOLUS_END_PEDANTIC

G_DEFINE_TYPE(BudgiePanelX11Window, budgie_panel_x11_window, BUDGIE_TYPE_PANEL_WINDOW)

static void budgie_panel_x11_window_set_struts(BudgiePanelWindow *self, gint primary_monitor,
                                               PanelPosition position);

/** Atoms used specifically on X11 */
static GdkAtom atom_wm_partial;
static GdkAtom atom_cardinal;

/**
 * budgie_panel_x11_window_new:
 *
 * Construct a new BudgiePanelX11Window widget
 */
GtkWidget *budgie_panel_x11_window_new()
{
        return g_object_new(BUDGIE_TYPE_PANEL_X11_WINDOW, NULL);
}

/**
 * Handle cleanup
 */
static void budgie_panel_x11_window_dispose(GObject *obj)
{
        G_OBJECT_CLASS(budgie_panel_x11_window_parent_class)->dispose(obj);
}

/**
 * Class initialisation
 */
static void budgie_panel_x11_window_class_init(BudgiePanelX11WindowClass *klazz)
{
        GObjectClass *obj_class = G_OBJECT_CLASS(klazz);
        BudgiePanelWindowClass *panel_class = BUDGIE_PANEL_WINDOW_CLASS(klazz);

        /* gobject vtable hookup */
        obj_class->dispose = budgie_panel_x11_window_dispose;

        /* panel vtable hookup */
        panel_class->set_struts = budgie_panel_x11_window_set_struts;
}

/**
 * Initialise atoms once and once only
 */
static void budgie_panel_x11_window_init_xatoms(void)
{
        atom_wm_partial = gdk_atom_intern("_NET_WM_STRUT_PARTIAL", FALSE);
        atom_cardinal = gdk_atom_intern("CARDINAL", FALSE);
}

/**
 * Instaniation
 */
static void budgie_panel_x11_window_init(__solus_unused__ BudgiePanelX11Window *self)
{
        budgie_panel_x11_window_init_xatoms();
}

static void budgie_panel_x11_window_set_struts(BudgiePanelWindow *self, gint monitor,
                                               PanelPosition position)
{
        GdkWindow *window = NULL;
        GdkRectangle mg = { 0 };
        GdkScreen *screen = NULL;
        long *struts = NULL;
        gint monitor_number = monitor;
        gint monitor_count = 0;
        gint screen_height = 0;
        gint ps = self->priv->size_extent;

        /* Ensure we have a window + realized state */
        window = gtk_widget_get_window(GTK_WIDGET(self));
        if (!window) {
                return;
        }
        if (!gtk_widget_get_realized(GTK_WIDGET(self))) {
                return;
        }

        screen = gtk_widget_get_screen(GTK_WIDGET(self));
        monitor_count = gdk_screen_get_n_monitors(screen);
        /* <1 = primary monitor */
        if (monitor_number < 0) {
                monitor_number = gdk_screen_get_primary_monitor(screen);
        }

        /* Useful during development */
        if (monitor_number > monitor_count) {
                g_warning("monitor_number > monitor_count: %d %d\n", monitor_number, monitor_count);
        }

        screen_height = gdk_screen_get_height(screen);
        gdk_screen_get_monitor_geometry(screen, monitor_number, &mg);

        /* Determine the appropriate struts for the given position */
        switch (position) {
        case PANEL_POSITION_TOP:
                struts =
                    (long[]){ 0, 0, mg.y + ps, 0, 0, 0, 0, 0, mg.x, (mg.x + mg.width) - 1, 0, 0 };
                break;
        case PANEL_POSITION_BOTTOM:
                struts = (long[]){ 0, 0, 0,    (screen_height - mg.height - mg.y) + ps,
                                   0, 0, 0,    0,
                                   0, 0, mg.x, (mg.x + mg.width) - 1 };
                break;
        case PANEL_POSITION_LEFT:
                struts = (long[]){ ps, 0, 0, 0, mg.y, mg.y + mg.height, 0, 0, 0, 0, 0, 0 };
                break;
        case PANEL_POSITION_RIGHT:
                struts = (long[]){ 0, ps, 0, 0, 0, 0, mg.y, mg.y + mg.height, 0, 0, 0, 0 };
                break;
        default:
                g_assert_not_reached();
        }

        /* Fire off the property change */
        gdk_property_change(window,
                            atom_wm_partial,
                            atom_cardinal,
                            32,
                            GDK_PROP_MODE_REPLACE,
                            (guchar *)struts,
                            12);
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 expandtab:
 * :indentSize=8:tabSize=8:noTabs=true:
 */
