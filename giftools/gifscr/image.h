struct image {
  int x,y,w,h;
  short **buf;
};

struct image *imageAlloc(int, int);
struct image *imagePop();
struct image *imageTop();
int imagePush(struct image *);
int imageFree(struct image *);

