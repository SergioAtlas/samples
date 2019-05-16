#include "powerdata.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

void class1::getpowerdata(string file,int finaltime[24],float finalgendata[24],float finalcondata[24])
{
     ifstream inputfile;
     inputfile.open(file.c_str());
     
     for(line=0; line<24; line++)
     {
                 
       inputfile >> time[line] >> gendata[line] >> condata[line];
       finaltime[line]= time[line];
       finalgendata[line]=gendata[line];
       finalcondata[line]=condata[line];                      
     }
}

     
