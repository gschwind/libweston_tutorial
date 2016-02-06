/*
 * move_grab.h
 *
 *  Created on: 6 févr. 2016
 *      Author: gschwind
 */

#ifndef SRC_MOVE_GRAB_H_
#define SRC_MOVE_GRAB_H_

#include <stdio.h>
#include <stdlib.h>

#include <poll.h>
#include <wayland-server.h>
#include <weston-1/compositor.h>

struct lwt_move_grab {
	struct weston_pointer_grab base;
	float origin_x;
	float origin_y;
};

struct lwt_move_grab *
lwt_move_grab_create();

#endif /* SRC_MOVE_GRAB_H_ */
