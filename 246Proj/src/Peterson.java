// Did Peterson's solution work?
// yes

/** A java program for trying out Peterson's algorithm. */
public class Peterson {
  /** A variable visible to both threads. */
  private static volatile int sharedVar = 0;
  
  /** A variable to tell the threads when to stop rnning. */
  private static volatile boolean running = true;
 
  // Any state you need to implement peterson's solution.  Be sure
  // you mark these variables as volatile. 

  // ...
  private static volatile int fl = 0;
  
  /** A thread to increment and then decrement a shared variable as
      fast as it can. */
  static class Thread1 implements Runnable {
    public void run() {
      while ( running ) {

        // Entry code for Peterson's solution.

        // ...
        while( fl == 1 )
            ;

        // This is like the critical section, access the shared variable.
        sharedVar++;
        sharedVar--;

        // Exit code for Peterson's solution.

        // ...
        fl = 1;

        // This is the remainder section. It's empty, but that's not typical.
        // Normally, we'd expect threads to spend most of their time in
        // the remainder section.  But, for this example, we want to
	// see if we get a race condition, so it's best to go right back
  	// into the ciritical section.

      } 
    }
  }

  /** A thread to decrement and then increment a shared variable as
      fast as it can. */
  static class Thread2 implements Runnable {
    public void run() {
      while ( running ) {

        // Entry code for Peterson's solution.

        // ...
        while ( fl == 0 )
            ;

        // This is like the critical section, access the shared variable.
        sharedVar--;
        sharedVar++;

        // Exit code for Peterson's solution.

        // ...
        fl = 0;

        // This is the remainder section. Again, empty.

      }
    }
  }

  public static void main( String[] args ) {
    // Make a thread for each of our Runnables
    Thread t1 = new Thread( new Thread1() );
    Thread t2 = new Thread( new Thread2() );
    t1.start();
    t2.start();

    try {
      // Wait a few seconds.
      Thread.sleep( 10000 );

      // Tell the threads to stop.
      running = false;

      // Wait for our threads to finish.
      t1.join();
      t2.join();
    } catch ( InterruptedException e ) {
      System.out.println( "Interrupted!" );
    }

    // See what's in the shared variable.
    System.out.println( "sharedVar: " + sharedVar );
  }
}
