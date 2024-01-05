/* Win32-Lite Template
 * Ver 0071
 *
 * General Purpose Template that can be expanded on
 */

/* GCC Build:
 * gcc <path>.cpp -luser32  -lgdi32 -o <path>.exe
 */

// Includes
// Make sure you have the Windows SDK installed in order to include windows.h

#include <windows.h>
#include <winuser.h>

#include "win32_lite.h"



void buttonFunc() {
   printf("This is a button function\n");
}


w32l_window mainWin; 
// The parameters go like the following: Internal name (Not shown) | Window Title | Background color | Width | Height
// Main function to draw windows

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    mainWin = w32l_window_new("win32_liteTemplate", "Win32-Lite Template", RGB(255, 255, 255), 800, 600); 

    // Make sure to add controls, like buttons, before you generate the window

    w32l_window_drawControl("button", "This is a button", 250, 300, 100, 20, 0);
    // The parameters go like:
    // string Control Type (Not shown) | string Control Text | int X Position | int Y Position | int Control Width | int Control Height | int Index
    // Control Type is how you define what type of control you want to use, so Control Type of "button" creates a button
    // i is index of the button. The index must be between 0 and 1000. Indexes must start from 0 and then increase by one. Buttons with a higher Index will be drawn above other buttons


    w32l_window_createBtnFunc(buttonFunc, 0);
    // The parameters go like:
    // void (*func)() | int Index
    // The func parameter is just a pointer to a function
    // i is the index of what button you want to create a button function to
    // All buttons must have a button function with the same index, or else it risks a crash

    // Generates the window

    int gen = w32l_window_generate(mainWin, hInstance, hPrevInstance, lpCmdLine);

    // Make sure you add paint items, like text, after you generate the window, but before you show the window

    w32l_window_drawText("I love Win32-Lite!", RGB(0, 0, 0), RGB(150, 150, 150), 150, 100, 40, 800, 0);
    // The parameters go like:
    // string Text | COLORREF Text Color | COLORREF Background Color | int X Position | int Y Position | int Font Height | int Text Weight | int Index
    // Text Weight 400 = Normal Weight, Text Weight = 800 = Bold Weight
    // i is index of the text. The index must be between 0 and 1000. Indexes must start from 0 and then increase by one. Text with a higher Index will be drawn above other text

    RECT rect;         // Rectangle Object
    rect.left = 0;     // The Top-Left Corner X Position of Rectangle
    rect.top = 0;      // The Top-Left Corner Y Position of Rectangle
    rect.right = 600;  // The Bottom-Right Corner X Position of Rectangle
    rect.bottom = 600; // The Bottom-Right Corner Y Position of Rectangle

    w32l_window_drawRect(rect, RGB(150, 150, 150), RGB(0, 0, 0), 0);
    // The parameters go like:
    // RECT Rectangle | COLORREF Background Color | COLORREF Outline Color | int Index

    int show = w32l_window_show(nCmdShow);

    return 0; // Return of 0 means program ran successfully
}

// LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
//     HDC hdc;
//     HBRUSH b;// = CreateSolidBrush(RGB(255, 0, 0));

//     switch (msg) {
//         case WM_CLOSE:
//             DestroyWindow(hwnd);

//             break;
        
//         case WM_DESTROY:
//             PostQuitMessage(0);

//             break;

//        case WM_PAINT: {
//             PAINTSTRUCT ps;
//             hdc = BeginPaint(hwnd, &ps);

//             RECT r;

//             r.bottom = 30;
//             r.left = 0;
//             r.top = 0;
//             r.right = 150;

//             b = CreateSolidBrush(RGB(255, 0, 0));
//             FillRect(hdc, &r, b);

//             DrawText(hdc, "Hello world retard", -1, &r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

//             RECT fuckme;

//             fuckme.bottom = 100;
//             fuckme.left = 0;
//             fuckme.top = 50;
//             fuckme.right = 100;

//             FrameRect(hdc, &fuckme, b);
//             DrawText(hdc, "fuck me", -1, &fuckme, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            

//             DeleteObject(b);
//             EndPaint(hwnd, &ps);

//             break;
//        }


//         default:
//             return DefWindowProc(hwnd, msg, wParam, lParam);
//     }
// }

// int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow) {
//     WNDCLASSEX wc;
//     HWND hwnd;
//     MSG msg;

//     wc.cbSize        = sizeof(WNDCLASSEX);
//     wc.style         = 0;
//     wc.lpfnWndProc   = WinProc;
//     wc.cbClsExtra    = 0;
//     wc.cbWndExtra    = 0;
//     wc.hInstance     = hInst;
//     wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
//     wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
//     wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
//     wc.lpszMenuName  = NULL;
//     wc.lpszClassName = "win32-game";
//     wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

//     if (!RegisterClassEx(&wc)) {
//         MessageBox(NULL, "Window Reg Failed!", "Error!", MB_ICONEXCLAMATION| MB_OK);

//         return 0;
//     }

//     hwnd = CreateWindowEx(
//         WS_EX_CLIENTEDGE,
//         "win32-game",
//         "Win32 Game",
//         WS_OVERLAPPEDWINDOW,
//         CW_USEDEFAULT,
//         CW_USEDEFAULT,
//         800,
//         600,
//         NULL,
//         NULL,
//         hInst,
//         NULL
//     );

//     if (hwnd == NULL) {
//        MessageBox(NULL, "Win creation  failed!", "Error", MB_ICONEXCLAMATION | MB_OK);

//        return 0; 
//     }

//     ShowWindow(hwnd, nCmdShow);

//     UpdateWindow(hwnd);

//     while (GetMessage(&msg, NULL, 0, 0) > 0) {
//         TranslateMessage(&msg);
//         DispatchMessage(&msg);
//     }

//     return msg.wParam;
// }