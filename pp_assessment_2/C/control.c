/*
 *
 * Control program for the MD update
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <mm_malloc.h>
#include <malloc.h>

#define DECL
#include "coord.h"

double second(void); 
int main(int argc, char *argv[]){
  int i,j;
  FILE *in, *out;
  double tstart,tstop;
  double start,stop;
  char name[80];
  /*  timestep value */
  double dt=0.02;
  size_t alignment = 64;
  /*  number of timesteps to use. */
  int Nstep=100;
  //int Nsave=5; 			//original_config
  int Nsave=1;
  printf("Ndim == %d\n",Ndim);
  printf("Npair == %d\n",Npair);
  if( argc > 1 ){
    Nstep=atoi(argv[1]);
  }
  wind[Xcoord] = 0.9;
  wind[Ycoord] = 0.4;
  wind[Zcoord] = 0.0;
  /* set up multi dimensional arrays */

  /*
 */ 

  r = calloc(Nbody,sizeof(double));					// 4096 * 8
  delta_r = calloc(Nbody*Nbody,sizeof(double));				// 4096 * 4096 * 8
  mass = calloc(Nbody,sizeof(double));					// 4096 * 8
  radius = calloc(Nbody,sizeof(double));				// 4096 * 8
  vis = calloc(Nbody,sizeof(double));					// 4096 * 8
  f[0] = calloc(Ndim*Nbody,sizeof(double));				// 3 * 4096 * 8
  pos[0] = calloc(Ndim*Nbody,sizeof(double));				// 3 * 4096 * 8
  velo[0] = calloc(Ndim*Nbody,sizeof(double));				// 3 * 4096 * 8
  delta_pos[0] = calloc(Ndim*Nbody*Nbody,sizeof(double));		// 3 * 4096 * 4096 * 8


  for(i=1;i<Ndim;i++){							// to small to vectorise. Ndim == 3.
    f[i] = f[0] + i * Nbody;
    pos[i] = pos[0] + i * Nbody;
    velo[i] = velo[0] + i * Nbody;
    delta_pos[i] = delta_pos[0] + i*Nbody*Nbody;
    //printf("Delta_pos[%d] = %p + %d\n", i, delta_pos[0], i*Nbody*Nbody);
  }

/* read the initial data from a file */

  collisions=0;
  in = fopen("input.dat","r");

  if( ! in ){
    perror("input.dat");
    exit(1);
  }

  for(i=0;i<Nbody;i++){								// 4096
    fscanf(in,"%16le%16le%16le%16le%16le%16le%16le%16le%16le\n",
      mass+i,radius+i,vis+i,							// mass,vis,radius all pointers to array 4096
      &pos[Xcoord][i], &pos[Ycoord][i], &pos[Zcoord][i],
      &velo[Xcoord][i], &velo[Ycoord][i], &velo[Zcoord][i]);
  }
  fclose(in);

/*
 * Run Nstep timesteps and time how long it takes
 */
 
   tstart=second();				// timer start
   for(j=1;j<=Nsave;j++){			// Nsave == 5;
      start=second();
      evolve(Nstep,dt); 			// Nstep == 100; dt=0.02;
      stop=second();
      printf("%d timesteps took %f seconds\n",Nstep,stop-start);
      printf("collisions %d\n",collisions);
      fflush(stdout);
/* write final result to a file */
      sprintf(name,"output.dat%03d",j*Nstep);
      out = fopen(name,"w");

      if( ! out ){
	perror(name);
	exit(1);
      }

      for(i=0;i<Nbody;i++){
 //	printf("writing [%d]\n",i);
	fprintf(out,"%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E\n",
		mass[i],radius[i],vis[i],
		pos[Xcoord][i], pos[Ycoord][i], pos[Zcoord][i],
		velo[Xcoord][i], velo[Ycoord][i], velo[Zcoord][i]);
      }
      fclose(out);
  }
  tstop=second();
  printf("%d timesteps took %f seconds\n",Nsave*Nstep,tstop-tstart);

//  _mm_free(r);
  /*
  _mm_free(delta_r);
  _mm_free(mass); 
  _mm_free(radius);
  _mm_free(vis);
  _mm_free(f[0]);
  _mm_free(pos[0]);
  _mm_free(velo[0]); 
  _mm_free(delta_pos[0]);
	*/
}

double second()
{
        struct timeval tp;
        struct timezone tzp;
        int i;

        i = gettimeofday(&tp,&tzp);
        return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

