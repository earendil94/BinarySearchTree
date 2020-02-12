#include <bst.hpp>

int main(){
/*
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
*/

    std::cout << "Testing the Erase Function :" << std::endl;
    bst<int, int, std::less<int>> azza{std::less<int>()};
    azza.insert({8,8});
    azza.insert({3,3});
    azza.insert({6,6});
    azza.insert({1,1});
    azza.insert({10,10});
    azza.insert({7,7});
    azza.insert({14,14});
    azza.insert({4,4});
    azza.insert({13,13});
    
    //azza.erase(1); //delete a leaf on left
    //azza.erase(7); //delete a leaf on right
    azza.erase(14); //delete a node that has a node on left only ---> NOT WORKING
    
    //azza.erase(10); //delete a node that has a node on right only ---> NOT WORKING
    
    //azza.erase(6); //delete a node has right and left nodes ---> NOT WORKING
    
    //azza.erase(8); //delete the root ---> NOT WORKING
    
    //azza.erase(20); //delete a key not present
    azza.draw();
/*
    //Emplace test

    std::cout << "sartoriBis after emplace of (20,20)" << std::endl;
    sartoriBis.emplace(20,20);
    std::cout << sartoriBis << std::endl;

    std::cout << "sartoriBis after emplace of (13,13): already has it and should not insert" << std::endl;
    sartoriBis.emplace(13,13);
    std::cout << sartoriBis << std::endl;

    std::cout << "sartoriBis after emplace of (std::make_pair(21,21)): should be inserted" << std::endl;
    sartoriBis.emplace(std::make_pair(21,21));
    std::cout << sartoriBis << std::endl; 

    //getters Test: we try to see what we can achieve with actually returning a reference with begin

    //uselessVariable actually does not modify anything BUT it seems it is storing a value
    //since it will still be alive even when the tree is dead
    
    auto uselessVariable = *(sartoriBis.begin());
    (*(sartoriBis.begin())).second = 10;
    std::cout << "Hi, I am the first value of sartoriBis: " << uselessVariable.second << std::endl;
    uselessVariable.second = 3;
    std::cout << "Hi, I am the first value of sartoriBis: " << uselessVariable.second << std::endl;

    std::cout << "sartoriBis " << std::endl << sartoriBis<< std::endl;
    std::cout << "sartoriBis BOOM!" << std::endl;

    sartoriBis.clear();

    //actually uselessVariableKey is still alive! Even though sartoriBis is clearly not
    std::cout << "Hi, I am the first value of sartoriBis: " << uselessVariable.second << std::endl;
    std::cout << "sartoriBis " << std::endl << sartoriBis<< std::endl;

    //Balance test
    std::cout << "Imbalance sartori bst" << std::endl;
    sartori.draw();
    sartori.balance();
    std::cout << "Balance sartori bst" << std::endl;
    sartori.draw();
<<<<<<< HEAD
    
    return 0;
    */
=======
    */

    //TODO: for debugging purposes, let's just stick with key=value (just like Alberto)
    //TODO: Should we just have one big try catch block in our main?
    try{
        //Constructor with head
        bst<int, int, std::less<int>> t{1,1,std::less<int>()};
        t.insert({3,3});
        t.insert({6,6});
        std::cout << t << std::endl;

        //Constructor without head: insert should create the head: WORKS
        bst<int, int, std::less<int>> abba{1,1,std::less<int>()};
        abba.insert({2,2});
        std::cout<< abba << std::endl;


        //Construct S.A.R.T.O.R.I. (Something abstract related to our recursive implementation)
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

        //Emplace test

        std::cout << "sartoriBis after emplace of (20,20)" << std::endl;
        sartoriBis.emplace(20,20);
        std::cout << sartoriBis << std::endl;

        std::cout << "sartoriBis after emplace of (13,13): already has it and should not insert" << std::endl;
        sartoriBis.emplace(13,13);
        std::cout << sartoriBis << std::endl;

        std::cout << "sartoriBis after emplace of (std::make_pair(21,21)): should be inserted" << std::endl;
        sartoriBis.emplace(std::make_pair(21,21));
        std::cout << sartoriBis << std::endl;    

        //getters Test: we try to see what we can achieve with actually returning a reference with begin

        //uselessVariable actually does not modify anything BUT it seems it is storing a value
        //since it will still be alive even when the tree is dead
        
        // auto uselessVariable = *(sartoriBis.begin());
        // (*(sartoriBis.begin())).second = 10;
        // std::cout << "Hi, I am the first value of sartoriBis: " << uselessVariable.second << std::endl;
        // uselessVariable.second = 3;
        // std::cout << "Hi, I am the first value of sartoriBis: " << uselessVariable.second << std::endl;

        // std::cout << "sartoriBis " << std::endl << sartoriBis<< std::endl;
        // std::cout << "sartoriBis BOOM!" << std::endl;

        // sartoriBis.clear();

        // //actually uselessVariableKey is still alive! Even though sartoriBis is clearly not
        // std::cout << "Hi, I am the first value of sartoriBis: " << uselessVariable.second << std::endl;
        // std::cout << "sartoriBis " << std::endl << sartoriBis<< std::endl;

        // Let's build the upside-down tree!

        bst<int, int, std::greater<int>> irotras{8,8,std::greater<int>()};
        irotras.insert({3,3});
        irotras.insert({6,6});
        irotras.insert({1,1});
        irotras.insert({10,10});
        irotras.insert({7,7});
        irotras.insert({14,14});
        irotras.insert({4,4});
        irotras.insert({13,13});

        std::cout << "irotras" << std::endl;
        std::cout<< irotras << std::endl;

    } catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch(...) {
        std::cerr << "Unknown exception occured" << std::endl;
        return 2;
    }
    return 0;
    
>>>>>>> draw() function and updates to the erase() function
}


