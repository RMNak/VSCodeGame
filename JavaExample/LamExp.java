import java.util.ArrayList;
import java.util.List;

class AlternativeDisplay {

    volatile static int counter = 1;
    int limit = 10;
    List<Integer> list = new ArrayList<Integer>();

    AlternativeDisplay(int limit) {
        this.limit = limit;
    }

    public synchronized void evenDisplay() {
        
        while(counter < limit) {
            if(counter % 2 == 0) {
                list.add(counter);
                //System.out.println("Even: " + counter);
                counter++;
                notify();
            } else {
                try {
                    wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public synchronized void oddDisplay() {
        
        while(counter < limit) {
            if(counter % 2 != 0) {
                list.add(counter);
                //System.out.println("Odd: " + counter);
                counter++;
                notify();
            } else {
                try {
                    wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void main(String[] args) {
        AlternativeDisplay display = new AlternativeDisplay(20);
        Thread t1 = new Thread(new Runnable() {
            @Override
            public void run() {
                display.evenDisplay();
            }
        });

        Thread t2 = new Thread(new Runnable() {
            @Override
            public void run() {
                display.oddDisplay();
            }
        });

        t1.start();
        t2.start();

        while (t1.isAlive()) {
            continue;
        }

       for (Integer x : display.list) {
           System.out.println(x); 
       }
    }

//Namede vstring variabvle

String converExp = "";

    NextRecu(BoaoleanEx e)
    {
        //tree 
        if(e == null)
        {
            return;
        }

        converExp += e.left;

    }
}   