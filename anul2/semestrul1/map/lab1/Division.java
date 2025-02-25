import java.util.ArrayList;

public class Division extends ComplexExpression{
    public Division(ArrayList<NumarComplex> args){
        super(Operation.DIVISION, args);
    }

    @Override
    protected NumarComplex executeOneOperation(NumarComplex a, NumarComplex b) {
        return a.impartire(b);
    }
}
