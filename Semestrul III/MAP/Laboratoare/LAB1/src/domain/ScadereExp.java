package domain;

public class ScadereExp extends ComplexExpression {
    public ScadereExp(NumarComplex[] args) {
        super(Operation.SUBTRACTION, args);
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
        return op1.scadere(op2);
    }
}
