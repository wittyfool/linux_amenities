#include <stdio.h>
#include "gd.h"
// 減色混合？する

char *infile1=0, *infile2=0, *outfile=0;
gdImagePtr fromGif(char *);

int main(int argc, char *argv[]){
  FILE *fp;
  gdImagePtr im1, im2, imOut;
  int i,x,y,xsize,ysize,c;
  int c1,c2;
  int r,g,b;
  int r1[256], g1[256], b1[256];
  int r2[256], g2[256], b2[256];

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

  for(i=0; i<256; i++){
    r1[i] = g1[i] = b1[i] = 255;
    r2[i] = g2[i] = b2[i] = 255;
  }
  for(i=0; i<gdImageColorsTotal(im1); i++){
    r1[i] = gdImageRed(  im1, i);
    g1[i] = gdImageGreen(im1, i);
    b1[i] = gdImageBlue( im1, i);
  }
  for(i=0; i<gdImageColorsTotal(im2); i++){
    r2[i] = gdImageRed(  im2, i);
    g2[i] = gdImageGreen(im2, i);
    b2[i] = gdImageBlue( im2, i);
  }

  for(y=0; y<ysize; y++){
    for(x=0; x<xsize; x++){
      c1 = gdImageGetPixel(im1, x, y);
      c2 = gdImageGetPixel(im2, x, y);
      r = r1[c1] * r2[c2] / 255;
      g = g1[c1] * g2[c2] / 255;
      b = b1[c1] * b2[c2] / 255;
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

