#include <stdio.h>
#include "image.h"

double center_x=0, center_y=0;

static long histgram[300];

int enhance(){
  int i,j,c,sum;
  struct image *img,*new;

  img = imagePop();
  new = imageAlloc(img->w, img->h);
  if(!new) return 0;

  for(j=1; j<(img->h-1); j++){
    for(i=1; i<(img->w-1); i++){
      sum  = img->buf[j+1][i-1];
      sum += img->buf[j+1][i];
      sum += img->buf[j+1][i+1];
      sum += img->buf[j  ][i-1];
      sum += img->buf[j  ][i];
      sum += img->buf[j  ][i+1];
      sum += img->buf[j-1][i-1];
      sum += img->buf[j-1][i];
      sum += img->buf[j-1][i+1];
      sum /= 16;
      c = 2 * img->buf[j][i] - sum;
      new->buf[j][i] = c;
    }
  }
  imageFree(img);
  imagePush(new);

  return 1;
}

#define MIN(X,Y) ((X)>(Y)?(Y):(X))

int subtract(){
  int i,j,ii,jj,x,y;
  struct image *a, *b;

  a = imagePop();
  if(!a) return 0;
  b = imagePop();
  if(!b) return 0;

  for(j=0; j<(b->h); j++){
    jj = (b->y) + j - (a->y);
    if((jj<0)||(jj>=(a->h))) continue;
    for(i=0; i<(b->w); i++){
      ii = (b->x) + i - (a->x);
      if((ii<0)||(ii>=(a->w))) continue;
      b->buf[j][i] -= (a->buf[jj][ii]);
    }
  }
  imagePush(b);
  imageFree(a);
  return 1;
}

int darkim(){
  int i,j,ii,jj,x,y;
  struct image *a, *b;

  a = imagePop();
  if(!a) return 0;
  b = imagePop();
  if(!b) return 0;

  for(j=0; j<(b->h); j++){
    jj = (b->y) + j - (a->y);
    if((jj<0)||(jj>=(a->h))) continue;
    for(i=0; i<(b->w); i++){
      ii = (b->x) + i - (a->x);
      if((ii<0)||(ii>=(a->w))) continue;
      if(b->buf[j][i]>(a->buf[jj][ii])){
        (b->buf[j][i]) = (a->buf[jj][ii]);
      }
    }
  }
  imagePush(b);
  imageFree(a);
  return 1;
}

int addim(){
  int i,j,ii,jj,x,y;
  struct image *a, *b;

  a = imagePop();
  if(!a) return 0;
  b = imagePop();
  if(!b) return 0;

  for(j=0; j<(b->h); j++){
    jj = (b->y) + j - (a->y);
    if((jj<0)||(jj>=(a->h))) continue;
    for(i=0; i<(b->w); i++){
      ii = (b->x) + i - (a->x);
      if((ii<0)||(ii>=(a->w))) continue;
      b->buf[j][i] += (a->buf[jj][ii]);
    }
  }
  imagePush(b);
  imageFree(a);
  return 1;
}

int binaryIm(int c){
  int i,j,x,y;
  struct image *a;

  a = imageTop();
  if(!a) return 0;

  for(j=0; j<(a->h); j++){
    for(i=0; i<(a->w); i++){
      if((a->buf[j][i])>c){
        a->buf[j][i] = 255;
      } else {
        a->buf[j][i] = 0;
      }
    }
  }
  return 1;
}

int medianIm(){		// 中間値を返す
  int i;
  long sum;
  long accum[256];

  if(!histgramIm()) return -1;

  sum = 0;
  for(i=0; i<256; i++){
    sum += histgram[i];
    accum[i] = sum;
  }
  sum /= 2;

  if(accum[0]>sum){
    printf("histgram[0] = %d\n", histgram[0]);
  }


  for(i=0; i<256; i++){
    if(accum[i]>sum){
      printf("median value = %d, sum = %d\n", i, sum);
      return i;
    }
  }
  return -1;
}

int histgramIm(){	// ヒストグラムを計算する
  int i,j,x,y;
  int c;
  struct image *a;

  printf("Histogram >>> \n");

  for(c=0; c<=257; c++)
    histgram[c] = 0;

  a = imageTop();
  if(!a) return 0;

  for(j=0; j<(a->h); j++){
    for(i=0; i<(a->w); i++){
      c = (a->buf[j][i]);
      c = (c>255)?256:c;
      c = (c<0)?257:c;
      histgram[c]++;
    }
  }
  printf("Histogram <<< \n");
  return 1;
}





int guessCircle(){	// 円の中心を推定する
  int y1 = 100;
  int y2 = 358;
  int x1,x2;
  int i,j,x,y;
  int in, out;
  int span=5;
  int x_length=400;
  int center_x_cnt=0, center_y_cnt=0;
  struct image *a;

  center_x=0, center_y=0;

  a = imageTop();
  if(!a) return 0;
  if((a->h) < y2) return 0;

  for(j=y1; j<y2; j++){
    out = 0;
    in  = 0;
    x1  = 0;
    for(i=0; i<(a->w); i++){
      if((a->buf[j][i])==255){  // 宇宙空間 or ノイズ
	if(out == span){
	  x2 = i - span-1;
	}
	out++;
	in = 0;
      } else {			// 地球をスキャン中 or ノイズ
	if((x1==0)&&(in==span)){
	  x1 = i - span;
	}
	in++;
	out = 0;
      }
    }
    if((x2-x1)>x_length){
      center_y += (double)j;
      center_y_cnt++;
    }
    center_x += ((double)(x1+x2)/2.0);
    center_x_cnt++;
    if((j%2)==0){
      a->buf[j][x1] = 10;
      a->buf[j][x2] = 10;
    }
  }
  center_x /= (double)center_x_cnt;
  center_y /= (double)center_y_cnt;

  printf("center_x = %g\n", center_x);
  printf("center_y = %g\n", center_y);
  return 0;
}

int absolute(){
  int i,j,x,y;
  struct image *a;

  a = imagePop();
  if(!a) return 0;

  for(j=0; j<(a->h); j++){
    for(i=0; i<(a->w); i++){
      a->buf[j][i] = abs(a->buf[j][i]);
    }
  }
  imagePush(a);
  return 1;
}

int multi(int k){
  int i,j,x,y;
  struct image *a;

  a = imagePop();
  if(!a) return 0;

  for(j=0; j<(a->h); j++){
    for(i=0; i<(a->w); i++){
      a->buf[j][i] *= k;
    }
  }
  imagePush(a);
  return 1;
}

int divide(int k){
  int i,j,x,y;
  struct image *a;

  a = imagePop();
  if(!a) return 0;

  for(j=0; j<(a->h); j++){
    for(i=0; i<(a->w); i++){
      a->buf[j][i] /= k;
    }
  }
  imagePush(a);
  return 1;
}

int edgeX(){
  int i,j,x,y;
  struct image *a;

  a = imagePop();
  if(!a) return 0;

  for(j=0; j<(a->h); j++){
    for(i=0; i<(a->w-1); i++){
      a->buf[j][i] = (a->buf[j][i+1]) - (a->buf[j][i]);
    }
  }
  imagePush(a);
  return 1;
}

int average(){	// 輝度の平均値の１００倍を返す
  int i,j,sum=0;
  struct image *a;

  a = imageTop();
  if(!a) return 0;

  for(j=0; j<(a->h); j++){
    for(i=0; i<(a->w); i++){
      sum += (a->buf[j][i]);
    }
  }
  sum *= 100;
  sum /= (a->w);
  sum /= (a->h);
  return sum;
}

int shift(int x, int y){
  struct image *a;

  a = imageTop();
  a->x = (a->x)+x;
  a->y = (a->y)+y;
}
