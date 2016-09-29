/*
 * This file is part of anti-budgie
 *
 * Copyright © 2016 Ikey Doherty <ikey@solus-project.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include "util.h"

SOLUS_BEGIN_INCLUDES
#include "radial-progress.h"
SOLUS_END_INCLUDES

#include <stdlib.h>

int main(int argc, char **argv)
{
        gtk_init(&argc, &argv);
        GtkWidget *window, *box, *radial = NULL;

        /* Set up the window */
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        g_signal_connect(window, "delete-event", gtk_main_quit, NULL);
        gtk_window_set_title(GTK_WINDOW(window), "Radial Progress Demo");

        /* Box */
        box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_container_add(GTK_CONTAINER(window), box);

        /* Progress */
        radial = su_radial_progress_new();
        gtk_box_pack_start(GTK_BOX(box), radial, FALSE, FALSE, 0);

        /* Show the widget tree */
        gtk_widget_show_all(window);

        /* Main loop */
        gtk_main();

        return EXIT_SUCCESS;
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
