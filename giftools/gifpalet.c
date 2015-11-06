#include <stdio.h>
#include "gd.h"

/*** set colors of palets automatically ***/

main(int argc, char *argv[]){
  FILE *fp;
  gdImagePtr im, im2;
  int i,x,y,xsize,ysize,c;

  if(argc<3){
    fprintf(stderr, "make grey scale image with ordered color palets.\n");
    fprintf(stderr, "カラーパレットをグレースケールに変換してコピーする.\n");
    fprintf(stderr, "Usage : %s in-gif out-gif\n", argv[0]);
    exit(1);
  }

  fp = fopen(argv[1], "rb");
  if(!fp){
    fprintf(stderr, "Can't open [%s]\n", argv[1]);
    exit(1);
  }
  im = gdImageCreateFromGif(fp);
  fclose(fp);

  printf("color:%d\n", gdImageColorsTotal(im));
  xsize = gdImageSX(im);
  ysize = gdImageSY(im);

  im2 = gdImageCreate(xsize, ysize);
  for(i=0; i<256; i++){
    gdImageColorAllocate(im2, i, i, i);
  }
  for(y=0; y<ysize; y++){
    for(x=0; x<xsize; x++){
      c = gdImageGetPixel(im, x, y);
      gdImageSetPixel(im2, x, y, c);
    }
  }
  gdImageDestroy(im);

  fp = fopen(argv[2], "wb");
  if(!fp){
    fprintf(stderr, "Can't open [%s]\n", argv[2]);
    exit(1);
  }
  gdImageGif(im2, fp);
  fclose(fp);
}
