#ifndef __Q2MATRIXMULTIPLY_H__
#define __Q2MATRIXMULTIPLY_H__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <uCobegin.h>
#include <uC++.h>
using namespace std;


/*********** rowSummation ***********
    Purpose: Sums up the rows of given matrix.


    Returns: None.


    Errors: No error.
************************************/

void rowSummation( int *Z[], int *X[], unsigned int row, unsigned int xc, int *Y[], unsigned int yc ) {
    for ( unsigned int col = 0; col < yc; col++ ) {
        int sum = 0;
        for ( unsigned int i = 0; i < xc; i++ ) {
            sum += X[row][i] * Y[i][col];
        } // for
        Z[row][col] = sum;
    } // for
}


_Task MatrixCalculator {
    // Matrices
    int **X, **Y, **Z;
    // Ranges
    unsigned int row, xr, xc, yc;

    void main() {
        if ( 2 * row + 2 < xr ) {
            MatrixCalculator jthRow(Z, X, 2 * row + 2, xc, Y, yc, xr);
            MatrixCalculator ithRow(Z, X, 2 * row + 1, xc, Y, yc, xr);
        } else if ( 2 * row + 1 < xr ) {
            MatrixCalculator ithRow(Z, X, 2 * row + 1, xc, Y, yc, xr);
        } // if
        rowSummation( Z, X, row, xc, Y, yc );
    }

    public:
        MatrixCalculator( int *Z[], int *X[], unsigned int row, unsigned int xc_yr, int *Y[], unsigned int yc, unsigned int xr ) :
            Z(Z), X(X), Y(Y), row(row), xc(xc_yr), yc(yc), xr(xr)  {}
};


/*********** matrixmultiply ***********
    Purpose: Uses the task MatrixCalculator to compute two matrix multiplication by
        using the method rowSummation() which calculates summation of each rows.


    Returns: None.


    Errors: Preprocessor variable IMPLICT or EXPLICIT not defined.
************************************/

void matrixmultiply( int *Z[], int *X[], unsigned int xr, unsigned int xc, int *Y[], unsigned int yc ) {
    #if defined( IMPLICIT )
        COFOR( row, 0, xr,
            rowSummation( Z, X, row, xc, Y, yc );
        );
    #elif defined( EXPLICIT )
        MatrixCalculator rows( Z, X, 0, xc, Y, yc, xr );
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
    } // for
    return matrix;
}


/*********** genMatrix ***********
    Purpose: Returns a new matrix filled with values from the file if given
        else set to 37 by default.


    Returns: A 2D integer array (matrix)


    Errors: If invalid value is in the given value, throw exception.
************************************/

int **genMatrix( int rows, int cols, ifstream &matrixFile, bool isFileExist ) {
    int **matrix = initMatrix( rows, cols );
    try {
        for ( int r = 0; r < rows; r++ ) {
            for ( int c = 0; c < cols; c++ ) {
                if ( isFileExist ) {
                    matrixFile >> matrix[r][c];
                } else {
                    matrix[r][c] = 37;
                } // if
            } // for
        } // for
        return matrix;
    } catch ( ... ) {
        throw exception();
    } // try
    
}

/*********** genWhiteSpace ***********
    Purpose: Generate a string filled with the given character in the parameter.


    Returns: A string accumulated with the given character.


    Errors: No error.
************************************/

string genWhiteSpace( int num, char fill) {
    string space = "";
    for ( int i = 0; i < num; i++ ) {
        space = space + fill;
    } // for
    return space;
}

void prettyPrint( int *matrix[], int row, int cols, bool isBottomLeft = false ) {
    for ( int j = 0; j < cols; j++ ) { 
        int len = isBottomLeft ?  9 - (j == 0 ? 1 : 0) : 9;
        int numLength = to_string( matrix[row][j] ).length();
        string whiespace = genWhiteSpace( len - numLength, ' ' );
        cout << whiespace << matrix[row][j];
    } // for
}


/*********** printMatrix ***********
    Purpose: Prints the multiplicaiton of two matricies (Z = X * Y).


    Returns: None.


    Errors: No error.
************************************/

void printMatrix( int *Z[], int *X[], int xr, int xc_yr, int *Y[], int yc ) {
    int leftSpacing = -1 + xc_yr * 9 + 4;
    string leftSpace = genWhiteSpace( leftSpacing, ' ' );

    for ( int i = 0; i < xc_yr; i++ ) {                             // Print top half
        cout << leftSpace << "|";                                   // Print top left
        prettyPrint( Y, i, yc );                                    // Print top right
        cout << " " << endl;
    } // for

    int rightSpacing = 9 * yc + 1;
    
    cout << genWhiteSpace( leftSpacing, '-' ) 
     << "*" << genWhiteSpace( rightSpacing, '-' ) << endl;               // Print center horizontal

    for ( int i = 0; i < xr; i++ ) {                                // Print bottom half
        prettyPrint( X, i, xc_yr, true );                           // Print bottom left
        cout << genWhiteSpace( 4, ' ' ) << '|';
        prettyPrint( Z, i, yc );                                    // Print bottom right
        cout << " " << endl;
    } // for
}


#endif