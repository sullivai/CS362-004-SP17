/****************************************
** Aimee Sullivan (sullivai)
** CS362-400 Random Testing Quiz 2
** April 30, 2017
**

I developed the random tester using a very basic method of generating
pseudo-random numbers with the built-in library function rand().  Even 
though I am aware that this usually provides results with a skewed 
distribution, I left this simple implementation.

The first function, inputChar(), generates random characters within the 
ASCII range 32 - 125 (or ' ' to '}') inclusive, since this range encompasses
all the characters that are required to change the state value in the 
first 9 if statements.

The second function, inputString(), generates random characters in the 
same way as above, but using a much narrower range of characters (ASCII 
101-116 ('e'-'t')), which again is the only set required for the final
if statement which triggers the error.  This code uses the strdup library 
function to return a pointer to the string, per this answer on stackoverflow:
http://stackoverflow.com/a/43106294.  In particular, I did not want to 
start malloc'ing millions of strings that I may not manage to delete, and 
this seemed to be a very handy way to return the string from the function
without creating a huge memory leak.

While the state seems to get to 9 pretty quickly on all my test runs,
I find that getting the string correct can take some time.  One run of 
this test on the flip server found the error on iteration 
2,313,956, taking around two minutes to complete.  This could probably
be improved by using a more sophisticated PRNG method.
*/
