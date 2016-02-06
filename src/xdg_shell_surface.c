/*
 * xdg_shell_surface.c
 *
 *  Created on: 6 févr. 2016
 *      Author: gschwind
 */

#include "xdg_shell_surface.h"
#include "move_grab.h"

static void
lwt_weston_shell_surface_configure(struct weston_surface * s,
		int32_t x , int32_t y) {
	weston_log("call %s\n", __PRETTY_FUNCTION__);
}

static void
lwt_xdg_surface_destroy(struct wl_client *client,
		    struct wl_resource *resource)
{
	wl_resource_destroy(resource);
}

static void
lwt_xdg_surface_set_parent(struct wl_client *client,
		       struct wl_resource *resource,
		       struct wl_resource *parent_resource)
{
	weston_log("call %s\n", __PRETTY_FUNCTION__);
}

static void
lwt_xdg_surface_set_app_id(struct wl_client *client,
		       struct wl_resource *resource,
		       const char *app_id)
{
	weston_log("call %s\n", __PRETTY_FUNCTION__);
}

static void
lwt_xdg_surface_show_window_menu(struct wl_client *client,
			     struct wl_resource *surface_resource,
			     struct wl_resource *seat_resource,
			     uint32_t serial,
			     int32_t x,
			     int32_t y)
{
	weston_log("call %s\n", __PRETTY_FUNCTION__);
}

static void
lwt_xdg_surface_set_title(struct wl_client *client,
			struct wl_resource *resource, const char *title)
{
	weston_log("call %s\n", __PRETTY_FUNCTION__);
}

static void
lwt_xdg_surface_move(struct wl_client *client, struct wl_resource *resource,
		 struct wl_resource *seat_resource, uint32_t serial)
{
	weston_log("call %s\n", __PRETTY_FUNCTION__);

	struct weston_seat * seat =
			(struct weston_seat*)wl_resource_get_user_data(seat_resource);
	struct lwt_xdg_shell_surface * xdg_surface =
			(struct lwt_xdg_shell_surface *)wl_resource_get_user_data(resource);

	struct lwt_move_grab * grab_data =
			lwt_move_grab_create();

	/* get the current global position of the client */
	weston_view_to_global_float(xdg_surface->view, 0.0f, 0.0f,
			&grab_data->origin_x, &grab_data->origin_y);

	wl_list_remove(&(xdg_surface->view->layer_link.link));
	wl_list_insert(&(xdg_surface->shell->cmp->default_layer.view_list.link),
			&(xdg_surface->view->layer_link.link));

	weston_pointer_start_grab(seat->pointer, &grab_data->base);

}

static void
lwt_xdg_surface_resize(struct wl_client *client, struct wl_resource *resource,
		   struct wl_resource *seat_resource, uint32_t serial,
		   uint32_t edges)
{
	weston_log("call %s\n", __PRETTY_FUNCTION__);
}

static void
lwt_xdg_surface_ack_configure(struct wl_client *client,
			  struct wl_resource *resource,
			  uint32_t serial)
{
	weston_log("call %s\n", __PRETTY_FUNCTION__);
}

static void
lwt_xdg_surface_set_window_geometry(struct wl_client *client,
				struct wl_resource *resource,
				int32_t x,
				int32_t y,
				int32_t width,
				int32_t height)
{
	weston_log("call %s\n", __PRETTY_FUNCTION__);
}

static void
lwt_xdg_surface_set_maximized(struct wl_client *client,
			  struct wl_resource *resource)
{
	weston_log("call %s\n", __PRETTY_FUNCTION__);
}

static void
lwt_xdg_surface_unset_maximized(struct wl_client *client,
			    struct wl_resource *resource)
{
	weston_log("call %s\n", __PRETTY_FUNCTION__);
}

static void
lwt_xdg_surface_set_fullscreen(struct wl_client *client,
			   struct wl_resource *resource,
			   struct wl_resource *output_resource)
{
	weston_log("call %s\n", __PRETTY_FUNCTION__);
}

static void
lwt_xdg_surface_unset_fullscreen(struct wl_client *client,
			     struct wl_resource *resource)
{
	weston_log("call %s\n", __PRETTY_FUNCTION__);
}

static void
lwt_xdg_surface_set_minimized(struct wl_client *client,
			    struct wl_resource *resource)
{
	weston_log("call %s\n", __PRETTY_FUNCTION__);
}

const struct xdg_surface_interface lwt_xdg_surface_implementation = {
	lwt_xdg_surface_destroy,
	lwt_xdg_surface_set_parent,
	lwt_xdg_surface_set_title,
	lwt_xdg_surface_set_app_id,
	lwt_xdg_surface_show_window_menu,
	lwt_xdg_surface_move,
	lwt_xdg_surface_resize,
	lwt_xdg_surface_ack_configure,
	lwt_xdg_surface_set_window_geometry,
	lwt_xdg_surface_set_maximized,
	lwt_xdg_surface_unset_maximized,
	lwt_xdg_surface_set_fullscreen,
	lwt_xdg_surface_unset_fullscreen,
	lwt_xdg_surface_set_minimized
};

static void
xdg_shell_surface_delete_resource(struct wl_resource *resource)
{
	free(wl_resource_get_user_data(resource));
}

struct lwt_xdg_shell_surface *
lwt_xdg_shell_surface_create(struct wl_client *client,
		struct lwt_xdg_shell * shell,
		uint32_t id,
		struct weston_surface * surface)
{

	struct lwt_xdg_shell_surface * ret =
			(struct lwt_xdg_shell_surface *)malloc(sizeof *ret);

	ret->client = client;
	ret->shell = shell;
	ret->id = id;
	ret->surface = surface;

	ret->resource =
			wl_resource_create(client, &xdg_surface_interface, 1, id);

	wl_resource_set_implementation(ret->resource,
			&lwt_xdg_surface_implementation,
			ret, xdg_shell_surface_delete_resource);

	/** tell weston how to use this surface **/
	if (weston_surface_set_role(surface, "xdg_surface",
			ret->resource, XDG_SHELL_ERROR_ROLE) < 0)
		return 0;

	/* the first output */
	struct weston_output * output =
			wl_container_of(shell->cmp->wcmp->output_list.next,
					output, link);

	/**
	 * This function is called when a client reconfigure the
	 * wl_surface.
	 **/
	surface->configure = &lwt_weston_shell_surface_configure;
	surface->configure_private = ret;

	surface->output = output;

	/* create the view of the surface */
	ret->view = weston_view_create(surface);
	weston_view_set_position(ret->view, 0, 0);
	surface->timeline.force_refresh = 1;
	weston_layer_entry_insert(
			&shell->cmp->default_layer.view_list,
			&ret->view->layer_link);

	weston_view_geometry_dirty(ret->view);

	/* request weston for repaint */
	weston_output_schedule_repaint(output);

	return ret;

}
