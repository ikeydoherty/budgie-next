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

#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef struct _BudgiePanelWindowPrivate BudgiePanelWindowPrivate;
typedef struct _BudgiePanelWindow BudgiePanelWindow;
typedef struct _BudgiePanelWindowClass BudgiePanelWindowClass;

#define BUDGIE_TYPE_PANEL_WINDOW budgie_panel_window_get_type()
#define BUDGIE_PANEL_WINDOW(o)                                                                     \
        (G_TYPE_CHECK_INSTANCE_CAST((o), BUDGIE_TYPE_PANEL_WINDOW, BudgiePanelWindow))
#define BUDGIE_IS_PANEL_WINDOW(o) (G_TYPE_CHECK_INSTANCE_TYPE((o), BUDGIE_TYPE_PANEL_WINDOW))
#define BUDGIE_PANEL_WINDOW_CLASS(o)                                                               \
        (G_TYPE_CHECK_CLASS_CAST((o), BUDGIE_TYPE_PANEL_WINDOW, BudgiePanelWindowClass))
#define BUDGIE_IS_PANEL_WINDOW_CLASS(o) (G_TYPE_CHECK_CLASS_TYPE((o), BUDGIE_TYPE_PANEL_WINDOW))
#define BUDGIE_PANEL_WINDOW_GET_CLASS(o)                                                           \
        (G_TYPE_INSTANCE_GET_CLASS((o), BUDGIE_TYPE_PANEL_WINDOW, BudgiePanelWindowClass))

/**
 * The position to set the panel to
 */
typedef enum {
        PANEL_POSITION_MIN = 1 << 0,
        PANEL_POSITION_TOP = 1 << 1,
        PANEL_POSITION_BOTTOM = 1 << 2,
        PANEL_POSITION_LEFT = 1 << 3,
        PANEL_POSITION_RIGHT = 1 << 4,
        PANEL_POSITION_MAX = 1 << 5
} PanelPosition;

struct _BudgiePanelWindowClass {
        GtkWindowClass parent_class;
};

struct _BudgiePanelWindow {
        GtkWindow parent;
        BudgiePanelWindowPrivate *priv;

        /** Currently runtime stuff, in future will be a BudgiePanelX11Window */
        void (*set_struts)(BudgiePanelWindow *, gint, PanelPosition);
};

GtkWidget *budgie_panel_window_new(void);

GType budgie_panel_window_get_type(void);

/**
 * Set the position of the panel to be that of @position on the given @monitor
 *
 * @note This is currently X11 specific.
 *
 * @position: The number of the monitor to place the panel. -1 means primary monitor.
 */
void budgie_panel_window_set_position(BudgiePanelWindow *self, gint monitor,
                                      PanelPosition position);

/**
 * Update the struts for this panel using the display protocol specific method
 */
void budgie_panel_window_set_struts(BudgiePanelWindow *self, gint monitor, PanelPosition position);

G_END_DECLS

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
