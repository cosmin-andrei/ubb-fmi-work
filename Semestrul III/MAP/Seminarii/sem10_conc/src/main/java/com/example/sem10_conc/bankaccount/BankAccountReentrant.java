package com.example.sem10_conc.bankaccount;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class BankAccountReentrant implements BankAccount {
    private double balance;

    private final Lock lock = new ReentrantLock();

    public BankAccountReentrant(double bal) {
        balance = bal;
    }

    public BankAccountReentrant() {
        this(0);
    }


    public double getBalance() {
        try {
            System.out.println(Thread.currentThread().getName() + " waiting for lock");
            lock.lock();
            System.out.println(Thread.currentThread().getName() + " acquired lock");
            try {
                Thread.sleep(3000); // simulate processing time
            } catch (InterruptedException ie) {
                System.err.println(ie.getMessage());
            }
            return balance;
        } finally {
            lock.unlock();
            System.out.println(Thread.currentThread().getName() + " released lock");
        }
    }

    public void deposit(double amt) {
        try {
            lock.lock();
            double temp = balance + amt;
            try {
                Thread.sleep(100); // simulate processing time
            } catch (InterruptedException ie) {
                System.err.println(ie.getMessage());
            }
            balance = temp;
            System.out.println("after deposit balance = $" + balance);
        } finally {
            lock.unlock();
        }
    }

    public void withdraw(double amt) {
        try {
            lock.lock();
            if (balance < amt) {
                System.out.println("Insufficient funds!");
                return;
            }
            double temp = balance - amt;
            try {
                Thread.sleep(100); // simulate processing time
            } catch (InterruptedException ie) {
                System.err.println(ie.getMessage());
            }
            balance = temp;
            System.out.println("after withdrawal balance = $" + balance);
        }  finally {
            lock.unlock();
        }
    }
}
