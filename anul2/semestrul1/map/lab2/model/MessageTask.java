package model;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class MessageTask extends Task{
    private String mesaj;
    private String from;
    private String to;
    private LocalDateTime date;
    //static pentru ca nu e nevoie ca alta clasa sa il suprascrie
    //final pentru ca nu trebuie sa fie modificat, o data instantiat
    private static final DateTimeFormatter dateFormatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");

    public MessageTask(String taskID, String descriere, String mesaj, String from, String to, LocalDateTime date) {
        super(taskID, descriere);
        this.mesaj = mesaj;
        this.from = from;
        this.to = to;
        this.date = date;
    }

    @Override
    public String toString() {
        return "id = " + getTaskID() +
                " | description = " + getDescriere() +
                " | message = " + mesaj +
                " | from = " + from +
                " | to = " + to +
                " | date = " + date.format(dateFormatter);
    }

    @Override
    public void execute() {
        System.out.println(mesaj + ": " + date.format(dateFormatter));
    }
}
