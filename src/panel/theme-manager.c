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
SOLUS_END_PEDANTIC

struct _BudgieThemeManagerClass {
        GObjectClass parent_class;
};

struct _BudgieThemeManager {
        GObject parent;
};

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
static void budgie_theme_manager_init(__solus_unused__ BudgieThemeManager *self)
{
        /* Currently, do nothing.. */
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
