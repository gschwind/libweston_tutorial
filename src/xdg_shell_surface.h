/*
 * xdg_shell_surface.h
 *
 *  Created on: 6 févr. 2016
 *      Author: gschwind
 */

#ifndef SRC_XDG_SHELL_SURFACE_H_
#define SRC_XDG_SHELL_SURFACE_H_

#include "xdg-shell-server-protocol.h"
#include "xdg_shell.h"

struct lwt_xdg_shell_surface {

	/**
	 * Creation parameters, not all are needed but
	 * keep a trace in case
	 **/
	struct wl_client *client;
	struct lwt_xdg_shell * shell;
	uint32_t id;
	struct weston_surface * surface;

	/* handle the wayland resource related to this xdg_surface */
	struct wl_resource * resource;

	/* keep the view corresponding to this xdg shell surface */
	struct weston_view * view;

};

struct lwt_xdg_shell_surface *
lwt_xdg_shell_surface_create(struct wl_client *client,
		struct lwt_xdg_shell * shell,
		uint32_t id,
		struct weston_surface * surface);

#endif /* SRC_XDG_SHELL_SURFACE_H_ */
