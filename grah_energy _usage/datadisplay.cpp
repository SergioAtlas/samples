#include "datadisplay.h"
#include "graphics.h"
#include <iostream>
#include <string>
#include <iomanip>
#include<conio.h>
#include <fstream>
using namespace std;

void class3::displaynumdata(int finaltime[24],float finalgendata[24], float finalcondata[24])
{
      for(i=0; i< 10; i++)
     {
      cout<< finaltime[i] << "           " << finalgendata[i] << "               " << finalcondata[i] << endl;
     }
      for(i=10; i< 24; i++)
     {
      cout<< finaltime[i] << "          " << finalgendata[i] << "               " << finalcondata[i] << endl;
     }
     
}

void class3::displaygraphdata(int finaltime[24],float finalgendata[24], float finalcondata[24])
{
 char *label="HOURS";
 initwindow(900,850,"Power generation Vs Power Consumption");
 for(i=0; i< 24; i++)
 {             
             line(150+(27*finaltime[i]),700-(finalgendata[i]/2),150+(27*finaltime[i+1]),700-(finalgendata[i+1]/2));
               circle(150+(27*finaltime[i]),700-(finalgendata[i]/2),5);
       // cout<<"y"<<700-(finalgendata[i]/2);     
 }
 
 
cout<<"x"<<"     y"<<endl;

for(i=0; i< 24; i++)
 {
             //line(150+(27*finaltime[i]),700-(finalgendata[i]/2),150+(27*finaltime[i+1]),700-(finalgendata[i+1]/2));
       setcolor(WHITE);
       
        circle(150+(27*finaltime[i]),700-(finalgendata[i]/2),5);
        cout<<150+(27*finaltime[i])<<"     "<<700-(finalgendata[i]/2)<<endl;     
 }
 cout<<"x"<<"     y"<<endl;
             setcolor(RED);
             line(150,702,150,5);  
              line(150,702,800,702) ; 
               
               //line(150,702,700,84.7) ; 
               //
              
              
                        outtextxy(150,710,"0");
                        outtextxy(177,710,"1");
                        outtextxy(204,710,"2");
                        outtextxy(231,710,"3");
                        outtextxy(258,710,"4");                        
                        outtextxy(285,710,"5");
                        outtextxy(312,710,"6");
                        outtextxy(339,710,"7");
                        outtextxy(366,710,"8");
                        outtextxy(393,710,"9");
                        outtextxy(420,710,"10");
                        outtextxy(447,710,"11");                        
                        outtextxy(474,710,"12");
                        outtextxy(501,710,"13");
                        outtextxy(528,710,"14");
                        outtextxy(555,710,"15");
                        outtextxy(582,710,"16");
                        outtextxy(609,710,"17");
                        outtextxy(636,710,"18");
                        outtextxy(663,710,"19");
                        outtextxy(690,710,"20");
                        outtextxy(717,710,"21");
                        outtextxy(744,710,"22");
                        outtextxy(771,710,"23");
                       
                      
                       
                       outtextxy(110,700,"0");
                       outtextxy(110,650,"100");
                       outtextxy(110,600,"200");
                       outtextxy(110,550,"300");
                       outtextxy(110,500,"400");
                       outtextxy(105,450,"500");
                        outtextxy(110,400,"1400");
                       
                       outtextxy(110,350,"800"); 
                       outtextxy(110,300,"900");
                       outtextxy(110,250,"1400");
                       outtextxy(110,200,"1000");
                       outtextxy(110,150,"1100");
                       outtextxy(110,100,"1200");
                       outtextxy(110,50,"1300");
                       outtextxy(110,3,"1400");
                      
                        int x;
                       for(x=150;x<800;x+2)
                       {
                        line(x,650,x+1,650);
                             x=x+8;            
                       }
                       for(x=150;x<800;x+2)
                       {
                        line(x,600,x+1,600);
                             x=x+8;            
                       }
                       for(x=150;x<800;x+2)
                       {
                        line(x,550,x+1,550);
                             x=x+8;            
                       }
                       for(x=150;x<800;x+2)
                       {
                        line(x,500,x+1,500);
                             x=x+8;            
                       }
                       for(x=150;x<800;x+2)
                       {
                        line(x,450,x+1,450);
                             x=x+8;            
                       }for(x=150;x<800;x+2)
                       {
                        line(x,400,x+1,400);
                             x=x+8;            
                       }
                       for(x=150;x<800;x+2)
                       {
                        line(x,350,x+1,350);
                             x=x+8;            
                       }
                       for(x=150;x<800;x+2)
                       {
                        line(x,300,x+1,300);
                             x=x+8;            
                       }
                       
                       for(x=150;x<800;x+2)
                       {
                        line(x,250,x+1,250);
                             x=x+8;            
                       }
                       for(x=150;x<800;x+2)
                       {
                        line(x,200,x+1,200);
                             x=x+8;            
                       }
                        for(x=150;x<800;x+2)
                       {
                        line(x,150,x+1,150);
                             x=x+8;            
                       }
                        for(x=150;x<800;x+2)
                       {
                        line(x,100,x+1,100);
                             x=x+8;            
                       }
                        for(x=150;x<800;x+2)
                       {
                        line(x,50,x+1,50);
                             x=x+8;            
                       }
                       /*
                       int x1;
                      
                        int y=650;
                        int y1;
                        
                            while (y>50)
                        {    
                       for(x=0;x<702;x+2)
                       {
                                         line(x,y,x+1,y);
                                         //line(x,y,x,y+1);
                                         
                                         x=x+8;
                                         y=x+8;
                                         }
                                         y=y-50;
                               
                              }*/  
                              setcolor(WHITE);      
                             settextjustify(100,200);
                             outtextxy(830,700,label);
                             settextjustify(600,70);
                             outtextxy(40,50,"WATTS-HOURS(WH)");
                       
                                               
                              
 while(!kbhit())
 {
  delay(200);               
 }
 
}
