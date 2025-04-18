#include <stdio.h>

int main(int argc, char **argv){
  int i,j,k;
  double d;
  float f;
  void *p;
  struct fred {
     int a;			// 4 bytes
     short s;			// 2 bytes,
     double d;			// 8 bytes
     short s2;			// 8 bytes, 
     double d2;			// 8 bytes
     short s3;			// 2 bytes
     short s4;			// 2 bytes
     short s5;			// 2 bytes
     short s6;			// 2 bytes
     double d3;			// 2 bytes
     short s7;			// 2 bytes
  }var;

  struct tom {
     double d;
     short s;			// 4 bytes
  }var1;

  double a[20][30];

  printf("Integer   i %d %016lx\n",sizeof(i),&i);
  printf("Integer   j %d %016lx\n",sizeof(j),&j);
  printf("Integer   k %d %016lx\n",sizeof(k),&k);
  printf("\n");
  printf("Double    d %d %016lx\n",sizeof(d),&d);		// double
  printf("Float     f %d %016lx\n",sizeof(f),&f);		// float
  printf("\n");
  printf("int(ptr) *p %d %016lx\n",sizeof(*(int*)p),&p);
  printf("\n");
  printf("fred        %d %016lx\n",sizeof(var),(void*)&var);
  printf("int fred.a  %d %016lx\n",sizeof(var.a),&var.a);
  printf("short fred.s  %d %016lx\n",sizeof(var.s),&var.s);
  printf("double fred.d  %d %016lx\n",sizeof(var.d),&var.d);
  printf("short fred.s2  %d %016lx\n",sizeof(var.s2),&var.s2);
  printf("double fred.d2  %d %016lx\n",sizeof(var.d2),&var.d2);
  printf("short fred.s3  %d %016lx\n",sizeof(var.s3),&var.s3);
  printf("short fred.s4  %d %016lx\n",sizeof(var.s4),&var.s4);
  printf("short fred.s5  %d %016lx\n",sizeof(var.s5),&var.s5);
  printf("short fred.s6  %d %016lx\n",sizeof(var.s6),&var.s6);
  printf("double fred.d3  %d %016lx\n",sizeof(var.d3),&var.d3);
  printf("short fred.s7  %d %016lx\n",sizeof(var.s7),&var.s7);
  printf("\n");

  printf("tom            %d %016lx\n",sizeof(var1),(void*)&var1);
  printf("double tom.s  %d %016lx\n",sizeof(var1.d),&var1.d);
  printf("short tom.i  %d %016lx\n",sizeof(var1.s),&var1.s);
  printf("\n");

  printf("a              %d (30x30*8) %016lx\n",sizeof(a),&a);
  printf("double a[7][7] %d %016lx\n",sizeof(a[7][7]), &a[7][7]);
  printf("double a[0]    %d %016lx\n",sizeof(a[0]), &a[0]);
  printf("double a[2]    %d %016lx\n",sizeof(a[2]), &a[2]);
  printf("double a[0][x]    %d %016lx\n",sizeof(a[0])/sizeof(a[0][0]), &a[2]);
  
}
