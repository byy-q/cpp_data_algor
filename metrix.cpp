#include <cstdint>


template<class T>
class metrix
{
    public:
        metrix();
        metrix(uint32_t Rows,uint32_t Columns,const T& Data);
        metrix(const metrix<T>& copy);
        metrix(metrix<T>&& copy);
        ~metrix();
        metrix<T>& operator=(const metrix<T>& copy);
        metrix<>& operator=(metrix<T>&& copy);
        bool operator==(const metrix<T>& compare);
        bool operator!=(const metrix<T>& compare);
        metrix<T>& operator*=(const metrix<T>& Metrix_2);
        friend metrix<T> operator*(const metrix<T>& Metrix_1,const metrix<T>& Metrix_2);
    private:
        T**     data = 0;
        uint32_t    rows;
        uint32_t    columns; 
};