package domain;

public class InmultireExp extends ComplexExpression {
    public InmultireExp(NumarComplex[] args) {
        super(Operation.MULTIPLICATION, args);
    }

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
        return op1.inmultire(op2);
    }
}
