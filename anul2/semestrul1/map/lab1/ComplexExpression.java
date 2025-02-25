import java.util.ArrayList;

public abstract class ComplexExpression {
    //template method

    //instante
    private Operation operation;
    private ArrayList<NumarComplex> args;

    //constructor
    public ComplexExpression(Operation operation, ArrayList<NumarComplex> args) {
        this.operation = operation;
        this.args = args;
    }

    //getters
    public Operation getOperation() {

        return operation;
    }
    public ArrayList<NumarComplex> getArgs() {

        return args;
    }

    //setters
    public void setOperation(Operation operation) {

        this.operation = operation;
    }
    public void setArgs(ArrayList<NumarComplex> args) {

        this.args = args;
    }

    //metoda abstracte
    protected abstract NumarComplex executeOneOperation(NumarComplex z1, NumarComplex z2);

    public final NumarComplex execute(){
        NumarComplex result = executeOneOperation(args.get(0), args.get(1));
        for(int i = 2; i < args.size(); i++){
            result = executeOneOperation(result, args.get(i));
        }
        return result;
    }
}
