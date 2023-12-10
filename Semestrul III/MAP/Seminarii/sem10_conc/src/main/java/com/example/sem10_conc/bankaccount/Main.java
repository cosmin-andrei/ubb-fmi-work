package com.example.sem10_conc.bankaccount;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {

    public static void runWithThreads(BankAccount account) throws InterruptedException {
        Thread t1 = new Thread(() -> account.deposit(100));
        Thread t2 = new Thread(() -> account.deposit(100));

        t1.start();
        t2.start();

        t1.join();
        t2.join();

        System.out.println("final balance = $" + account.getBalance());
    }

    public static void runReaders(BankAccount account) throws InterruptedException {
        Thread t1 = new Thread(account::getBalance);
        Thread t2 = new Thread(account::getBalance);

        t1.start();
        t2.start();

        t1.join();
        t2.join();
    }

    private static void runWithThreadPool(BankAccount account) throws InterruptedException {
        int numThreads = 3;
        ExecutorService executor = Executors.newFixedThreadPool(numThreads);
        for (int i = 0; i < 10; i++) {
            Runnable task = () -> account.deposit(100);
            executor.submit(task);
        }
        executor.shutdown();

    }

    public static void main(String[] args) throws InterruptedException {
        BankAccount account;
        // wrong
         account = new BankAccountWrong(0);
        // correct
//        account = new BankAccountSync(0);
        runWithThreads(account);
//        //runWithThreadPool(account);

//        account = new BankAccountReentrant(0);
//        runWithThreadPool(account);
    }
}
