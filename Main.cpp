#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fstream>
#include "vertical.h"
using namespace std;
bool ame=false;
float v2=0,stall=0,vapp=0;
bool prsch_show=false;
double dalt,v2spd,cspd,clspd,dis,calt,dspd,dlspd,apalt,apspd,lalt;
double prsch_v[11],dist[5],Salt; // 11 elements for pre-schedule
string title="FSS-3.4 (Flight Schedule System)";
void setNonCanonicalMode(){
    struct termios term;
    tcgetattr(STDIN_FILENO,&term);
    term.c_lflag&=~(ICANON|ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&term);
}
void resetTerminalMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
bool isNum(string str){
    for(int i=0;i<str.size();i++){
        int tmp=(int)str[i];
        if(tmp>=48&&tmp<=57||tmp==46){
            continue;
        }else{
            return false;
        }
    }
    return true;
}
void VAPP(){
    system("clear");
    float S_without,S_within,quantity,Cl;
    int option=1;
    const int quantity_option=4;
    while(true){
        system("clear");
        cout <<title<<endl;
        cout <<"Select Aircraft"<<endl;
        string options[quantity_option]={"Boeing 737-800","Airbus A330-300","Boeing 787-9","Exit"};
        for(int i=1;i<=quantity_option;i++){
            cout <<" ";
            if(i==option){
                cout <<"[";
            }
            cout <<options[i-1];
            if(i==option){
                cout <<"]"<<endl;
                continue;
            }
            cout <<endl;
        }
        char ch=getchar();
        if((ch=='w'||ch=='W')&&option>1){
            option--;
        }else if((ch=='s'||ch=='S')&&option<quantity_option){
            option++;
        }else if(ch=='\n'){
            if(option==1){
                S_without=124.6;
                S_within=149.5;
                quantity=40;
                Cl=1.37;
            }else if(option==2){
                S_without=361.6;
                S_within=452.0;
                quantity=4;
                Cl=1.31;
            }else if(option==3){
                S_without=325;
                S_within=390;
                quantity=30;
                Cl=1.41;
            }else if(option==quantity_option){
                return ;
            }
            break;
        }
    }

    float mass,pos,pa,t;
    option=1;
    const int quantity_option2=6;
    string options_ame_off[quantity_option2]={"Landing Weight(kg)","Flaps position","Air pressure(hPa)","Temperature(C)","Continue","Exit"};
    string options_ame[quantity_option2]={"Landing Weight(lb)","Flaps position","Air pressure(inHg)","Temperature(C)","Continue","Exit"};
    float value[quantity_option2]={0,0,0,0};
    string in_val_s="";
    while(true){
        system("clear");
        cout <<title<<endl;
        cout <<"Input Values"<<endl;
        for(int i=1;i<=quantity_option2;i++){
            cout <<" ";
            if(ame==false){
                cout <<options_ame_off[i-1];
            }else{
                cout <<options_ame[i-1];
            }
            
            if(option==i&&i<quantity_option2-1){
                cout <<':';
                cout <<'['<<value[i-1]<<']'<<endl;
            }else if(i<quantity_option2-1){
                cout <<':';
                cout <<value[i-1]<<endl;
            }else if(option!=i){
                cout <<endl;
            }

            if(option==i&&i>=quantity_option2-1){
                cout <<"<-"<<endl;
            }
        }
        cout <<endl<<in_val_s;
        char ch=getchar();
        if((ch=='w'||ch=='W')&&option>1){
            option--;
        }else if((ch=='s'||ch=='S')&&option<quantity_option2){
            option++;
        }else if(ch=='\n'){
            if(in_val_s==""&&option<quantity_option2-1){
                option++;
                continue;
            }
            if(ame==false&&isNum(in_val_s)){
                if(option==1){
                    mass=stof(in_val_s);
                    value[0]=mass;
                }else if(option==2){
                    pos=stof(in_val_s);
                    value[1]=pos;
                }else if(option==3){
                    pa=stof(in_val_s);
                    value[2]=pa;
                    pa=pa*100;
                }else if(option==4){
                    t=stof(in_val_s);
                    value[3]=t;
                }else if(option==quantity_option2-1){
                    break;
                }else if(option==quantity_option2){
                    return;
                }
            }else if(ame==true&&isNum(in_val_s)){
                if(option==1){
                    mass=stof(in_val_s);
                    value[0]=mass;
                    mass=mass/2.20462;
                }else if(option==2){
                    pos=stof(in_val_s);
                    value[1]=pos;
                }else if(option==3){
                    pa=stof(in_val_s);
                    value[2]=pa;
                    pa=pa*33.8638;
                }else if(option==4){
                    t=stof(in_val_s);
                    value[3]=t;
                }else if(option==quantity_option2-1){
                    break;
                }else if(option==quantity_option2){
                    return ;
                }
            }else{
                in_val_s="ERROR";
                continue;
            }
            option++;
            in_val_s="";
        }else if(ch==127){
            if(in_val_s.length()>0){
                in_val_s.erase(in_val_s.length()-1);
            }
        }else{
            in_val_s+=ch;
        }
    }
    vapp=(int)(v2_speed(mass,S_without,S_within,pos,quantity,pa,t,Cl)*1.94384)+20;
}
void V2(){
    system("clear");
    float S_without,S_within,quantity,Cl;
    int option=1;
    const int quantity_option=4;
    while(true){
        system("clear");
        cout <<title<<endl;
        cout <<"Select Aircraft"<<endl;
        string options[quantity_option]={"Boeing 737-800","Airbus A330-300","Boeing 787-9","Exit"};
        for(int i=1;i<=quantity_option;i++){
            cout <<" ";
            if(i==option){
                cout <<"[";
            }
            cout <<options[i-1];
            if(i==option){
                cout <<"]"<<endl;
                continue;
            }
            cout <<endl;
        }
        char ch=getchar();
        if((ch=='w'||ch=='W')&&option>1){
            option--;
        }else if((ch=='s'||ch=='S')&&option<quantity_option){
            option++;
        }else if(ch=='\n'){
            if(option==1){
                S_without=124.6;
                S_within=149.5;
                quantity=40;
                Cl=1.37;
            }else if(option==2){
                S_without=361.6;
                S_within=452.0;
                quantity=4;
                Cl=1.31;
            }else if(option==3){
                S_without=325;
                S_within=390;
                quantity=30;
                Cl=1.41;
            }else if(option==quantity_option){
                return ;
            }
            break;
        }
    }

    float mass,pos,pa,t;
    option=1;
    const int quantity_option2=6;
    string options_ame_off[quantity_option2]={"Weight(kg)","Flaps position","Air pressure(hPa)","Temperature(C)","Continue","Exit"};
    string options_ame[quantity_option2]={"Weight(lb)","Flaps position","Air pressure(inHg)","Temperature(C)","Continue","Exit"};
    float value[quantity_option2]={0,0,0,0};
    string in_val_s="";
    while(true){
        system("clear");
        cout <<title<<endl;
        cout <<"Input Values"<<endl;
        for(int i=1;i<=quantity_option2;i++){
            cout <<" ";
            if(ame==false){
                cout <<options_ame_off[i-1];
            }else{
                cout <<options_ame[i-1];
            }
            
            if(option==i&&i<quantity_option2-1){
                cout <<':';
                cout <<'['<<value[i-1]<<']'<<endl;
            }else if(i<quantity_option2-1){
                cout <<':';
                cout <<value[i-1]<<endl;
            }else if(option!=i){
                cout <<endl;
            }

            if(option==i&&i>=quantity_option2-1){
                cout <<"<-"<<endl;
            }
        }
        cout <<endl<<in_val_s;
        char ch=getchar();
        if((ch=='w'||ch=='W')&&option>1){
            option--;
        }else if((ch=='s'||ch=='S')&&option<quantity_option2){
            option++;
        }else if(ch=='\n'){
            if(in_val_s==""&&option<quantity_option2-1){
                option++;
                continue;
            }
            if(ame==false&&isNum(in_val_s)){
                if(option==1){
                    mass=stof(in_val_s);
                    value[0]=mass;
                }else if(option==2){
                    pos=stof(in_val_s);
                    value[1]=pos;
                }else if(option==3){
                    pa=stof(in_val_s);
                    value[2]=pa;
                    pa=pa*100;
                }else if(option==4){
                    t=stof(in_val_s);
                    value[3]=t;
                }else if(option==quantity_option2-1){
                    break;
                }else if(option==quantity_option2){
                    return;
                }
            }else if(ame==true&&isNum(in_val_s)){
                if(option==1){
                    mass=stof(in_val_s);
                    value[0]=mass;
                    mass=mass/2.20462;
                }else if(option==2){
                    pos=stof(in_val_s);
                    value[1]=pos;
                }else if(option==3){
                    pa=stof(in_val_s);
                    value[2]=pa;
                    pa=pa*33.8638;
                }else if(option==4){
                    t=stof(in_val_s);
                    value[3]=t;
                }else if(option==quantity_option2-1){
                    break;
                }else if(option==quantity_option2){
                    return ;
                }
            }else{
                in_val_s="ERROR";
                continue;
            }
            option++;
            in_val_s="";
        }else if(ch==127){
            if(in_val_s.length()>0){
                in_val_s.erase(in_val_s.length()-1);
            }
        }else{
            in_val_s+=ch;
        }
    }
    v2=(int)(v2_speed(mass,S_without,S_within,pos,quantity,pa,t,Cl)*1.94384);
}
void planning(){
    cout <<"TAKE-OFF-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-"<<endl;
        cout <<"  [SPD]"<<prsch_v[1]<<" KT->"<<prsch_v[2]<<" KT"<<endl;
        cout <<"  [V S]"<<prsch_v[3]<<" ft/min"<<endl;
        cout <<"  [ALT]"<<prsch_v[0]<<" ft->"<<prsch_v[5]<<" ft"<<endl;
        cout <<" [DIST]"<<prsch_v[4]<<"-"<<prsch_v[4]-dist[0]<<" nmi"<<endl;
        cout <<"Cruising-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-"<<endl;
        cout <<"  [SPD]"<<prsch_v[2]<<" KT"<<endl;
        cout <<"  [ALT]"<<prsch_v[5]<<" ft"<<endl;
        cout <<" [DIST]"<<prsch_v[4]-dist[0]<<"-"<<dist[1]<<" nmi"<<endl;
        cout <<"DESCENDING ALTITUDE-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_"<<endl;
        cout <<"  [SPD]"<<prsch_v[2]<<" KT->"<<prsch_v[6]<<" KT"<<endl;
        cout <<"  [V S]"<<prsch_v[7]<<" ft/min"<<endl;
        cout <<"  [ALT]"<<prsch_v[5]<<" ft->"<<Salt<<" ft"<<endl;
        cout <<" [DIST]"<<dist[1]<<"-"<<dist[2]<<" nmi"<<endl;
        cout <<"DESCENDING SPEED-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-"<<endl;
        cout <<"  [SPD]"<<prsch_v[6]<<" KT->"<<prsch_v[9]<<" KT"<<endl;
        cout <<"  [V S]500 ft/min"<<endl;
        cout <<"  [ALT]"<<Salt<<" ft->"<<prsch_v[8]<<" ft"<<endl;
        cout <<" [DIST]"<<dist[2]<<"-"<<dist[3]<<" nmi"<<endl;
        cout <<"APPROACH-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-"<<endl;
        cout <<"  [SPD]"<<prsch_v[9]<<" KT"<<endl;
        cout <<"  [V S]700 ft/min"<<endl;
        cout <<"  [ALT]"<<prsch_v[8]<<" ft->"<<prsch_v[10]<<" ft"<<endl;
        cout <<" [DIST]"<<dist[3]<<"-0 nmi"<<endl;
        cout <<"INFORMATION-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_"<<endl;
        cout <<" [TOTAL DISTANCE]"<<prsch_v[4]<<" nmi"<<endl;
        float time=eqx(prsch_v[5],prsch_v[0],prsch_v[1],prsch_v[2],prsch_v[3])/((prsch_v[2]+prsch_v[1])/2)+(prsch_v[4]-eqx(prsch_v[5],0,prsch_v[1],prsch_v[2],prsch_v[3])-dist[1])/prsch_v[2]+(dist[1]-dist[2])/((prsch_v[2]+prsch_v[7])/2)+(dist[2]-dist[3])/((prsch_v[7]+prsch_v[9])/2)+dist[3]/prsch_v[9];
        cout <<" [EST. TIME(hr)]"<<round(time*100)/100<<" hr"<<endl;
}
void prsch(){
    redo:
    system("clear");
    string in_val_s="";

    int option=1;
    const int quantity_option=13;
    double in_val[quantity_option]={0,0,0,0,0,0,0,0,0,0,0,0,0};
    string options[quantity_option]={"DEP. ALTITUDE(ft)","V2 SPEED(KT)","CRUISING SPEED(KT&MACH)","CLIMBING SPEED(ft/min)","DISTANCE(nmi)","CRUISING ALTITUDE(ft)","DESCENDING SPEED(KT)","DESCENDING ALTITUDE SPEED(ft/min)","APP. ALTITUDE(ft)","APP. SPEED(KT)","LAND. ALTITUDE(ft)","Continue","Exit"};
    /*                                        0                  1                  2                  3                           4                  5                     6                           7                                8                  9                  10 */
    if(v2!=0){
        in_val[1]=v2;
    }
    if(vapp!=0){
        in_val[9]=vapp;
    }
    while(true){
        system("clear");
        cout <<title<<endl;
        cout <<"Pre-Schedule"<<endl;
        for(int i=1;i<=quantity_option;i++){
            if(options[i-1]=="Continue"||options[i-1]=="Exit"){
                cout <<options[i-1];
                if(option==i){
                    cout <<"<-"<<endl;
                }else cout <<endl;
                continue;
            }
            cout <<" ";
            cout <<options[i-1]<<':';
            if(i==option){
                cout <<'[';
            }
            cout <<in_val[i-1];
            if(i==option){
                cout <<']';
            }
            cout <<endl;
        }
        cout <<in_val_s;

        char ch=getchar();
        if((ch=='w'||ch=='W')&&option>1){
            option--;
        }else if((ch=='s'||ch=='S')&&option<quantity_option){
            option++;
        }else if(ch=='\n'){
            if(option==quantity_option){
                return ;
            }if(option==quantity_option-1){
                break;
            }

            if(in_val_s==""||!isNum(in_val_s)){
                in_val_s="ERROR";
                continue;
            }
            in_val[option-1]=stof(in_val_s);
            in_val_s="";
            option++;
        }else if(ch==127){
            if(in_val_s.length()>0){
                in_val_s.erase(in_val_s.length()-1);
            }
        }else{
            in_val_s+=ch;
        }
    }
    if(in_val[2]<=2.3){
        in_val[2]=in_val[2]*661.47; // Convert to knots
    }
    for(int i=0;i<11;i++){
        prsch_v[i]=in_val[i];
    }
    
    dist[0]=eqx(prsch_v[5],prsch_v[0],prsch_v[1],prsch_v[2],prsch_v[3]); //5->0
    dist[3]=eqx(prsch_v[8],prsch_v[10],prsch_v[9],prsch_v[9],700);
    dist[2]=dist[3]+15;
    Salt=eqh(prsch_v[8],prsch_v[6],prsch_v[9],500,15);
    dist[1]=eqx(prsch_v[5],Salt,prsch_v[2],prsch_v[6],prsch_v[7])+dist[2];

    if(prsch_v[4]<(prsch_v[4]-dist[0])||(prsch_v[4]-dist[0])<dist[1]||dist[1]<dist[2]||dist[2]<dist[3]||dist[3]<0){
        cout <<"ERROR: Distance is not valid!"<<endl;
        sleep(1);
        goto redo;
    }
    int option2=1;
    while(true){
        system("clear");
        cout <<title<<endl;
        cout <<"Pre-Schedule(Preview)"<<endl;
        planning();
        cout <<endl;

        const int quantity_option2=2;
        string options2[quantity_option2]={"Save&Back","Redo"};
        
        for(int i=1;i<=quantity_option2;i++){
            if(i==option2){
                cout <<"[";
            }
            cout <<options2[i-1];
            if(i==option2){
                cout <<"]"<<endl;
            }else{
                cout <<endl;
            }
        }
        
        char ch2=getchar();
        if((ch2=='w'||ch2=='W')&&option2>1){
            option2--;
        }else if((ch2=='s'||ch2=='S')&&option2<quantity_option2){
            option2++;
            cout <<option2<<endl;
        }else if(ch2=='\n'){
            if(option2==1){
                prsch_show=true;
                return ;
            }else if(option2==2){
                goto redo;
            }
        }
    }
}
void STALL(){
    system("clear");
    float S,Cl;
    int option=1;
    const int quantity_option=4;
    while(true){
        system("clear");
        cout <<title<<endl;
        cout <<"Select Aircraft"<<endl;
        string options[quantity_option]={"Boeing 737-800","Airbus A330-300","Boeing 787-9","Exit"};
        for(int i=1;i<=quantity_option;i++){
            cout <<" ";
            if(i==option){
                cout <<"[";
            }
            cout <<options[i-1];
            if(i==option){
                cout <<"]"<<endl;
                continue;
            }
            cout <<endl;
        }
        char ch=getchar();
        if((ch=='w'||ch=='W')&&option>1){
            option--;
        }else if((ch=='s'||ch=='S')&&option<quantity_option){
            option++;
        }else if(ch=='\n'){
            if(option==1){
                S=124.6;
                Cl=0.17;
            }else if(option==2){
                S=361.6;
                Cl=0.11;
            }else if(option==3){
                S=325;
                Cl=0.14;
            }else if(option==quantity_option){
                return ;
            }
            break;
        }
    }

    float mass,height;
    string in_val_s="";
    option=1;
    const int quantity_option2=4;
    string options_ame_off[quantity_option2]={"Height(ft)","Weight(kg)","Continue","Exit"};
    string options_ame[quantity_option2]={"Height(ft)","Weight(lb)","Continue","Exit"};
    float value[quantity_option2]={0,0,0};
    while(true){
        system("clear");
        cout <<title<<endl;
        cout <<"Input Values"<<endl;
        for(int i=1;i<=quantity_option2;i++){
            cout <<" ";
            if(ame==false){
                cout <<options_ame_off[i-1];
            }else{
                cout <<options_ame[i-1];
            }
            if(option==i&&i<quantity_option2-1){
                cout <<':';
                cout <<'['<<value[i-1]<<']'<<endl;
            }else if(i<quantity_option2-1){
                cout <<':';
                cout <<value[i-1]<<endl;
            }else if(option!=i){
                cout <<endl;
            }

            if(option==i&&i>=quantity_option2-1){
                cout <<"<-"<<endl;
            }
        }
        cout <<endl<<in_val_s;

        char ch=getchar();
        if((ch=='w'||ch=='W')&&option>1){
            option--;
        }else if((ch=='s'||ch=='S')&&option<quantity_option2){
            option++;
        }else if(ch=='\n'){
            if(in_val_s==""&&option<quantity_option2-1){
                option++;
                continue;
            }
            if(ame==false&&isNum(in_val_s)){
                if(option==1){
                    height=stof(in_val_s);
                    value[0]=height;
                }else if(option==2){
                    mass=stof(in_val_s);
                    value[1]=mass;
                }else if(option==quantity_option2-1){
                    break;
                }else if(option==quantity_option2){
                    return;
                }
            }else if(ame==true&&isNum(in_val_s)){
                if(option==1){
                    height=stof(in_val_s);
                    value[0]=height;
                }else if(option==2){
                    mass=stof(in_val_s);
                    value[1]=mass;
                    mass=mass/2.20462;
                }else if(option==quantity_option2-1){
                    break;
                }else if(option==quantity_option2){
                    return ;
                }
            }else{
                in_val_s="ERROR";
                continue;
            }
            option++;
            in_val_s="";
        }else if(ch==127){
            if(in_val_s.length()>0){
                in_val_s.erase(in_val_s.length()-1);
            }
        }else{
            in_val_s+=ch;
        }
    }
    stall=(int)(stall_speed(mass,S,height,Cl)*1.94384);
}
void Setting(){
    int option=1;
    const int quantity_option=2;
    while(true){
        system("clear");
        cout <<title<<endl;
        
        string options[quantity_option]={"American system","Exit"};
        cout <<"Options"<<endl;
        for(int i=1;i<=quantity_option;i++){
            cout <<"     ";
            if(i==option){
                cout <<"[";
            }
            if(i==1&&ame==false){
                cout <<"Metric system";
                goto next;
            }
            cout <<options[i-1];
            next:
            if(i==option){
                cout <<"]"<<endl;
                continue;
            }
            cout <<endl;
        }
        // setNonCanonicalMode();
        char ch=getchar();
        if((ch=='w'||ch=='W')&&option>1){
            option--;
        }else if((ch=='s'||ch=='S')&&option<=quantity_option){
            option++;
        }else if(ch=='\n'){
            if(option==1) ame=!ame;
            if(option==quantity_option) return;
        }
    }
}
void self_check(){

}
int main()
{
    cout <<title<<endl;
    self_check();
    char ch;
    int option=1;
    const int quantity_option=6;
    string options[quantity_option]={"V2 Speed","Pre-Schedule","Stall Speed","Vapp Speed","Setting","Exit"};
    while(true){
        system("clear");
        cout <<title<<endl;
        if(prsch_show==true){
            planning();
            cout <<endl;
        }
        if(v2!=0&&prsch_show==false){
            cout <<"V2 Speed: "<<v2<<" knot "<<v2*0.00149984<<" mach"<<endl;
        }
        if(stall!=0){
            cout <<"Stall Speed: "<<stall<<" knot "<<stall*0.00149984<<" mach"<<endl;
        }
        if(vapp!=0){
            cout <<"Vapp Speed: "<<vapp<<" knot "<<vapp*0.00149984<<" mach"<<endl;
        }
        if(ame==true){
            cout <<"<American system>"<<endl;
        }else{
            cout <<"<Metric system>"<<endl;
        }
        for(int i=1;i<=quantity_option;i++){
            cout <<"     ";
            if(i==option){
                cout <<"[";
            }
            cout <<options[i-1];
            if(i==option){
                cout <<"]"<<endl;
                continue;
            }
            cout <<endl;
        }
        setNonCanonicalMode();
        ch=getchar();
        if((ch=='w'||ch=='W')&&option>1){
            option--;
        }else if((ch=='s'||ch=='S')&&option<quantity_option){
            option++;
        }else if(ch=='\n'){
            if(option==1){
                V2();
            }else if(option==2){
                prsch();
            }else if(option==3){
                STALL();
            }else if(option==4){
                VAPP();
            }else if(option==quantity_option-1){
                Setting();
            }else if(option==quantity_option){
                return 0;
            }
        }
    }

    return 0;
}