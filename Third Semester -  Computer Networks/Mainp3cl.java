import java.io.*;
import java.net.*;

public class Main {
    private static final String SERVER_ADDRESS = "127.0.0.1";
    private static final int SERVER_PORT = 1234;

    public static void main(String[] args) {
        Socket socket = null;
        BufferedReader reader = null;
        try {
            reader = new BufferedReader(new InputStreamReader(System.in));
            socket = new Socket(SERVER_ADDRESS, SERVER_PORT);

            // Citesc șirul de la tastatură
            System.out.print("Introduceti sirul de caractere: ");
            String sir = reader.readLine();

            // Trimit lungimea șirului la server
            int length = sir.length() + 1;
            sendUnsignedShort(length, socket);

            // Trimit șirul de caractere la server
            sendString(sir + "\0", socket);

            // Primesc sirul oglindit de la server
            receiveString(socket, length);
        } catch (IOException e) {
            System.err.println("Caught exception: " + e.getMessage());
        } finally {
            closeStreams(socket, reader);
        }
    }

    // Trimit unsigned short către server
    private static void sendUnsignedShort(int numar, Socket socket) throws IOException {
        DataOutputStream socketOut = new DataOutputStream(socket.getOutputStream());
        socketOut.writeShort(numar);  // Trimit lungimea șirului
        socketOut.flush();
    }

    // Trimit șirul de caractere ca octeți ASCII
    private static void sendString(String string, Socket socket) throws IOException {
        DataOutputStream socketOut = new DataOutputStream(socket.getOutputStream());
        socketOut.writeBytes(string);  // Trimit fiecare caracter ca un singur octet
        socketOut.flush();
    }

    // Primesc numărul de spații de la server
    private static void receiveString(Socket socket, int length) throws IOException {
        DataInputStream socketIn = new DataInputStream(socket.getInputStream());

        //citesc sirul oglindit din server
        byte[] buffer = new byte[length];
        int bytesRead = socketIn.read(buffer, 0, length);

        // Convertim buffer-ul la String și afișăm rezultatul
        if (bytesRead > 0) {
            String sirOglindit = new String(buffer, 0, bytesRead - 1);  // Eliminăm terminatorul de linie '\0'
            System.out.println("Șirul oglindit primit de la server: " + sirOglindit);
        } else {
            System.out.println("Eroare la primirea șirului oglindit de la server.");
        }
    }

    // Închid conexiunea și resursele
    private static void closeStreams(Socket socket, BufferedReader reader) {
        if (socket != null) {
            try {
                socket.close();
            } catch (IOException e) {
                System.err.println("Could not close socket!");
            }
        }
        if (reader != null) {
            try {
                reader.close();
            } catch (IOException e) {
                System.err.println("Could not close reader!");
            }
        }
    }
}
