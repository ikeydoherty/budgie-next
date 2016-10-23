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

#include <stdio.h>
#include <stdlib.h>

#include "util.h"

SOLUS_BEGIN_PEDANTIC
#include "panel-window.h"
#include "x11/panel-window-x11.h"
#include <gdk/gdkx.h>
SOLUS_END_PEDANTIC

int main(__solus_unused__ int argc, __solus_unused__ char **argv)
{
        gtk_init(&argc, &argv);
        GtkWidget *panel_window = NULL;
        GdkDisplay *display = NULL;

        display = gdk_display_get_default();
        if (GDK_IS_X11_DISPLAY(display)) {
                panel_window = budgie_panel_x11_window_new();
        } else {
                g_warning("Running fallback panel on unknown protocol");
                panel_window = budgie_panel_window_new();
        }

        gtk_widget_show_all(panel_window);
        gtk_main();

        gtk_widget_destroy(panel_window);

        return EXIT_FAILURE;
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
