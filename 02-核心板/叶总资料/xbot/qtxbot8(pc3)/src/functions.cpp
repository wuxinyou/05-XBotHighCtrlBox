#include "functions.h"

#include <iostream>
using namespace std; 

double minimalStep(double scaleSize, int steps)
{
  scaleSize = std::abs(scaleSize); 
  double ms = scaleSize/steps; 
  double fractions[]={5,2,1}; 
  double multiply = 10; 
  double fraction = 1.0; 
  double test; 
  if (static_cast<int>(ms)<=5) multiply = 0.1 ; 

  while (true)
  {
     for (int i=0;i<3;i++)
     {
      //cout<<"Fractions:"<<fractions[i]<<" scaleSize:"<<scaleSize<<" steps:"<<steps<<" steps*farction:"<<steps*fractions[i]<<endl; 
       if (fractions[i]<ms)
          { 
           fraction =fractions[i]; 
          }
       
         fractions[i]*=multiply; 
         test = steps * fractions[i]; 
         if ( (test < scaleSize) && multiply< 1.0 ) return fraction; 
         if ( (test > scaleSize) && multiply> 1.0 ) return fraction; 
     }  
  }
 
  return fraction; 
}
