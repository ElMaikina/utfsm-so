import java.lang.System;
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
        this.finish = System.currentTimeMillis();;
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

    public void divideMatrix(int tresure, int x, int y) {
        int[][] oldmatrix = getMatrix();
        
        int half = getLen() / 2;
        int len = getLen();

        if (len > tresure) {
            
            // Obtener primer cuadrante
            int[][] matrix1 = new int[half][half];
            int[][] matrix2 = new int[half][half];
            int[][] matrix3 = new int[half][half];
            int[][] matrix4 = new int[half][half];
            
            for (int i = 0; i < half; i++) {
                for (int j = 0; j < half; j++) {
                    matrix1[i][j] = oldmatrix[i][j];
                    matrix2[i][j] = oldmatrix[i+half][j];
                    matrix3[i][j] = oldmatrix[i][j+half];
                    matrix4[i][j] = oldmatrix[i+half][j+half];
                }
            }
            long t = this.getStart();
            Matriz result1 = new Matriz(matrix1, tresure, t);
            Matriz result2 = new Matriz(matrix2, tresure, t);
            Matriz result3 = new Matriz(matrix3, tresure, t);
            Matriz result4 = new Matriz(matrix4, tresure, t);

            result1.divideMatrix(tresure, x, y);
            result2.divideMatrix(tresure, x+half, y);
            result3.divideMatrix(tresure, x, y+half);
            result4.divideMatrix(tresure, x+half, y+half);
        }
        else {
            this.searchTresure(x, y);
        }        
    }
    public void searchTresure(int x, int y) {
        for (int i = 0; i < this.getLen(); i++){
            for (int j = 0; j < this.getLen(); j++){
                if (this.matrix[i][j] == 1) {
                    int fila = x+i;
                    int columna = y+j;
                    this.setFinish();
                    System.out.println("fila " + fila + ", columna " + columna);
                    this.getTime();
                    return;
                }
            }
        }
    }
}
