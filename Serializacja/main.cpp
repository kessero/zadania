/*
serializacja do pliku tekstowego lub binarnego w zależności od parametru programu
./nazwa --help
./nazwa txt
./nazwa bin
klasa powinna sygnalizować sytuacje wyjątkowe
*/

#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/array.hpp>

enum class FuelType{
  benzyna,
  prad,
  gaz,
  };
enum class Colour{
  niebieski,
  zielony,
  czerwony,
};
enum class EmissionsStandards{
  cat1,
  cat2,
  cat3,
  cat4,
};
struct Weels{
  std::string name;
};

class Car {
  public:
    Car(){};
    Car(FuelType f, std::array<Weels, 4> w, uint32_t m, Colour c){
      fuel_type =f;
      weels = w;
      max_speed = m;
      colour = c;
    }
    FuelType getFuellType(){
      return fuel_type;
    }
    std::array<Weels, 4> getWeelsArr(){
      return weels;
    }
    uint32_t getMaxSpeed(){
      return max_speed;
    }
    Colour getColour(){
      return colour;
    }
  protected:
      FuelType fuel_type;
      std::array<Weels, 4> weels;
      uint32_t max_speed;
      Colour colour;
};

class PersonalCar: public Car {
  public:
    PersonalCar():Car(){};
    PersonalCar(FuelType f, std::array<Weels, 4> w, uint32_t m, Colour c, uint8_t n, EmissionsStandards em):Car(f,w,m,c){
      fuel_type =f;
      weels = w;
      max_speed = m;
      colour = c;
      number_of_places = n;
      emission = em;
    }
    uint8_t getNumber_Of_Places(){
      return number_of_places;
    }
    EmissionsStandards getEmission(){
      return emission;
    }
  private:
      friend class boost::serialization::access;
      //template<class Archive,class T, size_t N>
      template<class Archive>
      void serialize(Archive & ar,  const unsigned int version)
      {
          ar & fuel_type;
        //  ar & boost::serialization::make_array(weellss.data(), weellss.size());
          ar & max_speed;
          ar & colour;
          ar & number_of_places;
          ar & emission;
      }
      uint8_t number_of_places;
      EmissionsStandards emission;
};


void menu(std::string flag){
    if(flag == "--help"){
      std::cout<<"Choice -txt or -bin"<<"\n";
    }else if (flag == "-txt"){
      std::cout<<"TXT"<<"\n";
    }else if (flag == "-bin"){
      std::cout<<"BIN"<<"\n";
    }else{
      std::cout<<"--help"<<"\n";
    }
}
int main(int argc, char* argv[]) {
  std::ofstream ofs("filename");
  FuelType fuel_Type;
  Colour colourType;
  EmissionsStandards emissionType;
/*  if(argc < 2){
    std::cout<<"--help"<<"\n";
  }else if(argc > 3){
    std::cout<<"Too many flags try --help"<<"\n";
  }else{
    std::string arg = argv[1];
    menu(arg);
  }*/
  PersonalCar toyota(fuel_Type = FuelType::benzyna,{"205","205","205","205"}, 200, colourType = Colour::czerwony, 4, emissionType = EmissionsStandards::cat1);
  std::cout<<toyota.getMaxSpeed()<<"\n";
  {
        boost::archive::text_oarchive oa(ofs);
        oa << toyota;
    }

    PersonalCar newtoyota;
    {
        std::ifstream ifs("filename");
        boost::archive::text_iarchive ia(ifs);
        ia >> newtoyota;
    }
    std::cout<<newtoyota.getMaxSpeed()<<"\n";
  return 0;
}
