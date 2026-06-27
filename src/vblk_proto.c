#include "vblk_proto.h"
#include <stdio.h>
#include <stdbool.h>



bool vblk_parse_request(VuDev *dev, VuVirtqElement *elem, VblkRequest *req){
  if (elem->out_num < 1){
    return false;
  }

  //Map the header as the first descriptor 
  req->header = *(struct virtio_blk_outhdr *)vu_gpa_to_va(dev, &elem->out_sg[0]);
  //Map data: if it is write (type=1), the 2nd FD is for data 
  if(elem->out_num>1){
    req->data_ptr = vu_gpa_to_va(dev, &elem->out_sg[1]);
    req->data_len = elem->out_sg[1].iov_len;
  }else{
    req->data_ptr=NULL;
    req->data_len=0;
  }


//Map status: this is the last FD 
//status is in in_sg (input scatter-gather)list 
req->status_ptr = (uint8_t*)vu_gpa_to_va(dev, &elem->in_sg[0]);
return true;
}

