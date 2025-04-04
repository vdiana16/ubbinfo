import java.util.ArrayList;

public class Addition extends ComplexExpression{
    //constructor
    public Addition(ArrayList<NumarComplex> args){
        //apeleaza constructorul clasei de baza
        super(Operation.ADDITION, args);
    }

    @Override
    protected NumarComplex executeOneOperation(NumarComplex a, NumarComplex b){
        return a.adunare(b);
    }
}

    
