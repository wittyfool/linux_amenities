#include <stdio.h>
#include <strings.h>
#include "gd.h"

/*** degrade gif image to decrease size of file ***/
int mapR[256];
int mapG[256];
int mapB[256];
int bitShiftR,bitShiftG, bitShiftB;

main(int argc, char *argv[]){
  FILE *fp;
  gdImagePtr im, im2;
  int i,x,y,xsize,ysize;

  if(argc<6){
    fprintf(stderr, "[%s] compiled [%s/%s at %s]\n", argv[0], __DATE__, __TIME__, DIRE);
    fprintf(stderr, "This command decrease size of gif file.\n", argv[0]);
    fprintf(stderr, "Usage : %s in-gif out-gif red-bit-shift(1-7) green-bit-shift blue-bit-shift\n", argv[0]);
    exit(1);
  }

  bitShiftR = atoi(argv[3]);
  bitShiftG = atoi(argv[4]);
  bitShiftB = atoi(argv[5]);

  if((bitShiftR <1)||(bitShiftR>7)||
     (bitShiftG <1)||(bitShiftG>7)||
     (bitShiftB <1)||(bitShiftB>7)){
    fprintf(stderr, "bitshift must be (1-7).\n");
    exit(1);
  }
  makeMap();

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

  for(y=0; y<ysize; y++){
    int dr, dg, db;
    dr = dg = db = 0;
    for(x=0; x<xsize; x++){
      int r,g,b,c;
      int rr,gg,bb,cc;

      c = gdImageGetPixel(im, x, y);
      r = gdImageRed(  im, c);
      g = gdImageGreen(im, c);
      b = gdImageBlue( im, c);
      rr = r;
      gg = g;
      bb = b;
      rr += dr;
      gg += dg;
      bb += db;
      rr = ( rr > 255) ? 255 : rr;
      gg = ( gg > 255) ? 255 : gg;
      bb = ( bb > 255) ? 255 : bb;
      rr = ( rr < 0) ? 0 : rr;
      gg = ( gg < 0) ? 0 : gg;
      bb = ( bb < 0) ? 0 : bb;
      rr = mapR[rr];
      gg = mapG[gg];
      bb = mapB[bb];

      cc = getPalet(im2, rr, gg, bb);
      gdImageSetPixel(im2, x, y, cc);
      rr = gdImageRed(  im2, cc);
      gg = gdImageGreen(im2, cc);
      bb = gdImageBlue( im2, cc);
      dr = r - rr;
      dg = g - gg;
      db = b - bb;
      dr = dr * 2 /4;
      dg = dg * 2 /4;
      db = db * 2 /4;

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

int getPalet(gdImagePtr im, int r, int g, int b){
  int c;

  c = gdImageColorExact(im, r,g,b);
  if(c<0){
    c = gdImageColorAllocate(im, r,g,b);
  }
  if(c<0){
    c = gdImageColorClosest(im, r,g,b);
  }

  return c;
}

int myRnd(int b){
  int i,mask=0;
  static long rand = 17;

  for(i=0; i<b; i++){
    mask *= 2;
    mask += 1;
  }
  // mask = 1, 3, 5, ....

  rand = rand * 1793 + 5123;
  rand %= 655536;

  return (rand & mask);

}

int makeMap() {
  int i,r,g,b;
  int rr, gg, bb;

  rr = 1 << (8-bitShiftR); // R¿§¿ô
  gg = 1 << (8-bitShiftG); // G
  bb = 1 << (8-bitShiftB); // B


  for(i=0; i<256; i++){
    r = i * rr / 255; r = r * 255 /(rr-1); r = (r>255) ? 255 : r;
    g = i * gg / 255; g = g * 255 /(gg-1); g = (g>255) ? 255 : g;
    b = i * bb / 255; b = b * 255 /(bb-1); b = (b>255) ? 255 : b;
    mapR[i] = r;
    mapG[i] = g;
    mapB[i] = b;
//    printf(" %4d ---> %4d\n", i, mapR[i]);
  }
}

