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
        Socket socket = new Socket("127.0.0.1", 1234);
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        DataInputStream socketIn = new DataInputStream(socket.getInputStream());
        DataOutputStream socketOut = new DataOutputStream(socket.getOutputStream());

        // Citirea șirului complet de numere
        System.out.println("Introduceți numere separate prin spațiu (0 pentru a termina):");
        String inputLine = reader.readLine();

        // Împărțirea șirului în numere individuale
        String[] inputNumbers = inputLine.trim().split("\\s+"); // Împarte după spațiu
        short[] numbers = new short[inputNumbers.length];
        int count = 0;

        // Conversia fiecărui număr la `short` și numărarea acestora
        for (String numStr : inputNumbers) {
            short num = Short.parseShort(numStr); // Conversie la short
            numbers[count++] = num;
            if (num == 0) { // Oprim la primul 0 (dacă există)
                break;
            }
        }

        // Trimiterea numărului de elemente și a fiecărui număr din listă
        socketOut.writeShort(count); // Trimitem dimensiunea listei ca short
        for (int i = 0; i < count; i++) {
            socketOut.writeShort(numbers[i]); // Trimitem fiecare număr ca short
        }
        socketOut.flush();

        // Așteptăm răspunsul serverului (suma calculată)
        int result = socketIn.readUnsignedShort(); // Citim răspunsul ca short
        System.out.println("Suma primită de la server: " + result);

        // Închide resursele
        reader.close();
        socketIn.close();
        socketOut.close();
        socket.close();

    }

}