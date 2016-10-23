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
#include "panel-window.h"
SOLUS_END_PEDANTIC

struct _BudgiePanelWindowPrivate {
        gint size_extent;
};

G_DEFINE_TYPE_WITH_PRIVATE(BudgiePanelWindow, budgie_panel_window, GTK_TYPE_WINDOW)

/**
 * budgie_panel_window_new:
 *
 * Construct a new BudgiePanelWindow widget
 */
GtkWidget *budgie_panel_window_new()
{
        return g_object_new(BUDGIE_TYPE_PANEL_WINDOW, "type", GTK_WINDOW_TOPLEVEL, NULL);
}

/**
 * Handle cleanup
 */
static void budgie_panel_window_dispose(__solus_unused__ GObject *obj)
{
        /* skip for now */
}

/**
 * Class initialisation
 */
static void budgie_panel_window_class_init(BudgiePanelWindowClass *klazz)
{
        GObjectClass *obj_class = G_OBJECT_CLASS(klazz);

        /* gobject vtable hookup */
        obj_class->dispose = budgie_panel_window_dispose;
}

/**
 * Instaniation
 */
static void budgie_panel_window_init(BudgiePanelWindow *self)
{
        self->priv = budgie_panel_window_get_instance_private(self);

        /* Initialise private variables */
        self->priv->size_extent = 40;

        /* Hacky for testing. */
        gtk_window_set_skip_pager_hint(GTK_WINDOW(self), TRUE);
        gtk_window_set_skip_taskbar_hint(GTK_WINDOW(self), TRUE);
        gtk_window_set_type_hint(GTK_WINDOW(self), GDK_WINDOW_TYPE_HINT_DOCK);
        gtk_window_set_decorated(GTK_WINDOW(self), FALSE);

        /* Again, testing. */
        budgie_panel_window_set_position(self, -1, PANEL_POSITION_BOTTOM);
        budgie_panel_window_set_struts(self, -1, PANEL_POSITION_BOTTOM);
}

void budgie_panel_window_set_position(BudgiePanelWindow *self, gint monitor, PanelPosition position)
{
        GdkScreen *screen = NULL;
        gint monitor_number = monitor;
        GdkRectangle monitor_geom = { 0 };
        gint monitor_count = 0;
        gint panel_x = 0, panel_y = 0;
        gint panel_w = 0, panel_h = 0;

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

        gdk_screen_get_monitor_geometry(screen, monitor_number, &monitor_geom);

        /* Determine size and position geometry */
        switch (position) {
        case PANEL_POSITION_TOP:
                panel_w = monitor_geom.width;
                panel_h = self->priv->size_extent;
                panel_x = monitor_geom.x;
                panel_y = monitor_geom.y;
                break;
        case PANEL_POSITION_BOTTOM:
                panel_w = monitor_geom.width;
                panel_h = self->priv->size_extent;
                panel_x = monitor_geom.x;
                panel_y = monitor_geom.y + (monitor_geom.height - self->priv->size_extent);
                break;
        case PANEL_POSITION_LEFT:
                panel_w = self->priv->size_extent;
                panel_h = monitor_geom.height;
                panel_x = monitor_geom.x;
                panel_y = monitor_geom.y;
                break;
        case PANEL_POSITION_RIGHT:
                panel_w = self->priv->size_extent;
                panel_h = monitor_geom.height;
                panel_x = monitor_geom.x + (monitor_geom.width - self->priv->size_extent);
                panel_y = monitor_geom.y;
                break;
        default:
                g_assert_not_reached();
        }

        gtk_widget_set_size_request(GTK_WIDGET(self), panel_w, panel_h);
        gtk_window_move(GTK_WINDOW(self), panel_x, panel_y);
}

void budgie_panel_window_set_struts(BudgiePanelWindow *self, gint monitor, PanelPosition position)
{
        BudgiePanelWindowClass *klazz = NULL;

        klazz = BUDGIE_PANEL_WINDOW_GET_CLASS(self);
        if (!klazz->set_struts) {
                g_warning("No set_struts implementation available on this display");
                return;
        }
        klazz->set_struts(self, monitor, position);
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
