#include <bst.hpp>

int main(){

    //Constructor with head
    //bst<int, int, std::less<int>> t{std::less<int>()};
    bst<int, int, std::less<int>> t{1,1,std::less<int>()};

    //TODO: for debugging purposes, let's just stick with key=value (just like Alberto)
    // t.insert({2,2});
    // t.insert({3,3});
    t.insert({3,3});
    t.insert({6,6});
    // std::cout<< t << std::endl;
    std::cout << t << std::endl;
    //t.isThere({9});

    // //Constructor without head: insert should create the head: WORKS
    // bst<int, int, std::less<int>> abba{1,1,std::less<int>()};
    // abba.insert({2,2});
    // std::cout<< abba << std::endl;

    // //Construct S.A.R.T.O.R.I. (Something abstract related to our recursive implementation)
    bst<int, int, std::less<int>> sartori{8,8,std::less<int>()};
    sartori.insert({3,3});
    sartori.insert({6,6});
    sartori.insert({1,1});
    sartori.insert({10,10});
    sartori.insert({7,7});
    sartori.insert({14,14});
    sartori.insert({4,4});
    sartori.insert({13,13});

    std::cout << "Sartori" << std::endl;
    std::cout<< sartori << std::endl;

    std::cout << sartori[3] << std::endl;
    //std::cout << sartori[60] << std::endl;
    //std::cout<< sartori << std::endl;

    //Copy constructor test-case
    bst<int, int, std::less<int>> sartoriBis{sartori};
    std::cout << "Sartori bis" << std::endl;
    std::cout<< sartoriBis << std::endl;
    sartoriBis.isThere(8);

    sartoriBis.insert({5,5});
    std::cout << "SartoriBis after insert on sartoriBis" << std::endl;
    std::cout<< sartoriBis << std::endl;

    std::cout << "Sartori after insert on sartoriBis" << std::endl;
    std::cout<< sartori << std::endl;

    //Clear test

    std::cout << "t after t.clear()" << std::endl;
    t.clear();
    std::cout<< t << std::endl;

    //Copy assignment test

    std::cout << "sartoriBis after sartoriBis = sartori " << std::endl;
    sartoriBis = sartori;
    std::cout << sartoriBis << std::endl;

    //Move constructor test

    std::cout << "sartoriTris after sartoriTris{std::move(sartoriBis)}" << std::endl;
    bst<int,int,std::less<int>> sartoriTris{std::move(sartoriBis)};
    std::cout << sartoriTris << std::endl;
    
    std::cout << "sartoriBis after sartoriTris{std::move(sartoriBis)} ? " << std::endl;
    std::cout << sartoriBis << std::endl;

    //Move assignment test

    std::cout << "sartoriBis after sartoriBis = std::move(sartoriTris)" << std::endl;
    sartoriBis = std::move(sartoriTris);
    std::cout << sartoriBis << std::endl;
    
    std::cout << "sartoriTris after sartoriBis = std::move(sartoriTris) ? " << std::endl;
    std::cout << sartoriTris << std::endl;

    return 0;
}

