#include <stdio.h>
#include "gd.h"
#include "image.h"

int enhance(){
  int i,j,c,sum;
  struct image *img,*new;

  img = imagePop();
  new = imageAlloc(img->w, img->h);
  if(!new) return 0;

  for(j=1; j<(img->h-1); j++){
    for(i=1; i<(img->w-1); i++){
      sum  = img->buf[j+1][i-1];
      sum += img->buf[j+1][i];
      sum += img->buf[j+1][i+1];
      sum += img->buf[j  ][i-1];
      sum += img->buf[j  ][i];
      sum += img->buf[j  ][i+1];
      sum += img->buf[j-1][i-1];
      sum += img->buf[j-1][i];
      sum += img->buf[j-1][i+1];
      sum /= 16;
      c = 2 * img->buf[j][i] - sum;
      new->buf[j][i] = c;
    }
  }
  imageFree(img);
  imagePush(new);

  return 1;
}

