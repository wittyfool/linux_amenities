#include <stdio.h>
#include "gd.h"

// back.gif の上に　logo.gif をはりつけて out.gif に出力する

gdImagePtr readGIF(char *fname){
  FILE *fp;
  gdImagePtr im;

  fp = fopen(fname, "rb");
  if(!fp){
    fprintf(stderr, "Can't open [%s]\n", fname);
    exit(1);
  }
  im = gdImageCreateFromGif(fp);
  fclose(fp);
  return im;
}

main(int argc, char *argv[]){
  FILE *fp;
  int xpos,ypos;

  if(argc<6){
    fprintf(stderr, "[%s] compiled [%s/%s at %s]\n", argv[0], __DATE__, __TIME__, DIRE);
    fprintf(stderr, "Usage : %s logo-gif base-gif out-gif x-pos y-pos\n", argv[0]);
    exit(1);
  }


  xpos = atoi(argv[4]);
  ypos = atoi(argv[5]);

// ------------- src open -----------------
  { 
    gdImagePtr logo, back, out;
    int back_w, back_h;
    int logo_w, logo_h;

    logo = readGIF(argv[1]);
    back = readGIF(argv[2]);
    back_w = gdImageSX(back);
    back_h = gdImageSY(back);
    logo_w = gdImageSX(logo);
    logo_h = gdImageSY(logo);
    out = gdImageCreate(back_w, back_h);
    gdImageCopy(out, back, 0, 0, 0, 0, back_w, back_h);
    gdImageCopy(out, logo, xpos, ypos, 0, 0, logo_w, logo_h);
    
    fp = fopen(argv[3], "wb");
    if(!fp){
      fprintf(stderr, "Can't open [%s]\n", argv[3]);
      exit(1);
    }
    gdImageGif(out, fp);
    fclose(fp);

    gdImageDestroy(logo);
    gdImageDestroy(back);
    gdImageDestroy(out);
  }

}

