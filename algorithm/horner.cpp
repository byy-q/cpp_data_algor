int Horner_polynome(int x,int* A,int n)
{
    int y = 0;
    for(int i = 0 ;i < n;i++) 
    {
        y = x * y + *(A+i);
    }
    return y;
}

