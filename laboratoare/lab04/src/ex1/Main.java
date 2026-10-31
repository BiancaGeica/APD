package ex1;

public class Main {
    public static void main(String[] args) {
        int numCores = Runtime.getRuntime().availableProcessors();

        Thread[] threads = new Thread[numCores];
        for (int i = 0; i < numCores; i++) {
            threads[i] = new MyThread(i);

            threads[i].start();
        }

        try {
            for (int i = 0; i < numCores; i++) {
                threads[i].join();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
