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
#include "theme-manager.h"
#include <budgie-desktop/theme.h>
#include <gtk/gtk.h>
SOLUS_END_PEDANTIC

struct _BudgieThemeManagerClass {
        GObjectClass parent_class;
};

struct _BudgieThemeManager {
        GObject parent;
        GtkCssProvider *css_provider;
};

static void budgie_theme_manager_set_theme_css(BudgieThemeManager *self,
                                               const gchar *theme_portion);

G_DEFINE_TYPE(BudgieThemeManager, budgie_theme_manager, G_TYPE_OBJECT)

/**
 * budgie_theme_manager_new:
 *
 * Construct a new BudgieThemeManager object
 */
BudgieThemeManager *budgie_theme_manager_new()
{
        return g_object_new(BUDGIE_TYPE_THEME_MANAGER, NULL);
}

/**
 * Handle cleanup
 */
static void budgie_theme_manager_dispose(GObject *obj)
{
        G_OBJECT_CLASS(budgie_theme_manager_parent_class)->dispose(obj);
}

/**
 * Class initialisation
 */
static void budgie_theme_manager_class_init(BudgieThemeManagerClass *klazz)
{
        GObjectClass *obj_class = G_OBJECT_CLASS(klazz);

        /* gobject vtable hookup */
        obj_class->dispose = budgie_theme_manager_dispose;
}

/**
 * Instaniation
 */
static void budgie_theme_manager_init(BudgieThemeManager *self)
{
        /* For now just set the default theme */
        budgie_theme_manager_set_theme_css(self, "theme.css");
}

/**
 * Set the current process-wide styling to the selected theme portion, i.e.
 * "theme.css" or "theme_hc.css".
 *
 * @note passing NULL to theme_portion will remove any theme providers allowing
 * user themes to completely override the styling.
 */
static void budgie_theme_manager_set_theme_css(BudgieThemeManager *self, const gchar *theme_portion)
{
        GdkScreen *screen = NULL;
        GtkCssProvider *css_provider = NULL;
        gchar *theme_uri = NULL;
        GError *error = NULL;
        GFile *file = NULL;

        screen = gdk_screen_get_default();

        /* NULL portion, just remove the CSS provider */
        if (!theme_portion) {
                goto remove_provider;
        }

        /* Setting an invalid theme */
        theme_uri = budgie_form_theme_path(theme_portion);
        if (!theme_uri) {
                g_warning("Requested invalid theme: %s", theme_portion);
                return;
        }

        /* Attempt to load theme for the given URI */
        file = g_file_new_for_uri(theme_uri);
        g_free(theme_uri);
        css_provider = gtk_css_provider_new();
        if (!gtk_css_provider_load_from_file(css_provider, file, &error)) {
                g_warning("Cannot load theme %s: %s\n", theme_uri, error->message);
                g_error_free(error);
                g_object_unref(css_provider);
                g_object_unref(file);
                return;
        }
        g_object_unref(file);

remove_provider:
        if (self->css_provider) {
                gtk_style_context_remove_provider_for_screen(screen,
                                                             GTK_STYLE_PROVIDER(
                                                                 self->css_provider));
                g_object_unref(self->css_provider);
                self->css_provider = NULL;
        }

        /* No new theme has been set, just bail */
        if (!css_provider) {
                return;
        }
        /* Set the style globally */
        gtk_style_context_add_provider_for_screen(screen,
                                                  GTK_STYLE_PROVIDER(css_provider),
                                                  GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        self->css_provider = css_provider;
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
