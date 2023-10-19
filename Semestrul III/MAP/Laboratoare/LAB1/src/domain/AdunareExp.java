package domain;

public class AdunareExp extends ComplexExpression {
    public AdunareExp(NumarComplex[] args) {
        super(Operation.ADDITION, args);
    }

    //calculul expresiei
    @Override
    public NumarComplex execute() {
        NumarComplex rez = args[0];
        for (int i = 1; i < args.length; i++) {
            rez = executeOneOperation(rez, args[i]);
        }
        return rez;
    }

    @Override
    protected NumarComplex executeOneOperation(NumarComplex op1, NumarComplex op2) {
        return op1.adunare(op2);
    }
}
