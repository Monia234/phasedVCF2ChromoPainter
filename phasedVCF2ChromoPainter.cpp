/*
 * phasedVCF2ChromoPainter
 * Date: Nov-05-2018 
 * Author : Gabriel Renaud gabriel.reno [at sign here ] gmail.com
 *
 */

#include <iostream>
#include <fstream>
#include <gzstream.h>

#include "utils.h"

using namespace std;

int main (int argc, char *argv[]) {

   string line;
   igzstream myFile;
   string filename = string(argv[1]);
   myFile.open(filename.c_str(), ios::in);
   vector<string> * sequences;
   unsigned int indCounter=0;

   vector<unsigned int> pos;
   if (myFile.good()){
       while ( getline (myFile,line)){

	   if(!line.empty()){
	       if(line[0]=='#'){
		   if(line.substr(0,6) == "#CHROM"){
		       vector<string> fields=allTokens(line,'\t');
		       sequences = new  vector<string> (2*(fields.size()-9),"") ;
		       indCounter = fields.size()-9 ;
		   }
		   continue;
	       }

	       vector<string> fields=allTokens(line,'\t');
	       //cout<<fields.size()<<endl;
	       if(fields[3].size() != 1) continue;
	       if(fields[4].size() != 1) continue;
	       if(!isResolvedDNA(fields[3][0]) ) continue;
	       if(!isResolvedDNA(fields[4][0]) ) continue;
	       string r=fields[3];
	       string a=fields[4];
	       pos.push_back( destringify<unsigned int>(fields[1]));

	       for(unsigned int i=9;i<fields.size();i++){
		   //cout<<(2*(i-9))<<"\t"<<(2*(i-9)+1)<<"\t"<<fields[i]<<"\t"<<r<<" "<<a<<endl;
		   vector<string> infoFields=allTokens( fields[i] ,':');
		   if(infoFields[0] == "0|0"){
		       sequences->at(2*(i-9)  ) += r;
		       sequences->at(2*(i-9)+1) += r;
		       continue;
		   }
		   if(infoFields[0] == "1|1"){
		       sequences->at(2*(i-9)  ) += a;
		       sequences->at(2*(i-9)+1) += a;
		       continue;
		   }
		   if(infoFields[0] == "0|1"){
		       sequences->at(2*(i-9)  ) += r;
		       sequences->at(2*(i-9)+1) += a;
		       continue;
		   }
		   if(infoFields[0] == "1|0"){
		       sequences->at(2*(i-9)  ) += a;
		       sequences->at(2*(i-9)+1) += r;
		       continue;
		   }
	       }
	   }

       }
       myFile.close();
   }else{
       cerr << "Unable to open file "<<filename<<endl;
       return 1;
    }

   cout<<(2*indCounter)<<endl;
   cout<<pos.size()<<endl;
   cout<<"P "<<vectorToString(pos," ")<<"#"<<endl;
   for(unsigned int i=0;i<(2*indCounter);i++){
       cout<<sequences->at(i)<<endl;
   }

   return 0;
}

