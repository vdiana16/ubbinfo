package decorator;

import model.Task;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class PrinterTaskRunner extends AbstractTaskRunner {
    private static final DateTimeFormatter timeformatterr = DateTimeFormatter.ofPattern("HH:mm");

    public PrinterTaskRunner(TaskRunner taskRunner) {
        super(taskRunner);
    }

    @Override
    public void executeOneTask() {
        super.executeOneTask();
        System.out.println("Task-ul s-a executat la: " + LocalDateTime.now().format(timeformatterr));
    }

}
