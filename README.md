budgie-next
-----------

This tree will be used for the exploratory stages for the next major version of the Budgie Desktop.

As a high level overview, we essentially want to achieve the following:

 - Pure C11 implementation (No transpilers)
 - Stable ABI definition
 - Rich UI via `libsolus-ui`
 - Easier C with `libsolus` (less boilerplate)

Component overview
------------------

The new architecture will initially consist of the following components to enable a quicker TTM

**libsolus**:

Convenience functionality common to C programs using modern standards.

**libsolus-ui**:

Extends upon GTK+ to provide the ability to create rich UIs for both the desktop itself and applications.

**budgie-panel**:

The main panel component of the desktop. The process consists of a manager, multiple panels and the Raven UI. Each panel is a toplevel `GtkWindow` expressing the DOCK EWMH hint.

License
-------

The shared libraries are available under the terms of the `LGPL-2.1`,
allowing developers to link against the API without any issue, and
to use all exposed APIs without affecting their project license.

The remainder of the project (i.e. installed binaries) is available
under the terms of the `GPL 2.0` license. This is clarified in the headers
of each source file.


Authors
-------

Copyright © 2015-2016 Ikey Doherty <ikey@solus-project.com>

*I _might_ be a lying bastid.
