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

enum { PROP_FRACTION = 1, N_PROPS };

struct _SuRadialProgressPrivate {
        gdouble fraction;
};

static GParamSpec *obj_properties[N_PROPS] = {
        NULL,
};

G_DEFINE_TYPE_WITH_PRIVATE(SuRadialProgress, su_radial_progress, GTK_TYPE_DRAWING_AREA)

/**
 * Set GObject properties
 */
static void su_radial_progress_set_property(GObject *object, guint id, const GValue *value,
                                            GParamSpec *spec)
{
        SuRadialProgress *self = SU_RADIAL_PROGRESS(object);

        switch (id) {
        case PROP_FRACTION:
                self->priv->fraction = g_value_get_double(value);
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID(object, id, spec);
                break;
        }
}

/**
 * Get GObject properties
 */
static void su_radial_progress_get_property(GObject *object, guint id, GValue *value,
                                            GParamSpec *spec)
{
        SuRadialProgress *self = SU_RADIAL_PROGRESS(object);

        switch (id) {
        case PROP_FRACTION:
                g_value_set_double(value, self->priv->fraction);
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID(object, id, spec);
                break;
        }
}

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

        /* vtable hookup */
        obj_class->dispose = su_radial_progress_dispose;
        obj_class->get_property = su_radial_progress_get_property;
        obj_class->set_property = su_radial_progress_set_property;

        /**
         * SuRadialProgress:fraction:
         *
         * The completion factor of the progress display
         */
        obj_properties[PROP_FRACTION] =
            g_param_spec_double("fraction",
                                "Progress fraction",
                                "The completion of this progress widget",
                                0.0,
                                1.0,
                                0.0,
                                G_PARAM_READWRITE);

        g_object_class_install_properties(obj_class, N_PROPS, obj_properties);
}

/**
 * Object methods
 */

/**
 * su_radial_progress_get_fraction:
 *
 * Get the fraction used by this SuRadialProgress
 */
gdouble su_radial_progress_get_fraction(SuRadialProgress *self)
{
        g_return_val_if_fail(self != NULL, -1.0);
        return self->priv->fraction;
}

/**
 * su_radial_progress_set_fraction:
 *
 * Set the fraction for this SuRadialProgress
 */
void su_radial_progress_set_fraction(SuRadialProgress *self, gdouble fraction)
{
        g_return_if_fail(self != NULL);
        gdouble nfraction = CLAMP(fraction, 0.0, 1.0);
        self->priv->fraction = nfraction;
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
