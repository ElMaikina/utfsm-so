public class Matriz {
    private int[][] matrix;
    private int len;
    private long start;
    private long finish;

    public void setMatrix(int[][] m) {
        this.matrix = m;
    }

    public void setLen(int l) {
        this.len = l;
    }

    public void setStart() {
        this.start = System.currentTimeMillis();
    }

    public void setStart(long time) {
        this.start = time;
    }

    public long getStart() {
        return start;
    }

    public void setFinish() {
        this.finish = System.currentTimeMillis();
    }

    public void getTime() {
        long time = finish - start;
        System.out.println("Tiempo de ejecucion: " + time + " ms");
    }

    public int[][] getMatrix() {
        return matrix;
    }

    public int getLen() {
        return len;
    }

    public Matriz(int[][] M, int tresure, long t) {
        int width = M.length;
        int height = M[0].length;

        if (width != height) {
            throw new IllegalArgumentException("La matriz debe ser cuadrada.");
        }

        setMatrix(M);
        setLen(width);
        setStart(t);
    }

    public void printMatrix() {
        int[][] M = getMatrix();

        for (int[] fila : M) {
            for (int elemento : fila) {
                System.out.print(elemento + " ");
            }
            System.out.println();
        }
    }

    public void searchTresure(int x, int y) {
        boolean encontrado = false;
        for (int i = 0; i < this.getLen(); i++) {
            for (int j = 0; j < this.getLen(); j++) {
                if (this.matrix[i][j] == 1) {
                    int fila = x + i + 1;
                    int columna = y + j + 1;
                    System.out.println("fila " + fila + ", columna " + columna);
                    encontrado = true;
                    break;
                }
            }
            if (encontrado) {
                break;
            }
        }
        setFinish();  // Establecer el tiempo de finalización
        this.getTime();
    }
}
