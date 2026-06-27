#ifndef VHOST_BACKEND_H
#define VHOST_BACKEND_H

#include "libvhost-user.h"

// Export the interface so main.c can see it
extern const VuDevIface vblk_iface;

// Export the init function
int vhost_backend_init(const char *socket_path, VuDev *dev);

#endif
