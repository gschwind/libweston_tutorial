/*
 * xdg_shell.h
 *
 *  Created on: 6 févr. 2016
 *      Author: gschwind
 */

#ifndef SRC_XDG_SHELL_H_
#define SRC_XDG_SHELL_H_

#include "compositor.h"

struct lwt_xdg_shell {
	struct lwt_compositor * cmp;
	struct wl_client * client;
	uint32_t id;

	struct wl_resource * resource;

};

struct lwt_xdg_shell *
lwt_xdg_shell_create(struct wl_client * client,
		struct lwt_compositor * data, uint32_t id);


#endif /* SRC_XDG_SHELL_H_ */
