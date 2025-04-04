using lab10.decorator;
using lab10.factory;
using lab10.model;
using System;
using lab10.sort;

namespace lab10;

public class Tests
{
    private static MessageTask[] createMessageTasks()
    {
        MessageTask msg1 = new MessageTask("1", "feedback lab 1", "Te-ai descurcat binisor!","profesor", "Ana", DateTime.Now);
        MessageTask msg2 = new MessageTask("2", "feedback lab 2", "Te-ai descurcat bine!","profesor", "Ana", new DateTime(2024,10,01, 12, 0, 0));
        MessageTask msg3 = new MessageTask("3", "feedback lab 3", "Te-ai descurcat foarte bine!","profesor", "Ana", new DateTime(2024,10,07, 12, 0, 0));
        MessageTask msg4 = new MessageTask("4", "feedback lab 4", "Te-ai descurcat decent!","profesor", "Ana", new DateTime(2024,11,14, 12, 0, 0));
        MessageTask msg5 = new MessageTask("5", "feedback lab 5", "Te-ai descurcat perfect!","profesor", "Ana", new DateTime(2024,11,21, 12, 0, 0));
        return new MessageTask[] { msg1, msg2, msg3, msg4, msg5 };
    }

    private void testMessageTaskp4()
    {
        MessageTask[] tasks = createMessageTasks();
        foreach(MessageTask m in tasks)
        {
            Console.WriteLine(m);
        }
    }

    private void testCreateStrategyp10(String strategy)
    {
        MessageTask[] tasks = createMessageTasks();
        StrategyTaskRunner strategyTaskRunner = new StrategyTaskRunner(Enum.Parse<Strategy>(strategy));
        foreach(MessageTask m in tasks)
        {
            strategyTaskRunner.AddTask(m);
        }

        strategyTaskRunner.ExecuteAllTasks();
    }

    private void StrategyPrinterp13(String strategy)
    {
        MessageTask[] tasks = createMessageTasks();
        StrategyTaskRunner strategyTaskRunner = new StrategyTaskRunner(Enum.Parse<Strategy>(strategy));
        ITaskRunner runner = new PrinterTaskRunner(strategyTaskRunner);
        foreach(MessageTask m in tasks)
        {
            runner.AddTask(m);
        }

        runner.ExecuteAllTasks();
    }

    private void StrategyDelayPrinterp14(String strategy)
    {
        Console.WriteLine("Strategia: " + strategy + "(Strategy -> Delay -> Printer");
        MessageTask[] tasks = createMessageTasks();
        StrategyTaskRunner strategyTaskRunner = new StrategyTaskRunner(Enum.Parse<Strategy>(strategy));
        foreach (MessageTask m in tasks)
        {
            strategyTaskRunner.AddTask(m);
        }
        
        ITaskRunner delayTaskRunner = new DelayTaskRunner(strategyTaskRunner);
        foreach (MessageTask m in tasks)
        {
            delayTaskRunner.AddTask(m);
        }
        
        ITaskRunner printerTaskRunner = new PrinterTaskRunner(strategyTaskRunner);
        foreach (MessageTask m in tasks)
        {
            printerTaskRunner.AddTask(m);
        }
        
        printerTaskRunner.ExecuteAllTasks();
        Console.WriteLine("\n");
    }

    private void testSorting(int[] array, String strategy)
    {
        Console.WriteLine("Strategia: " + strategy);
        SortingTask sortingTask = new SortingTask("1", "sa fiu organizata", Enum.Parse<SortingStrategy>(strategy), array);
        sortingTask.execute();

        foreach (var st in array)
        {
            Console.WriteLine(st + " ");
        }
        Console.WriteLine("\n");
    }

    private void testSort(int[] array)
    {
        Console.WriteLine("Vector: ");
        foreach (var v in array)
        {
            Console.WriteLine(v + " ");
        }
        
        int arrayLength = array.Length;
        int[] arrayCopy = new int[arrayLength];
        array.CopyTo(arrayCopy, 0);
        
        testSorting(array, "BubbleSort");
        testSorting(array, "MergeSort");
    }

    public void testAll(String[] args)
    {
        testMessageTaskp4();

        int[] array = new int[] { 22, 1, 30, 17, 30, 9, 1 };
        testSort(array);
        Console.WriteLine("\n");

        Console.WriteLine("Test FIFO");
        testCreateStrategyp10("FIFO");
        Console.WriteLine("\n");
        
        Console.WriteLine("Test LIFO");
        testCreateStrategyp10("LIFO");
        Console.WriteLine("\n");
        
        Console.WriteLine("Test Stack LIFO");
        StrategyPrinterp13("LIFO");
        Console.WriteLine("\n");
        
        Console.WriteLine("Test Queue FIFO");
        StrategyPrinterp13("FIFO");
        Console.WriteLine("\n");

        if (args.Length == 0)
        {
            Console.WriteLine("No input given");
            return;
        }
        
        String strategy = args[0];
        try
        {
            Console.WriteLine("Test 14 cu strategia: " + strategy);
            StrategyDelayPrinterp14(strategy);
        }
        catch (Exception e)
        {
            Console.WriteLine(e.Message);
        }
    }
}