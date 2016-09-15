# dining-philosophers
College work to solve the problem of the dining philosophers using semaphores.

**Dining Philosophers problem:**<br>
https://en.wikipedia.org/wiki/Dining_philosophers_problem

**Solution:**<br>
There are two solutions for the deadlock problem:<br>
- *diningPhilosophersSemaphores.c*:
The act of grabing the left and the right fork is atomic. 

- *diningPhilosophersSemaphores-v2.c*: The first philosopher (position 0) always grabs the left fork first. The rest of them grabs the right one first. This breaks the cicle and avoids the deadlock.

**Compile and run**<br>
  `gcc diningPhilosophersSemaphores.c -lpthread && ./a.out <number_of_philosophers>`
