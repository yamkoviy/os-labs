# Lab 6: Profiling


**Formulation of the problem** Profile initial code, write parameters and try to get better profiling parameters via code optimization

### **Initial code**

    #include<stdio.h>

    void new_func1(void);

    int func1(int a, int b)
    {
	    int res = 0
        for(int i = 0; i < 10; i++)
	    {
		    sleep(1);
		    if(i>8)
			    res = resultOfSum(a, b);
		    if(res > 0)
			    return res;
	    }
        return res;
    }
    int func2(int a, int b)
    {
        int res = 0;
        for(int i = 0; i < 10; i++)
        {
		    int res = func1(a, b);
		    if(res > 0)
			    return res;
	    }

        return;
    }   


    int resultOfSum(int a, int b)
    {
	    return a+b;
    }

    int main(void)
    {
        func2(51, 110);

        return 0;
    }

У коді присутня функція sleep. Поки основний потік знаходився у сплячому режимі, то процесор був звільнений і виконував інші задачі.

## **Results**

*Result of executing initial program*

Runtime - 3.252

*Result of executing optimized code* 

Runtime - 1.399
