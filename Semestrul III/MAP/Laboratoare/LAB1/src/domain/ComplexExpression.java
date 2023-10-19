package domain;

//clasa abstracta pt definirea expresiilor complexe
public abstract class ComplexExpression {
    protected Operation operation;
    protected NumarComplex[] args; //vector de numere complexe

    //constructor clasa
    public ComplexExpression(Operation operation, NumarComplex[] args) {
        this.operation = operation;
        this.args = args;
    }

    //clasa pur abstracta folosita in operatii pt a executa
    public abstract NumarComplex execute();

    //execut o operatie intre 2 numere complexe
    protected abstract NumarComplex executeOneOperation(NumarComplex op1, NumarComplex op2);

}