import java.util.ArrayList;

public class Substraction extends ComplexExpression{
    public Substraction(ArrayList<NumarComplex> args){
        super(Operation.SUBSTRACTION, args);
    }

    @Override
    protected NumarComplex executeOneOperation(NumarComplex a, NumarComplex b){
       return a.scadere(b);
    }
}
