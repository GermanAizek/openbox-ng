/* -*- indent-tabs-mode: nil; tab-width: 4; c-basic-offset: 4; -*-

   window.h for the Openbox window manager
   Copyright (c) 2003-2007   Dana Jansens

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See the COPYING file for a copy of the GNU General Public License.
*/

#ifndef __window_h
#define __window_h

#include "stacking.h"

#include <X11/Xlib.h>
#include <glib.h>

// Optimize memory placement, replaced struct _ObWindow to enum ObWindowClass
// typedef struct _ObWindow         ObWindow;
typedef struct _ObInternalWindow ObInternalWindow;

typedef enum ObWindow {
    OB_WINDOW_CLASS_MENUFRAME,
    OB_WINDOW_CLASS_DOCK,
    OB_WINDOW_CLASS_CLIENT,
    OB_WINDOW_CLASS_INTERNAL,
    OB_WINDOW_CLASS_PROMPT
}; // ObWindowClass

/* In order to be an ObWindow, you need to make this struct the top of your
   struct */
// Optimize memory placement, replaced struct _ObWindow to enum ObWindowClass
// struct _ObWindow {
//     ObWindowClass type;
// };

#define WINDOW_IS_MENUFRAME(win) \
    ((enum ObWindow*)win == OB_WINDOW_CLASS_MENUFRAME)
#define WINDOW_IS_DOCK(win) \
    ((enum ObWindow*)win == OB_WINDOW_CLASS_DOCK)
#define WINDOW_IS_CLIENT(win) \
    ((enum ObWindow*)win == OB_WINDOW_CLASS_CLIENT)
#define WINDOW_IS_INTERNAL(win) \
    ((enum ObWindow*)win == OB_WINDOW_CLASS_INTERNAL)
#define WINDOW_IS_PROMPT(win) \
    ((enum ObWindow*)win == OB_WINDOW_CLASS_PROMPT)

struct _ObMenu;
struct _ObDock;
struct _ObDockApp;
struct _ObClient;
struct _ObPrompt;

#define WINDOW_AS_MENUFRAME(win) ((struct _ObMenuFrame*)win)
#define WINDOW_AS_DOCK(win) ((struct _ObDock*)win)
#define WINDOW_AS_CLIENT(win) ((struct _ObClient*)win)
#define WINDOW_AS_INTERNAL(win) ((struct _ObInternalWindow*)win)
#define WINDOW_AS_PROMPT(win) ((struct _ObPrompt*)win)

#define MENUFRAME_AS_WINDOW(menu) ((enum ObWindow*)menu)
#define DOCK_AS_WINDOW(dock) ((enum ObWindow*)dock)
#define CLIENT_AS_WINDOW(client) ((enum ObWindow*)client)
#define INTERNAL_AS_WINDOW(intern) ((enum ObWindow*)intern)
#define PROMPT_AS_WINDOW(prompt) ((enum ObWindow*)prompt)

void window_startup (gboolean reconfig);
void window_shutdown(gboolean reconfig);

Window          window_top  (enum ObWindow *self);
ObStackingLayer window_layer(enum ObWindow *self);

enum ObWindow* window_find  (Window xwin);
void      window_add   (Window *xwin, enum ObWindow *win);
void      window_remove(Window xwin);

/* Internal openbox-owned windows like the alt-tab popup */
struct _ObInternalWindow {
    enum ObWindow type : 3; // 3-bit max value enum 0x000 (ObWindowClass)
    Window window;
};

void window_manage_all(void);
void window_manage(Window win);
void window_unmanage_all(void);

#endif
