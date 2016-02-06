/*
 * compositor.c
 *
 *  Created on: 6 févr. 2016
 *      Author: gschwind
 */

#include "compositor.h"

struct lwt_compositor *
lwt_compositor_create(struct wl_display * dpy) {

	struct lwt_compositor * ret =
			(struct lwt_compositor *)malloc(sizeof *ret);

	/**
	 * initialise the weston part of the compositor
	 *
	 * You may setup userdata to be able to retrieve some data
	 * within some callback functions.
	 **/
	ret->wcmp = weston_compositor_create(dpy, NULL);

	/**
	 * Weston has a 2 level stacking, the first level are layers,
	 * the second a the list of surface within each layer. List are
	 * sorted from top-most to bottom-most. In our tutorial we will
	 * use only one layer that will be below the cursor layer.
	 **/
	weston_layer_init(&ret->default_layer, &ret->wcmp->cursor_layer.link);

	return ret;

}
