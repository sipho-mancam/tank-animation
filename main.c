#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "ESD.h"
#include <math.h>

int i, j, x, y, iCount, time, oTime, level, oFlow, l_cont;

void tank_flow(int iCount);
void clr_in();
void flow_out();
void clr_out();
void sys_draw();
void tank_fill();
void tank_clr();
void screen_eff(int x, int y, int col, char text[]);

int main()
{

    char key;

    i=0;
    x=0;
    y=1;
    iCount=0;
    time=5000;
    oTime=5000;
    level=0;
    oFlow=3;
    l_cont=19;
    sys_draw(); // draw the  tank.... and the pipes

    do
    {
        gotoxy(4,28);
        printf("%d --> l_cont", l_cont);
        //key management
        if(kbhit())
        {
            key=getch();

            if(key=='i')
            {
                if(time > 50)
                {
                    time/=5;
                }
            }
            else if(key=='I')
            {
                if(time<500000)time*=5;
            }
            if(key=='O')
            {
                if(oFlow<10)
                {
                    oFlow+=2;
                }
            }
            else if(key=='o')
            {
                if(oFlow>=1)
                {
                    oFlow-=2;
                }
            }
        }

        //fill up the tank
        tank_fill();
        //in let pipe flow
        tank_flow(iCount);

        //when the tank is full stop the inlet and get the outlet flowing and reduce the fluid level
        if(level==19)
        {
            int newTime=50000;

            //stop the inlet !
            clr_in();

            clr_out();

            screen_eff(25,3,10,"Tank is Full !!!");

            do
            {
                gotoxy(4,28);
                printf("%d --> l_cont", l_cont);
                //keys management
               if(kbhit())
               {
                   key=getch();

                   if(key=='o')
                   {
                       newTime/=5;
                   }
                   else if(key=='O')
                   {
                       newTime*=5;
                   }
               }

                if(iCount%oFlow>0)
                {
                    ++iCount;
                    continue;
                }

                // outlet tank pipe
                flow_out();

                //clear out the tank
                tank_clr();

                iCount ++;
                usleep(newTime);


                //add inward flow
                if(level <=14)
                {
                       tank_flow(iCount);

                        if(level==1)
                        {
                        //stop the outward flow at 10 units
                        clr_out();

                        //stop the inward flow
                        for(int i=19;i>=1;--i)
                        {
                            gotoxy(14,i);
                            printf(" ");
                        }
                        for(int k=0;k<15;k++)
                        {
                            gotoxy(k,1);
                            printf(" ");
                        }

                        //screen effects for full tank
                        screen_eff(25,16,12,"Tank is Empty !!!");
                        int counter=0;
                        do
                        {
                                tank_flow(iCount);

                                iCount++;

                            counter++;
                        }while(counter<=10);
                        //while(1);

                        //increase level once before the outflow starts

                        sleep(1);
                        break;
                    }
            }
            }while(level!=1);
        }

        // control the outlet flow with oFlow
        if(iCount%oFlow>0)
        {
            ++iCount;
            continue;
        }
        // outlet tank pipe
        flow_out();

        iCount ++;



    }while(key!=27);
    return 0;
}


void tank_flow(int iCount)
{
    if(iCount%2==0)
    {
        setColor(11);
        for(i=0;i<=1;++i)
        {
            for(j=0;j<=20;j+=2)
                {
                    if(j<=14 && i==0)
                    {
                        gotoxy(j+1,y);
                        printf(" ");
                        gotoxy(j,y);
                        printf("%c",219);
                        usleep(time);
                        //initialize the vertical print
                        if(j==14)
                        {
                            break;
                        }
                    }
                    else
                    {
                            if(j==l_cont+1)
                            {
                                break;
                            }
                            gotoxy(14,j+2);
                            printf(" ");
                            gotoxy(14, j+1);
                            printf("%c",219);
                            usleep(time);
                    }
                }
            }
        }
        else
        {
            // second state of the tank flow
            for(i=0;i<=1;++i)
            {
                for(j=1;j<=19;j+=2)
                {
                    if(j<=13 && i==0)
                    {
                        //horizontal print
                        gotoxy(j+1,y);
                        printf(" ");
                        gotoxy(j,y);
                        printf("%c",219);
                        gotoxy(j-1,y);
                        printf(" ");
                        usleep(time);

                        //initialize the vertical print
                        if(j==13)
                        {
                            break;
                        }
                    }
                    else
                    {
                        //print until certain level
                        if(j==l_cont)
                        {

                            break;
                        }
                        gotoxy(14,j); //go one step behind
                        printf(" ");
                        gotoxy(14, j+2); // go one step ahead
                        printf(" ");
                        gotoxy(14, j+1); //printing position
                        printf("%c",219);
                        usleep(time);

                }
            }
        }
    }
}

void clr_in()
{
    //stop the inward flow
        for(int i=5;i>=1;--i)
        {
            gotoxy(14,i);
            printf(" ");
        }
        for(int k=0;k<15;k++)
        {
            gotoxy(k,1);
            printf(" ");
        }

}

void flow_out()
{
    if(iCount%2!=0)
    {
        setColor(11);
        for(i=0;i<=1;++i)
        {
            for(j=0;j<=10;j+=2)
            {
                if(j<=10 && i==0)
                {
                    gotoxy(j+61,y+20);
                    printf(" ");
                    gotoxy(j+60,y+20);
                    printf("%c",219);
                    usleep(oTime);
                    //initialize the vertical print
                    if(j==10)
                    {
                        break;
                    }
                }
                else
                {
                    //downward flow
                    if(j==4)
                    {
                        break;
                    }
                    //downward flow
                    gotoxy(70,j+22);
                    printf(" ");
                    gotoxy(70,j+23);
                    printf("%c",219);
                }
            }
        }
    }
    else
    {
    // second state of the tank flow
        for(i=0;i<=1;++i)
        {
            for(j=1;j<=10;j+=2)
            {
                if(j<=9 && i==0)
                {
                    gotoxy(j+59,y+20);
                    printf(" ");
                    gotoxy(j+60,y+20);
                    printf("%c",219);
                    gotoxy(j+61,y+20);
                    printf(" ");
                                //initialize the vertical print
                    if(j==9)
                    {
                        break;
                    }
                }
                else
                {
                    //the bug is here
                    //downward flo
                    if(j==5)
                    {
                        break;
                    }
                    gotoxy(70,j+20); //go one step behind
                    printf(" ");
                    gotoxy(70, j+22); // go one step ahead
                    printf(" ");
                    gotoxy(70, j+21); //printing position
                    printf("%c",219);
                }
            }
        }

    }
}

void clr_out()
{
    for(int out=60;out<=70;++out)
    {
        gotoxy(out,21);
        printf(" ");
    }
    for(int outy=21;outy<25;++outy)
    {
        gotoxy(70,outy);
        printf(" ");
    }
}

void sys_draw()
{
    // inlet tube

    for(int k=0; k<=14; k++)
    {
        gotoxy(k,0);
        printf("%c",205);
        gotoxy(k,2);
        printf("%c",k<14?205:032);
    }
    // tank sides
    for(int i=5;i<25;++i)
    {
        gotoxy(10,i);
        printf("%c",179);
        gotoxy(60,i);
        printf("%c",179);

    }
    //tank label
    for(int s=5;s<25;s+=2)
    {
        gotoxy(4,s);
        printf("%03d - ", 100-s*5+25);
    }
    //take bottom
    for(int j=11;j<=59;++j)
    {
        gotoxy(j,25);
        printf("%c",196);
    }

    gotoxy(10,25);
    printf("%c",192);
    gotoxy(60,25);
    printf("%c",217);

    // code for outlet tube on the tank

    gotoxy(60,20);
    printf("%c",192);
    gotoxy(60,22);
    printf("%c",218);
    gotoxy(60,21);
    printf(" ");
    for(int t=61;t<67;++t)
    {
        gotoxy(t,20);
        printf("%c",196);
        gotoxy(t,22);
        printf("%c",t<65?196:32);
    }
}

void tank_fill()
{

    if(iCount%10==0)
    {
        l_cont=21-level;
        if(l_cont%2==0)l_cont--;
        setColor(11*16+11*1);
        for(int y=24;y>23-level;--y)
        {
            for(int x=11;x<=59;++x)
            {
                gotoxy(x,y);
                printf("%c",223);
            }
        }
        if(level<=20)
        {
            ++level;
        }
        setColor(11);
    }


}

void tank_clr()
{
    if(iCount%10==0)
    {
        setColor(7);
        //level control
        for(int y=6;y<=(17-level)+7;++y)
        {
            for(int x=11;x<=59;++x)
            {
                gotoxy(x,y);
                printf(" ");
            }
        }
        level--;
        setColor(11);
        if(level>=14)return;
        l_cont=21-level;
        if(l_cont%2==0)l_cont++;
    }
}

void screen_eff(int x, int y, int col, char text[])
{
    int s_e=0;
    setColor(col);
    while(s_e<=6)
    {
        gotoxy(x,y);
        printf("%s",text);
        sleep(1);
        gotoxy(x,y);
        printf("                      ");
        s_e++;
        sleep(1);
    }
    setColor(11);
}
