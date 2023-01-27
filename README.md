# ParallelAssign1

This approach uses the sqrt primality test to find all of the primes. The specific approach uses the fact that all primes greater than 3 are of the form 6k ± 1, so this method tests whether n is divisible by 2 or 3, then checks through all numbers of the form 6k ± 1 <= √n. This is 3 times faster than just checking all numbers through √n.
The threads are set up in a way so that they all do the same amount of work and they never do work on the same number, and they only ever lock themselves once.

Using only one thread this approach took aorund 20 seconds. While with the use of 8 threads it went down to 4 seconds, which is a 500% speed up.

To run this program all you have to do is download the cpp file, and then in the terminal run the command:
To compile: g++ <source file> -o <you name this file>
To execute: ./<name you gave>
