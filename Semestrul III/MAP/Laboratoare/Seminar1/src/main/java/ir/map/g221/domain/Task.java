package ir.map.g221.domain;

public abstract class Task {
    private String taskID;
    private String descriere;

    public Task() {
        this.taskID = "5678";
        this.descriere = "Ion";

        System.out.println("Task");
    }

    public Task(String taskID, String descriere) {
        this.taskID = taskID;
        this.descriere = descriere;
    }

    public abstract void run();

    public String getTaskID() {
        return taskID;
    }

    public String getDescriere() {
        return descriere;
    }

    public void setTaskID(String taskID) {
        this.taskID = taskID;
    }

    public void setDescriere(String descriere) {
        this.descriere = descriere;
    }

    @Override
    public int hashCode() {
        return super.hashCode();
    }

    @Override
    public boolean equals(Object obj) {
        return super.equals(obj);
    }

    @Override
    public String toString() {
        return taskID + " " + descriere;
    }
}
