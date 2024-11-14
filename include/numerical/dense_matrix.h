#ifndef __JETS_DENSE_MATRIX_H__
#define __JETS_DENSE_MATRIX_H__
#include "base_matrix.h"
#include "jetscomm.h"
#include <vector>

namespace jets
{

// Forward declaration
class DenseVector;
/**
 * @class DenseMatrix
 * @brief A class representing a dense matrix.
 * 
 * This class provides various operations for dense matrices including
 * addition, subtraction, multiplication, and transposition.
 */

/**
 * @brief Constructs a DenseMatrix with given dimensions.
 * 
 * @param m Number of rows.
 * @param n Number of columns.
 */
class DenseMatrix : public BaseMatrix
{
public:

    DenseMatrix(size_type m, size_type n);

    /**
     * @brief Constructs a DenseMatrix with given dimensions and initializes it with a list of values.
     * 
     * @param m Number of rows.
     * @param n Number of columns.
     * @param init_list Initializer list of values.
     */
    DenseMatrix(size_type m, size_type n, std::initializer_list<Real> init_list);

    /**
     * @brief Move constructor.
     * 
     * @param other DenseMatrix to move.
     */
    DenseMatrix (DenseMatrix && other);

    /**
     * @brief Copy constructor.
     * 
     * @param other DenseMatrix to copy.
     */
    DenseMatrix (const DenseMatrix & other);

    /**
     * @brief Copy assignment operator.
     * 
     * @param other DenseMatrix to copy.
     * @return Reference to this DenseMatrix.
     */
    DenseMatrix& operator= (const DenseMatrix & other);

    /**
     * @brief Move assignment operator.
     * 
     * @param other DenseMatrix to move.
     * @return Reference to this DenseMatrix.
     */
    DenseMatrix& operator= (DenseMatrix && other);

    /**
     * @brief Destructor.
     */
    ~DenseMatrix();

    /**
     * @brief Access element at (i, j).
     * 
     * @param i Row index.
     * @param j Column index.
     * @return Reference to the element at (i, j).
     */
    Real& operator() (size_type i, size_type j);

    /**
     * @brief Access element at (i, j) (const version).
     * 
     * @param i Row index.
     * @param j Column index.
     * @return Const reference to the element at (i, j).
     */
    const Real& operator() (size_type i, size_type j) const;

    /**
     * @brief Adds two DenseMatrix objects.
     * 
     * @param other DenseMatrix to add.
     * @return A new DenseMatrix that is the sum of this and other.
     */
    DenseMatrix operator+(const DenseMatrix& other);

    /**
     * @brief Subtracts another DenseMatrix from this one.
     * 
     * @param other DenseMatrix to subtract.
     * @return A new DenseMatrix that is the difference of this and other.
     */
    DenseMatrix operator-(const DenseMatrix& other);

    /**
     * @brief Multiplies two DenseMatrix objects.
     * 
     * @param other DenseMatrix to multiply.
     * @return A new DenseMatrix that is the product of this and other.
     */
    DenseMatrix operator*(const DenseMatrix& other);

    /**
     * @brief Multiplies this DenseMatrix by a scalar.
     * 
     * @param k Scalar value.
     * @return A new DenseMatrix that is the product of this and k.
     */
    DenseMatrix operator*(const Real k);

    /**
     * @brief Adds a scalar to each element of this DenseMatrix.
     * 
     * @param k Scalar value.
     * @param m DenseMatrix to add.
     * @return Reference to this DenseMatrix.
     */
    DenseMatrix& add(const Real k, const DenseMatrix& m);

    /**
     * @brief Multiplies this DenseMatrix by another DenseMatrix.
     * 
     * @param other DenseMatrix to multiply.
     * @return Reference to this DenseMatrix.
     */
    DenseMatrix& mult(const DenseMatrix& other);

    /**
     * @brief Multiplies this DenseMatrix by a scalar.
     * 
     * @param k Scalar value.
     * @return Reference to this DenseMatrix.
     */
    DenseMatrix& mult(const Real k);

    /**
     * @brief Sets all elements of this DenseMatrix to zero.
     */
    void zero();

    /**
     * @brief Creates a DenseMatrix of zeros with given dimensions.
     * @param m Number of rows.
     * @param n Number of columns.
     */
    static DenseMatrix zeros(size_type m, size_type n);

    /**
     * @brief Resizes this DenseMatrix to new dimensions.
     * 
     * @param new_m New number of rows.
     * @param new_n New number of columns.
     */
    void resize(const size_type new_m, const size_type new_n);

    /**
     * @brief Transposes this DenseMatrix.
     * 
     * @return Reference to this DenseMatrix.
     */
    DenseMatrix& T();

    /**
     * @brief Extracts a submatrix from this DenseMatrix.
     * 
     * @param m_start Starting row index.
     * @param m_end Ending row index.
     * @param n_start Starting column index.
     * @param n_end Ending column index.
     * @return A new DenseMatrix that is the submatrix.
     */
    DenseMatrix submatrix(size_type m_start, size_type m_end, size_type n_start, size_type n_end) const;

    /**
     * @brief Prints this DenseMatrix to an output stream.
     * 
     * @param os Output stream.
     */
    void print(std::ostream& os) const;

    /**
     * @brief Prints this DenseMatrix to an output stream in scientific notation.
     * 
     * @param os Output stream.
     * @param precision Number of decimal places.
     */
    void print_scientific(std::ostream & os, unsigned precision=8) const;

    /**
     * @brief Output stream operator for DenseMatrix.
     * 
     * @param os Output stream.
     * @param m DenseMatrix to output.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator << (std::ostream & os, const DenseMatrix& m);
private:
    std::vector<Real> _val;
};
} // namespace jets

#endif // __JETS_DENSE_MATRIX_H__