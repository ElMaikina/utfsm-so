public class Matriz extends Thread {
    private int[][] matrix;
    private int len;
    private int treasure;
    private int x;
    private int y;
    private volatile long start;
    private volatile long finish;

    public void setMatrix(int[][] m) {
        this.matrix = m;
    }
    
    public void setLen(int l) {
        this.len = l;
    }
    
    public void setX(int x) {
        this.x = x;
    }
    
    public void setY(int y) {
        this.y = y;
    }
    
    public void setTresure(int t) {
        this.treasure = t;
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
    
    public int getTresure() {
        return treasure;
    }
    
    public int getX() {
        return x;
    }
    
    public int getY() {
        return y;
    }
    

    public Matriz(int[][] M, int tresure, int x, int y, long t) {
        int width = M.length;
        int height = M[0].length;
        
        if (width != height) {
            throw new IllegalArgumentException("La matriz debe ser cuadrada.");
        }

        this.setMatrix(M);
        this.setLen(width);
        this.setTresure(tresure);
        this.setX(x);
        this.setY(y);
        this.setStart(t);
        this.setFinish();
    }
    public void printMatrix() {
        int[][] M = getMatrix();

        for (int[] fila : M) {
            for (int elemento : fila) {
                System.out.print(elemento + " ");
            }
            System.out.println();
        }
        System.out.println();
    }

    public void divideMatrix() {
        int[][] oldmatrix = getMatrix();
        
        int half = getLen() / 2;
        int len = getLen();
        int tresure = getTresure();
        
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
            int x = this.getX();
            int y = this.getY();
            long t = this.getStart();

            Matriz result1 = new Matriz(matrix1, tresure, x, y, t);
            Matriz result2 = new Matriz(matrix2, tresure, x+half, y, t);
            Matriz result3 = new Matriz(matrix3, tresure, x, y+half, t);
            Matriz result4 = new Matriz(matrix4, tresure, x+half, y+half, t);
            
            result1.start();
            result2.start();
            result3.start();
            result4.start();
            
            try {
                result1.join();
                result2.join();
                result3.join();
                result4.join();
            } catch (InterruptedException e) {}        
        } else {
            this.searchTresure(x, y);
        }   
        
    }
    public void run() {
        divideMatrix();
    }
    public void searchTresure(int x, int y) {
        for (int i = 0; i < this.getLen(); i++){
            for (int j = 0; j < this.getLen(); j++){
                if (this.matrix[i][j] == 1) {
                    int fila = this.getX()+i;
                    int columna = this.getY()+j;
                    this.setFinish();
                    System.out.println("fila " + fila + ", columna " + columna);
                    this.getTime();
                    return;
                }
            }
        }
    }
}
