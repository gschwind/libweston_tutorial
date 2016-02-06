/*
 * xdg_shell_suraface_popup.c
 *
 *  Created on: 6 févr. 2016
 *      Author: gschwind
 */

#include "xdg-shell-server-protocol.h"
#include "xdg_shell_surface_popup.h"

static void
lwt_xdg_popup_destroy(struct wl_client *client,
		  struct wl_resource *resource)
{
	wl_resource_destroy(resource);
}

static const struct xdg_popup_interface xdg_popup_implementation = {
	lwt_xdg_popup_destroy,
};

static void
lwt_weston_shell_surface_popup_configure(
		struct weston_surface * s, int32_t x , int32_t y) {
	weston_log("call %s\n", __PRETTY_FUNCTION__);
	if(s->output != 0)
		weston_output_schedule_repaint(s->output);
}

static void
lwt_xdg_popup_delete(struct wl_resource *resource)
{
	free(wl_resource_get_user_data(resource));
}

struct lwt_xdg_shell_surface_popup *
lwt_xdg_shell_surface_popup_create(
		struct wl_client * client,
		struct lwt_xdg_shell * shell,
		uint32_t id,
		struct weston_surface * surface,
		int32_t x,
		int32_t y)
{

	struct lwt_xdg_shell_surface_popup * ret =
			(struct lwt_xdg_shell_surface_popup *)malloc(sizeof *ret);

	ret->client = client;
	ret->shell = shell;
	ret->id = id;
	ret->surface = surface;
	ret->ox = x;
	ret->oy = y;

	ret->resource =
			wl_resource_create(client, &xdg_surface_interface, 1, id);
	wl_resource_set_implementation(ret->resource,
			&xdg_popup_implementation, ret, lwt_xdg_popup_delete);

	/** tell weston how to use this data **/
	if (weston_surface_set_role(surface, "xdg_popup",
				    ret->resource, XDG_SHELL_ERROR_ROLE) < 0)
		return 0;

	/* the first output */
	struct weston_output * output =
			wl_container_of(shell->cmp->wcmp->output_list.next,
					output, link);

	surface->configure = &lwt_weston_shell_surface_popup_configure;
	surface->configure_private = ret;

	surface->output = output;

	ret->view = weston_view_create(surface);
	weston_view_set_position(ret->view, x, y);
	surface->timeline.force_refresh = 1;
	weston_layer_entry_insert(
			&shell->cmp->default_layer.view_list,
			&ret->view->layer_link);

	weston_view_geometry_dirty(ret->view);

	return ret;

}
