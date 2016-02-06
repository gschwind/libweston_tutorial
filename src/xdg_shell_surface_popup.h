/*
 * xdg_shell_surface_popup.h
 *
 *  Created on: 6 févr. 2016
 *      Author: gschwind
 */

#ifndef SRC_XDG_SHELL_SURFACE_POPUP_H_
#define SRC_XDG_SHELL_SURFACE_POPUP_H_

#include "xdg_shell.h"

struct lwt_xdg_shell_surface_popup {

	/* the client that own the popup */
	struct wl_client *client;

	/* the shell that own the popup */
	struct lwt_xdg_shell * shell;
	uint32_t id;
	struct weston_surface * surface;

	/* handle the wayland resource related to this xdg_surface */
	struct wl_resource * resource;
	struct weston_view * view;

	int32_t ox, oy;

};

struct lwt_xdg_shell_surface_popup *
lwt_xdg_shell_surface_popup_create(
		struct wl_client * client,
		struct lwt_xdg_shell * shell,
		uint32_t id,
		struct weston_surface * surface,
		int32_t x,
		int32_t y);



#endif /* SRC_XDG_SHELL_SURFACE_POPUP_H_ */
