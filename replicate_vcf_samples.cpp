#include <iostream>
 #include "ctype.h"
 #include "stdlib.h"
#include <stdio.h>
#include <string.h>


#include <iterator>
 #include <sstream>
#include <fstream>
#include <vector>
 using namespace std;

 int debugging=0;

 string snpChrA[245000];
 int snpPosA[245000];
 int snpPositionI=0;
 ofstream log("log");
 string jumpGaps(string seq){
     
     
      int len=seq.length();
      int i=0;
     
      for(;i<len;i++){
          
          
          
           if(seq[i]==' '||seq[i]=='\t') break;
          
          
     }
     
     
     
     
     
     
      for(;i<len;i++){
          
          
           if(!(seq[i]==' '||seq[i]=='\t')) break;
          
          
      }
     
      return seq.substr(i);
     
 }


 string getFirst(string seq){
     
      int len=seq.length();
      string result="";
      int i=0;
     
      while(seq[i]!=' '&&seq[i]!='\t'&&i<=len){
           result=result+seq[i];
          
          
           i++;
      }
     
      return result;
     
 }





 int main(int argc, char* argv[]){
	 
	 std::ofstream log("replicate_vcf_samples.log");
	 
	 std::ofstream output("fixed.vcf");
	 cout<<"file 1:list of original name       replicate name/nfile 2: vcf"<<endl;

	 std::ifstream listF(argv[1]);
	
	 vector < vector <string> > listA;
	 
	 
	 long maxlength=100000;
	 	 cout<<"Check the length of the files. Current length allowed: "<<maxlength<<endl;
	 
	 char buf[maxlength];
	 maxlength=100;
	 listF.clear();
	 listF.getline(buf,maxlength);
	 string content=buf;
	 string content_sub;
	 
	 log<<"list:"<<content<<endl;
	int index=0;
	 while(!listF.eof()){
		 
		 
		 content_sub=getFirst(content);
		 content=jumpGaps(content);
		 
		 vector <string> lista;
		 listA.push_back(lista);
		 listA[index].push_back(content_sub);
		 listA[index].push_back(content);
			
		
		listF.clear();
		listF.getline(buf,maxlength);
		
		content=buf;
		 index++;
		log<<"list:"<<content<<endl;
	 }
	 
	 cout<<index<<" replicate targets are read from the list file"<<endl;
	 listF.close();
	 
	maxlength=100000;
	std::ifstream vcf(argv[2]);
	 
	 vcf.clear();
	 vcf.getline(buf,maxlength);
	 content=buf;
	 cout<<"The first line of the vcf file:"<<content<<endl;
	 
	vector <string> headerA;
	
		string header_last,header_last_backup;
		while(strstr(content.c_str(),"#")){
			log<<"header:"<<content<<endl;
			vcf.clear();
			vcf.getline(buf,maxlength);
			
			header_last=content;
			header_last_backup=header_last;
			content=buf;
		}
		cout<<"Found header:"<<header_last<<endl;
		 
		 for(int i=0;i<9;i++){
			header_last=jumpGaps(header_last);
		 }
		 while(header_last.length()>0){
			 content_sub=getFirst(header_last);
			 headerA.push_back(content_sub);
			 header_last=jumpGaps(header_last);
		 }
		 cout<<"Number of samples:"<<headerA.size()<<endl;
		for(int i=0;i<headerA.size();i++){
			cout<<headerA[i]<<" ";
		 }
		 cout<<endl;
		 
		 output<<header_last_backup<<endl;
		 log<<header_last;
		 
		 for(int i;i<index;i++){
			 output<<"\t"<<listA[i][1];
		 }
		 output<<endl;
		 

	 content=buf;
	 
	 int rd=0;
	 int lineC=0;
	 
	 while(!vcf.eof()){
		
		output<<content;
		 for(int i=0;i<2;i++){
			 output<<getFirst(content)<<"\t";if(rd%100==0){ log<<getFirst(content)<<"\t";}
			content=jumpGaps(content);
		 }
		
		 content=jumpGaps(content);
	

		 
		  for(int i=0;i<6;i++){
			 output<<getFirst(content)<<"\t";
			 content=jumpGaps(content);
		 }
		 
		  vector <string> genotypes;
		
		
		
			 
			 
			
			 while(content.length()>0){
				genotypes.push_back(getFirst(content));
				content=jumpGaps(content);
			 }
			
			int error=0;
			for(int i=0;i<index;i++){
				int flag=0;
				int foundIndex=-1;
				for(int j=0;j<headerA.size();j++){
					if(listA[i][0]==headerA[j]){
						flag=1;foundIndex=j;break;
					}
				}
				if(flag==1){output<<"\t"<<genotypes[foundIndex];}
				else{if(lineC==0){cout<<"coudln't find "<<listA[i][0]<<endl;log<<"coudln't find "<<listA[i][0]<<endl;}//error=1;
				break;}
			}
			if(0) break;
		 
		
		 
		 	vcf.clear();
			vcf.getline(buf,maxlength);
		output<<endl;
			content=buf;
		 lineC++;
		if(content.length()<1) break;
	 }
	vcf.close();
	output.close();
 }

