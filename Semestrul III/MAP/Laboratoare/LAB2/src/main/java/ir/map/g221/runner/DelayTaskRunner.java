package ir.map.g221.runner;

import java.time.LocalDateTime;

public class DelayTaskRunner extends AbstractTaskRunner{

    public DelayTaskRunner(TaskRunner tr) {
        super(tr);
    }

    @Override
    public void executeOneTask() {

            try{
                Thread.sleep(3000);

            } catch (InterruptedException e) {
                e.printStackTrace(); //de intrebat dl profesor
            }

        tr.executeOneTask();
        System.out.println("Task executat cu succes la ora " + LocalDateTime.now());

    }

    @Override
    public void executeAll() {
        while(tr.hasTask())
            this.executeOneTask();
    }



}
