#include <iostream>
#include <cmath>
#include <stdlib.h>
#include<fstream>

//Global variables declaring
const double G=9.8;
const double dt=0.01; //Step for th method //M_PI/300.0;
const double eps=0.001;
//theta''+g/l theta + q theta' = F_d sin(Omega t)

class Pendulum
{
public:
  double L; //Lenght
  double q; //Friction coeficient
  double Fd; //External Force
  double Omega; //External force frequency
  double W; //Angular velocity 
  double Theta; //Angle
  Pendulum();// Initial values for the class
  ~Pendulum();//Anihilator
};
Pendulum::Pendulum()
{
  L=0.0;
  q=0.0;
  Fd=0.0;
  Omega=0.0;
  W=0.0;
  Theta=0.0;
}
Pendulum::~Pendulum()
{
}

//------------------------------Function declaring----------------------------
void initial_conditions(Pendulum & p, double fd_new);
void euler_cromer(Pendulum & p,double dt,double t, double &omega);


int main(int argc, char** argv)
{
  Pendulum p;
  double omega_repite = 0.0;
  double t=0.0;//Time 
  int N = atoi(argv[1]);//steps of evolution
  double fd_new = atof(argv[2]);
  // intialization
  initial_conditions(p, fd_new);
  std::ofstream outfile;
  outfile.open("puntos.dat");
  for (int ii=1; ii<=N; ii++)
    {
      double omega_repite = 0.0;
      euler_cromer(p,dt,t, omega_repite);
      std::cout << t << "\t" << p.Theta << "\t" << p.W  << std::endl;
      t+=dt;
      outfile << omega_repite << std::endl;
    }
    outfile.close();
  return 0;
}


// ------------------- Functions ------------------------------------
void euler_cromer(Pendulum & p,double dt,double t, double &omega)
{
  // Euler- Cromer
  p.W=p.W+(-(G/p.L)*sin(p.Theta) - p.q*p.W + p.Fd*sin(p.Omega*t))*dt;
  p.Theta=p.Theta + p.W*dt;
  if(p.Theta < - M_PI)
    {
      p.Theta += 2*M_PI;
       omega = p.W;
   
    }
  else if(p.Theta > M_PI)
    {
      p.Theta += -2*M_PI;
       omega = p.W;
      
    }
} 
 
void initial_conditions(Pendulum & p, double fd_new)
{
  p.q=0.5;
  p.Fd=fd_new;
  p.Omega=0.666;
  p.L=G;
  p.W=0.0;
  p.Theta=0.2;  
}