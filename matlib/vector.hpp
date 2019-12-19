#pragma once

#include<stdexcept>
#include<math.h>
#include<iostream>
#include<regex>
#include<stdlib.h>
#include<memory>
#include<ctype.h>
#include"../types/bsp_types.hpp"

#define N 10


class Matrix;

class Vector{

 public:

  // Konstruktori
 Vector(std::vector<double> values): elements(values){
    dimension=values.size();
    };

 Vector(std::vector<double> values, bool read): elements(values), readOnly(read){
    dimension=values.size();
  };

  Vector(double x, double y, double z){
    this->elements.push_back(x);
    this->elements.push_back(y);
    this->elements.push_back(z);
    dimension=3;
  }

  Vector(double x, double y, double z, double h){
    this->elements.push_back(x);
    this->elements.push_back(y);
    this->elements.push_back(z);
    this->elements.push_back(h);

    dimension=4;
  }


  // Konstruktor za quake vector
  Vector(vec3_t& vec3){
    this->elements.push_back(vec3.x);
    this->elements.push_back(vec3.y);
    this->elements.push_back(vec3.z);
    dimension=elements.size();
  }

  Vector(vertex_t& vec3){
    this->elements.push_back(vec3.x);
    this->elements.push_back(vec3.y);
    this->elements.push_back(vec3.z);
    dimension=elements.size();
  }


  // Read-only operator
  Vector(){};
    double operator()(unsigned int index){
    if(index < elements.size()){
       return elements[index];
    }
    else
      throw std::invalid_argument("Index value is greater than vector size");
     };

  // Operator[]. Vraća vrijednost vektora ukoliko nije read-only i ako je index unutar dimenzije vektora
  virtual double& operator[](unsigned int index){
    if(index < elements.size()){
      if(!readOnly)
        return elements[index];
      else
        throw std::invalid_argument("Vector is read only!");
    }
    else
      throw std::invalid_argument("Index value is greater than vector size");
  };

  // Vraća std::vector<double> svih elemenata vektora
  virtual std::vector<double> toArray() const{
    return this->elements;
  };

  // Vraća dimenziju vektora
  virtual int getDimension() const{return this->dimension;};

  // Copy konstruktor
  /* Recursive function for finding determinant of matrix.
   n is current dimension of A[][]. */



  Vector(const Vector& vector){

    elements=vector.toArray();
    dimension=vector.getDimension();

    };
 Vector(Vector& vector): elements(vector.toArray()), dimension(vector.getDimension()){
   };

  // Kopira dio vektora i vraća nazad novi objekt
  virtual Vector copyPart(int noOfParts){
    if(noOfParts <= this->getDimension()){
      std::vector<double> tmp;
      for(int i=0; i<noOfParts; i++)
        tmp.push_back(this->elements[i]);
      return Vector(tmp);
    }else
      throw std::invalid_argument("Cannot copy more than vector size!");
  };

  // Zbraja dva vektora, rezultat pohranjuje u trenutnom vektoru
  virtual Vector& operator+(Vector& vector){
    if(this->dimension == vector.getDimension()){
      std::vector<double> tmp(vector.toArray());
      for(int i=0; i<this->getDimension(); i++){
        this->elements[i]+=tmp[i];
      }
      return *this;
    }else
      throw std::invalid_argument("Vector dimensions need to be equal!");
  };

  // Zbraja dva vektora i vraća novi objekt sa rezultatom
   Vector operator+=(Vector& vector){
     if(this->getDimension() == vector.getDimension()){
      std::vector<double> tmp(vector.toArray());
      Vector ret (*this);
      ret+vector;
      
      return Vector(*&ret);
    }else
      throw std::invalid_argument("Vector dimensions need to be equal!");
  
  };

  // Oduzima dva vektora, rezultat pohranjuje u trenutnom vektoru
  virtual Vector& operator-(Vector& vector){
    if(this->getDimension() == vector.getDimension()){
      std::vector<double> tmp(vector.toArray());
      for(int i=0; i<this->getDimension(); i++){
        this->elements[i]-=tmp[i];
      }
      return *this;
    }else
      throw std::invalid_argument("Vector dimensions need to be equal!");
  
  };

  // Unarni minus, invertira vektor i vraća novi objekt sa rezultatom
  virtual Vector operator-(){
    std::vector<double> tmp(this->elements);
      for(int i=0; i<this->getDimension(); i++){
        tmp[i]=-tmp[i];
      }
      return Vector(tmp);
    
  };

  // Oduzima dva vektora i vraća novi objekt sa rezultatom
  virtual Vector operator-=(Vector& vector){
    if(this->getDimension() == vector.getDimension()){
      std::vector<double> tmp(vector.toArray());
      Vector ret(*this);
      ret-vector;
      return Vector(*&ret);
    }else
      throw std::invalid_argument("Vector dimensions need to be equal!");
  };



  // Množenje skalarom
  virtual Vector& operator*(double scalar){
    for(int i=0; i<this->getDimension(); i++){
      this->elements[i]*=scalar;
    }
    return *this;
  };

  // Množenje skalarom koje vraća novi objekt
  Vector operator*=(double scalar){
    Vector ret (*this);
    ret * scalar;
    return Vector(*&ret); 
  };

  // Vraća duljinu trenutnog vektora
  double norm(){
    double sum=0;
    for(int i=0; i<this->getDimension(); i++)
      sum+=this->toArray()[i]*this->toArray()[i];
    return sqrt(sum);
  };

  // Normira trenutačni vektor
  virtual Vector& normalize(){
    double norm = this->norm();
    for(int i=0; i<this->getDimension(); i++)
      this->elements[i]/=norm;
    return *this;
  };

  // Vraća objekt koji odgovara normiranom trenutnom vektoru
  virtual Vector nNormalize(){
    Vector ret(*this);
    ret.normalize();
    return Vector(*&ret);
  };


  // Vraća iznos kosinusa kuta između dva vektora
  double cosine(Vector& vector){

    if(this->getDimension() == vector.getDimension()){
    
      double firstNorm = this->norm();
      double secondNorm = vector.norm();
      double multiplicationSum = 0;

      for(int i=0; i<this->getDimension(); i++)
        multiplicationSum+=(*this)[i]*vector[i];

      return (multiplicationSum)/(firstNorm*secondNorm);

    }else
      throw std::invalid_argument("Vector dimensions must be equal!");
  };

  // Vraća skalarni produkt dva vektora
  double scalarProduct(Vector& vector){
    if(this->getDimension() == vector.getDimension()){
      double multiplicationSum = 0; 
      for(int i=0; i<this->getDimension(); i++){
        multiplicationSum+=(*this)[i]*vector[i];
      }

      return (multiplicationSum);

    }else
      throw std::invalid_argument("Vector dimensions must be equal!");
  };

  // Vraća vektor koji odgovara vektorskom umnošku trenutnog i zadanog vektora
  virtual Vector nVectorProduct(Vector vector){
    if(vector.getDimension()==3 && this->getDimension()==3 && this->getDimension()==vector.getDimension()){
      std::vector<double> newValues;
      newValues.push_back((*this)[1]*vector[2] - (*this)[2]*vector[1]);
      newValues.push_back((*this)[2]*vector[0] - (*this)[0]*vector[2]);
      newValues.push_back((*this)[0]*vector[1] - (*this)[1]*vector[0]);

      return Vector(newValues);

    }else
      throw std::invalid_argument("Vector dimensions must be equal and <=3 !");
  };

  // Vraća vektor koji odgovara trenutnom vektoru u radnom prostoru
  virtual Vector nFromHomogenous(){
    double lastElement = this->elements[this->getDimension()-1];
    std::vector<double> tmp;
    for(int i=0; i<this->getDimension()-1; i++)
      tmp.push_back(this->elements[i]/lastElement);
    return Vector(tmp);
  };

  // Parsira vektor iz ulaznog niza znakova i kreira novi Vector objekt
  static Vector parseSimple(std::string str){
    if(std::regex_match(str, Vector::parseRegex)){

      std::vector<double> tmp;
      for(int i=0; i<str.size();i++){
        if(str[i]!=' '){
          int k = i;
          while((isdigit(str[i]) || str[i]=='.' ||str[i]=='-') && i<str.size())
            i++;
          tmp.push_back(atof(str.substr(k, i).c_str()));
        }
      }

      return Vector(tmp);
    }else
      throw std::invalid_argument("Invalid input string!");

  };

  // Pretvara trenutni vektor u jednoretčani Matrix objekt
  Matrix toRowMatrix(bool live);
 
  // Pretvara trenutni vektor u jednostupčani Matrix objekt
  Matrix* toColumnMatrix(bool live);

  
  static std::regex parseRegex;

 private:
  std::vector<double> elements;
  int dimension;
  bool readOnly = false;
 
};


inline std::ostream & operator<<(std::ostream & Str, Vector& vector) { 
  for(int i=0; i<vector.getDimension(); i++){
    if(i+1 == vector.getDimension())
      Str<<vector[i];
    else
      Str<<vector[i]<<" ";
  }
  Str<<std::endl;
  return Str;
  }

inline std::ostream & operator<<(std::ostream & Str, Vector* vector) { 
  for(int i=0; i<vector->getDimension(); i++){
    if(i+1 == vector->getDimension())
      Str<<(*vector)[i];
    else
      Str<<(*vector)[i]<<" ";
  }
  Str<<"\n";
  return Str;
}







