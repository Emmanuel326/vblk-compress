#include <stdio.h>
#include <stdlib.h>
#include "libvhost-user.h"
#include "vhost_backend.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <socket_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    VuDev dev;

    // 1. Initialize the plumbing (socket + libvhost-user)
    if (vhost_backend_init(argv[1], &dev) != 0) {
        fprintf(stderr, "Failed to initialize vhost backend\n");
        return EXIT_FAILURE;
    }

    printf("Backend initialized. Waiting for VirtIO events...\n");

    // 2. The Polling Loop (To be implemented)
    // For now, just dispatch messages so the handshake completes
    while (1) {
        vu_dispatch(&dev);
    }

    return EXIT_SUCCESS;
}
