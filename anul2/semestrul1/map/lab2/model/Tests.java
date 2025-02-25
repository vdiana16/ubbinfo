package model;

import decorator.DelayTaskRunner;
import decorator.PrinterTaskRunner;
import decorator.StrategyTaskRunner;
import decorator.TaskRunner;
import factory.Strategy;
import sort.SortingStrategy;
import sort.SortingTask;

import java.time.LocalDateTime;

public class Tests {
    private static MessageTask[] createMessages() {
        MessageTask msg1 = new MessageTask("1", "feedback lab 2", "Te-ai descurcat bine", "teacher", "student", LocalDateTime.now());
        MessageTask msg2 = new MessageTask("2", "feedback lab 3", "Te-ai descurcat foarte bine", "teacher", "student", LocalDateTime.of(2024,10,1,10,0));
        MessageTask msg3 = new MessageTask("3", "feedback lab 4", "Te-ai descurcat rau", "teacher", "student", LocalDateTime.of(2024,9,16,11,0) );
        MessageTask msg4 = new MessageTask("4", "feedback lab 5", "Te-ai descurcat mai putin bine", "teacher", "student", LocalDateTime.of(2024,8,2,9,0) );
        MessageTask msg5 = new MessageTask("5", "feedback lab 6", "Te-ai descurcat perfect", "teacher", "student", LocalDateTime.of(2024,9,20,21,0));
        return new MessageTask[]{msg1, msg2, msg3, msg4, msg5};
    }

    private void testMessageTaskp4(){
        MessageTask[] messageTasks = createMessages();
        for (MessageTask messageTask: messageTasks) {
            System.out.println(messageTask);
        }
    }

    private void testCreateStrategyp10(String strategy) {
        MessageTask[] messages = createMessages();
        StrategyTaskRunner strategyTaskRunner = new StrategyTaskRunner(Strategy.valueOf(strategy));
        for(MessageTask msg: messages) {
            strategyTaskRunner.addTask(msg);
        }
        strategyTaskRunner.executeAll();
    }

    private void StrategyPrinterp13(String strategy) {
        MessageTask[] messages = createMessages();
        StrategyTaskRunner strategyTaskRunner = new StrategyTaskRunner(Enum.valueOf(strategy));
        TaskRunner runner = new PrinterTaskRunner(strategyTaskRunner);
        for(MessageTask msg: messages) {
            runner.addTask(msg);
        }
        runner.executeAll();
    }

    private void StrategyDelayPrinterp14(String strategy) {
        System.out.println("Strategia: " + strategy + "(Strategy -> Delay -> Printer)");
        MessageTask[] messages = createMessages();
        StrategyTaskRunner strategyTaskRunner = new StrategyTaskRunner(Strategy.valueOf(strategy));
        for(MessageTask msg: messages) {
            strategyTaskRunner.addTask(msg);
        }
        //System.out.println("Strategy: ");
        //strategyTaskRunner.executeAll();

        TaskRunner delayTaskRunner;
        delayTaskRunner = new DelayTaskRunner(strategyTaskRunner);
        for(MessageTask msg: messages) {
            delayTaskRunner.addTask(msg);
        }
        //System.out.println("Delay: ");
        //delayTaskRunner.executeAll();

        TaskRunner printerTaskRunner;
        printerTaskRunner = new PrinterTaskRunner(delayTaskRunner);
        for(MessageTask msg: messages) {
            printerTaskRunner.addTask(msg);
        }
        //System.out.println("Printer: ");
        printerTaskRunner.executeAll();
        System.out.println("\n");
    }

    private void testSorting(int[] array, SortingStrategy strategy) {
        System.out.println("Strategia: " + strategy.toString());
        SortingTask sortingTask = new SortingTask("1","sa fiu organizata", strategy, array);
        sortingTask.execute();

        for(int st: array) {
            System.out.println(st + " ");
        }
        System.out.println();
    }

    private void testSort(int[] array) {
        System.out.println("Vector: ");
        for(int v : array){
            System.out.println(v + " ");
        }

        int arraySize = array.length;
        int[] array2 = new int[arraySize];
        System.arraycopy(array, 0, array2, 0, arraySize);

        testSorting(array,SortingStrategy.BubbleSort);
        testSorting(array2,SortingStrategy.MergeSort);
    }


    public void testAll(String[] args){
        testMessageTaskp4();

        int[] array = new int[]{22,1,30,2,12,9,10};
        testSort(array);
        System.out.println("\n");

        System.out.println("Test FIFO");
        testCreateStrategyp10("FIFO");
        System.out.println("\n");

        System.out.println("Test LIFO");
        testCreateStrategyp10("LIFO");
        System.out.println("\n");

        System.out.println("Test Stack LIFO");
        StrategyPrinterp13("LIFO");
        System.out.println("\n");

        System.out.println("Test Queue FIFO");
        StrategyPrinterp13("FIFO");
        System.out.println("\n");

        if(args.length == 0){
            System.out.println("Nu exista parametrii!");
            return;
        }
        System.out.println("\n");
        String strategy = args[0];
        try{
            System.out.println("Test 14 cu strategie: " + strategy);
            StrategyDelayPrinterp14(strategy);
        }catch (IllegalArgumentException e){
            System.out.println(e.getMessage());
        }
    }
}
