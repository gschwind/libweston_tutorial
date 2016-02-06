/*
 * page.cxx
 *
 * copyright (2015) Benoit Gschwind
 *
 * This code is licensed under the GPLv3. see COPYING file for more details.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include <poll.h>
#include <wayland-server.h>
#include <weston-1/compositor.h>
#include <weston-1/compositor-x11.h>

/**
 * xdg_shell protocol is considered as unstable
 * thus it is not provided with wayland core
 * protocol. Here we have our own copy of it.
 **/
#include "xdg-shell-server-protocol.h"

#include "compositor.h"

int main(int argc, char ** argv) {

    weston_log_set_handler(vprintf, vprintf);

	/**
	 * First create the wayland display server.
	 **/
	struct wl_display * dpy = wl_display_create();

	/**
	 * Create the listening socket.
	 **/
	char const * sock_name = wl_display_add_socket_auto(dpy);
	weston_log("socket name = %s\n", sock_name);

	/**
	 * set the environment for childs process
	 **/
	setenv("WAYLAND_DISPLAY", sock_name, 1);

	struct lwt_compositor * cmp =
			lwt_compositor_create(dpy);

	/**
	 * setup the keyboard layout (MANDATORY)
	 **/
	struct xkb_rule_names kb_layout = {
			/*rules*/   "",
			/*model*/   "pc104",
			/*layout*/  "us",
			/*variant*/ "",
			/*option*/  ""
	};

	weston_compositor_xkb_init(cmp->wcmp, &kb_layout);

	/**
	 * Define x11 backend configuration
	 *
	 * Note: for the tutorial this is the only one
	 * backend supported. In real implementation
	 * you should implement several of them. currently
	 * Available are : wayland-backend, x11-backend,
	 * rdp-backend, drm-backend.
	 **/
	struct weston_x11_backend_config conf;

	/* use pixman (by default use gl) */
	conf.use_pixman = 0;

	/* disable inputs */
	conf.no_input = 0;

	/* initialize the x11-backend */
	weston_compositor_init_backend(cmp->wcmp,
			"x11-backend.so", &conf.base);

	/** the list of output screen we want to create **/
	struct weston_x11_backend_output_config output_config = {
			{ WL_OUTPUT_TRANSFORM_NORMAL, 800, 600, 1 }, 0
	};

	/**
	 * Actually create the output.
	 */
	struct weston_output * output =
			cmp->wcmp->backend->create_output(cmp->wcmp, /*name*/NULL, &output_config.base);


	/**
	 * run the wayland display
	 */
    wl_display_run(dpy);

}

