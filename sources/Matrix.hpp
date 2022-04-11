#include <algorithm>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <numeric>
using namespace std;

namespace zich
{

    class Matrix
    {
    private:
        vector<vector<double>> matrix;
        int cols;
        int rows;

    public:

        Matrix(vector<double> identity, int row, int col)
        {
            if (identity.size() != (row * col))
            {
                throw std::invalid_argument{"Vector size doesnt fit the matrix size.\n"};
            }
            rows = row;
            cols = col;
            for (size_t i = 0; i < row; i++)
            {
                vector<double> vec;

                for (size_t j = i * (size_t)col; j < (i + 1) * (size_t)col; j++)
                {
                    vec.push_back(identity.at(j));
                }
                matrix.push_back(vec);
            }
        };

        // Copy Constructor
        Matrix(const Matrix &mat)
        {
            matrix.resize((size_t)mat.rows);
            for (size_t i = 0; i < mat.rows; i++)
            {
                matrix[i].resize((size_t)mat.cols);
                for (size_t j = 0; j < mat.cols; j++)
                {
                    matrix[i][j] = mat.matrix[i][j];
                }
            }

            rows = mat.rows;
            cols = mat.cols;
        }

        // Rows Cols constructor
        Matrix(int row, int col)
        {
            matrix.resize((size_t)row);
            for (size_t i = 0; i < row; i++)
            {
                matrix[i].resize((size_t)col);
            }
            rows = row;
            cols = col;
        }

        // Input Output Stream operators
        friend ostream &operator<<(ostream &os, const Matrix &mat);
        friend istream &operator>>(istream &os, Matrix &mat);
        // Binary operators
        Matrix operator+(const Matrix &mat);
        Matrix operator-(const Matrix &mat);
        Matrix operator*(const Matrix &mat);
        Matrix operator*(const double x);
        friend Matrix operator*(double x, Matrix const &mat);
        Matrix &operator*=(const double x);
        Matrix &operator*=(Matrix const &mat);
        Matrix &operator+=(const Matrix &mat_b);
        Matrix &operator+=(double x);
        Matrix &operator-=(Matrix const &mat);
        Matrix &operator-=(double x);


        friend Matrix operator-(Matrix &mat);
        friend Matrix operator+(Matrix &mat);

        // Comparsion operators
        friend bool operator>(const Matrix &mat, const Matrix &mat_b);
        friend bool operator==(const Matrix &mat, const Matrix &mat_b);
        friend bool operator!=(const Matrix &mat, const Matrix &mat_b);
        friend bool operator<=(const Matrix &mat, const Matrix &mat_b);
        friend bool operator>=(const Matrix &mat, const Matrix &mat_b);
        friend bool operator<(const Matrix &mat, const Matrix &mat_b);

                // Increment operators
        Matrix &operator++();
        Matrix &operator--();
        Matrix operator++(int);
        Matrix operator--(int);
        double sum() const;

    
    };

    

};
