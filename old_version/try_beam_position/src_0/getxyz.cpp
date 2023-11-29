#include <iostream>
#include <cmath>

int main()
{
  for(int i=2;i<=20;i+=2){
    for(int j=0;j<360;j+=10){
      std::cout << (double)i << " " << (double)j << " " << (double)i*cos((double)j/180.*M_PI) << " " << (double)i*sin((double)j/180.*M_PI) << " " << 0. << std::endl;
    }
  }

  return 0;
}
