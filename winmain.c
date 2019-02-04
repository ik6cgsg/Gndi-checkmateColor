#include "handle.h"

#define WND_CLASS_NAME "My window class"

/* Pointer to handle function */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam );

/* The main program function */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  /* Class system registration */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return 0;
  }

  /* Window create */
  hWnd = CreateWindow( WND_CLASS_NAME, "CGSGFOREVER!", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 
                       CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL );

  if (hWnd == NULL)
  {
    MessageBox(NULL, "Error create window", "ERROR", MB_OK | MB_ICONSTOP);
    return 0;
  }
  /* Show and redraw window */
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);
  
  /* Message handle loop */
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
} /* End of 'WinMain' function */

/* Message handle function */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  switch(Msg)
  {
  case WM_CREATE:
    Init();
    return 0;
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  case WM_PAINT:
    Paint(hWnd);
    return 0;
  case WM_LBUTTONDOWN:
    ButtonDown((INT)(SHORT)LOWORD(lParam),
      (INT)(SHORT)HIWORD(lParam), (UINT)(SHORT)LOWORD(wParam));
    InvalidateRect(hWnd, NULL, TRUE);
    //RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWindowFunc' function */

/* END OF 'winmain.c' FILE */
