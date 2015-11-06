#include <stdio.h>
#include "gd.h"

char *infile=0, *outfile=0;
gdImagePtr im, im_out;

int w,h;
int sx,sy;

int percent = 0;	// 倍率指定のとき１

main(int argc, char *argv[]){
  FILE *fp;
  int i,j,x,y,c;

  if(argc<4){
    fprintf(stderr, "[%s] compiled [%s/%s at %s]\n", argv[0], __DATE__, __TIME__, DIRE);
    fprintf(stderr, "Usage1 : %s in-gif out-gif dstWidth,dstHeight\n", argv[0]);
    fprintf(stderr, "Usage2 : %s in-gif out-gif dstWidth(%%) dstHeight(%%) [-g | -a]\n", argv[0]);
    exit(1);
  }

  infile  = argv[1];
  outfile = argv[2];

  if(argc>=5){	// -------------- 倍率指定の場合 usage2
    w = atoi(argv[3]);
    h = atoi(argv[4]);
    percent = 1;
  } else {      // -------------- できあがりサイズ指定 usage1
    sscanf(argv[3], "%d,%d", &w, &h);
    percent = 0;
  }

  if((w<=0)||(h<=0)){
    fprintf(stderr, "Error! w,h =%d, %d\n", w, h);
    exit(1);
  }

// ------------- src open -----------------
  fp = fopen(infile, "rb");
  if(!fp){
    fprintf(stderr, "Can't open [%s]\n", infile);
    exit(1);
  }
  im = gdImageCreateFromGif(fp);
  fclose(fp);

  if(percent){
    printf("Not implemented yet.\n");
    exit(0);
    w = gdImageSX(im) * w / 100;
    h = gdImageSY(im) * h / 100;
    printf("w,h = %d,%d\n", w, h);
  }

  splitCopy(outfile, w,h);

  gdImageDestroy(im);
  gdImageDestroy(im_out);
}


splitCopy(char *outFname, int w, int h){
  int i, j;
  int x, y;
  char fname[256];
  int org_w, org_h;
  FILE *fp;

  // w, h 小画像サイズ

  im_out = gdImageCreate(w, h);

  org_w = gdImageSX(im);
  org_h = gdImageSY(im);

  for(x=0,i=0; x<org_w; x+=w,i++){
    for(y=0,j=0; y<org_h; y+=h,j++){
      memset(fname, 0, 256);
      sprintf(fname, "%s_%d_%d.gif", outFname, i, j);
      printf("Processing [%s]...\n", fname);
      gdImageCopy(im_out, im, 0, 0, x, y, w, h);
      fp = fopen(fname, "wb");
      if(fp){
	gdImageGif(im_out, fp);
	fclose(fp);
      }
    }
  }

}

