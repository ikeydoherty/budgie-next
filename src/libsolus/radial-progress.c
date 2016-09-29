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

#define _GNU_SOURCE

#include "util.h"

SOLUS_BEGIN_INCLUDES
#include "radial-progress.h"
SOLUS_END_INCLUDES

#include <math.h>

enum { PROP_FRACTION = 1, N_PROPS };

/**
 * Precompute this, no sense in calculating it at runtime. 90 degree offset
 */
#define RADIAL_DEFAULT_OFFSET (-(2.0 * M_PI * 0.25))

struct _SuRadialProgressPrivate {
        gdouble fraction;
        gdouble radial_offset;
        gdouble start_angle;
        gdouble end_angle;
};

static GParamSpec *obj_properties[N_PROPS] = {
        NULL,
};

G_DEFINE_TYPE_WITH_PRIVATE(SuRadialProgress, su_radial_progress, GTK_TYPE_DRAWING_AREA)

/**
 * Convert the given fractional "fraction" property into radians
 */
static inline gdouble fraction_to_radians(gdouble fraction)
{
        return 2.0 * M_PI * fraction;
}

/**
 * Precalculate angles so we don't do them on every draw
 */
static void su_radial_progress_update_internal(SuRadialProgress *self)
{
        self->priv->start_angle = self->priv->radial_offset;
        self->priv->end_angle =
            fraction_to_radians(self->priv->fraction) + self->priv->radial_offset;
        gtk_widget_queue_draw(GTK_WIDGET(self));
}

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
                su_radial_progress_update_internal(self);
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
 * Do the actual drawing
 */
static gboolean su_radial_progress_draw(GtkWidget *widget, cairo_t *cr)
{
        GtkAllocation alloc;
        gdouble radius;
        gdouble line_width_outer = 4;
        SuRadialProgress *self = NULL;
        GdkRGBA fg, track = { 0 };

        self = SU_RADIAL_PROGRESS(widget);

        gtk_widget_get_allocation(widget, &alloc);

        /* Antialias or gtfo */
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_SUBPIXEL);

        /* Move to center point */
        cairo_translate(cr, alloc.width / 2, alloc.height / 2);

        /* Keep it bound */
        radius = ((MIN(alloc.width, alloc.height)) / 2) - (line_width_outer * 2);

        /* Temporary colours */
        gdk_rgba_parse(&track, "#E5E5E5");
        gdk_rgba_parse(&fg, "#2F9CE0");

        /* Render the track, full circle */
        cairo_save(cr);
        cairo_set_source_rgba(cr, track.red, track.green, track.blue, track.alpha);
        cairo_set_line_width(cr, line_width_outer);
        cairo_arc(cr, 0, 0, radius, 0.0, 2.0 * M_PI);
        cairo_stroke(cr);
        cairo_restore(cr);

        /* Render the progress arc */
        cairo_save(cr);
        cairo_set_source_rgba(cr, fg.red, fg.green, fg.blue, fg.alpha);
        cairo_set_line_width(cr, line_width_outer);
        cairo_arc(cr, 0, 0, radius, self->priv->start_angle, self->priv->end_angle);
        cairo_stroke(cr);
        cairo_restore(cr);

        return GDK_EVENT_STOP;
}

/**
 * Class initialisation
 */
static void su_radial_progress_class_init(SuRadialProgressClass *klazz)
{
        GObjectClass *obj_class = G_OBJECT_CLASS(klazz);
        GtkWidgetClass *wid_class = GTK_WIDGET_CLASS(klazz);

        /* gobject vtable hookup */
        obj_class->dispose = su_radial_progress_dispose;
        obj_class->get_property = su_radial_progress_get_property;
        obj_class->set_property = su_radial_progress_set_property;

        /* widget vtable hookup */
        wid_class->draw = su_radial_progress_draw;

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
        su_radial_progress_update_internal(self);
}

/**
 * Instaniation
 */
static void su_radial_progress_init(SuRadialProgress *self)
{
        self->priv = su_radial_progress_get_instance_private(self);
        self->priv->radial_offset = RADIAL_DEFAULT_OFFSET;

        /* Update internal state before rendering */
        su_radial_progress_update_internal(self);

        /* TODO: Remove this fugly hack!! Only here until render code is done */
        gtk_widget_set_size_request(GTK_WIDGET(self), 64, 64);
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
