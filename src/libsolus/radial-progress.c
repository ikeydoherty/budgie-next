/*
 * This file is part of anti-budgie
 *
 * Copyright © 2016 Ikey Doherty <ikey@solus-project.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */

#include "util.h"

SOLUS_BEGIN_INCLUDES
#include "radial-progress.h"
SOLUS_END_INCLUDES

struct _SuRadialProgressPrivate {
        int __reserved1;
};

G_DEFINE_TYPE_WITH_PRIVATE(SuRadialProgress, su_radial_progress, GTK_TYPE_WIDGET)

/**
 * su_radial_progress_new:
 *
 * Construct a new SuRadialProgress widget
 */
GtkWidget *su_radial_progress_new()
{
        return g_object_new(SU_TYPE_RADIAL_PROGRESS, NULL);
}

/**
 * Handle cleanup
 */
static void su_radial_progress_dispose(__solus_unused__ GObject *obj)
{
        /* skip for now */
}

/**
 * Class initialisation
 */
static void su_radial_progress_class_init(SuRadialProgressClass *klazz)
{
        GObjectClass *obj_class = G_OBJECT_CLASS(klazz);

        obj_class->dispose = su_radial_progress_dispose;
}

/**
 * Instaniation
 */
static void su_radial_progress_init(SuRadialProgress *self)
{
        self->priv = su_radial_progress_get_instance_private(self);
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
