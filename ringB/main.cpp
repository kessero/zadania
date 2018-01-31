/*RingBuffer - potrafi przechowywać maksymalnie N elementów
https://en.wikipedia.org/wiki/Circular_buffer
RingBuffer ma być kontenerem STL
ma wspierać range for oraz podstawowe algorytmy STL'a
nie ma gwaracji co do stanu iteratorów
jeżeli RB zostanie zaimplementowany jako adaptor - std::list ma zostać wyłączony z możliwości użycia*/
#include <vector>
#include <iostream>

class Buffer
{
  public:
    Buffer (int size);
    int readBuffer();
    void writeBuffer(int value);
  private:
    std::vector<int> v;
    int size;
    int read_index, write_index;
    bool buffer_isEmpty = true;
    bool buffer_isFull = false;

};
Buffer::Buffer (int size) :
v(size), size(size), read_index(0), write_index(0),
buffer_isEmpty(true), buffer_isFull(false) {}

void Buffer::writeBuffer(int value){
  buffer_isEmpty = false;
  std::cout<<write_index<<" index ";
  v[write_index]=value;
  write_index = (write_index + 1) % size;
  if(buffer_isFull){
    read_index = write_index;
    buffer_isFull = (write_index == read_index);
  }

}
int Buffer::readBuffer(){
  if(buffer_isEmpty == true && read_index == 0){
    std::cout<<"There's nothing to read"<<"\n";
    exit(1);
  }
  if(buffer_isEmpty == true && read_index !=0){
    std::cout<<"There's nothing new to read"<<"\n";
    exit(1);
  }
  buffer_isFull = false;
  std::cout<<read_index<<" index ";
  int value_read = v[read_index];
  read_index = (read_index+1) % size;
  buffer_isEmpty = (read_index == write_index);
  return value_read;
}


int main()
{
  int value = 0;
  Buffer buf(4);
  
  buf.writeBuffer(++value);
  std::cout<<"Zapisuję: "<< value << "\n";
  buf.writeBuffer(++value);
  std::cout<<"Zapisuję: "<< value << "\n";
  buf.writeBuffer(++value);
  std::cout<<"Zapisuję: "<< value << "\n";
  buf.writeBuffer(++value);
  std::cout<<"Zapisuję: "<< value << "\n";
  buf.writeBuffer(++value);
  std::cout<<"Zapisuję: "<< value << "\n";
  buf.writeBuffer(++value);
  std::cout<<"Zapisuję: "<< value << "\n";
  buf.writeBuffer(++value);
  std::cout<<"Zapisuję: "<< value << "\n";
  buf.writeBuffer(++value);
  std::cout<<"Zapisuję: "<< value << "\n";
  std::cout<<"\n";

  std::cout<<"Czytam: "<< buf.readBuffer() <<"\n";
  std::cout<<"Czytam: "<< buf.readBuffer() <<"\n";
  std::cout<<"\n";

  buf.writeBuffer(++value);
  std::cout<<"Zapisuję: "<< value << "\n";
  buf.writeBuffer(++value);
  std::cout<<"Zapisuję: "<< value << "\n";
  buf.writeBuffer(++value);
  std::cout<<"Zapisuję: "<< value << "\n";
  std::cout<<"\n";

  std::cout<<"Czytam: "<< buf.readBuffer() <<"\n";
  std::cout<<"Czytam: "<< buf.readBuffer() <<"\n";
  std::cout<<"Czytam: "<< buf.readBuffer() <<"\n";




}
