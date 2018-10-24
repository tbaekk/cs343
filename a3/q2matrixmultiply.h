#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <uCobegin.h>
#include <uC++.h>
using namespace std;


/*********** sumRow ***********
    Purpose: Sums up the rows of given matrix.


    Returns: None.


    Errors: No error.
************************************/

void sumRow( int *Z[], int *X[], unsigned int row, unsigned int xc, int *Y[], unsigned int yc ) {
    for ( unsigned int col = 0; col < yc; col++ ) {
        int sum = 0;
        for ( unsigned int i = 0; i < xc; i++ ) {
            sum += X[row][i] * Y[i][col];
        }
        Z[row][col] = sum;
    }
}


_Task Calculator {
    // Matrices
    int **X, **Y, **Z;
    // Ranges
    unsigned int row, xr, xc, yc;

    void main() {
        if ( 2 * row + 2 < xr ) {
            Calculator jthRow(Z, X, 2 * row + 2, xc, Y, yc, xr);
            Calculator ithRow(Z, X, 2 * row + 1, xc, Y, yc, xr);
        }
        else if ( 2 * row + 1 < xr ) {
            Calculator ithRow(Z, X, 2 * row + 1, xc, Y, yc, xr);
        }
        sumRow( Z, X, row, xc, Y, yc );
    }

    public:
        Calculator( int *Z[], int *X[], unsigned int row, unsigned int xc_yr, int *Y[], unsigned int yc, unsigned int xr ) :
            Z(Z), X(X), Y(Y), row(row), xc(xc_yr), yc(yc), xr(xr)  {}
};


/*********** matrixmultiply ***********
    Purpose: Uses the task calculator to compute two matrix multiplication by
        using the method sumRow() which calculates summation of each rows.


    Returns: None.


    Errors: Preprocessor variable IMPLICT or EXPLICIT not defined.
************************************/

void matrixmultiply( int *Z[], int *X[], unsigned int xr, unsigned int xc, int *Y[], unsigned int yc ) {
    #if defined( IMPLICIT )
        COFOR( row, 0, xr, // for ( int row = 0; row < rows; row += 1 )
            sumRow( Z, X, row, xc, Y, yc );
        );
    #elif defined( EXPLICIT )
        Calculator r( Z, X, 0, xc, Y, yc, xr );
    #else
        #error Preprocessor variable IMPLICIT or EXPLICIT not defined
    #endif
}


/*********** initMatrix ***********
    Purpose: Returns a new matrix that is allocated.


    Returns: A 2D integer array (matrix)


    Errors: If invalid value is in the given value, throw exception.
************************************/

int **initMatrix( int rows, int cols ) {
    int **matrix = new int*[rows];
    for ( int r = 0; r < rows; r++ ) {
        matrix[r] = new int[cols];
    }
    return matrix;
}


/*********** genMatrix ***********
    Purpose: Returns a new matrix filled with values from the file if given
        else set to 37 by default.


    Returns: A 2D integer array (matrix)


    Errors: If invalid value is in the given value, throw exception.
************************************/

int **genMatrix( int rows, int cols, ifstream &matrixFile ) {
    int **matrix = initMatrix( rows, cols );
    try {
        for ( int r = 0; r < rows; r++ ) {
            for ( int c = 0; c < cols; c++ ) {
                if ( matrixFile ) {
                    matrixFile >> matrix[r][c];
                } else {
                    matrix[r][c] = 37;
                    cout << matrix[r][c] << endl;
                }
            }
        }
        return matrix;
    } catch ( ... ) {
        throw exception();
    }
    
}


/*********** freeMatrix ***********
    Purpose: Frees a matrix.


    Returns: None


    Errors: If matrix is not allocated, it can't be free.
************************************/

void freeMatrix( int **matrix, int rows ) {
    for (int r = 0; r < rows; r++) {
        delete [] matrix[r];
    }
    delete [] matrix;
}


/*********** genSpace ***********
    Purpose: Generate a string filled with the given character in the parameter.


    Returns: A string accumulated with the given character.


    Errors: No error.
************************************/

string genSpace( int num, char fill) {
    string space = "";
    for (int i = 0; i < num; i++) {
        space = space + fill;
    }
    return space;
}


/*********** output ***********
    Purpose: Prints the multiplicaiton of two matricies (Z = X * Y).


    Returns: None.


    Errors: No error.
************************************/

void output( int *Z[], int *X[], int *Y[], int xr, int xc_yr, int yc ) {
    int leftSpacing = -1 + xc_yr * 9 + 4;
    string space = genSpace( leftSpacing, ' ' );

    for ( int i = 0; i < xc_yr; i++ ) {
        cout << space << "|";
        for ( int j = 0; j < yc; j++ ) {
            int numLength = to_string( Y[i][j] ).length();
            string buff = genSpace( 9 - numLength, ' ' );
            cout << buff << Y[i][j];
        }
        cout << " " << endl;
    }

    int rightSpacing = 9 * yc + 1;
    cout << genSpace(leftSpacing, '-') << "*" << genSpace(rightSpacing, '-') << endl;

    for ( int i = 0; i < xr; i++ ) {
        for ( int j = 0; j < xc_yr; j++ ) {
            int numLength = to_string( X[i][j] ).length();
            string buff = genSpace( 9 - (j == 0 ? 1 : 0) - numLength, ' ' );
            cout << buff << X[i][j];
        }
        cout << genSpace( 4, ' ' ) << '|';
        for ( int j = 0; j < yc; j++ ) {
            int numLength = to_string( Z[i][j] ).length();
            string buff = genSpace( 9 - numLength, ' ' );
            cout << buff << Z[i][j];
        }
        cout << " " << endl;
    }
}