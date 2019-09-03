#ifndef SWTI_HEADER
#define SWTI_HEADER

////////////////////////////////////////////////////////////////
//                                                            //
//                SIMPLE WINDOWS TEXT INTERFACE               //
//             better interaction with console window         //
//                                                            //
//         Objects:                                           //
//            Cursor - for writing text                       //
//            Keyboard - for getting key input                //
//            Mouse - for getting mouse position              //
//            Window - for setting console window             //
//                                                            //
//         Basic Info:                                        //
//            Pixel - one point on screen with one color      //
//            Character - one character in console window     //
//            Column - x position of character                //
//            Row - y position of character                   //
//                                                            //
////////////////////////////////////////////////////////////////

#include <iostream> // printing and string
#include <windows.h> // windows console library

// all colors for cursor and window, DEFAULT color is the one currently in use
// change cursor color using Cursor.setColor and window colors Window.setColor
enum Color {BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, LIGHTGRAY,  DARKGRAY,
  LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, LIGHTYELLOW, WHITE, DEFAULT};

////////////////////////////////////////////////////////////////
//                     CURSOR OBJECT                          //
//         Cursor writes in console window all text           //
//            SetPosition, SetColor, clearScreen              //
////////////////////////////////////////////////////////////////

class SWTI_Cursor {
public:
  // get and set position
  int getX(); // x position in columns
  int getY(); // y position in rows
  int getColorForeground(); // get foreground printing color
  int getColorBackground(); // get background printing color
  bool setPosition(int x, int y); // set printing position
  bool setColor(Color foreground, Color background=DEFAULT); // set printing color
  bool printChar(int x, int y, int character, Color color=DEFAULT);
  bool printBlank(int x, int y);  // print blank character on position
  bool clearScreen(); // clears whole console window, slow function

  // font operations
  int getFontWidth();  // font width in pixels
  int getFontHeight(); // font height in pixels
  bool setFontSize(int size); // set font size proportionally to window size
  bool setFontPixels(int width, int height); // set font size, default (13,24)
  bool setFontCR(int columns, int rows); // adjust font size for columns and rows

  //creating and deleting the cursor is automatic
  static SWTI_Cursor& getInstance(); // get the only one intance of cursor
  ~SWTI_Cursor(); // destructor called automatically

private:
  HANDLE hOutput; // getting and setting the position
  Color cForeground; // foreground printing color
  Color cBackground; // background printing color
  SWTI_Cursor(); // private constructor for singleton pattern
};


////////////////////////////////////////////////////////////////
//                     KEYBOARD OBJECT                        //
//              Checks keys of keyboard or mouse              //
//                get, getPressed, getReleased                //
////////////////////////////////////////////////////////////////


class SWTI_Keyboard {
  // Keyboard keys are encoded as characters 'A' or virtual key kodes VK_LEFT
  // Mouse keys are encoded as VK_LBUTTON, VK_RBUTTON, VK_MBUTTON
  // https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
public:
  bool get(int key); // is currently a key pressed
  bool getPressed(int key); // was a key pressed since last call
  bool getReleased(int key); // was a key released since last call
  bool wait(unsigned int ticks); // sleep the program in frames per second
  bool waitUser(); // wait until user presses any key

  // creating and deleting the keyboard is automatic
  static SWTI_Keyboard& getInstance(); // get the only one intance of keyboard
  ~SWTI_Keyboard(); // destructor called automatically

private:
  bool bPressed[256]; // bool array that holds pressed keys
  bool bReleased[256]; // bool array that holds released keys
  SWTI_Keyboard();  // private constructor for singleton pattern
};


////////////////////////////////////////////////////////////////
//                       MOUSE OBJECT                         //
//               Checks position of fyzical mouse             //
//                    getColumns, getRows                     //
////////////////////////////////////////////////////////////////

class SWTI_Mouse {
  // Mouse Position checking
  // Mouse Buttons are checked with the Keyboard
public:
  int getX(); // x position in pixels
  int getY(); // y position in pixels
  int getColumns(); // x position in columns
  int getRows(); // y position in rows

  // creating and deleting the mouse is automatic
  static SWTI_Mouse& getInstance(); // get the only one intance of mouse
  ~SWTI_Mouse(); // destructor called automatically

public:
  int barHeight; // height of topbar in console
  SWTI_Mouse(); // private constructor for singleton pattern
};


////////////////////////////////////////////////////////////////
//                     WINDOW OBJECT                          //
//             Size and position of console window            //
//         setFullscreenBorderless, getColumns, getRows       //
////////////////////////////////////////////////////////////////

class SWTI_Window {
public:
  // get information about the window
  int getX(); // x position of top left corner in pixels
  int getY(); // y position of top left corner in pixels
  int getWidth(); // width in pixels
  int getHeight(); // height in pixels
  int getColumns(); // width in columns
  int getRows();    // height in rows
  int getBorderless(); // is window in borderless mode
  int getScreenWidth(); // screen width in pixels
  int getScreenHeight(); // screen height in pixels

  // set size and position of the window
  bool setSizeCR(int columns, int rows);  // set size in columns and rows
  bool setSizePixels(int width, int height); // set size in pixels, center window
  bool setPositionPixels(int x, int y); // set position in pixels
  bool setFullscreenWindow(); // set window to window fullscreen mode
  bool setFullscreenBorderless(); // set window to fullscreen borderless mode
  bool setColor(Color foreground, Color background);  // set default colors
  bool setTitle(std::string title); // set title of window

  // show and hide elements of the window
  bool showBlinking(); // show blinking cursor
  bool showSelection(); // show cursor selection
  bool showScrollbars(int columns, int rows); // show scrollbars
  bool hideBlinking(); // hide blinking cursor
  bool hideSelection(); // hide cursor selection
  bool hideScrollbars(); // hide right and bottom scrollbar

  // creating and deleting the window is automatic
  static SWTI_Window& getInstance(); // get the only one intance of window
  ~SWTI_Window(); // destructor called automatically

private:
  bool isBorderless; // is window in borderless mode, used in mouse checks
  HANDLE hOutput; // used when getting size in columns
  HANDLE hInput; // used when setting visibility
  HWND hWindow; // used when resizing
  SWTI_Window(); // private constructor for singleton pattern
};

////////////////////////////////////////////////////////////////
//                      CREATE ALL OBJECTS                    //
//                Cursor, Keyboard, Window, Mouse             //
////////////////////////////////////////////////////////////////

SWTI_Window Window = SWTI_Window::getInstance();
SWTI_Cursor Cursor = SWTI_Cursor::getInstance();
SWTI_Keyboard Keyboard = SWTI_Keyboard::getInstance();
SWTI_Mouse Mouse = SWTI_Mouse::getInstance();

#endif // end of include guard: SWTI_HEADER
