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

#include "util.h"

SOLUS_BEGIN_PEDANTIC
#include "panel-window.h"
#include "theme-manager.h"
SOLUS_END_PEDANTIC

struct _BudgiePanelWindowPrivate {
        gint size_extent;
        BudgieThemeManager *theme_manager;
        PanelPosition position;
        gint monitor;
};

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
