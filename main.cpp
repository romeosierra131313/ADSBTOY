
#include <iostream>
#include <sstream> 
#include <bitset>
#include <cstring>
#include <math.h>  

#include <iomanip> 
#define PI 3.1415926535



const float   dLe =  6.00000000F;
const float   dLo =  6.10169492F;
const uint16_t NZ = 15;
std::string RAW = "";
std::bitset<112> mybitset = 0;
int DF = 0; //////DownLinkFormat///
int CA = 0 ; ////Capablity/////
std::string ICAO = "";
int TC = 0;
std::bitset<3> EC = 0;
std::bitset<51> DATABLOCK = 0;
std::bitset<24> PARITY = 0;

std::string RAW2 = "";
std::bitset<112> mybitset2 = 0;
int DF2 = 0; //////DownLinkFormat///
int CA2 = 0 ; ////Capablity/////
std::string ICAO2 = "";
int TC2 = 0;
std::bitset<3> EC2 = 0;
std::bitset<51> DATABLOCK2 = 0;
std::bitset<24> PARITY2 = 0;

char charMap[] ={'#','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                 '#','#','#','#','#','_','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','0','1','2','3','4','5',
                 '6','7','8','9','#','#','#','#','#','#'};


                 
int velocityFormula(int sign,int number ){
    int result = 0;
        if(sign == 1){ result = -(number - 1); 
    }else{result = number - 1; }    
return result;    
    
}                 
                 
int processAsAirVel(std::bitset<51> bs)
{
    std::string data = "";
    std::string converted = "";
    data = bs.to_string();
/*splitting data */    
    ////////extract Sub-type/////////
    std::bitset<3> mySt(data,0,3);
    int St = mySt.to_ulong();
    std::cout<< St <<"  --- Subtype" <<std::endl;  
    if(St == 1){
    ////////extract Intent change flag/////////
    std::bitset<1> IC(data,3,1);
    std::cout<< IC <<"  --- Intent Change Flag" <<std::endl;    
    ////////extract Reserved-A/////////
    std::bitset<1> RESV_A(data,4,1);
    std::cout<< RESV_A <<"  --- Reserved-A" <<std::endl;  
     ////////extract Velocity uncertainty (NAC)/////////
    std::bitset<3> NAC(data,5,3);
    std::cout<< NAC <<"  --- Velocity uncertainty (NAC)" <<std::endl; 
    ////////extract  East-West velocity sign/////////
    std::bitset<1> S_ew(data,8,1);
    std::cout<< S_ew <<"  --- East-West velocity sign(S_ew)" <<std::endl; 
    ////////extract  East-West velocity/////////
    std::bitset<10> V_ew(data,9,10);
    std::cout<< V_ew <<"  --- East-West velocity(V_ew)" <<std::endl; 
    ////////extract  North-South velocity sign/////////
    std::bitset<1> S_ns(data,18,1);
    std::cout<< S_ns <<"  --- North-South  velocity sign(S_ns)" <<std::endl; 
    ////////extract  North-South velocity/////////
    std::bitset<10> V_ns(data,20,10);
    std::cout<< V_ns <<"  --- North-South  velocity(V_ns)" <<std::endl;     
    ////////extract  Vertical rate source/////////
    std::bitset<1> VrSrc(data,30,1);
    std::cout<< VrSrc <<"  --- Vertical rate source(VrSrc)" <<std::endl;    
    ////////extract  Vertical rate sign/////////
    std::bitset<1> S_vr(data,31,1);
    std::cout<< S_vr <<"  --- Vertical rate sign(S_vr)" <<std::endl;    
    ////////extract  Vertical rate/////////
    std::bitset<9> Vr(data,32,9);
    std::cout<< Vr <<"  --- Vertical rate(Vr)" <<std::endl;    
    ////////extract   Reserved-B/////////
    std::bitset<2> RESV_B(data,41,2);
    std::cout<< RESV_B <<"  ---  Reserved-B" <<std::endl;    
    ////////extract  Diff from baro alt, sign/////////
    std::bitset<1> S_Dif(data,43,1);
    std::cout<< S_Dif <<"  ---Diff from baro alt, sign(S_Dif)" <<std::endl;   
    ////////extract  Diff from baro alt/////////
    std::bitset<7> Dif(data,44,7);
    std::cout<< Dif <<"  ---Diff from baro alt(Dif)" <<std::endl;  

    /* Porcessing data */
long int V_we= 0;
long int V_sn=0;
V_we = velocityFormula( S_ew.to_ulong(), V_ew.to_ulong());
V_sn = velocityFormula( S_ns.to_ulong(), V_ns.to_ulong());
float v = std::sqrt((V_we*V_we)+(V_sn*V_sn));
std::cout<< v <<"  ---v(GroundSpeed)" <<std::endl;
float h = atan2(V_we, V_sn) *(360/(2*PI));
if(h<0){h += 360;}
std::cout<< h <<"  ---h" <<std::endl;  

std::string vertMove = "";
if (S_vr == 0){vertMove = "+++Climbing";}else{vertMove = "---Descending";}
int Vert = (Vr.to_ulong()-1)*64;
std::cout<< Vert << vertMove <<"  ---Vertical Rate" <<std::endl;  
if(VrSrc == 0){std::cout<<"  ---Using Baro-pressure altitude change rate" <<std::endl;}else{std::cout<<"  --- Geometric altitude change rate" <<std::endl;
return 0 ;
}
    }    
    else if(St == 2){std::cout<< "Subtype 2 is undefined"<< std::endl;
        return 1;
    }
    else if(St == 3){
    ////////extract Intent change flag/////////
    std::bitset<1> IC(data,3,1);
    std::cout<< IC <<"  --- Intent Change Flag" <<std::endl; 
    ////////extract Intent change flag/////////
    std::bitset<1> RESV_A(data,4,1);
    std::cout<< RESV_A <<"  ---  Reserved-A" <<std::endl; 
        ////////extract Intent change flag/////////
    std::bitset<3> NAC(data,5,3);
    std::cout<< NAC <<"  --- Velocity uncertainty (NAC)" <<std::endl; 
        ////////extract Intent change flag/////////
    std::bitset<1> S_hdg(data,8,1);
    std::cout<< S_hdg <<"  --- Heading status(0-N/A or 1 - availible)" <<std::endl; 
        ////////extract Intent change flag/////////
    std::bitset<10> Hdg(data,9,10);
    std::cout<< Hdg <<"  --- Heading (proportion)" <<std::endl; 
        ////////extract Intent change flag/////////
    std::bitset<1> AS_t(data,19,1);
    std::cout<< AS_t <<"  ---Airspeed Type(0-IAS or 1 -TAS)" <<std::endl; 
        ////////extract Intent change flag/////////
    std::bitset<10> AS(data,20,10);
    std::cout<< AS <<"  --- Airspeed" <<std::endl; 
        ////////extract Intent change flag/////////
    std::bitset<1> VrSrc(data,30,1);
    std::cout<< VrSrc <<"  --- Vertical rate source" <<std::endl; 
        ////////extract Intent change flag/////////
    std::bitset<1> S_vr(data,31,1);
    std::cout<< S_vr <<"  --- Vertical rate sign" <<std::endl; 
        ////////extract Intent change flag/////////
    std::bitset<9> Vr(data,32,9);
    std::cout<< Vr <<"  --- Vertical rate" <<std::endl; 
        ////////extract Intent change flag/////////
    std::bitset<2> RESV_B(data,41,2);
    std::cout<< RESV_B <<"  --- Reserved-B" <<std::endl; 
        ////////extract Intent change flag/////////
    std::bitset<1> S_Dif(data,43,1);
    std::cout<< S_Dif <<"  ---  Difference from baro alt, sign" <<std::endl; 
        ////////extract Intent change flag/////////
    std::bitset<7>  Dif(data,44,7);
    std::cout<<  Dif <<"  --- Difference from baro alt" <<std::endl; 

    /////////HEADING////////////
    if(S_hdg == 1)
    {
     int proportion = Hdg.to_ulong();
     float heading = (proportion/1024)*360;
      std::cout<<  heading<<" degrees --- heading" <<std::endl; 
    }else{std::cout<<"Heading information not availible" <<std::endl; }
    ////////////AirSpeed//////////
    int AS_dec = AS.to_ulong();
    if(AS_t == 0)
    {
      std::cout<<  AS_dec<<" knots --- IAS" <<std::endl;    
    }else{  std::cout<<  AS_dec<<" knots --- TAS" <<std::endl;    }
   ///////////////Vertical Rate//////////
    std::string vertMove = "";
    if (S_vr == 0){vertMove = "+++Climbing";}else{vertMove = "---Descending";}
    int Vert = (Vr.to_ulong()-1)*64;
    std::cout<< Vert << vertMove <<"  ---Vertical Rate" <<std::endl;  
    if(VrSrc == 0){std::cout<<"  ---Using Baro-pressure altitude change rate" <<std::endl;}else{std::cout<<"  --- Geometric altitude change rate" <<std::endl;
    }   
        
        
    }
    else{std::cout<< "Subtype" << St << "  is out of range, may have been interpretted wrong ";
        return 2;
    }
    

 return 0  ;
}
                 
                 
int mod(int x, int y)
{
    int modded = x- (y * floor(x/y));
    std::cout << "custom mod of : " << x << "," << y << " is " << modded  <<std::endl;
    return modded;
    
}                 
                 
int getLatindex(float cprE,float cprO)     
{
    int lIndex = floor(((59*cprE) - (60*cprO)) + 0.5);
    std::cout << lIndex << "---Index"<<std::endl;
    return lIndex;
    
    
}     

int NL(float lat)
{
    if(lat == 0){return 59;}
    if(lat == 87 || lat == -87 ){return 2;}
    if(lat > 87 || lat < -87){return 1;}
 //  float nl =  floor((2*PI)/ acos(1-(1-std::cos(PI/(2-NZ)))/(pow(std::cos((PI/180)*lat),2)))       );
float a = 1 -std::cos(PI/(2*NZ));
float b = std::cos(PI/180.0 *abs(lat))*std::cos(PI/180.0 *abs(lat));
float nl = 2 *PI/(std::acos(1-a/b));
    return nl;
    
}
std::string processAsAirPos(std::bitset<51> bs,std::bitset<51> bs2)
{

    
    
    
    
    
     /////////////////////bs /////////////////////////////////////////////////
     /////////////////////bs /////////////////////////////////////////////////
     /////////////////////bs /////////////////////////////////////////////////
    /////////////////////bs /////////////////////////////////////////////////
    std::string data = "";
    std::string converted = "";
    data = bs.to_string();
    
    ////////extract Surveillance status/////////
    std::bitset<2> mySS(data,0,2);
    int SS = mySS.to_ulong();
    std::cout<< SS <<"  --- SS" <<std::endl;
 
            ////////extract NIC supplement-B/////////
    std::bitset<1> myNICsb(data,2,1);
    int NICsb = myNICsb.to_ulong();
    std::cout<< NICsb <<"  --- NICsb" <<std::endl;
            ////////extract Altitude/////////
    std::bitset<7> firstEight(data,3,7);
    std::bitset<1> Qbit(data,10,1);
    std::bitset<4> secondFour(data,11,4);
    std::string Alt = firstEight.to_string()+ secondFour.to_string();

    std::cout<< Qbit <<"  --- Qbit" <<std::endl;
    std::cout<< Alt <<"  --- alt as binary (removed qbit position 8)" <<std::endl;
    
    std::bitset<1> T(data,15,1);
    std::cout<< T <<"  --- TIME" <<std::endl;

    std::bitset<1> F(data,16,1);
    std::cout<< F <<"  --- FFFFFFFF" <<std::endl;
    
    std::bitset<17> cprLat(data,17,17);
    std::cout<< cprLat <<"  --- Frame" <<std::endl;

    std::bitset<17> cprLon(data,34,17);
    std::cout<< cprLon <<"  --- Frame" <<std::endl;  
     /////////////////////bs /////////////////////////////////////////////////
     /////////////////////bs /////////////////////////////////////////////////
     /////////////////////bs /////////////////////////////////////////////////
     /////////////////////bs /////////////////////////////////////////////////
/*---------------------------------------------------------------------------------*/
     /////////////////////bs2/////////////////////////////////////////////////
     /////////////////////bs2/////////////////////////////////////////////////
     /////////////////////bs2/////////////////////////////////////////////////
     /////////////////////bs2/////////////////////////////////////////////////
    std::string data2 = "";
    std::string converted2 = "";
    data2 = bs2.to_string();
    
    ////////extract Surveillance status/////////
    std::bitset<2> mySS2(data2,0,2);
    int SS2 = mySS2.to_ulong();
    std::cout<< SS2 <<"  --- SS2" <<std::endl;
 
            ////////extract NIC supplement-B/////////
    std::bitset<1> myNICsb2(data2,2,1);
    int NICsb2 = myNICsb2.to_ulong();
    std::cout<< NICsb2 <<"  --- NICsb2" <<std::endl;
            ////////extract Altitude/////////
    std::bitset<7> firstEight2(data2,3,7);
    std::bitset<1> Qbit2(data2,10,1);
    std::bitset<4> secondFour2(data2,11,4);
    std::string Alt2 = firstEight2.to_string()+ secondFour2.to_string();

    std::cout<< Qbit2 <<"  --- Qbit2" <<std::endl;
    std::cout<< Alt2 <<"  --- alt as binary (removed qbit position 8)" <<std::endl;
    
    std::bitset<1> T2(data2,15,1);
    std::cout<< T2 <<"  --- TIME2" <<std::endl;

    std::bitset<1> F2(data2,16,1);
    std::cout<< F2 <<"  --- Frame2" <<std::endl;
    
    std::bitset<17> cprLat2(data2,17,17);
    std::cout<< cprLat2 <<"  --- cprlat2" <<std::endl;

    std::bitset<17> cprLon2(data2,34,17);
    std::cout<< cprLon2 <<"  --- cprLon22" <<std::endl;  
     
     
     
     
     
     
     
     
     /////////////////////bs2/////////////////////////////////////////////////
     /////////////////////bs2/////////////////////////////////////////////////
     /////////////////////bs2/////////////////////////////////////////////////
     /////////////////////bs2/////////////////////////////////////////////////
    
    
    int multiple = 0;
    if(Qbit == 0 ){multiple = 100;}else{multiple = 25;}
    std::bitset<11> decAlt(Alt);
    int Altitude = decAlt.to_ulong() * multiple -1000;
    std::cout<< Altitude<< " ft"  <<"  --- Accuracy +/- :"<< multiple <<std::endl;

    
    
if(ICAO == ICAO2 && F != F2)
{    
    float cprLatEven= 0.0000F;
    float cprLonEven = 0.0000F;
    float cprLatOdd= 0.0000F;
    float cprLonOdd = 0.0000F;
    float finalLatitiude = 0.0F;
    int tEven = 0;
    int tOdd = 0;
    
    if(F.to_ulong() == 0 )
    {///////////first message is even 
    cprLatEven = cprLat.to_ulong()/131072.0;
    cprLonEven = cprLon.to_ulong()/131072.0;
    cprLatOdd = cprLat2.to_ulong()/131072.0;
    cprLonOdd = cprLon2.to_ulong()/131072.0;
    tEven = T.to_ulong();
    tOdd = T2.to_ulong();
    }else{///////////first msg is odd
    cprLatEven = cprLat2.to_ulong()/131072.0;
    cprLonEven = cprLon2.to_ulong()/131072.0;
    cprLatOdd = cprLat.to_ulong()/131072.0;
    cprLonOdd = cprLon.to_ulong()/131072.0;  
    tEven = T2.to_ulong();
    tOdd = T.to_ulong();
    }
    
    
    

    std::cout<< cprLatEven << " -cle clo-" << cprLatOdd<<std::endl;
    std::cout<< cprLonEven << " -clone clono-" << cprLonOdd<<std::endl;
    int index = getLatindex(cprLatEven,cprLatOdd);
    float latEv = dLe * (mod(index,60) + cprLatEven  ); 
    float latOd = dLo * (mod(index,60) + cprLatOdd  );
    if(latEv >= 270){latEv -= 360;}
    if(latOd >= 270){latOd -= 360;}
    std::cout<< latEv<< "  --- LatitudeEvenframe"<< multiple <<std::endl;
    std::cout<< latOd<< "  --- LatitudeOddframe"<< multiple <<std::endl;
    if(tEven >= tOdd){finalLatitiude = latEv;}else{finalLatitiude = latOd;}
    std::cout<< finalLatitiude << "  ---final Latitude"<< multiple <<std::endl;
     std::cout<<NL(latEv)<< " NLEv" <<std::endl;
    std::cout<<NL(latOd)<< " NLOd" <<std::endl;
     if(NL(latEv) == NL(latOd) ) {
        if(tEven > tOdd){/////even frame came first 
          float ni = std::max(NL(latEv),1);   
          float dLon = 360.0/ni;
          float m = floor(cprLonEven*(NL(latEv)-1)-(cprLonOdd * NL(latEv))+0.5);
          float Lon = dLon *(mod(m,ni)+cprLonEven);
          if(Lon >= 180){Lon-=360;}
          
          
           std::cout<< Lon << "  ---final Lon even first "<< multiple <<std::endl;
           
             
    }else{ ///odd frame came first 
          float ni = std::max(NL(latOd),1);   
          float dLon = 360.0/ni;
          float m = floor((cprLonEven*(NL(latOd)-1)-cprLonOdd * NL(latOd))+0.5);
          float Lon = dLon *(mod(m,ni)+cprLonOdd);
          if(Lon >= 180){Lon-=360;}
           std::cout<< Lon << "  ---final Lon odd first"<< multiple <<std::endl;        
        
        
    }
         
         
    } 
       
     
}  else{}
    

    
    return Alt;
    0
}

std::string processAsId(std::bitset<51> bs){
    std::string data = "";
    std::string converted = "";
    data = bs.to_string();
    
    ////////extract EC/////////
    std::bitset<3> myEC(data,0,3);
    std::cout<< EC<<"  --- EC as Bin" <<std::endl;
    EC= myEC;
    
    for(int i = 0 ; i <=7 ; i++)
    {
  
    std::bitset<6> aChar(data,i*6+3,6);
    long int letter  = aChar.to_ulong();
    if(letter < 0 || letter > 63  )
        {std::cout << "coversion from binary to decimal went wrong!out of range!";
        }else{
    converted.push_back(charMap[aChar.to_ulong()]);
        }
    }       
 

 return converted;
}




int processDataBlock(int tc, std::bitset<51> bs){
    if(tc == 0 ){std::cout << "Typecode '0' is undefined , something when wrong" << std::endl;}
        else if(tc >=1 && tc <=4){std::cout << "Aircraft Identification" << std::endl; std::cout << "CallSign is :" << processAsId(bs) << std::endl;}
            else if(tc >=5 && tc <=8){std::cout << "Surface Position" << std::endl;}
                else if(tc >=9 && tc <=18){std::cout << "Airborne Postion with Baro Alititude --- A previously known position or addition message is needed to process" << std::endl;}
                    else if(tc == 19){std::cout << "Airborne velocity" << std::endl;processAsAirVel(bs);}
                        else if(tc >=20 && tc <=22){std::cout << "Airborne Postion with GNSS Height" << std::endl;}
                            else if(tc >=23 && tc <=27){std::cout << "Defined as reserved" << std::endl;}
                                else if(tc ==28){std::cout << "Aircraft Status" << std::endl;}
                                    else if(tc ==29){std::cout << "Target state and status information" << std::endl;}
                                    ////////Why isnt 30 defined???///////
                                        else if(tc == 31){std::cout << "Aircraft operation status" << std::endl;}
                                             else if(tc > 31){std::cout << "TC decoding was incorrect" << std::endl;}
    return 0;
    
    
    
}

int STHX(std::string g)
    {
    char mychar[28] ;
    std::string binary = "";
    strcpy(mychar,g.c_str());
    for(int i = 0 ; i < 28 ; i++) {
        ////range checking according to ASCII////
        if((int)mychar[i] <= 47 || (int)mychar[i] >= 91 )
        {
            std::cout << " character at index " << i << " is out of range" << std::endl;
            std::cout <<std::endl;
            return 1;
            
        }
        if((int)mychar[i] >= 58 && (int)mychar[i] <=  64 )
        {
            std::cout << " character at index " << i << " is out of range" << std::endl;
            std::cout <<std::endl;
            return 1;
        }
        
        
    }
  
/////In range ,then go ahead anf convert /////////
for(int i = 0 ; i < 28 ; i++)
    {
        std::stringstream str;
        unsigned  n;    
        str <<  std::hex << (uint8_t)mychar[i];
        str >> n;
        std::bitset<4> b(n);
        binary += b.to_string();   ///construct a binary string to workwith  
    } 
std::bitset<112> b(binary);
mybitset = b;
std::cout <<mybitset<<"  bitset as converted" <<std::endl;

////////Get DF///////////////
std::bitset<5> DFasBin(binary,0,5);
std::cout<< DFasBin<<"  --- DF as Bin" <<std::endl;
DF = DFasBin.to_ulong();
std::cout<< DF;
if(DF == 17){std::cout << " -- DownLinkFormat ADS-B"<< std::endl;}
if(DF == 18){std::cout << " -- DownLinkFormat TIS-B"<< std::endl;}

////////Get CA////////////////
std::bitset<3> CAasBin(binary,5,3);
std::cout<< CAasBin<<"  --- CA as Bin" <<std::endl;
CA = CAasBin.to_ulong();
std::cout<< CA<<"  CA cast to long int " <<std::endl;

///////////getICAO//////////
ICAO = RAW.substr(2,6);
std::cout<< ICAO<< "  ICAO " <<std::endl;

////////Get TC////////////////
std::bitset<5> TCasBin(binary,32,5);
std::cout<< TCasBin<<"  --- TC as Bin" <<std::endl;
TC = TCasBin.to_ulong();
std::cout<< TC<<"---TC cast to long int " <<std::endl;


////////extract DATABLOCK/////////
std::bitset<51> DB(binary,37,51);
std::cout<< DB<<"  --- DB as Bin" <<std::endl;
DATABLOCK = DB;
std::cout<< DATABLOCK<<"---DATABLOCK " <<std::endl;

////////extract PARITY/////////
std::bitset<24> PA(binary,89,24);
std::cout<< PA<<"  --- PA as Bin" <<std::endl;
PARITY = PA;
std::cout<< PARITY<<"---PARITY " <<std::endl;
return 0; 

}
int STHX(std::string msg ,std::string msg2 )
    {
    char mychar[28] ;
    std::string binary = "";
    strcpy(mychar,msg.c_str());
    for(int i = 0 ; i < 28 ; i++) {
        ////range checking according to ASCII////
        if((int)mychar[i] <= 47 || (int)mychar[i] >= 91 )
        {
            std::cout << " character at index " << i << " is out of range" << std::endl;
            std::cout <<std::endl;
            return 1;
            
        }
        if((int)mychar[i] >= 58 && (int)mychar[i] <=  64 )
        {
            std::cout << " character at index " << i << " is out of range" << std::endl;
            std::cout <<std::endl;
            return 1;
        }
        
        
    }
        char mychar2[28] ;
    std::string binary2 = "";
    strcpy(mychar2,msg2.c_str());
    for(int i = 0 ; i < 28 ; i++) {
        ////range checking according to ASCII////
        if((int)mychar2[i] <= 47 || (int)mychar2[i] >= 91 )
        {
            std::cout << " character at index " << i << " is out of range" << std::endl;
            std::cout <<std::endl;
            return 1;
            
        }
        if((int)mychar2[i] >= 58 && (int)mychar2[i] <=  64 )
        {
            std::cout << " character at index " << i << "in msg2 is out of range" << std::endl;
            std::cout <<std::endl;
            return 1;
        }
        
        
    }
  
/////In range ,then go ahead anf convert /////////
for(int i = 0 ; i < 28 ; i++)
    {
        std::stringstream str;
        unsigned  n;    
        str <<  std::hex << (uint8_t)mychar[i];
        str >> n;
        std::bitset<4> b(n);
        binary += b.to_string();   ///construct a binary string to workwith  
    } 
for(int i = 0 ; i < 28 ; i++)
    {
        std::stringstream str2;
        unsigned  n2;    
        str2 <<  std::hex << (uint8_t)mychar2[i];
        str2 >> n2;
        std::bitset<4> b2(n2);
        binary2 += b2.to_string();   ///construct a binary string to workwith  
    }    
    
    
    
    
    
std::bitset<112> b(binary);
mybitset = b;
std::cout <<mybitset<<"  bitset as converted" <<std::endl;

////////Get DF///////////////
std::bitset<5> DFasBin(binary,0,5);
std::cout<< DFasBin<<"  --- DF as Bin" <<std::endl;
DF = DFasBin.to_ulong();
std::cout<< DF;
if(DF == 17){std::cout << " -- DownLinkFormat ADS-B"<< std::endl;}
if(DF == 18){std::cout << " -- DownLinkFormat TIS-B"<< std::endl;}

////////Get CA////////////////
std::bitset<3> CAasBin(binary,5,3);
std::cout<< CAasBin<<"  --- CA as Bin" <<std::endl;
CA = CAasBin.to_ulong();
std::cout<< CA<<"  CA cast to long int " <<std::endl;

///////////getICAO//////////
ICAO = RAW.substr(2,6);
std::cout<< ICAO<< "  ICAO " <<std::endl;

////////Get TC////////////////
std::bitset<5> TCasBin(binary,32,5);
std::cout<< TCasBin<<"  --- TC as Bin" <<std::endl;
TC = TCasBin.to_ulong();
std::cout<< TC<<"---TC cast to long int " <<std::endl;


////////extract DATABLOCK/////////
std::bitset<51> DB(binary,37,51);
std::cout<< DB<<"  --- DB as Bin" <<std::endl;
DATABLOCK = DB;
std::cout<< DATABLOCK<<"---DATABLOCK " <<std::endl;

////////extract PARITY/////////
std::bitset<24> PA(binary,89,24);
std::cout<< PA<<"  --- PA as Bin" <<std::endl;
PARITY = PA;
std::cout<< PARITY<<"---PARITY " <<std::endl;



    
std::bitset<112> b2(binary2);
mybitset2 = b2;
std::cout <<mybitset2<<"  bitset2 as converted" <<std::endl;

////////Get DF///////////////
std::bitset<5> DFasBin2(binary2,0,5);
std::cout<< DFasBin2<<"  --- DF2 as Bin" <<std::endl;
DF2 = DFasBin2.to_ulong();
std::cout<< DF2;
if(DF == 17){std::cout << " -- DownLinkFormat ADS-B"<< std::endl;}
if(DF == 18){std::cout << " -- DownLinkFormat TIS-B"<< std::endl;}

////////Get CA////////////////
std::bitset<3> CAasBin2(binary2,5,3);
std::cout<< CAasBin2<<"  --- CA2 as Bin" <<std::endl;
CA2 = CAasBin2.to_ulong();
std::cout<< CA2<<"  CA2 cast to long int " <<std::endl;

///////////getICAO//////////
ICAO2 = RAW2.substr(2,6);
std::cout<< ICAO2<< "  ICAO2 " <<std::endl;

////////Get TC////////////////
std::bitset<5> TCasBin2(binary2,32,5);
std::cout<< TCasBin2<<"  --- TC as Bin" <<std::endl;
TC2 = TCasBin2.to_ulong();
std::cout<< TC2<<"---TC2 cast to long int " <<std::endl;


////////extract DATABLOCK/////////
std::bitset<51> DB2(binary2,37,51);
std::cout<< DB2<<"  --- DB2 as Bin" <<std::endl;
DATABLOCK2 = DB2;
std::cout<< DATABLOCK2<<"---DATABLOCK 2" <<std::endl;

////////extract PARITY/////////
std::bitset<24> PA2(binary2,89,24);
std::cout<< PA2<<"  --- PA2 as Bin" <<std::endl;
PARITY2 = PA2;
std::cout<< PARITY2<<"---PARITY2 " <<std::endl;


return 0; 

}

void setup(std::string g){
    RAW = g;
    std::cout <<"----------------------------------" << std::endl;
    std::cout <<"---"<< RAW<<"---" << std::endl;
    std::cout <<"----------------------------------" << std::endl;
    STHX(g);

    processDataBlock(TC,DATABLOCK);
}
void setup(std::string msg,std::string msg2){
    RAW = msg;
    std::cout <<"----------------------------------" << std::endl;
    std::cout <<"---"<< RAW<<"---" << std::endl;
    std::cout <<"----------------------------------" << std::endl;
    RAW2 = msg2;
    std::cout <<"----------------------------------" << std::endl;
    std::cout <<"---"<< RAW2<<"---" << std::endl;
    std::cout <<"----------------------------------" << std::endl;

            STHX(msg,msg2);
    
        if(TC >=9 && TC <=18 && TC2 >=9 && TC2 <=18  ){
         
            processAsAirPos(DATABLOCK,DATABLOCK2);
            
        }else{
            processDataBlock(TC,DATABLOCK);
            processDataBlock(TC,DATABLOCK2);
        }
}



int main()
{
///////////////Examples///////////////
////Velocity subtype 1(GS)///8D485020994409940838175B284F///
///subtype2 8DA05F219B06B6AF189400CBC33F
///callsign 8D4840D6202CC371C32CE0576098 
///position even frame 8D40621D58C382D690C8AC2863A7
///position odd frame 8D40621D58C386435CC412692AD6

    std::setw(40);
Start:
system("clear");
std::cout << "--------------------------------------------------------------------------------"<< std::endl;
std::cout << "------------------------------ADSBTOY-------------------------------------------"<< std::endl;
std::cout << "--------------------------------------------------------------------------------"<< std::endl;
std::cout << "--------------------------------------------------------------------------------"<< std::endl;
std::cout << "--------------------------------------------------------------------------------"<< std::endl;
std::cout << "--------------------------------------------------------------------------------"<< std::endl;
std::cout << "------------------------------Examples------------------------------------------"<< std::endl;
std::cout << "8D485020994409940838175B284F------------------------------Velocity subtype 1(GS)"<< std::endl;
std::cout << "8DA05F219B06B6AF189400CBC33F-------------------------Velocity subtype 3(IAS/TAS)"<< std::endl;
std::cout << "8D4840D6202CC371C32CE0576098--------------------------------------------callsign"<< std::endl;
std::cout << "8D40621D58C382D690C8AC2863A7---------------------------------position even frame"<< std::endl;
std::cout << "8D40621D58C386435CC412692AD6----------------------------------position odd frame"<< std::endl;
std::cout << std::endl;
std::cout << std::endl;
std::cout << std::endl;
std::string msg;
std::string msg2;
std::cout << "Enter a String of Hex :" << std::endl;
std::cin >> msg;
SecondMessage:
std::cout << "Enter another?'N','Q' or string:" << std::endl;
std::cin >> msg2;

if (msg2 == "N" || msg2 == "n"){setup(msg);
    std::cout << "press enter to continue." << std::endl;
   system("read");
    goto Start;}
else if(msg2.length() == 28){
    setup(msg,msg2);
     std::cout << "press enter to continue." << std::endl;
     system("read");
    goto Start;
}
else if(msg2 == "Q" || msg2 == "q"){
    return 0;
    goto Start;
}
else{
    std::cout << "Your response is not defined !";
     std::cout << "press enter to continue." << std::endl;
    system("read");
    goto SecondMessage;
}


    return 0;
}


