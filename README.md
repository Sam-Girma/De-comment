# De-comment
This c program does decomenting on behalf of the pre-processors.
The dfa design is as bellow.
![image](https://user-images.githubusercontent.com/93342851/200265043-a94ab539-d828-4f6e-9d8e-21922736720a.png)

This is the DFA design. There are 6 different states according to the DFA design for the decomment program. which are normal state, string literal state, character literal state, transition to comment state, comment state, and return from comment state.

The normal state is the beginning of the state while reading the c code. It puts every character entered into the output c file except:
1. When the ‘/’ character is encountered since it is a way to enter into the comment state the state is changed to transition to the comment state. Then:
    a. If "*" is encountered in the transition to comment state the state changes to comment state. And stops putting characters as the program is supposed to do. 
    b. If "/" is encountered it remains in transition to the comment state putting the previous "/" character encountered. 
    c. If any character other than "*" and "/" is encountered, "/" and the entered character are put and the state is changed to normal state.
   
2. In the comment state characters are not put to the output file. When the "*" character is encountered the state changes to return from the comment state. Then 
    a. If "/" is encountered the state is changed to the normal state and will begin putting characters as specified in 1. 
    b. if ‘*’ is encountered the state remains in return from the comment state since if ‘/’ is encountered in the next iteration the state could change to normal state. 
    c. If any character other than the "/" and "*" is encountered the state returns to the comment state.

3. When (‘\” ’) is encountered the state changes to the string literal state. Here it puts every character encountered in the state. The state checks for (‘\” ’) to be encountered again to return to the normal state. Transition to the string literal state is only possible from the normal state.

4. When (‘ \’ ’) is encountered the state changes to the character literal state. Here it puts every character encountered in the state. The state checks for (‘ \’ ’) to be encountered again to return to the normal state. And likewise, the transition to the character literal state is only possible from the normal state.
