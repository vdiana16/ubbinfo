import java.util.ArrayList;

public class ExpressionFactory {
    //Factory Pattern and Singleton Pattern

    //instanta unica
    private static ExpressionFactory instance;

    //constructor privat
    private ExpressionFactory() {}

    //singurul mod in care e accesibila instanta
    public static ExpressionFactory getInstance() {
        if(instance == null) {
            instance = new ExpressionFactory();
        }
        return instance;
    }

    //Factory method
    //codul care utilizeaza expresiile nu trebuie sa cunoasca detaliile implementarii fiecarei expresii
    public ComplexExpression createComplexExpression(Operation operation, ArrayList<NumarComplex> args) {
        switch(operation){
            case ADDITION:
                return new Addition(args);
            case SUBSTRACTION:
                return new Substraction(args);
            case MULTIPLICATION:
                return new Multiplication(args);
            case DIVISION:
                return new Division(args);
            default:
                throw new IllegalArgumentException("Operatie inexistenta");
        }
    }
}
