import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.Socket;


//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String args[]) throws Exception {
        Socket c = new Socket("127.0.0.1", 1234);
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        DataInputStream socketIn = new DataInputStream(c.getInputStream());
        DataOutputStream socketOut = new DataOutputStream(c.getOutputStream());

        System.out.println("Introduceți numere (0 pentru a termina):");
        short number;  // folosim short in loc de int

        // Citește și trimite numerele până la introducerea valorii 0
        while (true) {
            System.out.print("Număr: ");
            number = Short.parseShort(reader.readLine());  // Citim și convertim la short

            // Trimite numărul la server
            socketOut.writeShort(number);  // Trimite ca short (2 bytes)
            socketOut.flush();

            // Oprește bucla dacă numărul introdus este 0
            if (number == 0) {
                break;
            }
        }

        // Așteaptă răspunsul serverului
        int response = socketIn.readUnsignedShort();  // Citim răspunsul ca short
        System.out.println("Răspuns de la server: " + response);

        // Închide resursele
        reader.close();
        socketIn.close();
        socketOut.close();
        c.close();
    }

}