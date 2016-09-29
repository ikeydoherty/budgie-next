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

#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef struct _SuRadialProgressPrivate SuRadialProgressPrivate;
typedef struct _SuRadialProgress SuRadialProgress;
typedef struct _SuRadialProgressClass SuRadialProgressClass;

#define SU_TYPE_RADIAL_PROGRESS su_radial_progress_get_type()
#define SU_RADIAL_PROGRESS(o)                                                                      \
        (G_TYPE_CHECK_INSTANCE_CAST((o), SU_TYPE_RADIAL_PROGRESS, SuRadialProgress))
#define SU_IS_RADIAL_PROGRESS(o) (G_TYPE_CHECK_INSTANCE_TYPE((o), SU_TYPE_RADIAL_PROGRESS))
#define SU_RADIAL_PROGRESS_CLASS(o)                                                                \
        (G_TYPE_CHECK_CLASS_CAST((o), SU_TYPE_RADIAL_PROGRESS, SuRadialProgressClass))
#define SU_IS_RADIAL_PROGRESS_CLASS(o) (G_TYPE_CHECK_CLASS_TYPE((o), SU_TYPE_RADIAL_PROGRESS))
#define SU_RADIAL_PROGRESS_GET_CLASS(o)                                                            \
        (G_TYPE_INSTANCE_GET_CLASS((o), SU_TYPE_RADIAL_PROGRESS, SuRadialProgressClass))

struct _SuRadialProgressClass {
        GtkWidgetClass parent_class;
};

struct _SuRadialProgress {
        GtkWidget parent;
        SuRadialProgressPrivate *priv;
};

GtkWidget *su_radial_progress_new(void);

GType su_radial_progress_get_type(void);

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
