#ifndef VBLK_PROTO_H
#define VBLK_PROTO_H

#include <linux/virtio_blk.h>
#include "libvhost-user.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct{
  struct virtio_blk_outhdr header;
  void *data_ptr;
  size_t data_len;
  uint8_t *status_ptr;

} VblkRequest;

//func to parse the descripto chain into ur struct 
bool vblk_parse_request(VuDev *dev, VuVirtqElement *elem, VblkRequest *req);

#endif 
