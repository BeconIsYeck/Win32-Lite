/* win32_lite.hpp written By Babybunnyiscute19 / BeconIsYeck, Template written by theForger http://www.winprog.org/tutorial/simple_window.html
// Github Repo: N/A
// Build Ver: 0071
// Last Mod: 11-6-2023 / 12:26 PM | MM/DD/YYYY:
/// > Added bitmap image support with window.drawImage()
/// > Changed showStack from 100 => 1000
/// > Added drawLineW32L & window.drawLine() methods 
/// > Added int textAmount, int rectAmount, and int lineAmount variables to limit the amount of unnecessary objects being computed
/// > Added window.refreshWindow() method for faster way to InvalidateRect()
//
// TODO (Most -> Least Important): 
/// Add button customization
/// Basic template / documentation
/// Keyboard / Mouse input
/// Method to open close current window and open new window
*/


#include <iostream>
#include <string>

#include <windows.h>

using namespace std;


static HWND windowHandle;
static WNDCLASSEX windowsClass;

static COLORREF GlobalBackgroundColor = RGB(255, 255, 255);

// Stacks used to render text, rect, button, etc in WM_PAINT for continual display

const int showStack = 1000;

// Text stacks

string   textDrawStack[showStack];
COLORREF textForColorStack[showStack];
COLORREF textBckColorStack[showStack];
int      textWeightStack[showStack];
int      textPosXStack[showStack];
int      textPosYStack[showStack];
int      textSizeStack[showStack];

int textAmount = 0;

// Rect stacks

RECT rectDrawStack[showStack];
COLORREF rectBckColorStack[showStack];
COLORREF rectOlnColorStack[showStack];

int rectAmount = 0;

// Button stacks

string buttonTypeStack[showStack];
string buttonTextStack[showStack];
int buttonPosXStack[showStack];
int buttonPosYStack[showStack];
int buttonWidthStack[showStack];
int buttonHeightStack[showStack];

void (*buttonFuncStack[showStack])();

int buttonAmount = 0;

// W.I.P.

// Line Stacks

int lineStartXStack[showStack];
int lineStartYStack[showStack];
int lineEndXStack[showStack];
int lineEndYStack[showStack];
COLORREF lineColorStack[showStack];
int lineThicknessStack[showStack];

int lineAmount = 0;

// BMP Stacks

string bmpPathStack[showStack];
int bmpXStack[showStack];
int bmpYStack[showStack];

int bmpAmount = 0;

namespace win32_lite {
    void drawTextW32L(HDC hdc, string text, COLORREF forColor, COLORREF bckColor, int x, int y, int fontSize, int textWeight) {
        if (hdc == NULL) {
            cout << "null\n";
        }

        // Get / Set font

        HFONT hFont = static_cast<HFONT>(GetStockObject(DEFAULT_GUI_FONT));
        LOGFONT logfont;

        GetObject(hFont, sizeof(LOGFONT), &logfont);

        logfont.lfHeight = (long)fontSize;
        logfont.lfWeight = (long)textWeight;

        HFONT hNewFont = CreateFontIndirect(&logfont);
        HFONT hOldFont = (HFONT)SelectObject(hdc, hNewFont);

        // Display Text

        SetTextColor(hdc, forColor);
        SetBkColor(hdc, bckColor);

        TextOutA(hdc, x, y, text.c_str(), strlen(text.c_str()));

        // Cleanup

        SelectObject(hdc, hOldFont);
        DeleteObject(hNewFont);
    }

    void drawRectW32L(HDC hdc, RECT rect, COLORREF bckColor, COLORREF olnColor) {
        HBRUSH bckBrush = CreateSolidBrush(bckColor);
        HBRUSH olnBrush = CreateSolidBrush(olnColor);

        FillRect(hdc, &rect, bckBrush);
        FrameRect(hdc, &rect, olnBrush);

        DeleteObject(bckBrush);
        DeleteObject(olnBrush);
    }

    void drawLineW32L(HDC hdc, int startX, int startY, int endX, int endY, COLORREF color, int thickness) {
        RECT rc;

        GetClientRect(windowHandle, &rc);

        HPEN linePen = CreatePen(PS_SOLID, thickness, color);
        HPEN oldPen = (HPEN)SelectObject(hdc, linePen);

        MoveToEx(hdc, startX, startY, NULL);
        LineTo(hdc, endX, endY);

        BitBlt(hdc, 0, 0, rc.right - rc.left,
        rc.bottom - rc.top, hdc, 0, 00,
        SRCCOPY);

        SelectObject(hdc, oldPen);
        DeleteObject(linePen);
    }

    void drawEllipse(HDC hdc, int left, int top, int right, int bottom, COLORREF bckColor) {
        
    }

    LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        // HBRUSH btnBrush;
        // static HBRUSH hBrush = NULL;

        // const char* fileName = "D:\\Dev\\bmp_24.bmp";
        // HBITMAP bmp = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);

        switch(msg) {
            case WM_PAINT: {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);

                // Create an off-screen DC and an off-screen bitmap
                HDC hdcBuffer = CreateCompatibleDC(hdc);
                RECT rc;
                GetClientRect(hwnd, &rc);

                HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
                HBITMAP hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);

                // Fill the DC with a background color
                HBRUSH hbrBkGnd = CreateSolidBrush(GlobalBackgroundColor);
                FillRect(hdcBuffer, &rc, hbrBkGnd);
                DeleteObject(hbrBkGnd);


                // Actual drawing

                for (int i = 0; i < showStack; i++) {
                    // Meedlessly hacky solution for a minor problem, worsens performance for a little bit of UX
                    // Looks through stacks and draws objects in real time 

                    string tD = textDrawStack[i];

                    COLORREF tFC = textForColorStack[i];
                    COLORREF tBC = textBckColorStack[i];

                    int x = textPosXStack[i]; // Good luck decyphering what this means!
                    int y = textPosYStack[i];
                    int fS = textSizeStack[i];

                    long tW = textWeightStack[i];

                    RECT rD = rectDrawStack[i];
                    COLORREF rBC = rectBckColorStack[i];
                    COLORREF rOC = rectOlnColorStack[i];

                    int lineStartX = lineStartXStack[i];
                    int lineStartY = lineStartYStack[i];
                    int lineEndX = lineEndXStack[i];
                    int lineEndY = lineEndYStack[i];
                    COLORREF lineColor = lineColorStack[i];
                    int lineThickness = lineThicknessStack[i];

                    string bmpPath = bmpPathStack[i];
                    int bmpX = bmpXStack[i];
                    int bmpY = bmpYStack[i];

                    if (i <= rectAmount) {
                        drawRectW32L(hdcBuffer, rD, rBC, rOC); // Draw to hdcBuffer instead of hdc
                    }

                    if (i <= lineAmount) {
                        drawLineW32L(hdcBuffer, lineStartX, lineStartY, lineEndX, lineEndY, lineColor, lineThickness);
                    }

                    if (i <= bmpAmount) {
                        // Load the bmp into memory

                        HBITMAP bmpImg = (HBITMAP)LoadImage(NULL, bmpPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
                        
                        // Select the bitmap into the off-screen DC and draw it

                        HDC hdcMem = CreateCompatibleDC(hdcBuffer);
                        HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, bmpImg);

                        BitBlt(hdcBuffer, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hdcMem, -bmpX, -bmpY, SRCCOPY);
                        SelectObject(hdcMem, hbmOld);
                        
                        // Clean up

                        DeleteDC(hdcMem);
                        DeleteObject(bmpImg);
                    }

                    if (i <= textAmount) { 
                        drawTextW32L(hdcBuffer, tD, tFC, tBC, x, y, fS, tW); // Draw to hdcBuffer instead of hdc
                    }
                }

                // Copy from off-screen DC to on-screen DC

                BitBlt(hdc, 0, 0, rc.right, rc.bottom, hdcBuffer, 0, 0, SRCCOPY);

                // Clean up

                SelectObject(hdcBuffer, hbmOldBuffer);
                DeleteObject(hbmBuffer);
                DeleteDC(hdcBuffer);

                EndPaint(hwnd, &ps);
                break;
            }

            case WM_CREATE: {
                if (buttonAmount > 0) {
                    for (int i = 0; i < showStack; i++) {
                        CreateWindow(
                            buttonTypeStack[i].c_str(), // This exact line burned 40 minutes of my life
                            buttonTextStack[i].c_str(),    
                            WS_VISIBLE | WS_CHILD,
                            buttonPosXStack[i],
                            buttonPosYStack[i],
                            buttonWidthStack[i],
                            buttonHeightStack[i],        
                            hwnd, 
                            (HMENU) i, 
                            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                            NULL);
                    }
                }
            }
            break;

            case WM_COMMAND: {
                if (buttonAmount > 0) {
                    for (int i = 0; i < showStack; i++) {
                        if (LOWORD(wParam) == i) {
                            buttonFuncStack[i]();
                        }
                    }
                }
            }

            case WM_SIZE: {

            }
            break;

            case WM_CLOSE: {
                DestroyWindow(hwnd);
            }
            break;

            case WM_DESTROY: {
                PostQuitMessage(0);
            }
            break;

            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
        }

        return 0;
    }

    class window { // I wish I was using C#
        public:
            string ClassName;
            string Title;
            COLORREF BackgroundColor;

            int WidthX;
            int HeightY;
        
            window(string className, string title, COLORREF backColor, int widthX, int HeightY) {
                this->ClassName = className;
                this->Title = title;
                this->BackgroundColor = backColor;
                this->WidthX = widthX;
                this->HeightY = HeightY;

                GlobalBackgroundColor = this->BackgroundColor;
            }

            int generateWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine) {
                WNDCLASSEX wc;

                // Registering the Window Class

                wc.cbSize        = sizeof(WNDCLASSEX);
                wc.style         = 0;
                wc.lpfnWndProc   = WndProc;
                wc.cbClsExtra    = 0;
                wc.cbWndExtra    = 0;
                wc.hInstance     = hInstance;
                wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
                wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
                wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
                wc.lpszMenuName  = NULL;
                wc.lpszClassName = this->ClassName.c_str();
                wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

                if (!RegisterClassEx(&wc)) {
                    MessageBox(NULL, "Window Registration Failed!", "Error!",
                        MB_ICONEXCLAMATION | MB_OK);
                    return 0;
                }

                // Creating the Window

                windowHandle = CreateWindowEx(
                    WS_EX_CLIENTEDGE,
                    this->ClassName.c_str(),
                    this->Title.c_str(),
                    WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
                    CW_USEDEFAULT, CW_USEDEFAULT, this->WidthX, this->HeightY,
                    NULL, NULL, hInstance, NULL);

                if (windowHandle == NULL) {
                    MessageBox(NULL, "Window Creation Failed!", "Error!",
                        MB_ICONEXCLAMATION | MB_OK);
                    return 0;
                }

                // Setting global variable
                
                windowsClass = wc;
            }

            int showWindow(int nCmdShow) {
                MSG Msg;

                ShowWindow(windowHandle, nCmdShow);
                UpdateWindow(windowHandle);

                // The Message Loop

                while (GetMessage(&Msg, NULL, 0, 0)) {
                    TranslateMessage(&Msg);
                    DispatchMessage(&Msg);
                }
                
                return Msg.wParam; 
            }

            void drawText(string text, COLORREF forColor, COLORREF bckColor, int x, int y, int fontSize, int textWeight, int i) {
                // Adds text & text properies to the stack

                textDrawStack[i] = text;
                textForColorStack[i] = forColor;
                textBckColorStack[i] = bckColor;
                textPosXStack[i] = x;
                textPosYStack[i] = y;
                textSizeStack[i] = fontSize;
                textWeightStack[i] = textWeight;

                textAmount++;
            }

            void drawRect(RECT rect, COLORREF bckColor, COLORREF olnColor, int i) {
                // Adds rect & rect properties to the stack

                rectDrawStack[i] = rect;
                rectBckColorStack[i] = bckColor;
                rectOlnColorStack[i] = olnColor;

                rectAmount++;
            }

            void drawControl(string btnType, string btnText, int btnX, int btnY, int btnWidth, int btnHeight, int i) {
                // Adds button properties to the stack   
            
                buttonTypeStack[i] = btnType;
                buttonTextStack[i] = btnText;
                buttonPosXStack[i] = btnX;
                buttonPosYStack[i] = btnY;
                buttonWidthStack[i] = btnWidth;
                buttonHeightStack[i] = btnHeight;

                buttonAmount++;
            }

            void createBtnFunc(void (*func)(), int i) {
                // Adds function pointer to stack to be called later

                buttonFuncStack[i] = func;
            } 

            void drawLine(int startX, int startY, int endX, int endY, COLORREF color, int thickness, int i) {
                // Adds line properties to the stacks

                lineStartXStack[i] = startX;
                lineStartYStack[i] = startY;
                lineEndXStack[i] = endX;
                lineEndYStack[i] = endY;
                lineColorStack[i] = color;
                lineThicknessStack[i] = thickness;

                lineAmount++;
            }

            void drawImage(string imgPath, int x, int y, int i) {
                // Adds bmp properties to the stacks

                bmpPathStack[i] = imgPath;
                bmpXStack[i] = x;
                bmpYStack[i] = y;

                bmpAmount++;
            }

            void redrawWindow() {
                InvalidateRect(windowHandle, NULL, true);
            }
    };  
}
