#include <stdio.h>
#include <malloc.h>
#include "image.h"

static int pnt=0;
#define SIZE 1000
static struct image *stack[SIZE];

int imagePointer(){
  return pnt;
}

int imagePush(struct image *x){
  if(pnt<SIZE){
    stack[pnt] = x;
    pnt++;
    return 1;
  }
  printf("Stack Over Flow.\n");
  exit(0);
}

struct image *imageTop(){
  if(pnt){
    return stack[pnt-1];
  }
  return 0;
}

int imageDouble(){
  return imagePush(imageTop());
}

struct image *imagePop(){
  if(pnt){
    pnt--;
    return stack[pnt];
  }
  exit(0);
}

struct image *imageAlloc(int x, int y){
	struct image *im;
	short **p, *q;
	int i, j;

	im = calloc(1, sizeof(struct image));
	if(!im) goto ERROR;
	p = calloc(y, sizeof(short *));
	if(p){
	  for(j=0; j<y; j++){
	    p[j] = 0;
	  }
	  for(j=0; j<y; j++){
	    q = calloc(x, sizeof(short));
	    if(q) p[j] = q;
	    else goto ERROR;
	  }
	  
	} else {
ERROR:
	  printf("Can't alloc image\n");
	  exit(0);
	}
	im->x = 0;
	im->y = 0;
	im->w = x;
	im->h = y;
	im->buf = p;
	return im;
}

imageFree(struct image *im){
	int i,j;
	for(j=0; j<im->h; j++){
	  if(im->buf[j]) free(im->buf[j]);
	}
	if(im->buf) free(im->buf);
	free(im);
	return 0;
}

imageDelete(){
  return imageFree(imagePop());
}

#ifdef TEST
main(){
	struct image *a,*b,*c,*d;

	a = imageAlloc(10,10);
	b = imageAlloc(20,20);
	c = imageAlloc(30,30);
	d = imageAlloc(50,50);

	freeImage(a);
	freeImage(b);
	freeImage(c);
	freeImage(d);
}
#endif
