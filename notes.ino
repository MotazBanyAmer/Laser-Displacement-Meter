/* check list
   - need to test all the function and hte HTTP work
   - somtimes a problem in action post or get, and no data receved after perofrming the action only OK. so we need to handle this with timeout.
      the problem could be due to low power supply
   - so the id in feed get is fixed for the value, we can use it to compare.
   - tempreture form moduleStatus_Byte in laser_def.h
   - need to add check done and error after init the HTTP, the HTTPINIT command sometimes give error because it already init
   - meybe if not using cid we can keep connected and get faster, test this
   - later, maybe to change the system to send and receive data as a stand alone and depend on feed key and other stuff to seperate data,
     this will help improving hte speed of the system.
   - make sure to handle errors, and success, so not to show success unless it really happened.
   - update battery online
   **********done**************
   add the xio key parameter on request

*/

/*  issues tracker
    ((1))
    ((2))
    ((3))
    ((4))
*/

/* Functions To Do
    read CSQ for debugging
    read COPs for debugging
    read IP

*/

/*features to do
   direct debugging mode
    - connect through the app or serial port, and debug with AT commands directly.
    - add AT commands library to the app
    -the app can control the req tiem also the getting time (maybe)
*/

/* Reminders
   next
   - try GET commands
   - try GET with multy values if you may
   - get console and other value
   - get temp from laser
   - upload temp
   - deal with console
   - handle data from op mode in the code
   - handle data form req time in the code
   -handle errors from action

   done
   - enable sending periodiclly
   - see what to do with get value from post

*/
