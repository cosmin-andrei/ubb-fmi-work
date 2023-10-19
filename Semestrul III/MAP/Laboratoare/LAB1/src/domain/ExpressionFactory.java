//package domain;
//
//
////'fabrica' de numere complexe - crearea de instante de expresii complexe
//public class ExpressionFactory {
//    protected static ExpressionFactory instance;
//    protected ExpressionFactory() {} //permite claselor derivate accesul
//
//
//    //pe baza operatiei creez o expresie complexa
//    public ComplexExpression createExpression(Operation operation, NumarComplex[] args) {
//        return switch (operation) {
//            case Operation.ADDITION -> new AdunareExp(args);
//            case Operation.SUBTRACTION -> new ScadereExp(args);
//            case Operation.MULTIPLICATION -> new InmultireExp(args);
//            case Operation.DIVISION -> new ImpartireExp(args);
//        };
//    }
//}