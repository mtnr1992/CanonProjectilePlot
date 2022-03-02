/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: ExitFunc */
#define  PANEL_GRAPH                      2       /* control type: graph, callback function: (none) */
#define  PANEL_ANGLE                      3       /* control type: numeric, callback function: (none) */
#define  PANEL_INITVELOCITY               4       /* control type: numeric, callback function: (none) */
#define  PANEL_LOAD                       5       /* control type: command, callback function: Load */
#define  PANEL_CLEAR                      6       /* control type: command, callback function: Clear */
#define  PANEL_FIRE                       7       /* control type: command, callback function: Fire */
#define  PANEL_YPOS                       8       /* control type: numeric, callback function: (none) */
#define  PANEL_XPOS                       9       /* control type: numeric, callback function: (none) */
#define  PANEL_TIMER                      10      /* control type: timer, callback function: TimeTick */
#define  PANEL_GRAVITY                    11      /* control type: numeric, callback function: (none) */
#define  PANEL_background                 12      /* control type: canvas, callback function: (none) */
#define  PANEL_DECORATION_2               13      /* control type: deco, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Clear(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ExitFunc(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Fire(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Load(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TimeTick(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
