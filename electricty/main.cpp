#include <iostream>
#include <string.h>
#include <string>
#include <stack>
#include <vector>
using namespace std;

unsigned int nrORez;
float rez[100];
string input;

struct token{
//0 number 1 operation
bool type;
float nr;
char operation;
};

vector<token> output;
stack<token> wating;

void reversePolish(){
token temp;
int len = input.size(),parnr=0;
string tempin;
bool lastin=0;
for(int i=0;i<len;i++){
      cout<<i<<" "<<input[i]<<"  ";
      if((input[i]>='0'&&input[i]<='9')||input[i]=='.'){
       tempin+=input[i];
        cout<<" tepmval"<<tempin<<"  ";
      }else{
       if(tempin.size()!=0){
        output.push_back({0,stof(tempin),input[i]});
        cout<<"\n add nr "<<stof(tempin)<<endl;
        tempin.clear();
       }
       if(input[i]=='('||input[i]=='/'||input[i]=='+'||input[i]==')'){
        int opord;
        switch(input[i]){
            case '+':
                opord=1;
        break;
            case '/':
                opord=2;
        break;
            case '(':
                parnr+=1;
        break;
            case ')':
                parnr-=1;
        break;
        }
        if(input[i]!='('&&input[i]!=')'){
        opord+=parnr*3;
        cout<<"\n opord "<<opord<<" "<<input[i]<<endl;
        while(!wating.empty()&&wating.top().nr>=opord){
          output.push_back(wating.top());
          cout<<"\n add symb to out"<<wating.top().operation<<endl;
          wating.pop();
        }
        wating.push({1,opord,input[i]});
        cout<<"\n add wating "<<input[i]<<endl;
       }
       }
      }
      //space=0;
      cout<<endl;
   }
   if(tempin.size()!=0){
        output.push_back({0,stof(tempin),' '});
        cout<<"\n add nr "<<stof(tempin)<<endl;
        tempin.clear();
   }
    while(!wating.empty()){
          output.push_back(wating.top());
          cout<<"\n add symb to out"<<wating.top().operation<<endl;
          wating.pop();
    }
    for(int i=0;i<output.size();++i)
        if(!output[i].type)
            cout<<output[i].nr;
        else
            cout<<output[i].operation;
       // output.erase(output.begin()+i);i-=2
}

float finalRez=0;

float calcSeri(float r1,float r2){
    cout<<endl<<"calc serie \n";
    finalRez=r1+r2;
    cout<<"="<<finalRez<<endl;
    return finalRez;
}

float calcPara(float r1,float r2){
    cout<<endl<<"calc para \n";
    finalRez=1.0f/(1.0f/r1+1.0f/r2);
    cout<<"="<<finalRez<<endl;
    return finalRez;
}

void calcTotalRez(){
    while(output.size()>1){
        for(int i=0;i<output.size();++i){
            if(output[i].type){
                if(output.size()==2){
                  output.erase(output.begin()+i);
                  continue;
                }
                if(output[i].operation=='+'){
                    output[i-2].nr=calcSeri(output[i-2].nr,output[i-1].nr);
                }else{
                    output[i-2].nr=calcPara(output[i-2].nr,output[i-1].nr);
                }
                output.erase(output.begin()+i);
                output.erase(output.begin()+i-1);
                i-=2;
                for(int i=0;i<output.size();++i)
                    if(!output[i].type)
                        cout<<output[i].nr<<" ";
                    else
                        cout<<output[i].operation<<" ";
            }

        }

    }
    cout<<"\n\nfinal="<<output[0].nr;
}
int main()
{


    cout<<"Numarul de rezistente(max 100) = ";
    cin>>nrORez;
    for(int i =0;i<nrORez;++i){
    cout << "rezistenta "<<i+1<<" = ";
    cin>>rez[i];
    }
    cout<<endl;
    cout<<"calcul"<<endl;
    cin.ignore();
    getline(cin,input);
    string num;
    bool startR;
    int i=0;
    for(i;i<input.size();){
        if(input[i]>='0'&&input[i]<='9'){
            num+=input[i];
            if((input[i-1]=='r'||input[i-1]=='R')&&!startR){
                startR=true;
            }
        }else{
        if(num.size()!=0){
            string strval = to_string(rez[stoi(num)-1]);
            input.replace(i-num.size()-(int)startR,num.size()+(int)startR,strval);
            i+=strval.size()-num.size()-1;
            num.clear();
            startR=false;
        }
        if(input[i]==' '){
            input.erase(i,1);
            continue;
        }
        }
        //cout<<i<<"i "<<input.size()<<"size ";
        ++i;
    }
    if(num.size()!=0){
            string strval = to_string(rez[stoi(num)-1]);
            input.replace(i-num.size()-(int)startR,num.size()+(int)startR,strval);
    }
    cout<<"\n"<<input<<"\n";
    reversePolish();
    calcTotalRez();
    bool stop;
    cin>>stop;
    return 0;
}
