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
        int __reserved1;
};

G_DEFINE_TYPE_WITH_PRIVATE(BudgiePanelWindow, budgie_panel_window, GTK_TYPE_WINDOW)

/**
 * budgie_panel_window_new:
 *
 * Construct a new BudgiePanelWindow widget
 */
GtkWidget *budgie_panel_window_new()
{
        return g_object_new(BUDGIE_TYPE_PANEL_WINDOW, NULL);
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

        g_signal_connect(G_OBJECT(self), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
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
