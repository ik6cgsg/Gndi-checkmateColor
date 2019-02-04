#ifndef __HANDLE_H_
#define __HANDLE_H_

#include <windows.h>

typedef enum
{
  SAME, DIFF, FIRST, SCND
} TYPES;

/* Case WM_PAINT drawing function */
void Paint( HWND hWnd );

/* Mouse button down handle function */
void ButtonDown( INT X, INT Y, UINT Keys );

/* Init chess board array function */
void Init( void );

/* Check if coordinates inside array */
int Inside( INT X, INT Y );

#endif /* __HANDLE_H_ */

/* END OF 'handle.h' FILE */
