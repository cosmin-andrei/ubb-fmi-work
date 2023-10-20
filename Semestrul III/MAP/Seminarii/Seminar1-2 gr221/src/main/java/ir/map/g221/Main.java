package ir.map.g221;

import ir.map.g221.domain.MessageTask;
import ir.map.g221.domain.Task;
import ir.map.g221.factory.Container;
import ir.map.g221.factory.Factory;
import ir.map.g221.factory.Strategy;
import ir.map.g221.factory.TaskContainerFactory;
import ir.map.g221.runner.PrinterTaskRunner;
import ir.map.g221.runner.StrategyTaskRunner;
import ir.map.g221.runner.TaskRunner;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

import java.time.LocalDateTime;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) {
        MessageTask t1 = new MessageTask("2020", "Ana", "Mesaj1", "Ioana", "Andrei", LocalDateTime.now());
        MessageTask t2 = new MessageTask("2021", "Ana2", "Mesaj2", "Ioana", "Andrei3", LocalDateTime.now());
        MessageTask t3 = new MessageTask("2022", "Ana3", "Mesaj3", "Ioana2", "Andrei", LocalDateTime.now());
        MessageTask t4 = new MessageTask("2023", "Ana4", "Mesaj4", "Ioana", "Andrei", LocalDateTime.now());
        MessageTask t5 = new MessageTask("2024", "Ana5", "Mesaj5", "Ioana5", "Andrei1", LocalDateTime.now());


        // Factory factory = new TaskContainerFactory();
//        Container container = factory.createContainer(Strategy.valueOf(args[0]));
//        container.add(t1);
//        container.add(t2);
//        container.add(t3);
//        container.add(t4);
//        container.add(t5);

//        for (int i = container.size(); i > 0; i--) {
//            container.remove().run();
//        }

//        TaskRunner runner = new StrategyTaskRunner(Strategy.valueOf(args[0]));
//        runner.addTask(t1);
//        runner.addTask(t2);
//        runner.addTask(t3);
//        runner.addTask(t4);
//        runner.addTask(t5);
//
//        runner.executeAll();
//        runner.executeOneTask();

        TaskRunner runner = new PrinterTaskRunner(new StrategyTaskRunner(Strategy.valueOf(args[0])));
        runner.addTask(t1);
        runner.addTask(t2);
        runner.addTask(t3);
        runner.addTask(t4);
        runner.addTask(t5);

        runner.executeAll();
//        runner.executeOneTask();
    }
}