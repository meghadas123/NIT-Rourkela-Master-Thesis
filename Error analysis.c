#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define pi (3.141592653589793)
#define e  (2.718)
#define G  (6.67430*1/pow(10,11))
#define c  (3*pow(10,8))
int main()
{
  int index;
  float k, a, rms,l,nu_phi,nu_r,nu_theta;
  char output[1000];
  FILE* fp;
  FILE* qp;
  fp=fopen("input.txt","r");
  qp=fopen("output.txt","w");
  int cur_line=0;
  while(fgets(output,1000,fp)!=NULL)
  {
    sscanf(output,"%d %f %f %f \n",&index,&k,&a,&rms);
    for (float M=8.49*2*pow(10,30); M<=9.71*2*pow(10,30); M+=0.1*2*pow(10,30))
    {
      for (float r=rms; r<=rms+20; r+=0.1)
      {
        l=r*pow(e,-k/r);
        nu_phi = (pow(c,3)/(G*M))*1/(2*pi*(a+pow(l,1.5)));
        nu_r = nu_phi*pow(e,k/r)*sqrt(1- 6*(1/l)+8*a*pow(1/l,1.5)-3*pow(a,2)*pow(1/l,2));
        nu_theta = nu_phi*sqrt(1-4*a*pow(1/l,1.5)+3*pow(a,2)*pow(1/l,2));
      }
    }
    fprintf(qp,"%d \t %f \t %f \t %f \t %f \t %f \t %f \t %f \t %f\n",index,k,a,rms,nu_phi,nu_r,nu_theta,nu_phi-nu_r,nu_phi-nu_theta);
  }
  fclose(fp);
  fclose(qp);
}
