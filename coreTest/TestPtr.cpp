/*
**	Filename : TestPtr.cpp
**	2024-02-01
**	username : rsehgal
*/
#include<iostream>
#include <memory>
int main(int argc, char *argv[]){
std::unique_ptr<int> ptr(new int(5));// = intobj;
//int *ptr=new int(5);
ptr.reset(new int(10));
std::cout << "Hello" << std::endl;
return 0;
}
