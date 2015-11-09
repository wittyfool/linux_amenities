#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "gd.h"

/*** ユーザーのカスタムカラーパレットを使用して画像をコピーする  ***/
gdImagePtr imOut;
int optDiffuse=0;
int *diffR, *diffG, *diffB;

main(int argc, char *argv[]){
  FILE *fp;
  gdImagePtr im;
  int i,x,y,xsize,ysize;
  int dr, dg, db;

  if(argc<3){
    fprintf(stderr, "[%s]\n", argv[0]);
    fprintf(stderr, "compiled [%s/%s at %s]\n\n",  __DATE__, __TIME__, DIRE);
    fprintf(stderr, "ユーザーのカスタムカラーパレットを使用して画像をコピー\n");
    fprintf(stderr, "-d : 誤差拡散を利用する\n");
    fprintf(stderr, "Usage : %s in-gif out-gif palet-definition-file [-d]\n", argv[0]);
    fprintf(stderr, "\n\n");
    fprintf(stderr, "---- パレット定義ファイルの書式 ----\n");
    fprintf(stderr, "# コメント\n");
    fprintf(stderr, "10 20 30	// (r=10,g=20,b=20)\n");
    fprintf(stderr, "  ... ... \n");
    fprintf(stderr, "  ... ... \n");
    fprintf(stderr, "------------------------------\n");
    exit(1);
  }
  if(argc>4){
    if(0 == strncmp(argv[4], "-d", 2)) optDiffuse=1;
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
  
  {
    diffR = calloc(xsize, sizeof(int));
    diffG = calloc(xsize, sizeof(int));
    diffB = calloc(xsize, sizeof(int));
    if((diffR ==NULL)||(diffG ==NULL)||(diffB ==NULL)){
      fprintf(stderr, "Allocation error.\n");
      exit(1);
    }
    for(i=0; i<xsize; i++){
      diffR[i] = diffG[i] = diffB[i] = 0;
    }
  }

  imOut = gdImageCreate(xsize, ysize);
  readPalet(argv[3]);

  for(y=0; y<ysize; y++){
    dr = dg = db = 0;
    for(x=0; x<xsize; x++){
      int r,g,b,c;
      int rr,gg,bb,cc;

      c = gdImageGetPixel(im, x, y);
      r = gdImageRed(  im, c);
      g = gdImageGreen(im, c);
      b = gdImageBlue( im, c);

/*****
      rr = r + (dr + diffR[x])/2;
      gg = g + (dg + diffG[x])/2;
      bb = b + (db + diffB[x])/2;
*****/
      rr = r + (myRnd() ? dr : diffR[x]);
      gg = g + (myRnd() ? dg : diffG[x]);
      bb = b + (myRnd() ? db : diffB[x]);

      rr = ( rr > 255) ? 255 : rr;
      gg = ( gg > 255) ? 255 : gg;
      bb = ( bb > 255) ? 255 : bb;

      rr = ( rr < 0) ? 0 : rr;
      gg = ( gg < 0) ? 0 : gg;
      bb = ( bb < 0) ? 0 : bb;

      cc = gdImageColorClosest(imOut, rr,gg,bb);
      gdImageSetPixel(imOut, x, y, cc);
      rr = gdImageRed(  imOut, cc);
      gg = gdImageGreen(imOut, cc);
      bb = gdImageBlue( imOut, cc);

      if(optDiffuse){
        dr = r - rr;
        dg = g - gg;
        db = b - bb;
        diffR[x] = dr;
        diffG[x] = dg;
        diffB[x] = db;
      }
    } // x
  } // y
  gdImageDestroy(im);

  fp = fopen(argv[2], "wb");
  if(!fp){
    fprintf(stderr, "Can't open [%s]\n", argv[2]);
    exit(1);
  }
  gdImageGif(imOut, fp);
  fclose(fp);
}

readPalet(char *fname){
  FILE *fp;
  char buf[512];
  int r,g,b,c;

  fp = fopen(fname, "rt");
  if(fp==NULL){
    fprintf(stderr, "Can't open palet-definition-file [%s].\n", fname);
    return -1;
  }
  while(!feof(fp)){
    memset(buf, 0, 512);
    if(NULL==fgets(buf, 512, fp)) break;
    if(buf[0] == '#') continue;
    if(3!=sscanf(buf, "%d %d %d", &r, &g, &b)) continue;
    c = gdImageColorAllocate(imOut, r, g, b);
    if(c<0){
      fprintf(stderr, "Can't allocate color... r,g,b,c=%d,%d,%d,%d\n", r,g,b,c);
//    } else {
//      fprintf(stderr, "Allocated color... r,g,b,c=%d,%d,%d,%d\n", r,g,b,c);
    }
  }
  fclose(fp);
  return 0;
}

int myRnd(){
  return lrand48()&1;
}
