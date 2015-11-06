#include <stdio.h>
#define DATAPATH "/gp7000/share2/data/gms/gif/"

extern FILE *yyin,*yyout;
extern double center_x, center_y;

main(argc, argv)
int argc;
char **argv;
{
	int i,j;
	int size;

	printf("This is gifscr ...\n");

#if 0
	if(argc>=2){
	  yyin=fopen(argv[1], "r");
	  if(yyin==NULL){
	    fprintf(stderr, "%s : no such file.\n", argv[1]);
	    exit(1);
	  }
	  if(argc>=3){
	    yyout=fopen(argv[2], "w");
	    if(yyout==NULL){
	      fprintf(stderr, "%s : write open error.\n", argv[2]);
	      exit(1);
	    }
	  }
	}
	yylex();
#endif

#if 0
  readim(DATAPATH "IR1F0030.305.gif");
  guessCircle();
  writeim("test.gif");
#endif  

// read_IR1F();
  read_IR1J();
//  read_PV();

  size = imagePointer();
  while(imagePointer()>1){
	darkim();
//	addim();
  }
//  divide(size);
  writeim("test.gif");

}

bin(){
  int med;

  printf("-\n");
  med = medianIm();
  printf("=\n");
  if(med>0) binaryIm(med);
  else {
    printf("med = %d\n", med);
  }
}

readCenter(char *fname){
  int x,y;

  x = (x + 3) % 20;
  y = (y + 3) % 29;

  readim(fname);

  x = (int)center_x;
  y = (int)center_y;
  x -= 230;
  y -= 230;

  printf("x=%d, y=%d\n", x, y);
  shift(x,y);
}  

read_PV(){
  readimFromIndex("pvgif/pv.99020112.gif");
  readimFromIndex("pvgif/pv.99020212.gif");
  readimFromIndex("pvgif/pv.99020312.gif");
  readimFromIndex("pvgif/pv.99020412.gif");
  readimFromIndex("pvgif/pv.99020512.gif");
  readimFromIndex("pvgif/pv.99020612.gif");
  readimFromIndex("pvgif/pv.99020712.gif");
  readimFromIndex("pvgif/pv.99020812.gif");
  readimFromIndex("pvgif/pv.99020912.gif");
  readimFromIndex("pvgif/pv.99021012.gif");
}

read_IR1J(){
  readim("/gp7000/share2/data/gms/gif/0212/IR1J0030.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0212/IR1J0330.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0212/IR1J0630.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0212/IR1J0930.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0212/IR1J1230.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0212/IR1J1530.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0212/IR1J1830.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0212/IR1J2130.301.gif"); bin();

  readim("/gp7000/share2/data/gms/gif/0213/IR1J0030.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0213/IR1J0330.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0213/IR1J0630.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0213/IR1J0930.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0213/IR1J1230.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0213/IR1J1530.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0213/IR1J1830.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0213/IR1J2130.301.gif"); bin();

  readim("/gp7000/share2/data/gms/gif/0214/IR1J0030.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0214/IR1J0330.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0214/IR1J0630.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0214/IR1J0930.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0214/IR1J1230.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0214/IR1J1530.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0214/IR1J1830.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0214/IR1J2130.301.gif"); bin();

  readim("/gp7000/share2/data/gms/gif/0215/IR1J0030.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0215/IR1J0330.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0215/IR1J0630.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0215/IR1J0930.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0215/IR1J1230.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0215/IR1J1530.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0215/IR1J1830.301.gif"); bin();
  readim("/gp7000/share2/data/gms/gif/0215/IR1J2130.301.gif"); bin();


#if 0
  readim("/gp7000/share2/data/gms/gif/IR1J0030.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J0130.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J0230.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J0330.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J0420.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J0530.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J0630.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J0730.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J0830.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J0930.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J1020.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J1130.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J1230.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J1330.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J1430.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J1530.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J1620.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J1730.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J1830.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J1930.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J2030.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J2130.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J2220.301.gif");
  readim("/gp7000/share2/data/gms/gif/IR1J2330.301.gif");
#endif
}

read_IR1F(){
  readCenter("/gp7000/share2/data/gms/gif/IR1F0030.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F0130.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F0230.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F0330.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F0420.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F0530.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F0630.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F0730.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F0830.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F0930.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F1020.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F1130.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F1230.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F1330.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F1430.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F1530.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F1620.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F1730.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F1830.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F1930.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F2030.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F2130.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F2220.305.gif");
  readCenter("/gp7000/share2/data/gms/gif/IR1F2330.305.gif");
}
