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
