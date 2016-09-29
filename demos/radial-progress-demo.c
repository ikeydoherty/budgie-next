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

static inline void stylize_frame(GtkWidget *frame_widget)
{
        GtkFrame *frame = GTK_FRAME(frame_widget);
        GtkWidget *label = gtk_frame_get_label_widget(frame);

        gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
        g_object_set(label, "margin-left", 3, "margin-right", 3, NULL);
        g_object_set(gtk_bin_get_child(GTK_BIN(frame)), "margin", 10, NULL);
        g_object_set(frame, "margin", 10, NULL);
}

int main(int argc, char **argv)
{
        gtk_init(&argc, &argv);
        GtkWidget *window, *box, *radial, *frame, *progress = NULL;
        GtkSizeGroup *sgroup = NULL;

        sgroup = gtk_size_group_new(GTK_SIZE_GROUP_VERTICAL);

        /* Set up the window */
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        g_signal_connect(window, "delete-event", gtk_main_quit, NULL);
        gtk_window_set_title(GTK_WINDOW(window), "Radial Progress Demo");
        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
        gtk_container_set_border_width(GTK_CONTAINER(window), 100);

        /* Box */
        box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_container_add(GTK_CONTAINER(window), box);

        /* Radial rogress */
        radial = su_radial_progress_new();
        frame = gtk_frame_new("<b>SuRadialProgress</b>");
        gtk_container_add(GTK_CONTAINER(frame), radial);
        gtk_box_pack_start(GTK_BOX(box), frame, FALSE, FALSE, 0);
        stylize_frame(frame);
        gtk_size_group_add_widget(sgroup, frame);

        /* Legacy progress */
        progress = gtk_progress_bar_new();
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress), 0.6);
        frame = gtk_frame_new("<b>GtkProgressBar</b>");
        gtk_container_add(GTK_CONTAINER(frame), progress);
        gtk_box_pack_start(GTK_BOX(box), frame, FALSE, FALSE, 0);
        stylize_frame(frame);
        gtk_size_group_add_widget(sgroup, frame);

        /* Show the widget tree */
        gtk_widget_show_all(window);

        /* Main loop */
        gtk_main();

        g_object_unref(G_OBJECT(sgroup));

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
