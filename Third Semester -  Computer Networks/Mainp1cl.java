import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.net.*;
import java.io.*;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
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

                // Citim șirul de caractere de la utilizator
                System.out.print("Introduceți șirul de numere: ");
                String sir = reader.readLine();
                String[] numbers = sir.split(" ");

                //Convertesc sirul in numere intregi
                int[] numbersArray = new int[numbers.length];
                for(int i = 0; i < numbers.length; i++) {
                    numbersArray[i] = Integer.parseInt(numbers[i]);
                    if (numbersArray[i] < UNSIGNED_SHORT_MIN_VALUE || numbersArray[i] > UNSIGNED_SHORT_MAX_VALUE) {
                        throw new IllegalArgumentException("Numărul " + numbers[i] + " nu este un unsigned short [0..65535]!");
                    }
                }

                // Trimit șirul și lungimea lui către server
                writeToSocket(numbersArray, socket);

                // Citire rezultat (suma) de la server
                readFromSocket(socket);

            } catch (IOException e) {
                System.err.println("A apărut o eroare: " + e.getMessage());
            } finally {
                closeStreams(socket, reader);
            }
        }

        private static void writeToSocket(int[] numbers, Socket c) throws IOException {
            DataOutputStream socketOut = new DataOutputStream(c.getOutputStream());

            // Trimit lungimea șirului ca un short (2 bytes)
            socketOut.writeShort(numbers.length);

            // Trimit șirul propriu-zis
            for(int number: numbers) {
                socketOut.writeShort(number);
            }
            socketOut.flush(); //Ma asigur ca datele au fost trimise
        }

        private static void readFromSocket(Socket c) throws IOException {
            DataInputStream socketIn = new DataInputStream(c.getInputStream());

            // Citim suma trimisa de la server (ca short)
            int sum = socketIn.readUnsignedShort();
            System.out.println("Suma primita de la server este: " + sum);
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