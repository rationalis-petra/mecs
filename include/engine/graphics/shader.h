
/**@file
 */

/**@brief Creates a new shader program based on porgram_name
 * 
 * @details Looks in the folder resources/shaders and attempts to
 *          find two files program_name.vs and program_name.fs, 
 *          which correspond to the vertex and fragment shader 
 *          respectively. These are combined and a handle to the
 *          shader is returned.
 *
 * @param[in] program_name: The name of the shader program to be create
 *            must also correspond to the filename of the shaders
 *
 * @return A handle to the shader program
 */
unsigned int new_shader_program(char* program_name); 
