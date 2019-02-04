#include <stdlib.h>

#include "handle.h"

#define SIZE 100

UINT ChessBoard[8][8];
CHAR Type;

/* Init chess board array function */
void Init( void )
{
  int i, j;

  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
    {
      if (j == 3 || j == 7)
        ChessBoard[i][j] = 0xFF00FF;
      else
        ChessBoard[i][j] = rand() % ((2 << 24) - 1);
    }
  Type = FIRST;
} /* End of 'Init' function */

/* Case WM_PAINT drawing function */
void Paint( HWND hWnd )
{
  HDC hDC;
  PAINTSTRUCT PaintStruct;

  hDC = BeginPaint(hWnd, &PaintStruct);
  if (hDC)
  {
    HBRUSH hBrush, hOldBrush;
    int i, j;

    hBrush = (HBRUSH)GetStockObject(DC_BRUSH);
    hOldBrush = SelectObject(hDC, hBrush);

    for (i = 0; i < 8; i++)
      for (j = 0; j < 8; j++)
      {
        SetDCBrushColor(hDC, ChessBoard[i][j]);

        Rectangle(hDC, j * SIZE, i * SIZE, (j + 1) * SIZE - 1, (i + 1) * SIZE - 1);
      }

    //SetBkColor(hDC, RGB(170, 100, 0));
    if (Type == SAME)
      TextOut(hDC, 9 * SIZE, 3 * SIZE, "Same colour!", strlen("Same colour!"));
    else if (Type == DIFF)
      TextOut(hDC, 9 * SIZE, 3 * SIZE, "Different(Click on cell)", strlen("Different(Click on cell)"));
    else if (Type == SCND)
      TextOut(hDC, 9 * SIZE, 3 * SIZE, "Choose second", strlen("Choose second"));
    else
      TextOut(hDC, 9 * SIZE, 3 * SIZE, "Choose first", strlen("Choose first"));

    SelectObject(hDC, hOldBrush);
    DeleteObject(hBrush);

    EndPaint(hWnd, &PaintStruct);
  }

} /* End of 'Paint' function */

/* Check if coordinates inside array */
int Inside( INT X, INT Y )
{
  if (X >= 8 * SIZE || Y >= 8 * SIZE || X < 0 || Y < 0)
    return 0;
  return 1;
} /* End of 'Inside' function */

/* Mouse button down handle function */
void ButtonDown( INT X, INT Y, UINT Keys )
{
  static INT PrevX = -1, PrevY = -1;

  if (Keys == MK_LBUTTON)
  {
    if (Inside(X, Y))
    {
      int i, j;

      for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
          if (X >= j * SIZE && Y >= i * SIZE && X < (j + 1) * SIZE - 1 && Y < (i + 1) * SIZE - 1)
          {
            if (PrevX < 0)
            {
              PrevX = j;
              PrevY = i;
              Type = SCND;
            }
            else
            {
              if (j != PrevX || i != PrevY)
                if (ChessBoard[i][j] == ChessBoard[PrevY][PrevX])
                  Type = SAME;
                else
                  Type = DIFF;
              else
                Type = FIRST;
              PrevX = -1;
            }
            return;
          }
    }
  }
} /* End of 'ButtonDown' function */

/* END OF 'handle.c' FILE */
