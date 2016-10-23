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
#include "panel-window-x11.h"
SOLUS_END_PEDANTIC

G_DEFINE_TYPE(BudgiePanelX11Window, budgie_panel_x11_window, BUDGIE_TYPE_PANEL_WINDOW)

static void budgie_panel_x11_window_set_struts(BudgiePanelWindow *self, gint primary_monitor,
                                               PanelPosition position);

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
 * Instaniation
 */
static void budgie_panel_x11_window_init(__solus_unused__ BudgiePanelX11Window *self)
{
}

static void budgie_panel_x11_window_set_struts(__solus_unused__ BudgiePanelWindow *self,
                                               __solus_unused__ gint primary_monitor,
                                               __solus_unused__ PanelPosition position)
{
        g_message("BudgiePanelX11Window: Not yet implemented");
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
