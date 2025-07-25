const double Tk=273.15,R=287.05,g=9.81,T0=288.15,L=0.0065,P0=101325,GMRL=5.248,RP=8.314;
// Fl=(1/2)*rho*S*v^2*Cl
double v2_speed(float mass, float S_without, float S_within, int pos, int quan, float pa, float t, float Cl){
    //S_without means the wing's area without flaps, S_within means the wing's area with flaps
    //pos means the position of the flaps, quan means the quantity of the flaps
    //pa means the pressure of the air, unit is Pa
    double S=S_without+(S_within-S_without)*(pos/quan);
    double rho=pa/(R*(t+Tk));
    double mg=mass*g;
    double V2=sqrt((2*mg)/(rho*S*Cl));
    return V2;
}
double stall_speed(float mass, float S, float h, float Cl){
    return sqrt((2*RP*mass*g*(T0-L*h))/(S*Cl*P0*pow((1-(L*h)/T0),GMRL)));
}
double eqx(double h0,double ht,double v0,double vt,double vs){
    double h=h0-ht,v=v0+vt;
    return h*v/120/vs;
}
double eqh(double ht,double v0,double vt,double vs,double x){
    double k=x*120*vs;
    return k/(v0+vt)+ht;
}