/*
 * This file is part of budgie-next
 *
 * Copyright © 2016 Ikey Doherty <ikey@solus-project.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

#include "panel-window.h"
#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef struct _BudgiePanelX11Window BudgiePanelX11Window;
typedef struct _BudgiePanelX11WindowClass BudgiePanelX11WindowClass;

#define BUDGIE_TYPE_PANEL_X11_WINDOW budgie_panel_x11_window_get_type()
#define BUDGIE_PANEL_X11_WINDOW(o)                                                                 \
        (G_TYPE_CHECK_INSTANCE_CAST((o), BUDGIE_TYPE_PANEL_X11_WINDOW, BudgiePanelX11Window))
#define BUDGIE_IS_PANEL_X11_WINDOW(o)                                                              \
        (G_TYPE_CHECK_INSTANCE_TYPE((o), BUDGIE_TYPE_PANEL_X11_WINDOW))
#define BUDGIE_PANEL_X11_WINDOW_CLASS(o)                                                           \
        (G_TYPE_CHECK_CLASS_CAST((o), BUDGIE_TYPE_PANEL_X11_WINDOW, BudgiePanelX11WindowClass))
#define BUDGIE_IS_PANEL_X11_WINDOW_CLASS(o)                                                        \
        (G_TYPE_CHECK_CLASS_TYPE((o), BUDGIE_TYPE_PANEL_X11_WINDOW))
#define BUDGIE_PANEL_X11_WINDOW_GET_CLASS(o)                                                       \
        (G_TYPE_INSTANCE_GET_CLASS((o), BUDGIE_TYPE_PANEL_X11_WINDOW, BudgiePanelX11WindowClass))

struct _BudgiePanelX11WindowClass {
        BudgiePanelWindowClass parent_class;
};

struct _BudgiePanelX11Window {
        BudgiePanelWindow parent;
};

GtkWidget *budgie_panel_x11_window_new(void);

GType budgie_panel_x11_window_get_type(void);

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
