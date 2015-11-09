#include <stdio.h>
#include "gd.h"

/**** Make greyscale gif ***/

char *infile=0, *outfile=0;
int paletR[256];
int paletG[256];
int paletB[256];

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

  for(i=0; i<256; i++)
    gdImageColorAllocate(im2, i, i, i);

  for(i=0; i<gdImageColorsTotal(im); i++){
    paletR[i] = gdImageRed(im, i);
    paletG[i] = gdImageGreen(im, i);
    paletB[i] = gdImageBlue(im, i);
  }

  for(y=0; y<ysize; y++){
    for(x=0; x<xsize; x++){
      c = gdImageGetPixel(im, x, y);
      r = paletR[c];
      g = paletG[c];
      b = paletB[c];
      c = (r + g + g + b)/4;
      c = (c>255)?255:c;
      gdImageSetPixel(im2, x, y, c);
    }
  }
  gdImageDestroy(im);

  fp = fopen(outfile, "wb");
  if(!fp){
    fprintf(stderr, "Can't open [%s]\n", outfile);
    exit(1);
  }
  gdImageGif(im2, fp);
  fclose(fp);
}
