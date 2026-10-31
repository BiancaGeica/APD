package ex1;

public class MyThread extends Thread{
    private final int id;

    public MyThread(int id) {
        super();
        this.id = id;
    }

    @Override //
    public void run() {
        System.out.println("Hello from thread " + id);
    }
}
