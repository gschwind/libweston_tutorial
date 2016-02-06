/*
 * xdg_shell.c
 *
 *  Created on: 6 févr. 2016
 *      Author: gschwind
 */

#include "xdg-shell-server-protocol.h"
#include "xdg_shell.h"

static void
lwt_xdg_shell_delete_resource(struct wl_resource *resource) {
	free(wl_resource_get_user_data(resource));
}

static void
lwt_xdg_shell_destroy(struct wl_client *client,
		  struct wl_resource *resource) {
	weston_log("call %s\n", __PRETTY_FUNCTION__);
}

static void
lwt_xdg_use_unstable_version(struct wl_client *client,
			 struct wl_resource *resource,
			 int32_t version) {
	weston_log("call %s\n", __PRETTY_FUNCTION__);
}

static void
lwt_xdg_get_xdg_surface(struct wl_client *client,
		    struct wl_resource *resource,
		    uint32_t id,
		    struct wl_resource *surface_resource) {
	weston_log("call %s\n", __PRETTY_FUNCTION__);

}

static void
lwt_xdg_get_xdg_popup(struct wl_client *client,
		  struct wl_resource *resource,
		  uint32_t id,
		  struct wl_resource *surface_resource,
		  struct wl_resource *parent_resource,
		  struct wl_resource *seat_resource,
		  uint32_t serial,
		  int32_t x, int32_t y) {
	weston_log("call %s\n", __PRETTY_FUNCTION__);
}

static void
lwt_xdg_pong(struct wl_client *client,
	 struct wl_resource *resource, uint32_t serial)
{
	weston_log("call %s\n", __PRETTY_FUNCTION__);
}

const struct xdg_shell_interface lwt_xdg_shell_implementation = {
		lwt_xdg_shell_destroy,
		lwt_xdg_use_unstable_version,
		lwt_xdg_get_xdg_surface,
		lwt_xdg_get_xdg_popup,
		lwt_xdg_pong
};

struct lwt_xdg_shell *
lwt_xdg_shell_create(struct wl_client * client,
		struct lwt_compositor * data, uint32_t id) {

	struct lwt_xdg_shell * ret =
			(struct lwt_xdg_shell *)malloc(sizeof *ret);

	ret->cmp = data;
	ret->client = client;
	ret->id = id;

	/* allocate a wayland resource for the provided 'id' */
	struct wl_resource * resource =
			wl_resource_create(client, &xdg_shell_interface, 1, id);

	/**
	 * Define the implementation of the resource and the user_data,
	 * i.e. callbacks that must be used for this resource.
	 **/
	wl_resource_set_implementation(resource,
			&lwt_xdg_shell_implementation, ret,
			lwt_xdg_shell_delete_resource);

	return ret;

}




