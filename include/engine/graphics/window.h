
#define KEY_W 87
#define KEY_A 65
#define KEY_S 83
#define KEY_D 68

/** @file
 */


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

int window_should_close();

void display();

void poll_events();

void draw_triangle_at();

int key_is_pressed();
