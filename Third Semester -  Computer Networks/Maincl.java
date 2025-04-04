import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;


//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String args[]) throws Exception {
// Conectare la server
        Socket c = new Socket("127.0.0.1", 1234);
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        DataInputStream socketIn = new DataInputStream(c.getInputStream());
        DataOutputStream socketOut = new DataOutputStream(c.getOutputStream());

        List<Short> numbers = new ArrayList<>();
        short number;

        // Citirea numerelor până la introducerea valorii 0
        System.out.println("Introduceți numere (0 pentru a termina):");
        while (true) {
            System.out.print("Număr: ");
            number = Short.parseShort(reader.readLine()); // Citim ca short
            if (number == 0) {
                break; // Ieșim din ciclu dacă se introduce 0
            }
            numbers.add(number); // Adăugăm numărul în lista
        }

        // Trimiterea numărului de elemente
        socketOut.writeShort(numbers.size()); // Trimitem dimensiunea listei ca short

        // Trimiterea fiecărui număr din listă
        for (short num : numbers) {
            socketOut.writeShort(num); // Trimitem fiecare număr ca short
        }
        socketOut.flush();

        // Așteptăm răspunsul serverului (suma calculată)
        int result = socketIn.readUnsignedShort(); // Citim răspunsul ca short
        System.out.println("Suma primită de la server: " + result);

        // Închide resursele
        reader.close();
        socketIn.close();
        socketOut.close();
        c.close();
    }

}