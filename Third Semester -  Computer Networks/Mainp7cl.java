import java.io.*;
import java.net.*;

public class Main {
    private static final String SERVER_ADDRESS = "127.0.0.1";
    private static final int SERVER_PORT = 1234;
    private static final int UNSIGNED_SHORT_MAX_VALUE = 65535;
    private static final int UNSIGNED_SHORT_MIN_VALUE = 0;

    public static void main(String[] args) {
        Socket socket = null;
        BufferedReader reader = null;
        try {
            reader = new BufferedReader(new InputStreamReader(System.in));
            socket = new Socket(SERVER_ADDRESS, SERVER_PORT);

            // Citesc șirul de la tastatură
            System.out.print("Introduceti sirul de caractere: ");
            String sir = reader.readLine();
           
            //Citesc pozitia
            int poz = readUnsignedShort("Pozitia = ", reader);

            //Citesc lungimea
            int l = readUnsignedShort("Lungime = ", reader);

            // Trimit lungimea șirului la server
            int length = sir.length() + 1;
            sendUnsignedShort(length, socket);

            // Trimit șirul de caractere la server
            sendString(sir + "\0", socket);

            // Trimit pozitia la server
            sendUnsignedShort(poz, socket);

            // Trimit lungimea la server
            sendUnsignedShort(l, socket);

            // Primesc subsirul
            receiveSubstring(socket);
        } catch (IOException e) {
            System.err.println("Caught exception: " + e.getMessage());
        } finally {
            closeStreams(socket, reader);
        }
    }

    // Citesc unsigned short de la tastatura
    private static int readUnsignedShort(String message, BufferedReader reader) throws IOException {
        int unsignedShortNumber = 0;
        System.out.print(message);
        try {
            unsignedShortNumber = Integer.parseInt(reader.readLine());
            if (unsignedShortNumber < UNSIGNED_SHORT_MIN_VALUE || unsignedShortNumber > UNSIGNED_SHORT_MAX_VALUE) {
                throw new IllegalArgumentException("The given number must be unsigned short [0..65535]!");
            }
        } catch (NumberFormatException e) {
            System.err.println("The given input is not an integer!");
        }
        return unsignedShortNumber;
    }


    // Trimit unsigned short către server
    private static void sendUnsignedShort(int numar, Socket socket) throws IOException {
        DataOutputStream socketOut = new DataOutputStream(socket.getOutputStream());
        socketOut.writeShort(numar);
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

    // Primesc subsirul
    private static void receiveSubstring(Socket socket) throws IOException {
        DataInputStream socketIn = new DataInputStream(socket.getInputStream());

        int lg = socketIn.readUnsignedShort();

        byte[] buffer = new byte[lg];
        int bytesRead = socketIn.read(buffer, 0, lg);

        // Convertim buffer-ul la String și afișăm rezultatul
        if (bytesRead > 0) {
            String sirinterclasat = new String(buffer, 0, bytesRead - 1);  // Eliminăm terminatorul de linie '\0'
            System.out.println("Subsirul primit de la server: " + sirinterclasat);
        } else {
            System.out.println("Eroare la primirea subsirului de la server.");
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
