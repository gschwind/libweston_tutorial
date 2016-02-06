/*
 * move_grab.c
 *
 *  Created on: 6 févr. 2016
 *      Author: gschwind
 */

#include "move_grab.h"

static void
lwt_move_grab_motion(struct weston_pointer_grab *_grab,
		uint32_t time,
		wl_fixed_t x,
		wl_fixed_t y)
{

	struct lwt_move_grab * grab = (struct lwt_move_grab *)(_grab);

	struct weston_pointer * pointer = grab->base.pointer;

	/** global position of the cursor when grab started **/
	double ox = wl_fixed_to_double(pointer->grab_x);
	double oy = wl_fixed_to_double(pointer->grab_y);

	/** global position of the cursor **/
	double cx = wl_fixed_to_double(x);
	double cy = wl_fixed_to_double(y);

	/** relative move from the start of the grab **/
	double dx = cx - ox;
	double dy = cy - oy;

	/** update pointer position **/
	weston_pointer_move(pointer, x, y);

	/** move the surface from his invariant point **/
	weston_view_set_position(pointer->focus,
			grab->origin_x+dx,
			grab->origin_y+dy);
	weston_compositor_schedule_repaint(pointer->focus->surface->compositor);
}

static void
lwt_move_grab_button(struct weston_pointer_grab *grab,
		 uint32_t time, uint32_t button, uint32_t state_w)
{
	struct weston_pointer *pointer = grab->pointer;

	grab->pointer->focus;

	if (pointer->button_count == 0 &&
			state_w == WL_POINTER_BUTTON_STATE_RELEASED) {
		weston_pointer_end_grab(grab->pointer);
	}
}

static void
lwt_move_grab_cancel(struct weston_pointer_grab *grab)
{
	weston_pointer_end_grab(grab->pointer);
}

static void
lwt_move_grab_focus(struct weston_pointer_grab *grab)
{

}

static const struct weston_pointer_grab_interface move_grab_interface = {
	lwt_move_grab_focus,
	lwt_move_grab_motion,
	lwt_move_grab_button,
	lwt_move_grab_cancel
};

struct lwt_move_grab *
lwt_move_grab_create() {
	struct lwt_move_grab * ret =
			(struct lwt_move_grab *)malloc(sizeof *ret);
	ret->base.interface = &move_grab_interface;
	ret->base.pointer = 0;
	ret->origin_x = 0.0f;
	ret->origin_y = 0.0f;

	return ret;
}

