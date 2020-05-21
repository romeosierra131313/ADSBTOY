# ADSBTOY
ADSB message converter


An incomplete ADSB hex message converter , meant only as an exercise in understanding . 


features : 
>> callsign decoding
>>position decoding (using cpr)
>> flighht level 
>> heading 
>> airspeed (GroundSpeed,TAS and IAS)



missing or todo:



>> parity check
>> adsb version checking 
>> accuracy and status decoding 

The information here was based heavily , or rather , almost entirely on the book "The 1090Mhz riddle" by Junzi Sun.
In hindsight , the program flow and processing should have been separated from the start . Message and message information,
should be separated from the actual decoding solely due the the position type reports which in some cases require 2 messages.
Lastly , only testing on the few codes presented were done , as a result , edge cases and other conditions were not tested ...
also with the exception of a few obvious errors which can occur the amount of error handling is minimum. 

I wonder if it were possible to work directly with the bits using bitshifting in C++ instead of the amount of often unnessacary type conversions 

Limitations:
>> the main function has linux terminal specific commands i.e: 'system("read")' which can be replaced to 'system("PAUSE")' to work with windows .

built with and on :
gcc (SUSE Linux) 9.3.1 20200406 [revision 6db837a5288ee3ca5ec504fbd5a765817e556ac2]
