#include "libvhost-user.h"
#include <stdio.h>
#include <sys/socket.h>
#include "vblk_proto.h"
#include <stdlib.h>
#include <sys/un.h>
#include <unistd.h>

//tell  QEMU or any vmm what this device is capable of 
static uint64_t vblk_get_features(VuDev *dev){
  return 1ULL << VIRTIO_BLK_SIZE_MAX;

}

static void vblk_set_features(VuDev *dev, uint64_t features){
  printf("Features negotiated: %lx\n", features);

}

//we need these for the library to function 
static bool vblk_process_msg(Vudev *dev, VhostUserMsg *msg , int *do_reply){
  return false; //let the library handle this 
}

static void vblk_queue_kick(VuDev *dev, int qidx){
  printf("Queue %d was kicked by the guest!\n", qidx);

}

static void vblk_queue_set_started(VuDev *dev, int qidx, bool started){
  printf("Queue %d status: %s\n", qidx, started ? "STARTED": "STOPPED");
  //i will add the start/stop logic for the poll threads 
}

//the interface struct that binds funcs to the vhist protocol 
const VuDevIface vblk_iface ={
  .get_features = vblk_get_features,
  .set_features = vblk_set_features,
  .process_msg = vblk_process_msg,
  .queue_set_started = vblk_queue_set_started,
  .queue_kick = vblk_queue_kick,
};

int vhost_backend_init(const char *socket_path, VuDev *dev){
  int listen_sock= socket(AF_UNIX, SOCK_STREAM, 0);
  if(listen_sock <1){perror("socket"); return -1;}

  struct sockaddr_un addr ={.sun_family=AF_UNIX};

  strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);
  unlink(socke_path);

  if(bind(listen_sock, (struct sockaddr *) &addr, sizeof(addr)) !=0){
    perror("bind");
    return -1;
  }
  listen(listen_sock,1);
  printf("Waiting for QEMU connections on %s...\n", socket_path);
  int client_sock = accept(listen_sock, NULL, NULL);
  printf("Accept returned: %d\n", client_sock);

  if (client_sock < 0) {
    perror("accept")
      return -1;
  
  }
  close(listen_sock)// we need only the client connection 



  //init libvhost-user 
  //max_queues=2, client_sock= the active connection iface= the handlers 
  if (!vu_init(dev,2,client_sock, NULL,NULL,NULL,NULL, &vblk_iface)) {
    fprintf(stderr, "Failed to initialize vhost-user device\n");
    return -1;

  }
  return 0;

}
