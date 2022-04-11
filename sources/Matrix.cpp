#include "Matrix.hpp"
using namespace zich;

const int DIGIT_MIN = 48;
const int DIGIT_MAX = 57;

vector<double> create_vec_from_str(const string &data)
{
    vector<double> vec;
    string str;
    char ch = 0;
    double flag = 0;
    double x = 0;
    double col = 0;
    double row = 0;
    stringstream os = stringstream(data);

    while (!os.eof())
    {
        col = 0;
        os >> ch;

        // printf("Current string entered from os : %c\n", ch);
        if (ch != '[' || os.peek() < DIGIT_MIN || os.peek() > DIGIT_MAX)
        {
            throw invalid_argument("String is not in the right format: '[' \n");
        }

        while (os.peek() != ']' && !os.eof())
        {
            os >> x;
            // printf("Current double entered from os : %f\n", x);
            col++;
            if (col > flag && flag > 0)
            {
                throw invalid_argument("cols in every row must be even\n");
            }
            vec.push_back(x);
        }

        if (col == 0)
        {
            throw invalid_argument("String is not in the right format col = 0\n");
        }

        os >> str;

        if (str != "],")
        {
            cout << "Caught exception in sup last Error : " << str << endl;
            cout << "Next char is :" << os.peek() << endl;
            if (str == "]" && os.eof())
            {
                row++;

                break;
            }
            throw invalid_argument("String is not in the right format 3333\n");
        }

        row++;

        if (flag==0)
        {
            flag = col;
        }

        if (col != flag)
        {
            throw;
        }
    }
    vec.push_back(row);
    vec.push_back(col);

    return vec;
};

// Matrix sum function.
double Matrix::sum() const
{
    double sum = 0;

    for (auto x : this->matrix)
    {
        sum += accumulate(x.begin(), x.end(), 0.0);
    }
    return sum;
};

// Output Stream
std::ostream &zich::operator<<(ostream &os, const Matrix &mat)
{
    for (size_t i = 0; i < mat.rows; i++)
    {
        os << "[";
        for (size_t j = 0; j < mat.cols; j++)
        {
            os << mat.matrix[i][j];
            if (!(j == mat.cols - 1))
            {
                os << " ";
            }
        }

        os << ']';
        if (!(i == mat.rows - 1))
        {
            os << endl;
        }
    }

    return os;
};
istream &zich::operator>>(istream &os, Matrix &mat)
{
    string data;
    getline(os, data);
    vector<double> vec = create_vec_from_str(data);
    int col = vec[vec.size() - 1];
    vec.pop_back();
    int row = vec[vec.size() - 1];
    vec.pop_back();

    mat = Matrix(vec, row, col);
    // getline(os,data);
    // mat = data;
    return os;
};

// Binary operators

Matrix Matrix::operator+(const Matrix &mat)
{
    if (mat.cols != this->cols || mat.rows != this->rows)
    {
        throw invalid_argument{"Cannot sum matrix from diffrenet sizes.\n"};
    }

    Matrix ans(mat.rows, mat.cols);

    for (size_t i = 0; i < mat.rows; i++)
    {
        for (size_t j = 0; j < mat.cols; j++)
        {
            ans.matrix[i][j] = mat.matrix[i][j] + this->matrix[i][j];
        }
    }

    return ans;
};

Matrix Matrix::operator-(const Matrix &mat)
{
    if (mat.cols != this->cols || mat.rows != this->rows)
    {
        throw invalid_argument{"Cannot sum matrix from diffrenet sizes.\n"};
    }

    Matrix ans(mat.rows, mat.cols);

    for (size_t i = 0; i < mat.rows; i++)
    {
        for (size_t j = 0; j < mat.cols; j++)
        {
            ans.matrix[i][j] = this->matrix[i][j] - mat.matrix[i][j];
        }
    }

    return ans;
};

Matrix zich::operator-(Matrix &mat)
{
    return mat * -1;
};

Matrix zich::operator+(Matrix &mat)
{
    return mat * 1;
};

Matrix Matrix::operator*(const Matrix &mat)
{

    if (mat.rows != this->cols)
    {
        throw invalid_argument{"Cannot Multiply matrix from diffrenet sizes.\n"};
    }

    Matrix ans = Matrix(this->rows, mat.cols);

    for (size_t i = 0; i < ans.rows; i++)
    {
        for (size_t j = 0; j < ans.cols; j++)
        {
            ans.matrix[i][j] = 0;
            for (size_t k = 0; k < mat.rows; k++)
            {
                ans.matrix[i][j] += (this->matrix[i][k] * mat.matrix[k][j]);
            }
        }
    }

    return ans;
};

Matrix Matrix::operator*(const double x)
{
    Matrix ans = Matrix(*this);

    for (size_t i = 0; i < ans.rows; i++)
    {
        for (size_t j = 0; j < ans.cols; j++)
        {
            ans.matrix[i][j] *= x;
        }
    }

    return ans;
};

Matrix zich::operator*(double x, Matrix const &mat)
{
    Matrix ans = Matrix(mat);

    for (size_t i = 0; i < ans.rows; i++)
    {
        for (size_t j = 0; j < ans.cols; j++)
        {
            ans.matrix[i][j] *= x;
        }
    }

    return ans;
};

Matrix &Matrix::operator*=(Matrix const &mat)
{
    if (mat.rows != this->cols)
    {
        throw invalid_argument{"Cannot sum matrix from diffrenet sizes.\n"};
    }

   for (size_t i = 0; i < this->rows; i++)
    {
        for (size_t j = 0; j < this->cols; j++)
        {
            double x = 0;
            for (size_t k = 0; k < mat.rows; k++)
            {
                x += (this->matrix[i][k] * mat.matrix[k][j]);
            }

            this->matrix[i][j]= x;
        }
    }

    return *this;
};

Matrix &Matrix::operator*=(const double x)
{
    for (size_t i = 0; i < this->rows; i++)
    {
        for (size_t j = 0; j < this->cols; j++)
        {
            this->matrix[i][j] *= x;
        }
    }
    return *this;
};

Matrix &Matrix::operator+=(Matrix const &mat)
{
    if (this->cols != mat.cols || mat.rows != this->rows)
    {
        throw invalid_argument{"Cannot sum matrix from diffrenet sizes.\n"};
    }

    for (size_t i = 0; i < mat.rows; i++)
    {
        for (size_t j = 0; j < mat.cols; j++)
        {
            this->matrix[i][j] += mat.matrix[i][j];
        }
    }
    return *this;
};

Matrix &Matrix::operator+=(double x)
{

    for (size_t i = 0; i < this->rows; i++)
    {
        for (size_t j = 0; j < this->cols; j++)
        {
            this->matrix[i][j] += x;
        }
    }
    return *this;
};

Matrix &Matrix::operator-=(Matrix const &mat)
{
    if (this->cols != mat.cols || mat.rows != this->rows)
    {
        throw invalid_argument{"Cannot sum matrix from diffrenet sizes.\n"};
    }

    for (size_t i = 0; i < this->rows; i++)
    {
        for (size_t j = 0; j < this->cols; j++)
        {
            this->matrix[i][j] -= mat.matrix[i][j];
        }
    }
    return *this;
};

Matrix &Matrix::operator-=(double x)
{
    for (size_t i = 0; i < this->rows; i++)
    {
        for (size_t j = 0; j < this->cols; j++)
        {
            this->matrix[i][j] -= x;
        }
    }
    return *this;
};

// Comparison operators
bool zich::operator==(const Matrix &mat, const Matrix &mat_b)
{
    if (mat.cols != mat_b.cols || mat.rows != mat_b.rows)
    {
        throw invalid_argument{"Cannot compare matrix from diffrenet sizes.\n"};
    }

    for (size_t i = 0; i < mat.rows; i++)
    {
        for (size_t j = 0; j < mat.cols; j++)
        {
            if (mat.matrix[i][j] != mat_b.matrix[i][j])
            {
                return false;
            }
        }
    }
    return true;
};
bool zich::operator!=(const Matrix &mat, const Matrix &mat_b)
{
    if (mat.cols != mat_b.cols || mat.rows != mat_b.rows)
    {
        throw invalid_argument{"Cannot compare matrix from diffrenet sizes.\n"};
    }
    return !(mat == mat_b);
};
bool zich::operator<=(const Matrix &mat, const Matrix &mat_b)
{
    if (mat.cols != mat_b.cols || mat.rows != mat_b.rows)
    {
        throw invalid_argument{"Cannot compare matrix from diffrenet sizes.\n"};
    }
    return !(mat > mat_b);
};
bool zich::operator>=(const Matrix &mat, const Matrix &mat_b)
{
    if (mat.cols != mat_b.cols || mat.rows != mat_b.rows)
    {
        throw invalid_argument{"Cannot compare matrix from diffrenet sizes.\n"};
    }
    return !(mat < mat_b);
};
bool zich::operator>(const Matrix &mat, const Matrix &mat_b)
{
    if (mat.cols != mat_b.cols || mat.rows != mat_b.rows)
    {
        throw invalid_argument{"Cannot compare matrix from diffrenet sizes.\n"};
    }
    return (mat.sum() > mat_b.sum());
};
bool zich::operator<(const Matrix &mat, const Matrix &mat_b)
{
    if (mat.cols != mat_b.cols || mat.rows != mat_b.rows)
    {
        throw invalid_argument{"Cannot compare matrix from diffrenet sizes.\n"};
    }
    return (mat.sum() < mat_b.sum());
};

// Increment operators
Matrix &Matrix::operator++()
{
    *this += 1;
    return *this;
};
Matrix Matrix::operator++(int)
{
    Matrix temp = *this;
    ++*this;
    return temp;
}
Matrix &Matrix::operator--()
{
    *this -= 1;
    return *this;
};
Matrix Matrix::operator--(int)
{
    Matrix temp = *this;
    --*this;
    return temp;
};
