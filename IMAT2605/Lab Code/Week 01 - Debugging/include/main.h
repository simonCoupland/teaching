/*! \file main.h
 * \brief Contains function signatures for the application
 *
 * Contains the signatures for all the functions and a single global variable used to
 * exit the program when required.
 */

/*! \var bool exitProgram;
 * \brief Value true when the program should exit
 *
 * A global boolean, when true the program should exit 
 */
bool exitProgram; 

int main(); //!< Entry point for the application
void menu(); //!< A function which provides a simple text menu system 
void getNumbers(int * aNumber, int *anotherNumber); //!<
void add(int aNumber, int anotherNumber); //!<
void subtract(int aNumber, int anotherNumber); //!<
void multiply(int aNumber, int anotherNumber); //!<
void divide(int aNumber, int anotherNumber); //!<
