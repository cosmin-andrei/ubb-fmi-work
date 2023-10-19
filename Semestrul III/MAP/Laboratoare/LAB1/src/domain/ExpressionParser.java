package domain;

import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.ArrayList;


//analiza si evaluarea expresiilor
public class ExpressionParser {

    //Verific daca expresia este valida
    //2+3*i + 5+6*i
    public static boolean isExpressionValid(String[] args) {

        for(int i=0; i< args.length; i++){
            if(i%2==0) {
                if(!isValidComplexNumber(args[i])){
                    return false;
                }
            }
            else if(!isValidOperator(args[i])){
                return false;
            }
        }

        return true;
    }

    //unul dintre operatori: +, -, *, /
    private static boolean isValidOperator(String arg) {
        return arg.matches("[+\\-*/]*");
    }

    //verifica daca este numar complex
    private static boolean isValidComplexNumber(String arg) {
        String regex = "([+\\-/*]*[0-9]+[+-][0-9]+)+\\*i";
        return arg.matches(regex);
    }


    //evaluez expresia si
    public static NumarComplex evaluateExpression(String[] args) {

        List<NumarComplex> complexNumbers = new ArrayList<>(); //aici stochez numerele complexe

        Operation currentOperation = null;
        for(int i=0; i<args.length; i++){
            if(i%2==0){
                complexNumbers.add(parseComplexNumber(args[i])); //adaug numarul complex
            }else{
                currentOperation = (Operation) parseOperation(args[i]); //adaug operatia
            }
        }

        NumarComplex rez = complexNumbers.get(0); //initializez cu prima valoare din Array Listul de numere complexe
        for(int i=1; i< complexNumbers.size(); i++){
            rez=executeOperation(rez, complexNumbers.get(i), currentOperation);
        }

        return rez;

    }

    //efectuez operatia
    private static NumarComplex executeOperation(NumarComplex nr1, NumarComplex nr2, Operation operation) {

        return switch (operation) {
            case ADDITION -> nr1.adunare(nr2);
            case SUBTRACTION -> nr1.scadere(nr2);
            case MULTIPLICATION -> nr1.inmultire(nr2);
            case DIVISION -> nr1.impartire(nr2);
        };
    }

    //creez operatia
    private static Object parseOperation(String operator) {
        return switch (operator) {
            case "+" -> Operation.ADDITION;
            case "-" -> Operation.SUBTRACTION;
            case "*" -> Operation.MULTIPLICATION;
            case "/" -> Operation.DIVISION;
            default -> throw new IllegalArgumentException("Operator nevalid: " + operator);
        };
    }

    private static NumarComplex parseComplexNumber(String complexNumber) {
        //expresia regulata (SO) pt a afla partea re si im

        complexNumber = complexNumber.substring(0,complexNumber.length()-2);

        double re=0, im=0;
        String[] numere = complexNumber.split("[+-]");

        if(numere.length==2){
            re = Double.parseDouble(numere[0]);
            im = Double.parseDouble(numere[1]);
        } else {
            re = Double.parseDouble(numere[1]);
            im = Double.parseDouble(numere[2]);
        }

        String[] operatori = complexNumber.split("[0-9]+");

        if(operatori.length == 1 && operatori[0].equals("-"))
            im = im*(-1);

        else if(operatori.length==2){

            if(operatori[0].equals("-"))
                re = re*(-1);

            if(operatori[1].equals("-"))
                im = im*(-1);
        }

        return new NumarComplex(re,im);
    }

}
