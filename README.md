# OMP Matrix Product

## Developed by: [Desantis Clara](https://github.com/ClaraDeSantis) [Pavia Roberto](https://github.com/bloodsky)

> Fast benchmark program showing how matrix product can scale up in terms of speedup. 
> Speedup is serial time normalized over parallel time. The program implements matrix 
> product between two matrices A and B. In this example we have considered square matrices. 

![alt text](https://github.com/bloodsky/OMPMatrixProduct/blob/main/plot.png)

> Speedup grows with number of threads and matrix dimensions. 
> Exceptions are test cases with few threads and test cases with little matrix dimensions.
> Strange behaviour is achived when matrix dimensions approach 800.   

![alt text](https://github.com/bloodsky/OMPMatrixProduct/blob/main/plot2.png)
