package com.example.sem10_conc.bankaccount;

public class BankAccountWrong implements BankAccount {
    private double balance;

    public BankAccountWrong(double bal) {
        balance = bal;
    }

    public BankAccountWrong() {
        this(0);
    }

    public double getBalance() {
        return balance;
    }

    public void deposit(double amt) {
        double temp = balance + amt;
        try {
            Thread.sleep(300); // simulate processing time
        } catch (InterruptedException ie) {
            System.err.println(ie.getMessage());
        }
        balance = temp;
        System.out.println("after deposit balance = $" + balance);
    }

    public void withdraw(double amt) {
        if (balance < amt) {
            System.out.println("Insufficient funds!");
            return;
        }
        double temp = balance - amt;
        try {
            Thread.sleep(200); // simulate processing time
        } catch (InterruptedException ie) {
            System.err.println(ie.getMessage());
        }
        balance = temp;
        System.out.println("after withdrawal balance = $" + balance);
    }
}
