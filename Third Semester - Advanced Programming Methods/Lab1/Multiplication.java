import java.util.ArrayList;

public class Multiplication extends ComplexExpression{
    public Multiplication(ArrayList<NumarComplex> args){
        super(Operation.MULTIPLICATION, args);
    }

    @Override
    protected NumarComplex executeOneOperation(NumarComplex a, NumarComplex b) {
        return a.inmultire(b);
    }
}
