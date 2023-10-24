package ir.map.g221;

import ir.map.g221.domain.MessageTask;
import ir.map.g221.domain.Task;
import ir.map.g221.factory.Container;
import ir.map.g221.factory.Factory;
import ir.map.g221.factory.Strategy;
import ir.map.g221.factory.TaskContainerFactory;
import ir.map.g221.runner.*;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

import java.time.LocalDateTime;
public class Test {

    public Test() {
    }

    public void ex_4(){
        System.out.println("ex_4");
        MessageTask[] vector = new MessageTask[5];
        vector[0] = new MessageTask("2020", "Ana", "Mesaj1", "Ioana", "Andrei", LocalDateTime.now());
        vector[1] = new MessageTask("2030", "Task2", "Mesaj2", "Alex", "Sandu", LocalDateTime.now());
        vector[2] = new MessageTask("2024", "t3", "Mesaj3", "Lorena", "Andrei", LocalDateTime.now());
        vector[3] = new MessageTask("2023", "T4", "Mesaj4", "Elena", "Vasile", LocalDateTime.now());
        vector[4] = new MessageTask("200", "Task 5", "Mesaj5", "Daniela", "Lorand", LocalDateTime.now());
        for(MessageTask i: vector){
            i.run();
        }
    }

    public void ex_10(String strategy){
        System.out.println("ex_10");
        StrategyTaskRunner runner = null;
        if(strategy.equalsIgnoreCase("lifo"))
            runner = new StrategyTaskRunner(Strategy.LIFO);
        if(strategy.equalsIgnoreCase("fifo"))
            runner = new StrategyTaskRunner(Strategy.FIFO);
        runner.addTask(new MessageTask("233f","Task1","Mesaj1","Andrei1","Andrei1", LocalDateTime.now()));
        runner.addTask(new MessageTask("233f","Task2","Mesaj2","Andrei2","Andrei2", LocalDateTime.now()));
        runner.addTask(new MessageTask("233f","Task3","Mesaj3","Andrei3","Andrei3", LocalDateTime.now()));
        runner.addTask(new MessageTask("233f","Task4","Mesaj4","Andrei4","Andrei4", LocalDateTime.now()));
        try {
            runner.executeAll();
        }catch (Exception ex)
        {
            System.out.println(ex.toString());
        }
    }

    public void ex_13_14(String strategy){
        System.out.println("ex_13_14");
        AbstractTaskRunner runner = null;
        if(strategy.equalsIgnoreCase("lifo"))
            runner = new AbstractTaskRunner(new PrinterTaskRunner(new StrategyTaskRunner(Strategy.LIFO)));
        if(strategy.equalsIgnoreCase("fifo"))
            runner = new AbstractTaskRunner(new PrinterTaskRunner(new StrategyTaskRunner(Strategy.FIFO)));
        System.out.println("afisarea via StrategyTaskRunner a fost efectuala la ex_10");
        System.out.println("afisarea via PrinterTaskRunner");
        runner.addTask(new MessageTask("233f","Task1","Mesaj1","Andrei1","Andrei1", LocalDateTime.now()));
        runner.addTask(new MessageTask("233f","Task2","Mesaj2","Andrei2","Andrei2", LocalDateTime.now()));
        runner.addTask(new MessageTask("233f","Task3","Mesaj3","Andrei3","Andrei3", LocalDateTime.now()));
        runner.addTask(new MessageTask("233f","Task4","Mesaj4","Andrei4","Andrei4", LocalDateTime.now()));

        try {
            runner.executeAll();
        }catch (Exception ex)
        {
            System.out.println(ex.toString());
        }

        AbstractTaskRunner runner1 = null;
        if(strategy.equalsIgnoreCase("lifo"))
            runner1 = new AbstractTaskRunner(new DelayTaskRunner(new StrategyTaskRunner(Strategy.LIFO)));
        if(strategy.equalsIgnoreCase("fifo"))
            runner1 = new AbstractTaskRunner(new DelayTaskRunner(new StrategyTaskRunner(Strategy.FIFO)));
        System.out.println("afisarea via DelayTaskRunner");

        runner1.addTask(new MessageTask("233f","Task1","Mesaj1","Andrei1","Andrei1", LocalDateTime.now()));
        runner1.addTask(new MessageTask("233f","Task2","Mesaj2","Andrei2","Andrei2", LocalDateTime.now()));
        runner1.addTask(new MessageTask("233f","Task3","Mesaj3","Andrei3","Andrei3", LocalDateTime.now()));
        runner1.addTask(new MessageTask("233f","Task4","Mesaj4","Andrei4","Andrei4", LocalDateTime.now()));

        try {
            runner1.executeAll();
        }catch (Exception ex)
        {
            System.out.println(ex.toString());
        }
    }
}