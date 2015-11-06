#include <stdio.h>
#define DATAPATH "/gp7000/share2/data/gms/gif/"

main(int argc, char *argv[]) {
  int i,j;

  if(argc<2){
    fprintf(stderr, "Usage : %s gif-image-file\n", argv[0]);
    exit(1);
  }

  readim(argv[1]);
  guessCircle();
  writeim("test.gif");

}
