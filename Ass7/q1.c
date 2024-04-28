// Write a program where a parent process creates a shared memory and writes 1000 in a 
// variable in the shared memory before creating 2 children processes A and B. After that, the 
// parent waits for children termination and destroys the shared memory segment. Each child 
// process performs 5 iterations. Every iteration process A adds 200 to the shared variable, and 
// process B adds 100 to the shared variable. To help race conditions appear, both processes 
// sleep for a random amount of time between the time they read the shared variable and the 
// time they write back the shared variable after modification. 
// a. Could you predict the output of the program before execution? Explain your 
// answer. 
// b. Adjust the sleeping duration of one process (or both processes) to have a 
// different output. Could you predict this output? Explain your answer.




