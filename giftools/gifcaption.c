#include <stdio.h>
#include "gd.h"
#include "gdfonts.h"
#include "gdfontmb.h"
#include "gdfontl.h"
#include "gdfontt.h"
#include "gdfontg.h"

#define TINY	1	
#define SMALL	2	
#define MEDIUM	3
#define LARGE	4
#define GIANT	5

#ifndef ORIGIN_X
#define ORIGIN_X 20
#define ORIGIN_Y 20
#endif

char *infile=0, *outfile=0;
gdImagePtr im;
gdFontPtr myFonts;
int LineFeed;

int fontSelect(char c){
  switch(c){
    case 't':
	myFonts = gdFontTiny;
  	LineFeed = 10;
	break;

    case 'm':
	myFonts = gdFontMediumBold;
  	LineFeed = 20;
	break;

    case 'l':
	myFonts = gdFontLarge;
  	LineFeed = 25;
	break;

    case 'g':
	myFonts = gdFontGiant;
  	LineFeed = 25;
	break;

    default:
	;
  }
  return 0;
}

main(int argc, char *argv[]){
  FILE *fp;
  int fg,bg;
  int i,j,x,y,c;
  char *caption;

  if(argc<4){
    fprintf(stderr, "[%s] compiled [%s/%s at %s]\n", argv[0], __DATE__, __TIME__, DIRE);
    fprintf(stderr, "Usage : %s in-gif out-gif caption [t|s|m|l]\n", argv[0]);
    exit(1);
  }

  infile  = argv[1];
  outfile = argv[2];
  caption = argv[3];

  myFonts = gdFontSmall;
  LineFeed = 12;

  fp = fopen(infile, "rb");
  if(!fp){
    fprintf(stderr, "Can't open [%s]\n", infile);
    exit(1);
  }
  im = gdImageCreateFromGif(fp);
  fclose(fp);

  if((fg = gdImageColorAllocate(im, 0,0,0))<0){
    fg = gdImageColorClosest(im, 0,0,0);
  }
  if((bg = gdImageColorAllocate(im, 255,255,255))<0){
    bg = gdImageColorClosest(im, 255,255,255);
  }

  x = 20;
  y = 20;
  for(i=3; i<argc; i++){
    int option=1;
    if(option && (argv[i][0] == '-')){
      if(argv[i][1] == '-'){
	option=0;
	continue;
      }
      fontSelect(argv[i][1]);
      continue;
    }
    plot(x, y, argv[i], fg, bg);
    y += LineFeed;
  }
    
  fp = fopen(outfile, "wb");
  if(!fp){
    fprintf(stderr, "Can't open [%s]\n", outfile);
    exit(1);
  }

  gdImageGif(im, fp);
  fclose(fp);

  gdImageDestroy(im);
}

plot(int x, int y, char *str, int fg, int bg){
  int i,j;


  for(i = -1; i<2; i++){
    for(j = -1; j<2; j++){
      gdImageString(im, myFonts, x+i, y+j, str, bg);
    }
  }
  gdImageString(im, myFonts, x, y, str, fg);
}
