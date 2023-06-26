public class Main {
    public static void main(String[] args) {
        
        ReadText reader = new ReadText("ubicacion-tesoro.txt");
        int treasure = reader.getTreasureLen();
        String map = reader.obtenerString();
        int[][] M = parsearMatriz(map);
        Matriz matrix = new Matriz(M, treasure, 1, 1, 0);
        matrix.setStart();
        
        matrix.start();
        try {
            matrix.join();
        } catch (InterruptedException e) {}
    }

    private static int[][] parsearMatriz(String map) {
        String[] filas = map.split("\\],\\[");
        int n = filas.length;
        int m = filas[0].split(",").length;
        int[][] matriz = new int[n][m];

        for (int i = 0; i < n; i++) {
            String fila = filas[i].replaceAll("\\[|\\]", "");
            String[] elementos = fila.split(",");
            for (int j = 0; j < m; j++) {
                String elemento = elementos[j].trim();
                if (elemento.equals("x")) {
                    matriz[i][j] = 1;  // Transformar "x" a 1
                } else {
                    matriz[i][j] = Integer.parseInt(elemento);
                }
            }
        }
        return matriz;
    }
}

