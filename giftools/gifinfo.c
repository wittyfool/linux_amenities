#include <stdio.h>
#include "gd.h"



main(int argc, char *argv[]){
  FILE *fp;
  gdImagePtr im;

  if(argc<2){
    fprintf(stderr, "Usage : %s gif-file-name\n", argv[0]);
    exit(1);
  }

  fp = fopen(argv[1], "rb");
  if(!fp){
    fprintf(stderr, "Can't open [%s]\n", argv[1]);
    exit(1);
  }
  im = gdImageCreateFromGif(fp);
  fclose(fp);

  printf("xsize:%d\n", gdImageSX(im));
  printf("ysize:%d\n", gdImageSY(im));
  printf("color:%d\n", gdImageColorsTotal(im));
  gdImageDestroy(im);
}
