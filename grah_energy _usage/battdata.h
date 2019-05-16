#include "battdata.h"
#include <iostream>
#include <string>
#include <iomanip>
#include<conio.h>
#include <fstream>
using namespace std;


     
void class2::getbatterydata(int finaltime[24],float finalgendata[24], float finalcondata[24])  
{
     float temp1=0;
     float temp2=0;
     for(int n=0;n<24;n++)
     {
     percentage[n] = temp1+(((finalgendata[n]-finalcondata[n])/finalgendata[n])*100);
                if (percentage[n] >= 100)
                {
                     percentage[n]=100;
                     cout<<"time:  "<<finaltime[n]<<"   full battery 100%"<<endl;;
                }
                
                else if (percentage[n] <= 0)
                {
                     percentage[n]=0;
                     cout<<"time:  "<<finaltime[n]<<"  battery dead 0%"<<endl;
                }
     
                
                else
                {
                     temp1=percentage[n];
                     cout<<"time:  "<<finaltime[n]<<"  battery percentage level: "<< percentage[n] << "%" <<endl;

                }
     
    

     }

}

