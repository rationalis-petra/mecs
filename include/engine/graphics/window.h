
#define KEY_W 87
#define KEY_A 65
#define KEY_S 83
#define KEY_D 68

#define KEY_SPACE 32

#define KEY_ESC 256
#define KEY_ENTER 257
#define KEY_TAB 258

#define KEY_RIGHT 262
#define KEY_LEFT 263
#define KEY_DOWN 264
#define KEY_UP 265


/** @file
 */

typedef struct Cursor {
    double x;
    double y;
} Cursor;

/** @brief Creates a new window and returns an integer handle to it 
 * 
 * @details Requests a new glfw window with OpenGL version 3.3 and returns
 *          a handle which is a clone of the glfw handle
 *
 * @param[in] width: the width of the window, in pixels
 * 
 * @param[in] height: the height of the window, in pixels
 *
 * @return currently: and in handle, in the future - a pointer handle
 */
int new_window(int width, int height);

/** @brief deletes the window given by handle
 * 
 * @details: all windows are automatically deleted when clean() is called
 *           in the engine's core module
 */
void delete_window(int window);

/** @brief returns a boolean value which is true if the user wants the window to close
 *
 * @details acts as a wrapper around the glfwWindowShouldClose() function 
 */
int window_should_close();

/** @brief will swap buffers to display what has been rendered in the new frame
 */
void display();

/** @brief will check for various IO events, such as key-presses, minimisation, etc.
 */
void poll_events();

/** @brief will check if the key with id key is pressed
 */
int key_is_pressed(int key);

/**@brief returns the (x, y) position of the mouse cursor
 */
Cursor get_cursor_pos();

/** @brief returns the aspect ratio of the window
 */
float get_window_aspect();
