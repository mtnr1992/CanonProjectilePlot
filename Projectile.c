#include "bass.h"  
#include "toolbox.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "Projectile.h"

static int panelHandle;

HSTREAM FIRE;
HSTREAM FLY;
HSTREAM LAND;
FILE *fp;
int fire=1;  
double initvelocity, angle,radangle, dt=0.01,g=-9.81,vy,vx,vy0;


typedef struct
{
	 double xpos;
	 double ypos;
}object;

object ball;


int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Projectile.uir", PANEL)) < 0)
		return -1;
	BASS_Init( -1,44100, 0,0,NULL);
	FIRE = BASS_StreamCreateFile(FALSE,"Firing.WAV",0,0,0);
	FLY = BASS_StreamCreateFile(FALSE,"flyby.WAV",0,0,0);
	LAND = BASS_StreamCreateFile(FALSE,"APPLAUSE.WAV",0,0,0);
	DisplayPanel (panelHandle);
	RecallPanelState  (panelHandle,"Last_Save", 0);
	RunUserInterface ();
	SavePanelState (panelHandle, "Last_Save", 0); 
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK ExitFunc (int panel, int event, void *callbackData,
						  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK Fire (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
char filename[300]; 
	switch (event)
	{
		case EVENT_COMMIT:
			
			
			//get init values
			GetCtrlVal(panelHandle,PANEL_ANGLE,&angle);
			GetCtrlVal(panelHandle,PANEL_INITVELOCITY,&initvelocity);
			GetCtrlVal(panelHandle,PANEL_GRAVITY,&g);
			
			//init values setting
			g=-g;
			ball.xpos=0;
			ball.ypos=0;
			radangle=angle *Pi()/180;
			vy=initvelocity*sin(radangle);
			vx=initvelocity*cos(radangle);
			
			
			//select file name & open to write in it
			if(FileSelectPopup ("", "*.csv", "", "", VAL_SAVE_BUTTON, 0, 0, 1, 0, filename)){
			fp=fopen(filename,"w");   
			
			//Play fire sound
			BASS_ChannelPlay(FIRE,TRUE);
			BASS_ChannelPlay(FLY,TRUE);
			
			//start timer
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, fire%2);
			fire++;
			}
			break;
	}
	return 0;
}

int CVICALLBACK TimeTick (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
  static int i=0,k=0;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			//first dot as black
			if(fire%2)
			PlotPoint (panelHandle, PANEL_GRAPH, ball.xpos, ball.ypos, VAL_SOLID_CIRCLE, VAL_BLACK); 
			
			//calculations-----------------------------
			//x (dt)
			ball.xpos=ball.xpos+vx*dt; 
			
			//y (dt)
			vy=vy+g*dt;
			ball.ypos=ball.ypos + vy*dt + g*dt*dt/2;
			//-----------------------------------------
			
			//Ground Hit Check--------------------------------------------------------------------- ~~~~~~~~~
			if(ball.ypos<0.0) {
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
			fire++;
			fclose(fp); //close file and save
			i=0;
			k=0;
			
			BASS_ChannelPlay(LAND,TRUE);
			//stopsound
			BASS_ChannelStop(FLY);
			}
			else {
				//plot 
				{
						if(i<255){
							PlotPoint (panelHandle, PANEL_GRAPH, ball.xpos, ball.ypos, VAL_SOLID_CIRCLE, MakeColor(k,0,0)); 
							k++;
						}
						if(i>=255){		
						PlotPoint (panelHandle, PANEL_GRAPH, ball.xpos, ball.ypos, VAL_SOLID_CIRCLE, MakeColor(k,0,0)); 
						k--;
						}
						if(k==0)
							i=k;
							
						i++;
						}
					//numeric update
					SetCtrlVal(panelHandle,PANEL_XPOS,ball.xpos);
					SetCtrlVal(panelHandle,PANEL_YPOS,ball.ypos);
					 
					//writing to csv
					fprintf(fp,"%lf,%lf\n",ball.xpos,ball.ypos);
				}
			break;
	}
	return 0;
}			  

int CVICALLBACK Clear (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				DeleteGraphPlot (panelHandle, PANEL_GRAPH, -1, VAL_IMMEDIATE_DRAW);  
			break;
	}
	return 0;
}

int CVICALLBACK Load (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
char line[100],filename[300];
int i=0,k=0;
	
	switch (event)
	{
		case EVENT_COMMIT:

			 if( FileSelectPopup ("", "*.csv", "", "", VAL_LOAD_BUTTON, 0, 0, 1, 0, filename)){
	 		 fp=fopen(filename,"r");
			 while(fgets (line, 99, fp))
				{	
				sscanf(line,"%lf,%lf\n",&ball.xpos,&ball.ypos);	
				SetCtrlVal(panelHandle,PANEL_XPOS,ball.xpos);
				SetCtrlVal(panelHandle,PANEL_YPOS,ball.ypos);
				
				
				if(i<255){
				PlotPoint (panelHandle, PANEL_GRAPH, ball.xpos, ball.ypos, VAL_SOLID_CIRCLE, MakeColor(k,0,0)); 
				k++;
				}
				if(i>=255){		
				PlotPoint (panelHandle, PANEL_GRAPH, ball.xpos, ball.ypos, VAL_SOLID_CIRCLE, MakeColor(k,0,0)); 
				k--;
				if(k==0)
					i=k;
					}
				i++;
				}
				
			    fclose(fp);
			 }
			break;
	}
	return 0;
}
