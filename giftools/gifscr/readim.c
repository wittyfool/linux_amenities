#include <stdio.h>
#include "gd.h"
#include "image.h"

int readim(char *fname){
  FILE *fp;
  gdImagePtr im;
  struct image *img;
  int i,j,x,y;

  fp = fopen(fname, "rb");
  if(!fp) return 0;

  im = gdImageCreateFromGif(fp);
  fclose(fp);

  x = gdImageSX(im);
  y = gdImageSY(im);
  img = imageAlloc(x, y);
  for(j=0; j<y; j++){
    for(i=0; i<x; i++){
      (img->buf[j])[i] = (short)gdImageGetPixel(im, i, j);
    }
  }

  imagePush(img);
  return 1;
}

int readimFromIndex(char *fname){ // Index をグレースケールに変換しながら読込
  FILE *fp;
  gdImagePtr im;
  struct image *img;
  int i,j,x,y,c,r,g,b;

  fp = fopen(fname, "rb");
  if(!fp) return 0;

  im = gdImageCreateFromGif(fp);
  fclose(fp);

  x = gdImageSX(im);
  y = gdImageSY(im);
  img = imageAlloc(x, y);
  for(j=0; j<y; j++){
    for(i=0; i<x; i++){
      c = (short)gdImageGetPixel(im, i, j);
      r = gdImageRed(  im, c);
      g = gdImageGreen(im, c);
      b = gdImageBlue( im, c);
      c = (r + g + g + b ) /4;
      (img->buf[j])[i] = (short)c;
    }
  }

  imagePush(img);
  return 1;
}

int greyScale(gdImagePtr im){
  int i;
  for(i=0; i<256; i++){
    gdImageColorAllocate(im, i, i, i);
  }
}

int writeim(char *fname){
  gdImagePtr im;
  FILE *fp;
  int i,j,c;
  struct image *img;

  fp = fopen(fname, "wb");
  if(!fp) return 0;

  img = imagePop();
  if(!img) return 0;

  im = gdImageCreate(img->w, img->h);
  greyScale(im);
  for(j=0; j<(img->h); j++){
    for(i=0; i<(img->w); i++){
      c = img->buf[j][i];
      c = (c<0)?0:c;
      c = (c>255)?255:c;
      gdImageSetPixel(im, i, j, c);
    }
  }
  gdImageGif(im, fp);
  fclose(fp);
  gdImageDestroy(im);
}


#ifdef TEST
main(){

  readim("test.gif");
  enhance();
  writeim("test2.gif");
}
#endif
