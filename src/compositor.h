/*
 * compositor.h
 *
 *  Created on: 6 févr. 2016
 *      Author: gschwind
 */

#ifndef SRC_COMPOSITOR_H_
#define SRC_COMPOSITOR_H_

#include <wayland-server.h>
#include <weston-1/compositor.h>

struct lwt_compositor {
	struct weston_compositor * wcmp;
	struct weston_layer default_layer;

};

struct lwt_compositor *
lwt_compositor_create(struct wl_display * dpy);

#endif /* SRC_COMPOSITOR_H_ */
