import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class ReadText {
    private String nameText;
    private String linea1;
    private String linea2;
    private String linea3;

    public ReadText(String nombreArchivo) {
        if (nombreArchivo == null) {
            throw new IllegalArgumentException("El nombre del archivo no puede ser nulo.");
        }
        this.nameText = nombreArchivo;
        leerArchivo();
    }

    private void leerArchivo() {
        try (BufferedReader br = new BufferedReader(new FileReader(nameText))) {
            linea1 = br.readLine();
            linea2 = br.readLine();
            linea3 = br.readLine();
        } catch (IOException e) {
            e.printStackTrace();
            // Aquí podrías lanzar una excepción personalizada o manejar el error de otra forma apropiada.
        }
    }

    public int getMatrixLen() {
        return Integer.parseInt(linea1);
    }

    public int getTreasureLen() {
        return Integer.parseInt(linea2);
    }

    public String obtenerString() {
        return linea3;
    }
}

