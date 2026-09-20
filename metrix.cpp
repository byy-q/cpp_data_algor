#include <algorithm>
#include <cstdint>
#include <stdexcept>


template<class T>
class metrix
{
public:
    metrix();
    metrix(uint32_t row_count, uint32_t column_count, const T& initial_value);
    metrix(const metrix<T>& other);
    metrix(metrix<T>&& other) noexcept;
    ~metrix();

    metrix<T>& operator=(const metrix<T>& other);
    metrix<T>& operator=(metrix<T>&& other) noexcept;
    bool operator==(const metrix<T>& other) const;
    bool operator!=(const metrix<T>& other) const;
    metrix<T>& operator*=(const metrix<T>& rhs);
    friend metrix<T> operator*(const metrix<T>& lhs, const metrix<T>& rhs);

private:
    T** data = nullptr;
    uint32_t rows = 0;
    uint32_t columns = 0;
};

template<class T>
metrix<T>::metrix() : rows(0), columns(0), data(nullptr)
{
}

template<class T>
metrix<T>::metrix(uint32_t row_count, uint32_t column_count, const T& initial_value)
    : rows(row_count), columns(column_count), data(nullptr)
{
    data = new T*[rows];
    for (uint32_t row = 0; row < rows; ++row)
    {
        data[row] = new T[columns];
        for (uint32_t col = 0; col < columns; ++col)
        {
            data[row][col] = initial_value;
        }
    }
}

template<class T>
metrix<T>::metrix(const metrix<T>& other)
    : rows(other.rows), columns(other.columns), data(nullptr)
{
    data = new T*[rows];
    for (uint32_t row = 0; row < rows; ++row)
    {
        data[row] = new T[columns];
        for (uint32_t col = 0; col < columns; ++col)
        {
            data[row][col] = other.data[row][col];
        }
    }
}

template<class T>
metrix<T>::metrix(metrix<T>&& other) noexcept
    : rows(other.rows), columns(other.columns), data(other.data)
{
    other.rows = 0;
    other.columns = 0;
    other.data = nullptr;
}

template<class T>
metrix<T>::~metrix()
{
    if (data == nullptr)
    {
        return;
    }

    for (uint32_t row = 0; row < rows; ++row)
    {
        delete[] data[row];
    }
    delete[] data;
    data = nullptr;
    rows = 0;
    columns = 0;
}

template<class T>
metrix<T>& metrix<T>::operator=(const metrix<T>& other)
{
    if (this == &other)
    {
        return *this;
    }

    if (data != nullptr)
    {
        for (uint32_t row = 0; row < rows; ++row)
        {
            delete[] data[row];
        }
        delete[] data;
        data = nullptr;
    }

    rows = other.rows;
    columns = other.columns;
    data = new T*[rows];
    for (uint32_t row = 0; row < rows; ++row)
    {
        data[row] = new T[columns];
        for (uint32_t col = 0; col < columns; ++col)
        {
            data[row][col] = other.data[row][col];
        }
    }

    return *this;
}

template<class T>
metrix<T>& metrix<T>::operator=(metrix<T>&& other) noexcept
{
    if (this != &other)
    {
        if (data != nullptr)
        {
            for (uint32_t row = 0; row < rows; ++row)
            {
                delete[] data[row];
            }
            delete[] data;
        }

        rows = other.rows;
        columns = other.columns;
        data = other.data;
        other.rows = 0;
        other.columns = 0;
        other.data = nullptr;
    }

    return *this;
}

template<class T>
bool metrix<T>::operator==(const metrix<T>& other) const
{
    if (rows != other.rows || columns != other.columns)
    {
        return false;
    }

    for (uint32_t row = 0; row < rows; ++row)
    {
        for (uint32_t col = 0; col < columns; ++col)
        {
            if (data[row][col] != other.data[row][col])
            {
                return false;
            }
        }
    }

    return true;
}

template<class T>
bool metrix<T>::operator!=(const metrix<T>& other) const
{
    return !(*this == other);
}

template<class T>
metrix<T>& metrix<T>::operator*=(const metrix<T>& rhs)
{
    *this = *this * rhs;
    return *this;
}


template<class T>
metrix<T> operator*(const metrix<T>& metrix_1,const metrix<T>& metrix_2)
{
    if(metrix_1.columns != metrix_2.rows)
        throw std::invalid_argument("");
    metrix<T> result(lhs.rows, rhs.columns, T{}); 
    uint32_t block = 32;
    for(int row_block_begin = 0;row_block_begin < metrix_1.rows;row_block_begin+= block)
    {
        const uint32_t row_block_end = std::min(row_block_begin+block,metrix_1.rows);
        for(int line_block_begin = 0;line_block_begin < metrix_1.columns;line_block_begin+=block)
        {
            const uint32_t line_block_end = std::min(line_block_begin+block,metrix_1.columns);
            for(int 2_line_block_begin = 0;2_line_block_begin<metrix_2.columns;2_line_block_begin+=block)
            {
                uint32_t 2_line_block_end = std::min(2_line_block_begin+block,metrix_2.columns);
                for(int i = row_block_begin;i<row_block_begin;i++)
                {
                    for(int j = line_block_begin;j<line_block_end;j++)
                    {
                        for(int k = 2_line_block_begin;k<2_line_block_end;k++)
                        {
                            result.data[i][k] = metrix_1[i][j] * metrix_2[j][k];                       
                        }
                    }
                }
            }
        }
    }
}