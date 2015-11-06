#include <stdio.h>
#include "gd.h"

int blueValue=80;
int blueMode=0;
int x1,x2,x3,y1,y2,y3;
char *infile=0, *outfile=0;
/*** adjust contrast of gif image ***/
/*** map index value from x1-x2-x3 to y1-y2-y3 ***/

indexMap(int *c){
  static int map[256],i=0;
  int y;

  if(*c<0)   return 1;
  if(*c>255) return 1;
  if(i==0){
    for(i=0; i<256; i++){
      if(i<x2){
        y = (y2-y1)*(i-x1)/(x2-x1)+y1;
      } else {
        y = (y3-y2)*(i-x2)/(x3-x2)+y2;
      }
      y = (y<0)?0:y;
      y = (y>255)?255:y;
      map[i] = y;
    }
  }
  (*c) = map[*c];
  return 0;
}

main(int argc, char *argv[]){
  FILE *fp;
  gdImagePtr im, im2;
  int i,x,y,xsize,ysize,c;

  if(argc<9){
    fprintf(stderr, "[%s] compiled [%s/%s]\n", argv[0], __DATE__, __TIME__);
    fprintf(stderr, "Usage : %s x1 x2 x3 y1 y2 y3 in-gif out-gif [-blue]\n", argv[0]);
    exit(1);
  }
  if(argc>9){
    if(strcmp(argv[9], "-blue")==0) blueMode = 1;
  }

  x1 = atoi(argv[1]);
  x2 = atoi(argv[2]);
  x3 = atoi(argv[3]);
  y1 = atoi(argv[4]);
  y2 = atoi(argv[5]);
  y3 = atoi(argv[6]);

  infile  = argv[7];
  outfile = argv[8];

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

  if(blueMode){		// use bluish gradation for low index value
    int j;
    for(i=0; i<256; i++){
      j = (i-blueValue)*255/(255-blueValue); 	//////////////// blueValue --> 0, 255 --> 255
      j = (j<0)?0:j;
      j=  (j>255)?255:j;
      gdImageColorAllocate(im2, j, j, i);
    }
  } else {
    for(i=0; i<256; i++)
      gdImageColorAllocate(im2, i, i, i);
  }


  for(y=0; y<ysize; y++){
    for(x=0; x<xsize; x++){
      c = gdImageGetPixel(im, x, y);
      { int r,g,b;                      // fixed 2001.07.23
        r = gdImageRed(im, c);
        g = gdImageGreen(im, c);
        b = gdImageBlue(im, c);
        c = ( g + g + r + b )/4;
      }
      indexMap(&c);
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
