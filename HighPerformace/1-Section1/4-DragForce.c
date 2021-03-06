/*
Jonathan Urrutia
2020/12/21

Scientific computing with CUDA course

Quasistatic integration
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DRAG_COEFF 1e-2
#define STEP_SIZE 1e-3

typedef struct state{
  double x, y; // positions
  double vx, vy; // velocities
} state;

double ax ( state s); //x acceleration
double ay ( state s);  // y acceleration

state system_evol(state s);  // Our system evolution

int main(int argc, char *argv[]){
  //The program takes one argument, the initial velocity
  if(argc != 2){
    printf("Input number of data points in km/h! \n");
    return -1;
  }

  double v_i = atof(argv[1])/3.6; //Change from km/h to m/s
  state s;
  s.x = 0;
  s.y = 2; //Perosons height
  s.vx = v_i/sqrt(2); //throw at 45 degrees
  s.vy = v_i/sqrt(2);

  while(s.y > 0){ // Not toching the ground
    s = system_evol(s);
  }

  printf("You throw the ball a distance of %5.4e metres\n", s.x);
  return 0;
}



/*
 Differential equations
*/


double ax(state s){
  return -DRAG_COEFF*s.vx*s.vx / fabs(s.vx);
}

double ay(state s){
  return -9.81 - DRAG_COEFF*s.vy*s.vy / fabs(s.vy);
}

state system_evol(state s){
  state s_new;
  // Updte velocity half step
  s_new.vx = s.vx + 0.5 * STEP_SIZE * ax(s);
  s_new.vy = s.vy + 0.5 * STEP_SIZE * ay(s);

  // Update positions
  s_new.x = s.x + STEP_SIZE * s_new.vx;
  s_new.y = s.y + STEP_SIZE * s_new.vy;

  //UPdate velocities half STEP_SIZE
  s_new.vx += 0.5 * STEP_SIZE * ax(s);
  s_new.vy += 0.5 * STEP_SIZE * ay(s);

  return s_new;
}
