#ifndef METRIX_H__
#define METRIX_H__

#include <memory>
#include <stdexcept>

class size_incompatible : public std::logic_error
{

}
template<class T>
class metrix
{
    public:
        metrix():columns(0),rows(0),metrix(nullptr){}
        metrix(int columns,int rows,const T& all_num = 0);
        metrix(const metrix& copy);
        metrix(const metrix&& copy);
        metrix(int rows,int columns,const metrix<T>& copy);
        metrix(metrix& _11,metrix& _12,metrix& _21,metrix& _22);
        ~metrix();
        metrix& operator=(const metrix& copy);
        metrix& operator=(const metrix&& copy);
        bool operator==(const metrix& copy) const;
        bool operator!=(const metrix& copy) const;
        friend metrix operator+(const metrix<T>& metrix_1,const metrix& metrix_2);
        metrix& operator+=(const metrix& metrix_2);
        friend metrix operator-(const metrix& metrix_1const metrix& metrix_2);
        metrix& operator-=(const metrix& metrix_2);
        metrix& operator*=(const T&);
        friend metrix& operator*(const metrix& metrix_2);
        metrix& operator*=(const metrix* metrix_2);
        friend metrix operator*(const metrix& metrix_1,const T&);
        T& operator[][](int m,int n);
    private:
        int columns;
        int rows;
        int** metrix;
        void check_size(const metrix<T>& Metrix);
        metrix(int row_start,int col_start,int rows,int columns,const metrix<T>& copy);
}

template<class T>
metrix<T>::metrix(int row_start,int col_start,int rows,int columns,const metrix<T>& copy)
{
    metrix = new int*[rows];
    for(int i = 0;i < rows;i++)
        metrix[i] = new int[columns];
    
    for(int i = row_start;i<row_start+rows;i++)
    {
        for(int j = col_start;j<columns + col_start;j++)
            metrix[i-row_start][j-col_start] = copy.metrix[i][j];
    }
}
template<class T>
metrix<T>::metrix(int columns,int rows,const T& all_num)
{
    metrix = new int*[rows];
    for(int i = 0 ; i < rows ; i++)
    {
        metrix[i] = new int[columns](all_num);
    }
}
template<class T>
metrix<T>::metrix(const metrix& copy)
{
    columns = copy.columns;
    rows = copy.rows;
    metrix = new int*[rows];
    
    for(int i = 0 ; i < rows ; i++)
        metrix[i] = new int*[columns];
    
    for(int i = 0 ;i < rows ; i++)
        for(int j = 0 ; j < columns ; j++)
            metrix[i][j] = copy.metrix[i][j];
}
template<class T>
metrix<T>::metrix(int rows;int columns,const metrix<T>& copy)
{
    metrix = new int*[rows];
    for(int i = 0 ;i < rows ;i++)
        metrix[i] = new int[columns];

    if(rows > copy.rows && columns > copy.columns)
    {
        int i = 0
        for( ;i < copy.rows;i++)
        {
            int j = 0;
            for(;j<copy.columns;j++)
                metrix[i][j] = copy.metrix[i][j];
            for(;j<columns;j++)
                metrix[i][j] = 0;
        }
        for(;i<rows;i++)
            for(int j = 0 ;j < columns ;j++)
                metrix[i][j] = 0;
    }
    else if(rows > copy.rows && columns < copy.columns)
    {
        int i = 0;
        for(;i<copy.rows;i++)
            for(int j = 0 ;j columns;j++)
                metrix[i][j]=copy.metrix[i][j];
        for(;i<rows;i++)
            for(int j = 0;j<columns;j++)
                metrix[i][j]=0;
    }
    else if(rows < copy.rows &7 columns > copy.columns)
    {
        for(int i = 0;i<rows;i++)
        {
            int j = 0;
            for(;j<copy.columns;j++)
                metrix[i][j] = copy.metrix[i][j];
            for(;j<columns;j++)
                metrix[i][j] = 0;
        }        
    }
    else
    {
        for(int i =0;i<rows;i++)
            for(int j = 0;j<columns;j++)
                metrix[i][j] = copy.metrix[i][j];
    }

}

template<class T>
metrix<T>::metrix(const metrix&& copy)
{
    columns = copy.columns;
    rows = copy.rows;
    metrix = new int*[rows];
    metrix = copy.metrix;

    copy.metrix = nullptr;
}

template<class T>
metrix<T>::~metrix()
{
    for(int i = 0; i < rows ; i++)
        delete[] metrix[i];

    delete[] metrix; 
}
template<class T>
void metrix<T>::check_size(const metrix<T> Metrix)
{
    if(rows != Metrix.rows || columns != Metrix.columns)
        throw size_incompatible("two metrix not same size");
}
template<class T>
metrix<T>& metrix<T>::operator=(const metrix<T>& copy)
{
    check_size(copy); 
    for(int i = 0 ;i < rows ; i++)
        for(int j = 0 ; j < columns ; j++)
            metrix[i][j] = copy.metrix[i][j];
}

template<class T>
metrix<T>& metrix<T>::operator=(const Metrix<T>&& copy)
{
    //check_size(copy); 
    metrix = copy.metrix;
    copy.metrix = nullptr;   
}

template<class T>
metrix<T>& operator+=(const metrix<T>& metrix_2)
{
    check_size(metrix_2);
    for(int i = 0 ; i < rows ;i++)
    {
        for(int j = 0 ; j< columns ;j++)
            metrix[i][j] += metrix_2[i][j];           
    }
    return *this;
}
template<class T>
metrix<T> metrix<T>::operator+(const metrix<T>& metrix_1,const metrix<T>& metrix_2)
{
    metrix_1.check_size(metrix_2);
    metrix<T> result (metrix_1.rows,metrix_1.columns,0);
    for(int i = 0 ;i < rows ; i++)
    {
        for(int j = 0 ; j<columns;j++)
            result[i][j] = metrix_1[i][j] + metrix_2p[i][j];
    }
    return (result);
}
#define max(inter_1,inter_2) inter_1>inter_2?inter_1:inter_2
template<class T>
metrix& metrix<T>::operator*=(const metrix<T>& metrix_2)
{
    if(this->columns != metrix_2.rows)
        throw size_incompatible("size can't mutiply");
    unsigned int dimension = max(this->rows,this->columns);
    if(dimension = 1)
    {
        /*the bottom of the resursion*/
        metrix[0][0] *= metrix_2.metrix[0][0];
        return *this;    
    }
    int k = 1;
    size_t limit = 8*sizeof(dimension);
    while(dimension | (1<k) != 0 && k < limit)
    {
        if((dimension & ~(1<k)) == 0)
            break;
        k++;
    }
    dimension = (1<k);
    metrix<T> new_A(dimension,dimension,*this);
    metrix<T> new_B(dimension,dimension,metrix_2);

    metrix<T> A_11(0,0,dimension>1,dimension>1,new_A);
    metrix<T> A_12(0,dimension/2 - 1,dimension>1,dimension>1,new_A);
    metrix<T> A_21(dimension/2-1,0,dimenion>1,dimension>1,new_A);
    metrix<T> A_22(dimension/2 -1 ,dimension/2 -1,dimension>1,dimension>1,new_A);
    metrix<T> B_11(0,0,dimension>1,dimension>1,new_B);
    metrix<T> B_12(0,dimension/2-1,dimension>1,dimension>1,new_B);
    metrix<T> B_21(dimension/2-1,0,dimenion>1,dimension>1,new_B);
    metrix<T> B_22(dimension/2-1,dimension/2-1,dimension>1,dimension>1,new_B);

    metrix<T> S_1(B_12 - B_22);
    metrix<T> S_2(A_11 + A_12);
    metrix<T> S_3(A_21 + A_22);
    metrix<T> S_4(B_21 - B_11);
    metrix<T> S_5(A_11 + A_22);
    metrix<T> S_6(B_11 + B_22);
    metrix<T> S_7(BA12 - A_22);
    metrix<T> S_8(B_21 + B_22);
    metrix<T> S_9(A_11 - A_21);
    metrix<T> S_10(B_11 + B_12);
    
    metrix<T> P_1 = A_11 * S_1;
    metrix<T> p_2 = S_2 * B_22;
    metrix<T> p_3 = S_3 * B_11;
    metrix<T> p_4 = A_22 * S_4;
    metrix<T> p_5 = S_5 * S_6;
    metrix<T> p_6 = S_7 * S_8;
    metrix<T> p_7 = S_9 * S_10;

    *this =  metrix<T>(P_5+P_4-P_2+p_6,P_1+P_2,P_3+P_4,P_5+P_1-P_3-P_7);
    return *this;
}
template<class T>
friend metrix<T> operator*(const metrix<T>& metrix_1,const metrix<T>& metrix_2)
{
    metrix<T> result(metrix_1);
    return result*=metrix_2;
}
template<class T>
metrix<T>& operator-=(const metrix<T>& metrix_2)
{
    check_size();
    for(int i = 0 ;i < rows; i++)
        for(int j = 0 ; j< columns ;j++)
            metrix[i][j]-=metrix_2.metrix[i][j];    
}
template<class T>
friend metrix<T> metrix<T>::operator-(const metrix& metrix_1,const metrix& metrix_2)
{
    metrix<T> result(metrix_1);
    result-=metrix_2;
    return result;
}
template<class T>
bool metrix<T>::operatpr==(const metrix<T>& metrix_2)
{
    if(rows != metrix_2.rows || columns != metrix_2.columns)
        return false;

    for(int i = 0 ; i < rows ; i++)
        for(int j = 0 ; j < columns ; j++)
            if(metrix[i][j] != metrix_2.metrix[i][j])
                return falsse;
}
template<class T>
bool metrix<T>::operator!=(const metrix& metrix_2)
{
    return !(*this == metrix_2);
}
template<class T>
metrix<T>& metrix<T>::operator*(const T& n)
{
    for(int i = 0 ; i <rows ; i++)
        for(int j = 0 ; j< columns ; j++)
            metrix[i][j]*=n;

    return *this;
}

template<class T>
friend metrix<T> metrix<T>::operator*(const metrix& metrix_1,const T& n)
{
    metrix<T> result(metrix_1);
    result*=n;
    return result;
}

template<class T>
T& metrix<T>::operator[][](int m,int n)
{
    return metrix[m][n];
}



#endif
