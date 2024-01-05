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

// Make sure you get the right path

#include "win32_lite.hpp"

using namespace win32_lite;

void buttonFunc() {
    std::cout << "This is a button function\n";
}


window mainWin = window("win32_liteTemplate", "Win32-Lite Template", RGB(255, 255, 255), 800, 600); 
// The parameters go like the following: Internal name (Not shown) | Window Title | Background color | Width | Height

// Main function to draw windows

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    // Make sure to add controls, like buttons, before you generate the window

    mainWin.drawControl("button", "This is a button", 250, 300, 100, 20, 0);
    // The parameters go like:
    // string Control Type (Not shown) | string Control Text | int X Position | int Y Position | int Control Width | int Control Height | int Index
    // Control Type is how you define what type of control you want to use, so Control Type of "button" creates a button
    // i is index of the button. The index must be between 0 and 1000. Indexes must start from 0 and then increase by one. Buttons with a higher Index will be drawn above other buttons


    mainWin.createBtnFunc(buttonFunc, 0);
    // The parameters go like:
    // void (*func)() | int Index
    // The func parameter is just a pointer to a function
    // i is the index of what button you want to create a button function to
    // All buttons must have a button function with the same index, or else it risks a crash

    // Generates the window

    int gen = mainWin.generateWindow(hInstance, hPrevInstance, lpCmdLine);

    // Make sure you add paint items, like text, after you generate the window, but before you show the window

    mainWin.drawText("I love Win32-Lite!", RGB(0, 0, 0), RGB(150, 150, 150), 150, 100, 40, 800, 0);
    // The parameters go like:
    // string Text | COLORREF Text Color | COLORREF Background Color | int X Position | int Y Position | int Font Height | int Text Weight | int Index
    // Text Weight 400 = Normal Weight, Text Weight = 800 = Bold Weight
    // i is index of the text. The index must be between 0 and 1000. Indexes must start from 0 and then increase by one. Text with a higher Index will be drawn above other text

    RECT rect;         // Rectangle Object
    rect.left = 0;     // The Top-Left Corner X Position of Rectangle
    rect.top = 0;      // The Top-Left Corner Y Position of Rectangle
    rect.right = 600;  // The Bottom-Right Corner X Position of Rectangle
    rect.bottom = 600; // The Bottom-Right Corner Y Position of Rectangle

    mainWin.drawRect(rect, RGB(150, 150, 150), RGB(0, 0, 0), 0);
    // The parameters go like:
    // RECT Rectangle | COLORREF Background Color | COLORREF Outline Color | int Index

    int show = mainWin.showWindow(nCmdShow);

    return 0; // Return of 0 means program ran successfully
}