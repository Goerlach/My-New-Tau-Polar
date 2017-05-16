#include "a1Helper.h"
#include <iostream>


a1Helper::a1Helper(){
   mpi   = 0.13957018; // GeV 
   mpi0 = 0.1349766;   // GeV
   mtau = 1.776; // GeV
   coscab = 0.975; 
   mrho = 0.773; // GeV
   mrhoprime = 1.370; // GeV
   ma1 = 1.251; // GeV
   mpiprime = 1.300; // GeV
   Gamma0rho  =0.145; // GeV
   Gamma0rhoprime = 0.510; // GeV
   Gamma0a1 = 0.599; // GeV
   Gamma0piprime = 0.3; // GeV
   fpi= 0.093; // GeV
   fpiprime = 0.08; //GeV
   gpiprimerhopi = 5.8; //GeV
   grhopipi = 6.08;  //GeV
   beta = -0.145;
}
void 
a1Helper::Configure(TLorentzVector OSPion, TLorentzVector SSPion1, TLorentzVector SSPion2,TLorentzVector TauA1, TLorentzVector TauMu  ){


  Z_ =TauA1 + TauMu;
  TLorentzVector A1LabFrame = OSPion + SSPion1 + SSPion2;

   // OSPionZFrame_ = Boost(OSPion,Z_);
   // SSPion1ZFrame_= Boost(SSPion1,Z_);
   // SSPion2ZFrame_= Boost(SSPion2,Z_);
   // A1ZFrame_     = Boost(A1LabFrame,Z_);

   OSPionZFrame_ = OSPion;
   SSPion1ZFrame_= SSPion1;
   SSPion2ZFrame_= SSPion2;
   A1ZFrame_     = A1LabFrame;

   TauA1_ = TauA1;
  // std::cout<<"A1 Lab Frame  "<< A1LabFrame.Px() << "  " <<A1LabFrame.Py() << " "<< A1LabFrame.Pz() << "  " <<A1LabFrame.E()<<std::endl;
  // std::cout<<"A1 Z frame    "<< A1ZFrame_.Px() << "  "<< A1ZFrame_.Py() << " "<< A1ZFrame_.Pz() << "  " <<A1ZFrame_.E()<<std::endl;
  // std::cout<<"Z   "<< Z_.Px() << "  "<< Z_.Py() << " "<< Z_.Pz() << "  " <<Z_.E()<<std::endl;

}




void 
a1Helper::SetParametersReco(TLorentzVector tau, TLorentzVector mu ){
 Initialize(tau,mu);
}
void 
a1Helper::SetFrame(TLorentzVector vec){
  Boost_ = vec;
}



a1Helper::~a1Helper(){
}



void 
a1Helper::Initialize(TLorentzVector t, TLorentzVector mu){
  RecoMuon_=mu;
  KFitTau_=t;
}

double 
a1Helper::costheta(){
  
  TLorentzVector p1 = SSPion1ZFrame_;
  TLorentzVector p2 = SSPion2ZFrame_;
  TLorentzVector p3 = OSPionZFrame_;
  TLorentzVector Z=Z_;

  
  double zmass = Z.M();
  double mtau = 1.777;
  TLorentzVector a1 = p1+p2+p3;
  float QQ = a1.E()*a1.E() - a1.P()*a1.P();

  double x = a1.E()/TauA1_.E();
  double ctheta = (2*x*mtau*mtau - mtau*mtau - QQ)/((mtau*mtau - QQ)*sqrt(1 - 4*mtau*mtau/zmass/zmass));
  // std::cout<<"p1 "<< p1.Px() << "  " <<p1.Py() << " "<< p1.Pz() << "  " <<p1.M()<<std::endl;
  // std::cout<<"p2 "<< p2.Px() << "  "<< p2.Py() << " "<< p2.Pz() << "  " <<p2.M()<<std::endl;
  // std::cout<<"p3 "<< p3.Px() << "  "<< p3.Py() << " "<< p3.Pz() << "  " <<p3.M()<<std::endl;
  // std::cout<<"a1 "<< a1.Px() << "  "<< a1.Py() << " "<< a1.Pz() << "  " <<a1.M()<<"  " <<a1.M()*a1.M() <<std::endl;
  // std::cout<<"QQ "<< QQ << " x "<< x <<" zmass  " <<zmass <<std::endl;

  //  std::cout<<"2*x*mtau*mtau/mtau*mtau - QQ "<< 2*x*mtau*mtau/(mtau*mtau - QQ)<< "  "<< x <<std::endl;
  return ctheta;
}


double 
a1Helper::costheta1(){
  
  TLorentzVector p1 = SSPion1ZFrame_;
  TLorentzVector p2 = SSPion2ZFrame_;
  TLorentzVector p3 = OSPionZFrame_;
  TLorentzVector Z=Z_;

  double zmass = Z.M();
  double mt = 1.777;
  TLorentzVector a1 = p1+p2+p3;
  double ma  = a1.M();
  double diffmass = mt*mt - ma*ma;
  float QQ = a1.E()*a1.E() - a1.P()*a1.P();

  double x = 2*a1.E()/zmass;
  double ctheta = 4*mt*mt*a1.E()/zmass/diffmass   - (mt*mt + ma*ma)/diffmass;
  return ctheta;

}


float 
a1Helper::CosBeta(){
  TLorentzVector p1 = SSPion1ZFrame_;
  TLorentzVector p2 = SSPion2ZFrame_;
  TLorentzVector p3 = OSPionZFrame_;

  float mpi  = 0.139;
//   float E = p1.E() +  p2.E() +  p3.E(); 
//   float P = p1.P() +  p2.P() +  p3.P(); 
//   float QQ = E*E - P*P;


//   std::cout<<"  cosbeta --------------------- "<<std::endl;

  TLorentzVector a1 = p1+p2+p3;
  float QQ = a1.E()*a1.E() - a1.P()*a1.P();

  float B1 = (pow(p1.E()*a1.E()   - Scalar(p1,a1),2 ) - QQ*mpi*mpi)/QQ;
  float B2 = (pow(p2.E()*a1.E()   - Scalar(p2,a1),2 ) - QQ*mpi*mpi)/QQ;
  float B3 = (pow(p3.E()*a1.E()   - Scalar(p3,a1),2 ) - QQ*mpi*mpi)/QQ;

  float T = 0.5*sqrt(-lambda(B1,B2,B3));

  TLorentzVector p1Timesp2(p1.Py()*p2.Pz() - p1.Pz()*p2.Py(),p1.Pz()*p2.Px() - p1.Px()*p2.Pz(),p1.Px()*p2.Py() - p1.Py()*p2.Px(),1);
    
    
  float cbeta = Scalar(p3,p1Timesp2)/a1.P()/T;

//   std::cout<<"  T  "<< T<<std::endl;
//   std::cout<<"  B1  "<< B1<<std::endl;
//   std::cout<<"  B2  "<< B2<<std::endl;
//   std::cout<<"  B3  "<< B3<<std::endl;
//   std::cout<<"  QQ  "<< QQ<<std::endl;
//   std::cout<<"  Scalar(p3,p1Timesp2)  "<< Scalar(p3,p1Timesp2)<<std::endl;
//   std::cout<<"  cbeta  "<< cbeta  <<std::endl;


  return cbeta;

}


double 
a1Helper::CosBeta1(){
  TLorentzVector p1 = SSPion1ZFrame_;
  TLorentzVector p2 = SSPion2ZFrame_;
  TLorentzVector p3 = OSPionZFrame_;


  //std::cout<<"  cosbeta1  ================================= "<<std::endl;
  double mpi  = 0.139;
//   double E = p1.E() +  p2.E() +  p3.E(); 
//   double P = p1.P() +  p2.P() +  p3.P(); 
//   double QQ = E*E - P*P;

  TLorentzVector a1 = p1+p2+p3;
  //  float P = 
  TLorentzVector s12 = p1+p2;
  TLorentzVector s13 = p1+p3;
  TLorentzVector s23 = p2+p3;

  double QQ = a1.E()*a1.E() - a1.P()*a1.P();


  TLorentzVector p1Timesp2(p1.Py()*p2.Pz() - p1.Pz()*p2.Py(),p1.Pz()*p2.Px() - p1.Px()*p2.Pz(),p1.Px()*p2.Py() - p1.Py()*p2.Px(),1);
  float mm=a1.M()*a1.M();
  float mm12=s12.M()*s12.M();
  float mm13=s13.M()*s13.M();
  float mm23=s23.M()*s23.M();
  float mmpi=mpi*mpi;

  float l1  = lambda( mm, mm12 , mmpi);
  float l2  = lambda( mm, mm13 , mmpi);
  float l3  = lambda( mm, mm23 , mmpi);

 
  double cbeta = /*8*a1.M()*a1.M()**/Scalar(p3,p1Timesp2)*a1.P()/sqrt(-lambda(l1,l2,l3));

//   std::cout<<"  QQ  "<< QQ<<std::endl;
//   std::cout<<"  mm12  "<< mm12<<std::endl;
//   std::cout<<"  mm13  "<< mm13<<std::endl;
//   std::cout<<"  mm23  "<< mm23<<std::endl;
//   std::cout<<"  mm  "<< mm<<std::endl;

//   std::cout<<"  lambda1 = "<<l1<<std::endl;
//   std::cout<<"  lambda2 = "<<l2<<std::endl;
//   std::cout<<"  lambda3 = "<<l3<<std::endl;
//   std::cout<<"  lambda  = "<<-lambda(l1,l2,l3)<<std::endl;

  
//   std::cout<<"  Scalar(p3,p1Timesp2)*a1.P()  "<< Scalar(p3,p1Timesp2)<<std::endl;
//   std::cout<<"  a1.P()  "<< a1.P() <<std::endl;

//   std::cout<<"  a1.P()  "<< a1.P() << "   *  "<</*8*a1.M()*a1.M()**/Scalar(p3,p1Timesp2)/sqrt(-lambda(l1,l2,l3)) <<std::endl;



//   std::cout<<"  cbeta  "<< cbeta  <<std::endl;



  return cbeta;

}




double 
a1Helper::lambda(double x, double y, double z){
    return x*x +y*y +z*z - 2*x*y - 2*x*z - 2*z*y;
}
TLorentzVector 
a1Helper::Boost(TLorentzVector pB, TLorentzVector frame){
   TMatrixT<double> transform(4,4);
   TMatrixT<double> result(4,1);
   TVectorT<double> vec(4); 
   TVector3 b;
    if(frame.E()==0){ std::cout<<" Caution: Please check that you perform boost correctly!  " <<std::endl; return pB;} 
   else   b=frame.Vect()*(1/frame.E());
   vec(0)  = pB.E();    vec(1)  = pB.Px();
   vec(2)  = pB.Py();  vec(3)  = pB.Pz();
   double gamma  = 1/sqrt( 1 - b.Mag2());
   transform(0,0)=gamma; transform(0,1) =- gamma*b.X() ;  transform(0,2) =  - gamma*b.Y();  transform(0,3) = - gamma*b.Z(); 
   transform(1,0)=-gamma*b.X(); transform(1,1) =(1+ (gamma-1)*b.X()*b.X()/b.Mag2()) ;  transform(1,2) = ((gamma-1)*b.X()*b.Y()/b.Mag2());  transform(1,3) = ((gamma-1)*b.X()*b.Z()/b.Mag2());
   transform(2,0)=-gamma*b.Y(); transform(2,1) = ((gamma-1)*b.Y()*b.X()/b.Mag2());  transform(2,2) = (1 + (gamma-1)*b.Y()*b.Y()/b.Mag2());  transform(2,3) =  ((gamma-1)*b.Y()*b.Z()/b.Mag2()); 
   transform(3,0)=-gamma*b.Z(); transform(3,1) =((gamma-1)*b.Z()*b.X()/b.Mag2()) ;  transform(3,2) = ((gamma-1)*b.Z()*b.Y()/b.Mag2());  transform(3,3) = (1 + (gamma-1)*b.Z()*b.Z()/b.Mag2()); 
   result=transform*convertToMatrix(vec);
   return TLorentzVector(result(1,0), result(2,0) ,result(3,0), result(0,0));
}
double 
a1Helper::Scalar(TLorentzVector p1, TLorentzVector p2){
    return p1.Vect()*p2.Vect();
}

std::vector<float> 
a1Helper::Sin2Cos2Gamma(TLorentzVector p1,TLorentzVector p2, TLorentzVector p3){

  std::vector<float> sin2cos2;
  float mpi  = 0.139;
  TLorentzVector a1 = p1+p2+p3;
  float QQ = a1.E()*a1.E() - a1.P()*a1.P();

  float B1 = (pow(p1.E()*a1.E()   - Scalar(p1,a1),2 ) - QQ*mpi*mpi)/QQ;
  float B2 = (pow(p2.E()*a1.E()   - Scalar(p2,a1),2 ) - QQ*mpi*mpi)/QQ;
  float B3 = (pow(p3.E()*a1.E()   - Scalar(p3,a1),2 ) - QQ*mpi*mpi)/QQ;

  float T = 0.5*sqrt(-lambda(B1,B2,B3));

  float A1=(a1.E()*Scalar(a1,p1) - p1.E()*a1.P()*a1.P())/QQ;
  float A2=(a1.E()*Scalar(a1,p2) - p2.E()*a1.P()*a1.P())/QQ;
  float A3=(a1.E()*Scalar(a1,p3) - p3.E()*a1.P()*a1.P())/QQ;


  float cosgamma = A3/a1.P()/sqrt(B3)/sqrt(1 - CosBeta()*CosBeta());
  float singamma = -cosgamma*(B3*A1/A3 - 0.5*(B2 - B1 - B3))/T;

  sin2cos2.push_back(2*singamma*cosgamma);
  sin2cos2.push_back(2*cosgamma*cosgamma - 1);
  return sin2cos2;

}



float 
a1Helper::CosPsi(){

  TLorentzVector p1 = SSPion1ZFrame_;
  TLorentzVector p2 = SSPion2ZFrame_;
  TLorentzVector p3 = OSPionZFrame_;
  TLorentzVector Z=Z_;

  float mtau =1.777;
  TLorentzVector a1 = p1+p2+p3;
  float QQ = a1.E()*a1.E() - a1.P()*a1.P();
  float cos = (costheta()*(mtau*mtau  + QQ)   + (mtau*mtau  - QQ))/(costheta()*(mtau*mtau  - QQ)   + (mtau*mtau  + QQ));
  return cos;

}

 



//---------------------------------------  hadronic current ---------------------------
// float a1Helper::WA(TLorentzVector s1,TLorentzVector s2,TLorentzVector s3,float QQ){

//   float SS1 = (s2+s3).M()*(s2+s3).M();
//   float SS2 = (s1+s3).M()*(s1+s3).M();
//   float SS3 = (s1+s2).M()*(s1+s2).M();

//  return  VV1(SS1,SS2,SS3,QQ)*F(SS1,SS2,QQ).Rho2() + VV2(SS1,SS2,SS3,QQ)*F(SS2,SS1,QQ).Rho2()  + 2*V1V2(SS1,SS2,SS3,QQ)*( F(SS2,SS1,QQ)*Conjugate(F(SS1,SS2,QQ)) ).Re();
// }

// float a1Helper::WC(TLorentzVector s1,TLorentzVector s2,TLorentzVector s3,float QQ){

//   float SS1 = (s2+s3).M()*(s2+s3).M();
//   float SS2 = (s1+s3).M()*(s1+s3).M();
//   float SS3 = (s1+s2).M()*(s1+s2).M();

//   return  (VV1(SS1,SS2,SS3,QQ) - 2*h(SS1,SS2,SS3,QQ))*F(SS1,SS2,QQ).Rho2() + (VV2(SS1,SS2,SS3,QQ) - 2*h(SS1,SS2,SS3,QQ))*F(SS2,SS1,QQ).Rho2() +   (2*V1V2(SS1,SS2,SS3,QQ) + 4*h(SS1,SS2,SS3,QQ))*( F(SS2,SS1,QQ)*Conjugate(F(SS1,SS2,QQ)) ).Re();
// } 

// float
// a1Helper::WD(TLorentzVector s1,TLorentzVector s2,TLorentzVector s3,float QQ){
//   float SS1 = (s2+s3).M()*(s2+s3).M();
//   float SS2 = (s1+s3).M()*(s1+s3).M();
//   float SS3 = (s1+s2).M()*(s1+s2).M();
//   float mpi = 0.139;
//   float undersqrt1 = VV1(SS1,SS2,SS3,QQ)  -h(SS1,SS2,SS3,QQ);
//   float undersqrt2 = VV2(SS1,SS2,SS3,QQ)  -h(SS1,SS2,SS3,QQ);

//   if(undersqrt1 < 0) undersqrt1 =0;
//   if(undersqrt2 < 0) undersqrt2 =0;

//   //std::cout<<" debug Wd "<<h(SS1,SS2,SS3,QQ)<<" VV1(SS1,SS2,SS3,QQ)   "<<VV1(SS1,SS2,SS3,QQ) <<"  "<<VV2(SS1,SS2,SS3,QQ)<<"   "<<-h0(SS1,SS2,SS3,QQ) <<"  "<< ( F(SS2,SS1,QQ)*Conjugate(F(SS1,SS2,QQ)) ).Re()<<"   " <<VV1(SS1,SS2,SS3,QQ)  -h(SS1,SS2,SS3,QQ) << "    " << VV2(SS1,SS2,SS3,QQ)  -h(SS1,SS2,SS3,QQ)<<std::endl;
//   //  return  -sqrt(h(SS1,SS2,SS3,QQ))*(2*sqrt(VV1(SS1,SS2,SS3,QQ)  -h(SS1,SS2,SS3,QQ)) *F(SS1,SS2,QQ).Rho2() - 2*sqrt(VV2(SS1,SS2,SS3,QQ)  -h(SS1,SS2,SS3,QQ))*F(SS2,SS1,QQ).Rho2()  
//   //				    + (QQ- mpi*mpi + SS3)*(SS1 - SS2 )*( F(SS2,SS1,QQ)*Conjugate(F(SS1,SS2,QQ)) ).Re()/QQ/sqrt(-h0(SS1,SS2,SS3,QQ)));

//   return  -sqrt(h(SS1,SS2,SS3,QQ))*(2*sqrt(undersqrt1) *F(SS1,SS2,QQ).Rho2() - 2*sqrt(undersqrt2)*F(SS2,SS1,QQ).Rho2()  
// 				    + (QQ- mpi*mpi + SS3)*(SS1 - SS2 )*( F(SS2,SS1,QQ)*Conjugate(F(SS1,SS2,QQ)) ).Re()/QQ/sqrt(-h0(SS1,SS2,SS3,QQ)));


// }

// float
// a1Helper::WE(TLorentzVector s1,TLorentzVector s2,TLorentzVector s3,float QQ){
//   float SS1 = (s2+s3).M()*(s2+s3).M();
//   float SS2 = (s1+s3).M()*(s1+s3).M();
//   float SS3 = (s1+s2).M()*(s1+s2).M();
//   return  -3*sqrt(-h(SS1,SS2,SS3,QQ)*h0(SS1,SS2,SS3,QQ))*( F(SS2,SS1,QQ)*Conjugate(F(SS1,SS2,QQ)) ).Im();

// }


// TComplex 
// a1Helper::F(float s1, float s2,float QQ){


//   float beta= -0.145;
//   float fpi= 0.093;


//   TComplex factor(0,-2*sqrt(2)/3/fpi/(1+beta));
//   TComplex BreighWignerRhoPrime(beta*BWrhoPrime(s2).Re(), beta*BWrhoPrime(s2).Im());
//   TComplex out = factor*BWa1(QQ)*(BWrho(s2) + BreighWignerRhoPrime);
//   return out;
// }


double
a1Helper::VV1(double s1 ,double  s2, double  s3, double  Q){ //  this is -V1^{2}
  double QQ = Q*Q;
  return  s2 - 4*mpi*mpi + pow(s3 - s1,2)/4/QQ;
}

double
a1Helper::VV2(double s1 ,double s2,double  s3, double Q){ //  this is -V2^{2}
  double QQ = Q*Q;
  return  s1 - 4*mpi*mpi + pow(s3 - s2,2)/4/QQ;
}

double
a1Helper::V1V2(double s1, double s2, double s3, double Q){  // this is -V1V2
  double QQ = Q*Q;
  return  (QQ/2 - s3 - 0.5*mpi*mpi) + (s3 - s1)*(s3 - s2)/4/QQ;
}


double
a1Helper::h0(double s1, double s2, double s3, double Q){ // this is -3sqrt{h0}/2
  double QQ = Q*Q;
  return 4*mpi*mpi - pow(2*mpi*mpi - s1 - s2,2)/QQ;
}

double
a1Helper::h(double s1, double s2, double s3, double Q){
  double QQ = Q*Q;
  return (s1*s2*s3 - mpi*mpi*pow(QQ - mpi*mpi,2))/pow(-2*h0(s1,s2,s3,QQ)/3,2)/QQ;  // this is sqrt{h}
}



TComplex 
a1Helper::F1(double s1, double s2, double Q){
  double QQ = Q*Q;
  TComplex scale(0, -2*sqrt(2)/3/fpi);
  TComplex res = scale*BreitWigner(Q,"a1")*BRho(s2);
  return res;
}


TComplex 
a1Helper::F2(double s1, double s2, double Q){
  double QQ = Q*Q;
  TComplex scale(0, -2*sqrt(2)/3/fpi);
  TComplex res = scale*BreitWigner(Q,"a1")*BRho(s1);
  return res;
}

TComplex 
a1Helper::F4(double s1, double s2, double s3, double Q){
  double QQ = Q*Q;
  TComplex scale(0, -gpiprimerhopi*grhopipi*fpiprime/2/pow(mrho,4)/pow(mpiprime,3));
  TComplex res = scale*BreitWigner(Q,"piprime")*(s1*(s2-s3)*BRho(s1) + s2*(s1-s3)*BRho(s2));
  return res;
}


TComplex 
a1Helper::BRho(double Q){
  return (BreitWigner(Q) + beta*BreitWigner(Q,"rhoprime"))/(1+beta);
}

TComplex 
a1Helper::BreitWigner(double Q, string type){
  double QQ=Q*Q;
  double re,im;
  double m = Mass(type);
  double g  = Widths(Q,type);
  re = (m*m*pow(m*m - QQ,2))/(pow(m*m - QQ,2) + m*m*g*g);
  im = m*m*m*g/(pow(m*m - QQ,2) + m*m*g*g);
  TComplex out(re,im);
  return out;
}

double
a1Helper::Widths(double Q, string type){
  double QQ = Q*Q;
  double Gamma;
  Gamma = Gamma0rho*mrho*pow( ppi(QQ)  / ppi(mrho*mrho), 3) /sqrt(QQ);
  if(type == "rhoprime"){
    Gamma=Gamma0rhoprime*QQ/mrhoprime/mrhoprime;
 }
  if(type == "a1"){
    Gamma=Gamma0a1*ga1(Q)/ga1(ma1);
 }
  if(type == "piprime"){
    Gamma = Gamma0piprime*pow( sqrt(QQ)/mpiprime  ,5)*pow( (1-mrho*mrho/QQ)/(1-mrho*mrho/mpiprime/mpiprime) ,3);
  }

  std::cout<< "  type   " << type << " Gamma  " << Gamma <<std::endl;
  return Gamma;
}
double a1Helper::ga1(double  Q){
  double QQ = Q*Q;
  return (QQ > pow(mrho + mpi,2)) ?  QQ*(1.623 + 10.38/QQ - 9.32/QQ/QQ   + 0.65/QQ/QQ/QQ)  : 4.1*pow(QQ - 9*mpi*mpi,3)*(  1 - 3.3*(QQ - 9*mpi*mpi)  + 5.8*pow(QQ - 9*mpi*mpi,2)  );
}
double
a1Helper::Mass(string type){
  double m = mrho;
  if(type == "rhoprime") return mrhoprime; 
  if(type == "a1") return ma1;
  if(type == "piprime") return mpiprime;

  std::cout<< "  type   " << type << " Mass  " << std::endl;

  return m;
}
// double a1Helper::ga1(double  Q){
//   double QQ = Q*Q;
//   return (QQ > pow(mrho + mpi,2)) ?  QQ*(1.623 + 10.38/QQ - 9.32/QQ/QQ   + 0.65/QQ/QQ/QQ)  : 4.1*pow(QQ - 9*mpi*,mpi,3)*(  1 - 3.3*(QQ - 9*mpi*mpi)  + 5.8*pow(QQ - 9*mpi*mpi,2)  );
// }

double a1Helper::ppi(double QQ){return 0.5*sqrt(QQ - 4*mpi*mpi);}


// TComplex 
// a1Helper::BWa1(float QQ){
//   TComplex re,im;
//   re = (m*m*pow(m*m - QQ,2))/(pow(m*m - QQ,2) - m*m*GammaA1(QQ)*GammaA1(QQ));
//   im = m*m*m*GammaA1(QQ)/(pow(m*m - QQ,2) - m*m*GammaA1(QQ)*GammaA1(QQ));
//   TComplex out(re,im);
//   return out;
// }




// TComplex 
// a1Helper::BWrho(float QQ){
//   float m =  0.773;
//   TComplex re,im;
//   re = (m*m*pow(m*m - QQ,2))/(pow(m*m - QQ,2) - m*m*GammaRho(QQ)*GammaRho(QQ));
//   im = m*m*m*GammaRho(QQ)/(pow(m*m - QQ,2) - m*m*GammaRho(QQ)*GammaRho(QQ));
//   TComplex out(re,im);
//   return out;
// }




// TComplex 
// a1Helper::BWrhoPrime(float QQ){
//   float m =  1.251;
//   TComplex re,im;
//   re = (m*m*pow(m*m - QQ,2))/(pow(m*m - QQ,2) - m*m*GammaRhoPrime(QQ)*GammaRhoPrime(QQ));
//   im = m*m*m*GammaRhoPrime(QQ)/(pow(m*m - QQ,2) - m*m*GammaRhoPrime(QQ)*GammaRhoPrime(QQ));
//   TComplex out(re,im);
//   return out;
// }


// float
// a1Helper::GammaA1(float QQ){
//   float ma1 = 1.251;
//   float ga1 = 0.599;
//   float out = ga1*gForGammaA1(QQ)/gForGammaA1(ma1*ma1);
//   return out;
// }

// float
// a1Helper::gForGammaA1(float QQ){
//   float mpi  = 0.139;
//   float mrho = 0.773;
//   float out;
//   if(QQ > pow((mrho + mpi),2)){ out = QQ*(1.623 + 10.38/QQ - 9.34/QQ/QQ + 0.65/QQ/QQ/QQ);}
//   else out = 4.1*pow((QQ - 9*mpi*mpi),3)*(1- 3.3*(QQ - 9*mpi*mpi) + 5.8*pow(QQ - 9*mpi*mpi,2));
//   return out;
// }


// float
// a1Helper::GammaRho(float QQ){
//   float mpi  = 0.139;
//   float mrho = 0.773;
//   float grho = 0.599;
//   float out  =grho*mrho*pow( sqrt(QQ - 4*mpi*mpi)/sqrt(mrho*mrho - mpi*mpi)   ,3)/sqrt(QQ);
//   return out;
// }


// float
// a1Helper::GammaRhoPrime(float QQ){

//   float mrhoPrime = 1.370;
//   float grhoPrime = 0.510;
//   float out  =grhoPrime*QQ/mrhoPrime/mrhoPrime;
//   return out;
// }



// double
// a1Helper::GetOmegaA1(){
//         isValid_ = false;
//         double omega(-999.);
// 	TLorentzVector pi1 = SSPion1ZFrame_;
// 	TLorentzVector pi2 = SSPion2ZFrame_;
// 	TLorentzVector pi3 = OSPionZFrame_;
// 	TLorentzVector a = A1ZFrame_;
// 	float mtau = 1.777;
// 	float cospsi  = CosPsi();
// 	float sinpsi  = sqrt(1 - cospsi*cospsi);
// 	float sin2psi = 2*sinpsi*cospsi;
	
// 	float sin2gamma = Sin2Cos2Gamma(pi1,pi2,pi3).at(0);
// 	float cos2gamma = Sin2Cos2Gamma(pi1,pi2,pi3).at(1);
	
	
// 	float cosbeta=CosBeta();
// 	float sinbeta = sqrt(1  - cosbeta*cosbeta);
	
	  
// 	float cstheta=costheta();
// 	float sintheta = sqrt(1 - cstheta*cstheta);

// 	double RR  = mtau*mtau/a.M()/a.M();
// 	float U = 0.5*(3*cospsi*cospsi - 1)*(1 - RR);
// 	float V = 0.5*(3*cospsi*cospsi - 1)*(1 + RR)*cstheta + 0.5*3*sin2psi*sintheta*sqrt(RR);
// 	//	std::cout<< " cospsi  "<< cospsi <<" costheta  "<<costheta <<" sin2psi "<<sin2psi <<" sintheta  "<<sintheta  <<" RR  "<< RR <<std::endl;

// 	float Wa =WA(pi1,pi2,pi3,a.M()*a.M());
// 	float Wc =WC(pi1,pi2,pi3,a.M()*a.M());
// 	float Wd =WD(pi1,pi2,pi3,a.M()*a.M());
// 	float We =WE(pi1,pi2,pi3,a.M()*a.M());

// 	float fa1 = (2  + RR + 0.5*(3*cosbeta*cosbeta - 1)*U)*Wa/3 - 0.5*sinbeta*sinbeta*cos2gamma*U*Wc + 0.5*sinbeta*sinbeta*sin2gamma*U*Wd + cospsi*cosbeta*We;
// 	float ga1 = (cstheta*(RR -2) - 0.5*(3*cosbeta*cosbeta - 1)*V)*Wa/3 + 0.5*sinbeta*sinbeta*cos2gamma*V*Wc - 0.5*sinbeta*sinbeta*sin2gamma*V*Wd -cosbeta*(cstheta*cospsi + sintheta*sinpsi*sqrt(RR))*We;
// 	//	std::cout<< " U  "<< U <<" V  "<<V <<" Wa "<<Wa <<" Wc  "<<Wc  <<" Wd  "<< Wd <<" We  "<< We  <<" f "<< fa1 <<" g "<< ga1 <<std::endl;
// 	omega = ga1/fa1;
// 	if(omega > 0 or omega < 0) isValid_ = true;
// 	return omega;
// }

TComplex 
a1Helper::Conjugate(TComplex a){
  return TComplex(a.Re(), -a.Im());
}
TMatrixT<double> a1Helper::convertToMatrix(TVectorT<double> V){
  TMatrixT<double> M(V.GetNrows(),1);
  for(int i=0; i < M.GetNrows(); i++){
    M(i,0)=V(i);
  } return M;
}