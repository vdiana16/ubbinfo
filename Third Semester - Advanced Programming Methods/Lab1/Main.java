import java.util.Scanner;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
        ExpressionParser parser = new ExpressionParser();
        Scanner scanner = new Scanner(System.in);

        while (true){
            System.out.println("Introduceti o expresie sau exit: ");
            String inp = scanner.nextLine();
            if(inp.equals("exit"))
                break;
            try {
                ComplexExpression exp = parser.parseExpression(inp);
                System.out.println("Expresie corecta!");
                NumarComplex res = exp.execute();
                System.out.println("Raspunsul este:" + res.toString() + "\n");
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }
        System.out.println("Program finalizat!");
    }
}