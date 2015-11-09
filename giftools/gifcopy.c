#include <stdio.h>
#include "gd.h"

// just copy gif file ( for compression. since ImageMagick does not do compression);

/**** Make greyscale gif ***/

char *infile=0, *outfile=0;

main(int argc, char *argv[]){
  FILE *fp;
  gdImagePtr im, im2;
  int i,x,y,xsize,ysize,c;
  int r,g,b;

  if(argc != 3){
    fprintf(stderr, "[%s] compiled [%s/%s %s]\n", argv[0], __DATE__, __TIME__, DIRE);
    fprintf(stderr, "Usage : %s in-gif out-gif\n", argv[0]);
    exit(1);
  }

  infile  = argv[1];
  outfile = argv[2];

  fp = fopen(infile, "rb");
  if(!fp){
    fprintf(stderr, "Can't open [%s]\n", infile);
    exit(1);
  }
  im = gdImageCreateFromGif(fp);
  fclose(fp);

  xsize = gdImageSX(im);
  ysize = gdImageSY(im);

  im2 = gdImageCreate(xsize, ysize);
  gdImageCopy(im2, im, 0, 0, 0, 0, xsize, ysize);

  gdImageDestroy(im);

  fp = fopen(outfile, "wb");
  if(!fp){
    fprintf(stderr, "Can't open [%s]\n", outfile);
    exit(1);
  }
  gdImageGif(im2, fp);
  fclose(fp);
}
