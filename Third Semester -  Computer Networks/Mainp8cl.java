import java.io.*;
import java.net.*;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.Socket;

public class Main {
    private static final String SERVER_ADDRESS = "127.0.0.1"; // IP-ul serverului
    private static final int SERVER_PORT = 1234; // Portul serverului
    private static final int UNSIGNED_SHORT_MAX_VALUE = 65535;
    private static final int UNSIGNED_SHORT_MIN_VALUE = 0;

    public static void main(String[] args) {
        Socket socket = null;
        BufferedReader reader = null;

        try {
            reader = new BufferedReader(new InputStreamReader(System.in));
            socket = new Socket(SERVER_ADDRESS, SERVER_PORT);

            // Citim primul șir de numere de la utilizator
            System.out.print("Introduceți primul șir de numere (separate prin spațiu): ");
            String sir1 = reader.readLine();
            int[] numbers1 = parseInput(sir1);

            // Citim al doilea șir de numere de la utilizator
            System.out.print("Introduceți al doilea șir de numere (separate prin spațiu): ");
            String sir2 = reader.readLine();
            int[] numbers2 = parseInput(sir2);

            // Trimit șirurile și lungimea lor către server
            writeToSocket(numbers1, socket);
            writeToSocket(numbers2, socket);

            // Citire rezultat (numere comune) de la server
            readFromSocket(socket);

        } catch (IOException e) {
            System.err.println("A apărut o eroare: " + e.getMessage());
        } finally {
            closeStreams(socket, reader);
        }
    }

    private static int[] parseInput(String input) {
        String[] numbers = input.split(" ");
        int[] numbersArray = new int[numbers.length];
        for (int i = 0; i < numbers.length; i++) {
            numbersArray[i] = Integer.parseInt(numbers[i]);
            if (numbersArray[i] < UNSIGNED_SHORT_MIN_VALUE || numbersArray[i] > UNSIGNED_SHORT_MAX_VALUE) {
                throw new IllegalArgumentException("Numărul " + numbers[i] + " nu este un unsigned short [0..65535]!");
            }
        }
        return numbersArray;
    }

    private static void writeToSocket(int[] numbers, Socket c) throws IOException {
        DataOutputStream socketOut = new DataOutputStream(c.getOutputStream());

        // Trimit lungimea șirului ca un short (2 bytes)
        socketOut.writeShort(numbers.length);

        // Trimit șirul propriu-zis
        for (int number : numbers) {
            socketOut.writeShort(number);
        }
        socketOut.flush(); // Asigur că datele au fost trimise
    }

    private static void readFromSocket(Socket c) throws IOException {
        DataInputStream socketIn = new DataInputStream(c.getInputStream());

        // Citim lungimea șirului rezultat (numere comune)
        int resultSize = socketIn.readUnsignedShort();
        System.out.println("Lungimea sirului rezultat: " + resultSize);

        // Citim numerele comune
        if (resultSize > 0) {
            int[] result = new int[resultSize];
            for (int i = 0; i < resultSize; i++) {
                // Citim fiecare număr ca unsigned short și îl stocăm
                result[i] = socketIn.readUnsignedShort();
            }

            System.out.print("Numerele comune sunt: ");
            for (int num : result) {
                System.out.print(num + " ");
            }
            System.out.println();
        } else {
            System.out.println("Nu exista numere comune.");
        }
    }

    private static void closeStreams(Socket socket, BufferedReader reader) {
        try {
            if (socket != null) {
                socket.close();
            }
            if (reader != null) {
                reader.close();
            }
        } catch (IOException e) {
            System.err.println("Nu s-a putut închide socket-ul sau reader-ul!");
        }
    }
}
