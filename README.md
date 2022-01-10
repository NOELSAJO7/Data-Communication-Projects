# Data-Communication-Projects

1.Line Encoding:
Language used: C++. 
Libraries used: bits/stdc++ (for stl containers and code) ,graphics.h(for plotting digital signals).
Inputs : 
User can either generate random string of 0 and 1 or generate random string with some additional input like number of consecutive zeroes needed to be inserted and beginning ,end or at a particular position.	
User can select the encoding scheme to be applied; the program has specific functions for generating codes for different schemes(NRZI,NRZL,DIFFERENTIAL MANCHESTER,MANCHESTER ,AMI,SCRAMBLING(B8ZS and HDB3) ).
Output:
Since some of the schemes have 3 levels; I have used  0->0 , 1->1 and 2->-1 so that a common final encoding function can differentitate all three.
I have used the bar(){bar graph function} from graphics.h to generate the graphical output of input(above) and output(below).
It will display the Given signal code, line encoded signal code and graphical their plots respectively.
It also displays the longest palindromic sequence in given code and line encoded code. 
( 0--->0 , 1--->1 and 2--->-1 ).



2.  CRC(Cyclic Redundancy Check)
Language used: C++. 
Libraries used: bits/stdc++ (for stl containers and code) .
Inputs : 
User can  generate random string of 0 and 1 of length >=32 .which is tokenised to 16 bits.
Number of hops and their crossover probabilities 
Probability above which the error has to be generate in the bits.	


3. Hamming Code
Language used: C++. 
Libraries used: bits/stdc++ (for stl containers and code) .
Inputs : 
User can  generate random string of 0 and 1 of length >=16. Which is then tokenise to 4 bits.
Probability above which the error has to be generate in the bits.The error bit is selected randomly from the 7 bits.	
User can select whether to have single bit error or two bit error.However for two bit error we can only be assured of catching the error but not correcting it. 
