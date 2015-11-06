#include <stdio.h>
#include "gd.h"

char *infile1=0, *infile2=0, *outfile=0;
gdImagePtr fromGif(char *);

int main(int argc, char *argv[]){
  FILE *fp;
  gdImagePtr im1, im2, imOut;
  int i,x,y,xsize,ysize,c;
  int c1,c2;

  if(argc != 4){
    fprintf(stderr, "[%s] compiled [%s/%s %s]\n", argv[0], __DATE__, __TIME__, DIRE);
    fprintf(stderr, "Usage : %s in-gif1 in-gif2 out-gif\n", argv[0]);
    exit(1);
  }

  im1 = fromGif(argv[1]);
  im2 = fromGif(argv[2]);

  outfile = argv[3];

  xsize = gdImageSX(im1);
  ysize = gdImageSY(im2);

  imOut = gdImageCreate(xsize, ysize);

  for(i=0; i<gdImageColorsTotal(im1); i++){
    int r,g,b;
    r = gdImageRed(  im1, i);
    g = gdImageGreen(im1, i);
    b = gdImageBlue( im1, i);
  }

  for(y=0; y<ysize; y++){
    int r,g,b;
    for(x=0; x<xsize; x++){
      c1 = gdImageGetPixel(im1, x, y);
      c2 = gdImageGetPixel(im2, x, y);
      r = gdImageRed(  im1, c1) - gdImageRed(  im2, c2);
      g = gdImageGreen(im1, c1) - gdImageGreen(im2, c2);
      b = gdImageBlue( im1, c1) - gdImageBlue( im2, c2);
      r = (r + 256) % 256;
      g = (g + 256) % 256;
      b = (b + 256) % 256;
      c = allocOrExact(imOut, r, g, b);
      gdImageSetPixel(imOut, x, y, c);
    }
  }
  gdImageDestroy(im1);
  gdImageDestroy(im2);

  fp = fopen(outfile, "wb");
  if(!fp){
    fprintf(stderr, "Can't open [%s]\n", outfile);
    exit(1);
  }
  gdImageGif(imOut, fp);
  fclose(fp);

  gdImageDestroy(imOut);

  return 0;
}

gdImagePtr fromGif(char *fname) {
  FILE *fp;
  gdImagePtr im;

  fp = fopen(fname, "rb");
  if(!fp){
    fprintf(stderr, "Can't open [%s]\n", fname);
    return NULL;
  }

  im = gdImageCreateFromGif(fp);
  fclose(fp);

  return im;
}

int allocOrExact(gdImagePtr im, int r, int g, int b)
{
  int c;

  c = gdImageColorExact(im, r,g,b);
  if(c >= 0) return c;

  c = gdImageColorAllocate(im, r, g, b);
  if(c >= 0) return c;

  return gdImageColorClosest(im, r, g, b);
}

