
#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <assert.h>
#include <cmath>
//#include <iostream> // dla test體 

using namespace std;


double minimalStep(double scaleSize, int steps);

template <typename T> //模板函数 限定范围的模板函数
bool range(T m_minimum,T m_maximum, T & m_min, T & m_max,unsigned int steps, bool left = false,double inc = 5.0)
{
  //cout<<"("<<m_minimum<<","<<m_maximum<<")  ("<<m_min<<","<<m_max<<")"<<endl;
  T max_tmp = m_max, min_tmp = m_min;
  m_max=m_maximum;
  m_min=m_minimum;
  assert( m_max > m_min );
  //  assert( (m_max - m_min) > 0 );
  //  if (m_max<0) left!=left; 
  
  T diff = abs(m_max - m_min);
  T scale = 0, factor = 0 ;

  while (inc * steps > (m_maximum-m_minimum))
  if (inc/10 > 0 ) inc/=10;
  else break;

  bool done = false;
  while ( diff > scale ) 
   { factor+=static_cast<T>(inc);  scale = factor * steps;  }
   
  while (!done)
  {
    
    // dirty hack to have zero equal exactly zero 
    if (m_max<0)  m_max=m_min - fmodf(m_min,steps);
    else m_max = 0.0; 
    
     while ( m_max < m_maximum ) m_max +=factor;
     m_min = m_max - scale;
     if (m_min <= m_minimum ) done = true;
     else { factor+=static_cast<T>(inc); scale = factor * steps; }
  }
  // Wprowadzenie koretkty by skala nie przesuwa砤 si?w lewo na osi X
  if (left)
  	while (m_min + factor <= m_minimum)
  	{
	   	m_min+=factor;
   		m_max+=factor;
  	}
//  cout<<"Min:"<<m_min<<" Max:"<<m_max<<endl;
 return (m_max != max_tmp) | (m_min != min_tmp);
}


#endif // _FUNCTIONS_H_
