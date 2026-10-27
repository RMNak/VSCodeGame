package JavaExample;

//Create singleton class with thread safe
public class Singleton {
    private static Singleton instance;
    private Singleton() {
    }
    public static synchronized Singleton getInstance() {
        if (instance == null) {
            instance = new Singleton();
        }
        return instance;
    }

    public static void main(String[] args) {
        Singleton singleton = Singleton.getInstance();
        Singleton singleton1 = Singleton.getInstance();
        System.out.println(singleton == singleton1);
    }
}
 
/*
 In the above code, we have created a singleton class with a thread-safe implementation. We have used the synchronized keyword to make the getInstance() method thread-safe. 
 2. Using Double-Checked Locking 
 In the above example, we have used the synchronized keyword to make the getInstance() method thread-safe. But, the synchronized keyword is expensive and can reduce the performance of the application. 
 To avoid this, we can use the double-checked locking mechanism. In this mechanism, we check the instance variable twice. The first check is outside the synchronized block and the second check is inside the synchronized block. 
 If the instance is null, then only we create the instance inside the synchronized block. 
 Let’s see the implementation of the singleton class using the double-checked locking mechanism. */
