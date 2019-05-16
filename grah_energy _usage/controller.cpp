#include "powerdata.h"
#include "datadisplay.h"
//#include "battdata.h"
#include "graphics.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
int main()
{
class1 powerdata;
//class2 battdata;
class3 datadisplay;

// initialisation of variables
int useroption;
string filename=" ";
string file=" ";
int finaltime[24];
float finalgendata[24];
float finalcondata[24];

                  
                  cout<<"Enter day (eg: monday)"<<endl;
                  cin>>filename;
                  
                  file = filename + ".txt";
                  
                  // ask the user for input
                  cout<<"Select an option from the list"<<endl;
                  cout<<"[1] Display Power generation and consumption"<<endl;
                  cout<<"[2] Display Battery percentage level"<<endl;
                  cin>>useroption;
                  
                  // function call statements
                  powerdata.getpowerdata(file,finaltime,finalgendata,finalcondata);
                  cout<<"Time     Power generated      Power consumed"<<endl;
                  datadisplay.displaynumdata(finaltime,finalgendata,finalcondata);
                  datadisplay.displaygraphdata(finaltime,finalgendata,finalcondata);
                  
                  //battdata.getbatterydata(finaltime,finalgendata,finalcondata);
                  
                  system("pause");
                  }
                  
                  
    
