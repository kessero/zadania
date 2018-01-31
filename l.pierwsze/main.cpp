#include <iostream>
#include <bits/stdc++.h>
#include <chrono>
#include <stdlib.h>
#include <iterator>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <thread>
#include <gmp.h>

int power(int x, unsigned int y, int p)
{
    int res = 1;
    x = x % p;
    while (y > 0)
    {
        if (y & 1)
            res = (res*x) % p;
        y = y>>1;
        x = (x*x) % p;
    }
    return res;
}

bool miillerTest(int d, int n)
{
    int a = 2 + rand() % (n - 4);

    int x = power(a, d, n);

    if (x == 1  || x == n-1)
       return true;

    while (d != n-1)
    {
        x = (x * x) % n;
        d *= 2;

        if (x == 1)      return false;
        if (x == n-1)    return true;
    }

    return false;
}

void rabbin_prime(int n, int k)
{
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  if (n <= 1 || n == 4)
    std::cout<<n<<" Not prime number RABIN"<<"\n";
  if (n <= 3)
    std::cout<<n<<" is prime number RABIN"<<"\n";
  int d = n - 1;
  while (d % 2 == 0)
      d /= 2;
  for (int i = 0; i < k; i++){
     if (miillerTest(d, n) == false){
        std::cout<<n<<" Not prime number RABIN"<<"\n";
     };
     if (miillerTest(d, n) == true){
        std::cout<<n<<" is prime number RABIN"<<"\n";
     };
   }
std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
std::cout << "Time rabbin work = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<" microseconds"<<"\n";
}

void trial_division(int n){
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  int index = 2;
  while (index*index<= n){
    if (n % index == 0){
      std::cout<<n<<" Not prime number TRIAL"<<"\n";
      break;
    }
    ++index;
    if (index*index >n){
      std::cout<<n<<" is prime number TRIAL"<<"\n";
    }

  }
  std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
  std::cout << "Time trial work = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<" microseconds"<<"\n";
}

void generate_random_numbers_in_file(int number_of_numbers){
  unsigned long int max_number = 9223372036854775807;

  std::ofstream f;
  unsigned long int g_number;
  f.open("data.txt",std::ios::out ) ;
  for(int i=0; i<number_of_numbers; i++){
    g_number = rand() % max_number + 1;
    f << g_number<< " ";
}
f.close() ;
}
void mpz_prime(int n, int d){
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  mpz_t pz;
  mpz_init(pz);
  mpz_set_ui (pz, n);
  int val = mpz_probab_prime_p(pz, d);
  if(val == 0){
    std::cout<<n<<" Not prime number MPZ"<<"\n";
  }
  if(val>0){
    std::cout<<n<<" is prime number MPZ"<<"\n";
  }

  mpz_clear(pz);
  std::cout<<"\n";
  std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
  std::cout << "Time mpz_prime = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<" microseconds"<<"\n";

}
void task(std::vector<unsigned long int> v, int l, int n_p_thread){
  for(std::vector<unsigned long int>::iterator it = v.begin(); it != v.end(); ++it) {
     std::thread th1(trial_division, *it);
     std::thread th2(rabbin_prime, *it, l);
     std::thread th3(mpz_prime, *it, l);
     th1.join();
     th2.join();
     th3.join();
   }
}
int main(){
  int k = 1;
  int nproc = 4;
  int numbers_per_thread = 4;
  int generate_x_numbers = 200;
  generate_random_numbers_in_file(generate_x_numbers);
  std::ifstream inputFile{"data.txt"};
  std::vector<unsigned long int> numbers{std::istream_iterator<unsigned long int>{inputFile}, {}};
  if (numbers.size()>4){
    //TODO dopraować podział zbioru
    numbers_per_thread = numbers.size()/nproc;
    task(numbers, k, numbers_per_thread);
  }
  if (numbers.size()<4){
    for(std::vector<unsigned long int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
       std::thread th1(trial_division, *it);
       std::thread th2(rabbin_prime, *it, k);
       std::thread th3(mpz_prime, *it, k);
       th1.join();
       th2.join();
       th3.join();
    }
  }
  return 0;
}
//97 prime number
//96 not prime
