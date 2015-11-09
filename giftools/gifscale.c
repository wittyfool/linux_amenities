#include <stdio.h>
#include "gd.h"

char *infile=0, *outfile=0;
gdImagePtr im, im_out;

int w,h;
int sx,sy;

int percent = 0;	// 倍率指定のとき１
int gaussian = 0;	// ガウシアンフィルタ
int accum = 0;		// アキュムレートフィルタ
int shrink = 0;		// 縮小専用

main(int argc, char *argv[]){
  FILE *fp;
  int i,j,x,y,c;

  if(argc<4){
    fprintf(stderr, "[%s] compiled [%s/%s at %s]\n", argv[0], __DATE__, __TIME__, DIRE);
    fprintf(stderr, "Usage1 : %s in-gif out-gif dstWidth,dstHeight\n", argv[0]);
    fprintf(stderr, "Usage2 : %s in-gif out-gif dstWidth(%%) dstHeight(%%) [-g | -a | -s]\n", argv[0]);
    fprintf(stderr, " -g : gaussian  -a : accumrate filter  -s : shrink algorithm\n");
    exit(1);
  }

  infile  = argv[1];
  outfile = argv[2];

  if(argc>=5){	// -------------- 倍率指定の場合 usage2
    w = atoi(argv[3]);
    h = atoi(argv[4]);
    percent = 1;
    if(argc>5){
      if(strcmp(argv[5], "-g")==0){  // ガウシアンフィルタの適用
        gaussian = 1;
      } else if(strcmp(argv[5], "-a")==0){  // アキュムレートフィルタの適用
        accum = 1;
      } else if(strcmp(argv[5], "-s")==0){  // 縮小専用アルゴリズムの適用
        shrink = 1;
      }
    }
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
    w = gdImageSX(im) * w / 100;
    h = gdImageSY(im) * h / 100;
    printf("w,h = %d,%d\n", w, h);
  }

// ------------- dst open ----------------------
  fp = fopen(outfile, "wb");
  if(!fp){
    fprintf(stderr, "Can't open [%s]\n", outfile);
    exit(1);
  }
  im_out = gdImageCreate(w, h);

  sx = gdImageSX(im);
  sy = gdImageSY(im);

  if(gaussian){
    scaleCopy();
  } else if(accum){
    accumCopy();
  } else {
    gdImageCopyResized(im_out, im, 0, 0, 0, 0, w, h, sx, sy);
    scaleCopy();
  }

  gdImageGif(im_out, fp);
  fclose(fp);

  gdImageDestroy(im);
  gdImageDestroy(im_out);
}

#define gdR(x) gdImageRed(im,x)
#define gdG(x) gdImageGreen(im,x)
#define gdB(x) gdImageBlue(im,x)

shrinkCopy(){	// 1/3倍までの縮小コピー
  int x, y;
  int mx, my;

  for(my=0; my<10; my++){
  for(mx=0; mx<10; mx++){
      for(y=0; y<h; y+=10){
	if((y+my)>=h) continue;
        for(x=0; x<w; x+=10){
	  if((x+mx)>=w) continue;
          shrinkSub(x+mx,y+my);
	}
      }
  }
  }
}

shrinkSub(int x, int y){
  int i,j;
  int xx, yy, xxx,yyy;
  int c,r,g,b,cnt;

  r = g = b = cnt = 0;
  for(i=0; i<10; i++){
    xx = i + (x*sx/w);
    xxx = xx * w /sx;
    if(xxx > x) break;
    for(j=0; j<10; j++){
      yy = j + (y*sy/h);
      yyy = yy * h/sy; 
      if(yyy > y) break;

      c = gdImageGetPixel(im, xx, yy);
      r += gdR(c);
      g += gdG(c);
      b += gdB(c);
      cnt++;
    }
  }
  if(cnt <= 0) return 0;
  r /= cnt;
  g /= cnt;
  b /= cnt;

  c = gdImageColorExact(im_out, r,g,b);
  if(c<0){
    c = gdImageColorAllocate(im_out, r,g,b);
  }
  if(c<0){
    c = gdImageColorClosest(im_out, r,g,b);
  }
  gdImageSetPixel(im_out, x, y, c);
  return 0;
}


scaleCopy(){
  int x, y;
  int i, j;
  int c, c0, cL, cR, cU, cD;
  int r,g,b;
  int xx, yy;
  int wt[3][3] = { {1,2,1}, {2,4,2}, {1,2,1} };
  int w_sum =  16;

  for(y=0; y<h; y++){
  for(x=0; x<w; x++){

    xx = x * sx / w;
    yy = y * sy / h;

    xx = (xx >=  1)     ? xx : 1;
    xx = (xx <= (sx-2)) ? xx : (sx-2);
    yy = (yy >=  1)     ? yy : 1;
    yy = (yy <= (sy-2)) ? yy : (sy-2);

    r = g = b = 0;

    for(i=0; i<3; i++){
      for(j=0; j<3; j++){
        c = gdImageGetPixel(im, xx+i-1,   yy+j-1);
        r += ( wt[j][i] * gdR(c));
        g += ( wt[j][i] * gdG(c));
        b += ( wt[j][i] * gdB(c));
      }
    }

    r /= w_sum;
    g /= w_sum;
    b /= w_sum;

    c = gdImageColorExact(im_out, r,g,b);
    if(c<0){
      c = gdImageColorAllocate(im_out, r,g,b);
    }
    if(c<0){
      c = gdImageColorClosest(im_out, r,g,b);
    }

    gdImageSetPixel(im_out, x, y, c);

  }    
  }
}

accumCopy(){
  int x, y;
  int x0, y0;
  int i, j;
  int c;
  int r,g,b;
  int xx, yy;
  int cnt;

  for(y=0; y<h; y++){
  for(x=0; x<w; x++){

    xx = x * sx / w;
    yy = y * sy / h;

    cnt = 0;
    r = g = b = 0;
    for(i=0; i<5; i++){
      x0 = (xx+i)*w/sx;
      if(x0 != x) continue;
      for(j=0; j<5; j++){
        y0 = (yy+i)*h/sy;
        if(y0 != y) continue;
        c = gdImageGetPixel(im, xx+i,   yy+j);
        r += gdR(c);
        g += gdG(c);
        b += gdB(c);
	cnt++;
      }
    }
    if(cnt==0) continue;

    r /= cnt;
    g /= cnt;
    b /= cnt;

    c = gdImageColorExact(im_out, r,g,b);
    if(c<0){
      c = gdImageColorAllocate(im_out, r,g,b);
    }
    if(c<0){
      c = gdImageColorClosest(im_out, r,g,b);
    }

    gdImageSetPixel(im_out, x, y, c);

  }    
  }
}
