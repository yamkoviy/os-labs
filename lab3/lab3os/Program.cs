using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading;

namespace lab3os
{

class GFG
    {
        static void push(Stack<int> stack)
        {
            Console.WriteLine("------------------------:" + "\r\n");
            for (int i = 0; i < 1000; i++)
            {
                Stopwatch stopwatch = new Stopwatch();
                stopwatch.Start();
                stack.Push(i);
                Console.WriteLine("Push element " + i);
                stopwatch.Stop();
                Console.WriteLine("Потрачено тактов на выполнение: " + stopwatch.ElapsedTicks);
            }
        }

        
        static void pop(Stack<int> stack)
        {
            Console.WriteLine("------------------------:" + "\r\n");

            for (int i = 0; i < 1000; i++)
            {
                Stopwatch stopwatch = new Stopwatch();
                stopwatch.Start();
                int y = (int)stack.Pop();
                Console.WriteLine("Pop element " + y);
                stopwatch.Stop();
                Console.WriteLine("Потрачено тактов на выполнение: " + stopwatch.ElapsedTicks);
            }
        }

    
        static void peek(Stack<int> stack)
        {
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();
            int element = (int)stack.Peek();
            Console.WriteLine("Element on stack top : " + element);
            stopwatch.Stop();
            Console.WriteLine("Потрачено тактов на выполнение: " + stopwatch.ElapsedTicks);
        }

       
        static void search(Stack<int> stack, int element)
        {
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();
            bool pos = stack.Contains(element);

            if (pos == false)
                Console.WriteLine("Element not found");
            else
                Console.WriteLine("Element is found ? " + pos);
            stopwatch.Stop();
            Console.WriteLine("Потрачено тактов на выполнение: " + stopwatch.ElapsedTicks);
        }

        public static void Main(String[] args)
        {
            Stack<int> stack = new Stack<int>();

            push(stack);
            pop(stack);
            push(stack);
            peek(stack);
            
            search(stack, 15);
            search(stack, 3);
        }
    }

}

