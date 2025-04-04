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
            System.out.print("Introduceti  caracterul: ");
            char caracter = (char) reader.read();

            // Trimit lungimea șirului la server
            int length = sir.length() + 1;
            sendUnsignedShort(length, socket);

            // Trimit șirul de caractere la server
            sendString(sir + "\0", socket);

            sendChar(caracter, socket);

            // Primesc numarul de aparitii si pozitiile de la server
            receivePositions(socket);
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

    //Trimit caracterul
    private static void sendChar(char caracter, Socket socket) throws IOException {
        DataOutputStream socketOut = new DataOutputStream(socket.getOutputStream());
        socketOut.writeByte((byte) caracter);  // Trimitem caracterul ca un singur octet
        socketOut.flush();
    }

    // Primesc numărul de spații de la server
    private static void receivePositions(Socket socket) throws IOException {
        DataInputStream socketIn = new DataInputStream(socket.getInputStream());

        int nrAparitii = socketIn.readUnsignedShort();
        System.out.println("Numarul de aparitii al caracterului: " + nrAparitii);

        for(int i = 0; i < nrAparitii; i++) {
            int position = socketIn.readUnsignedShort();
            System.out.println("Caracterul gasit la pozitia: " + position);
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
