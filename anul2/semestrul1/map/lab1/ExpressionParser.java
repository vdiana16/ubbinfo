import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ExpressionParser {
    public ComplexExpression parseExpression(String expression) {
        //2+5*i + 8+7*i
        String[] components = expression.split(" ");

        //verific daca am cel putin un numar complex
        if(components.length < 3){
            throw new IllegalArgumentException("Expresie incorecta, trebuie sa contina cel putin trei elemente ");
        }

        //verific daca operatorii sunt asezati corect
        String op = components[1];
        for(int i = 3; i < components.length; i += 2){
            if(!components[i].equals(op)){
                throw new IllegalArgumentException("Expresie incorecta, operatori asezati intr-o ordine gresita");
            }
        }


        Operation operation = tipOperation(op);
        ArrayList<NumarComplex> args = parseArguments(components);

        ExpressionFactory factory = ExpressionFactory.getInstance();
        return factory.createComplexExpression(operation, args);
    }

    private Operation tipOperation(String op) {
        switch (op){
            case "+":
                return Operation.ADDITION;
            case "-":
                return Operation.SUBSTRACTION;
            case "*":
                return Operation.MULTIPLICATION;
            case "/":
                return Operation.DIVISION;
            default:
                throw new IllegalArgumentException("Operatie incorrecta");
        }
    }

    private ArrayList<NumarComplex> parseArguments(String[] components) {
        ArrayList<NumarComplex> args = new ArrayList<>();
        for (int i = 0; i < components.length; i += 2){
           double re = 0, im = 0;

           // verifica daca termenul curent reprezinta un numa complex
           if(!components[i].contains("i")){
               throw new IllegalArgumentException("Numarul nu este complex");
           }

           //valideaza daca termenul curent are formatul unui numar complex
           Pattern pattern = Pattern.compile("[^0-9+\\-*i]");
           Matcher matcher = pattern.matcher(components[i]);

           if (matcher.find()) {
               throw new IllegalArgumentException("Expresia nu reprezinta un numar complex");
           }

           //separa partea reala de partea imaginara
            // 2+3*i => ["2","+3*i"]
           String[] comps = components[i].split("(?=[+-])");
           for (String term : comps){
               //elimin spatiile care sunt in plus
               term = term.trim();

               if(term.endsWith("i")){
                   //elimin i-ul
                   String imgp = term.substring(0, term.length() - 1).trim();
                   if(imgp.isEmpty() || imgp.equals("+")) {
                       im = 1;
                   } else if (imgp.equals("-")) {
                       im = -1;
                   } else if (imgp.contains("*")) {
                       imgp = imgp.replaceAll("[^\\d-+]","");
                       im = Double.parseDouble(imgp);
                   } else {
                       throw new IllegalArgumentException("Parte imaginara incorecta!");
                   }
               } else {
                   re = Double.parseDouble(term);
               }
           }
           args.add(new NumarComplex(re, im));
        }
        return args;
    }
}
