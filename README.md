# OMP Matrix Product

## Developed by: [Desantis Clara] [Pavia Roberto](https://github.com/bloodsky)

> Fast benchmark program showing how matrix product can scale up in terms of speeup. 
> Speedup is just serial time normalized over parallel time. The program respects 
> general rule that given two matrices A and B then the product matrix C has the
> same number of A-rows and same number of B-cols. Product matrix can be produced
> if and only if number of A-cols is equal to B-rows. In this particular case we have 
> decided to create arrays with the same size of rows and columns for simplicity. 

![alt text](https://github.com/bloodsky/OMPMatrixProduct/blob/main/plot.png)
