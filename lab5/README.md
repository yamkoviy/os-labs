# Memory optimization

**Formulation of the problem** There are some initial code and we need optimize it.



### **Initial code**


    using System;
    using System.Diagnostics;

    namespace OSLab5
    {
        class Program
        {
            static void Main(string[] args)
            {
                Stopwatch stopwatch = new Stopwatch();

                stopwatch.Start();



                int[,] a = new int[100, 100];
                int res = 0;

                for (int i = 0; i < 100; i++)
                {
                    for (int j = 0; j < 100; j++)
                    {
                        //a[j, i]++;
                        a[i, j]++;
                    }
                }

                stopwatch.Stop();

                Console.WriteLine($"Number of ticks {stopwatch.ElapsedTicks}");
            }

        }
    }


У прикладі наведеному вище ми обходимо матрицю по стовпцях, що погано, оскільки дані матриці зберігаються по рядках. Тобто ми спочатку зверталися до першого елемента кожного стовпця, потім до кожного другого, і тд. Помінявши місцями індекси, ми тепер обходимо матрицю по рядках.


## Result

*Result of executing initial code*

Кількість тактів (один такт = 427 нсек) - 5543

*Result of executing optimized code*

Кількість тактів (один такт = 427 нсек) - 4650
