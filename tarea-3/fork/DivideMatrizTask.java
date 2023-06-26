import java.util.concurrent.RecursiveAction;

public class DivideMatrizTask extends RecursiveAction {
    private Matriz matriz;
    private int tresure;
    private int x;
    private int y;
    private int startX;
    private int startY;

    public DivideMatrizTask(Matriz matriz, int tresure, int x, int y, int startX, int startY) {
        this.matriz = matriz;
        this.tresure = tresure;
        this.x = x;
        this.y = y;
        this.startX = startX;
        this.startY = startY;
    }

    @Override
    protected void compute() {
        int[][] oldmatrix = matriz.getMatrix();
        int half = matriz.getLen() / 2;
        int len = matriz.getLen();

        if (len > tresure) {
            int[][] matrix1 = new int[half][half];
            int[][] matrix2 = new int[half][half];
            int[][] matrix3 = new int[half][half];
            int[][] matrix4 = new int[half][half];

            for (int i = 0; i < half; i++) {
                for (int j = 0; j < half; j++) {
                    matrix1[i][j] = oldmatrix[i][j];
                    matrix2[i][j] = oldmatrix[i + half][j];
                    matrix3[i][j] = oldmatrix[i][j + half];
                    matrix4[i][j] = oldmatrix[i + half][j + half];
                }
            }

            Matriz result1 = new Matriz(matrix1, tresure, matriz.getStart());
            Matriz result2 = new Matriz(matrix2, tresure, matriz.getStart());
            Matriz result3 = new Matriz(matrix3, tresure, matriz.getStart());
            Matriz result4 = new Matriz(matrix4, tresure, matriz.getStart());

            DivideMatrizTask task1 = new DivideMatrizTask(result1, tresure, x, y, startX, startY);
            DivideMatrizTask task2 = new DivideMatrizTask(result2, tresure, x + half, y, startX + half, startY);
            DivideMatrizTask task3 = new DivideMatrizTask(result3, tresure, x, y + half, startX, startY + half);
            DivideMatrizTask task4 = new DivideMatrizTask(result4, tresure, x + half, y + half, startX + half, startY + half);

            invokeAll(task1, task2, task3, task4);
        } else {
            matriz.searchTresure(startX, startY);
        }
    }
}
