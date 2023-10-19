import domain.NumarComplex;

import static domain.ExpressionParser.evaluateExpression;
import static domain.ExpressionParser.isExpressionValid;

public class Main {
    public static void main(String[] args) {

        //verificare expresie si calcule
        if(isExpressionValid(args)==true){
            NumarComplex rez = evaluateExpression(args);
            System.out.println("Rezultatul expresiei:" + rez.toString());
        }
       else{
            System.out.println("Expresia nu este valida");
        }
    }

}