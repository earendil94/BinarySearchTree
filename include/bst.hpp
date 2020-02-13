#ifndef __bst_hpp
#define __bst_hpp

#include <algorithm>
#include <iostream>
#include <memory>
#include <iterator>
#include <utility>
#include <vector>
#include <cmath>

template <typename T>
class node {
    T value;
    std::unique_ptr<node> left;
    std::unique_ptr<node> right;
    node* parent;

    public:
        node(T p): value{p}, parent{nullptr} {};
        node(T p, node* n): value{p}, parent{n} {};
        //Explicit node copy constructor
        explicit node(const std::unique_ptr<node> &p, node* parent): value{p->value}{
            this->parent = parent;
            if(p->right)
                right = std::make_unique<node>(p->right, this);
            if(p->left)
                left = std::make_unique<node>(p->left, this);
        }
        
        ~node() {}
        using value_type = T;

        //getters
        //TODO: Should we return a value or a reference to the value? Does this mean we can actually
        //Modify the value of the node? 
        //Francesco: Honestly, even returning a reference here is smelly: what does it happen to the
        //the reference if the node is destroyed?
        T& getValue() { return value;}
        node* getLeft() const {return left.get();}
        node* getRight() const {return right.get();}
        node* getParent() const {return parent;}

        //setters
        void setLeft(node* x) { left.reset(x); }
        void setRight(node* x) { right.reset(x); }
        void setParent(node* x) { parent = x; }
        

        //release 
        node* releaseRight() {return right.release();}
        node* releaseLeft() {return left.release();}
};

template <typename node_type, typename T>
class _iterator {
    node_type* current;
    node_type* next() noexcept;
    node_type* previous() noexcept;

    public:
        _iterator() noexcept: current{nullptr} {};
        explicit _iterator(node_type* x) noexcept : current{x} {};
        //TODO: do we need an iterator destructor?
        //(Francesco): probably not (see linked list)
        using value_type = T;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category =std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;

        //Actually a random super good guy said this is compiler doing its things under curtains
        //"But it's still bad, don't do it"
        // reference operator*() const noexcept { 
        //     value_type d = current->getValue();
        //     value_type &ref = d;
        //     return ref; 
        // }
        reference operator*() const noexcept { return(current->getValue()); }
        
        pointer operator->() const noexcept { return &(*(*this)); }

        _iterator& operator++() noexcept {  // pre increment
            current = next();
            return *this;
        }

        _iterator operator++(int) noexcept {
            _iterator tmp{current};
            ++(*this);
            return tmp;
        }
/*
        _iterator& operator--() noexcept { //pre decrement
            current = previous();
            return *this;
        }

        _iterator operator--(int) noexcept {
            _iterator tmp{current};
            --(*this);
            return tmp;
        }
*/
        friend bool operator==(const _iterator& a, const _iterator& b) {
            return a.current == b.current;
        }

        friend bool operator!=(const _iterator& a, const _iterator& b) {
            return !(a == b);
        }

        //getter
        node_type* getCurrent() const {return current;}

        //setter
        void setCurrent(node_type* x) { current = x;}
};

template <typename k, typename v, typename c = std::less<k> >
class bst{
    using node_type = node<std::pair<const k,v> >;
    using pair_type = typename node_type::value_type;
    c op;
    std::unique_ptr<node_type> head;

    //private functions for tree balance
    void balanceRec(std::vector<pair_type> values, size_t n);
    bool isBalanced(node_type* x);
    int height(node_type* x);
    void drawRec(const std::string& prefix, node_type* x, bool isLeft);

    public:
        bst(): op{c()}, head{nullptr} {};
        bst(c comp): op{comp}, head{nullptr} {};
        bst(k key, v value, c comp): op{comp}, head{ std::make_unique<node_type>(std::pair<k,v>(key,value))} {};
        
        using iterator = _iterator<node_type, pair_type>;
        using const_iterator = _iterator<node_type, const pair_type>;

        std::pair<iterator, bool> insert(const pair_type& x);
        std::pair<iterator, bool> insert(pair_type&& x);

        template<class... Types>
        std::pair<iterator,bool> emplace(Types&&... args); 

        void clear() noexcept; 

        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        const_iterator cbegin() const noexcept; 

        iterator end() noexcept {return iterator{nullptr};}
        const_iterator end() const noexcept { return const_iterator{nullptr};}
        const_iterator cend() const noexcept { return const_iterator{nullptr};}

        iterator find(const k& x) noexcept; 
        const_iterator find(const k& x) const; 

        //THIS FUNCTION IS FOR DEBUGGING PURPOSES, TO CHECK FIND FUNCTION 
        void isThere(const k& key){
            iterator result; 
            result = find(key);
            if(result == end()) std::cout<<"NOT FOUND"<<std::endl;
            else std::cout<<"FOUND"<<std::endl;
        }

        void balance(); 

        v& operator[](const k& x) {
            auto it = find(x);
            if(it != end())
                return (*it).second;
            else {
                auto p = insert({x,v{}});
                return (*(p.first)).second;
            }
        }

        v& operator[](k&& x){
            iterator it = find(std::move(x));
            if(it != end())
                return (*it).second;
            else {
                auto p = insert({std::move(x),v{}});
                return (*(p.first)).second;
            }
        }

        friend
        std::ostream& operator<<(std::ostream& os, const bst& x){
            auto it = x.begin();
            while (it != x.end()) {
                os << (*it).second << " ";
                ++it;
            }
            return os;
        }

        void draw();

        // copy semantic
        // copy constr 
        bst(const bst &b): op{b.op} { 
            head = std::make_unique<node_type>(b.head,nullptr);
        }
        
        bst& operator=(const bst& b){
            this->clear();
            op = b.op;
            head = std::make_unique<node_type>(b.head,nullptr);
            return *this;
        } 

        // move semantic
        // move constr 
        bst(bst&& b) noexcept = default;
        bst& operator=(bst&& b) noexcept = default; //move assignment

        void erase(const k& x);
};


////////////////////////////////
/////                     //////
/////  ITERATOR FUNCTIONS //////
/////                     //////
////////////////////////////////


//Iterator functions
template <typename node_type, typename T>
node_type* _iterator<node_type,T>::next() noexcept{
    if(current->getRight() != nullptr) {
        current = current->getRight();
        while(current->getLeft() != nullptr)
            current = current->getLeft();
    } else {
        //If we are the head we are done
        if(current->getParent() == nullptr){
            return nullptr;
        } 
        while(current->getParent()->getLeft() != current){
                current = current->getParent();
                if(current->getParent() == nullptr)
                    return nullptr;
        }
        current = current->getParent();
    }
    return current;
}
/*

template <typename node_type, typename T>
node_type* _iterator<node_type,T>::previous() noexcept{
    if(current->getLeft() != nullptr) {
        current = current->getLeft();
        while(current->getRight() != nullptr)
            current = current->getRight();
    } else {
        if(current->getParent() == nullptr){
            return nullptr;
        }

        while(current->getParent()->getRight() != current){
                current = current->getParent();
                if(current->getParent() == nullptr)
                    return nullptr;
        }

        current = current->getParent();
    }
    return current;
}
*/
///////////////////////////
/////                //////
/////  BST FUNCTIONS //////
/////                //////
///////////////////////////

//The first element of the bst is the leftmost element of the tree
template <typename k, typename v, typename c>
typename bst<k,v,c>::iterator bst<k,v,c>::begin() noexcept {

    if(head == nullptr)
        return iterator(nullptr);
    
    auto it = iterator(head.get());
    while( it.getCurrent()->getLeft() != nullptr)
        it.setCurrent(it.getCurrent()->getLeft());
    
    return it;   
}

template <typename k, typename v, typename c>
typename bst<k,v,c>::const_iterator bst<k,v,c>::begin() const noexcept {

    if(head == nullptr)
        return const_iterator(nullptr);

    auto it = const_iterator(head.get());
    while( it.getCurrent()->getLeft() != nullptr)
        it.setCurrent(it.getCurrent()->getLeft());
    
    return it;
}

template <typename k, typename v, typename c>
typename bst<k,v,c>::const_iterator bst<k,v,c>::cbegin() const noexcept{

    //TODO: maybe just call begin here
    if(head == nullptr)
        return const_iterator(nullptr);

    auto it = const_iterator(head.get());
    while( it.getCurrent()->getLeft() != nullptr)
        it.setCurrent(it.getCurrent()->getLeft());
    
    return it;
}

template <typename k, typename v, typename c>
std::pair<typename bst<k,v,c>::iterator,bool> bst<k,v,c>::insert(const pair_type& x){
    
    if (head == nullptr){
        head = new node_type(x, nullptr);
        return(std::make_pair(iterator(head.get()),true));
    }
    
    node_type* new_node = nullptr;  
    node_type* tmp = head ;
    
    while (tmp != nullptr){
        new_node = tmp;
        if (op(x.first,tmp->getValue().first))
        {
            tmp = tmp->getLeft();
        }
        else if (op(tmp->getValue().first, x.first))
        {
            tmp = tmp->getRight();
        }  
        else{
            //if the key is already exist 
             return(std::make_pair(iterator(),false));
        }
        
    }

    tmp = std::make_unique<node_type>(x, new_node);
    if (op(x.first,new_node->getValue().first)){ 
        new_node->setLeft(tmp); 
    }
    else{
        new_node->setRight(tmp); 
    }
     
    return(std::make_pair(iterator(tmp),true)); 
}

template <typename k, typename v, typename c>
std::pair<typename bst<k,v,c>::iterator,bool> bst<k,v,c>::insert(pair_type&& x){
    
    if (head == nullptr){
        head = std::make_unique<node_type>(std::move(x), nullptr);
        return(std::make_pair(iterator(head.get()),true));
    }
    
    node_type* new_node = nullptr;  
    auto tmp = head.get() ;
    
    while (tmp != nullptr){
        new_node = tmp;
        if (op(x.first,tmp->getValue().first))
        {
            tmp = tmp->getLeft();
        }
        else if (op(tmp->getValue().first,x.first))
        {
            tmp = tmp->getRight();
        }  
        else{
            //if the key is already exist 
             return(std::pair<iterator, bool> (iterator(),false));
        } 
    }
    tmp = new node_type(std::move(x), new_node);
    if (op(x.first,new_node->getValue().first)){ 
        new_node->setLeft(tmp); 
    }
    else{
        new_node->setRight(tmp);
    }
    return(std::make_pair(iterator(tmp),true)); 
}

template <typename k, typename v, typename c>
typename bst<k,v,c>::iterator bst<k,v,c>::find(const k& x) noexcept{
    
    auto it = iterator(head.get());
    while(it.getCurrent() != nullptr ){
        if(op(it.getCurrent()->getValue().first,x)){
            it.setCurrent(it.getCurrent()->getRight()); 
        }
        else if(op(x,it.getCurrent()->getValue().first)){
            it.setCurrent(it.getCurrent()->getLeft()); 
        }
        else{
            return(iterator(it));
        }   
    }
    return end();
}

template <typename k, typename v, typename c>
typename bst<k,v,c>::const_iterator bst<k,v,c>::find(const k& x) const{
        
    auto it = const_iterator(head.get());
    while(it.getCurrent() != nullptr ){
        if(op(it.getCurrent()->getValue().first,x)){
            it.setCurrent(it.getCurrent()->getRight()); 
        }
        else if(op(x,it.getCurrent()->getValue().first)){
            it.setCurrent(it.getCurrent()->getLeft()); 
        }
        else{
            return(const_iterator(it));
        }  
    }
    return end();
}

template <typename k, typename v, typename c>
void bst<k,v,c>::clear() noexcept {
    if(head)
        head.reset();
}

template <typename k, typename v, typename c>
void bst<k,v,c>::erase(const k& x){

    iterator p = find(x);
    //iterator q = p;

    if(p == end()) { //if the key is not in the tree
        std::cout<< "The tree doesn't have this key" << std::endl;
    } else {
        auto current = p.getCurrent();
        auto left = current->getLeft();
        auto right = current->getRight();
        auto parent = current->getParent();

        if(left && right) { //"full node"
            ++p;
            auto _current = p.getCurrent();
            auto _parent = _current->getParent();
            _current->setLeft(left);
            left->setParent(_current);
            if(_parent == current){_current->setParent(parent);}
            else {_parent->setParent(parent);}
            
            if(parent->getLeft() == current)
            {
                auto tmp = parent->releaseLeft();
                tmp->releaseRight();
                parent->setLeft(right);
                tmp->releaseLeft();
                delete tmp;
            }
            else
            {
                auto tmp = parent->releaseRight();
                tmp->releaseLeft();
                parent->setRight(right);
                tmp->releaseLeft();
                delete tmp;
            }
            if(head.get() == current)
            {
                current = head.release();
                head.reset(_current);
                current->releaseRight();
                current->releaseLeft();
                delete current;
            }
            //if(q.getCurrent()->getParent() == nullptr)
                //current->setParent(nullptr);
                //head = std::make_unique(p.getCurrent()); //TODO:Why not working? 
        } else if(!left && !right) { //leaf node  
            //if(current == head) {head.reset();} 
            if(parent->getLeft() == current)
                parent->setLeft(nullptr);
            else
                parent->setRight(nullptr);
        } else if(left && !right) { //node with only left child
            
            left->setParent(parent);
            if(parent->getLeft() == current)
            {
                auto tmp = parent->releaseLeft();
                tmp->releaseRight();
                parent->setLeft(left);
                delete tmp;
            }
            else
            {
                auto tmp = parent->releaseRight();
                tmp->releaseLeft();
                parent->setRight(left);
                delete tmp;
            }
                
        } else { //node with only right child 
            right->setParent(parent);
            if(parent->getLeft() == current)
            {
                auto tmp = parent->releaseLeft();
                tmp->releaseRight();
                parent->setLeft(right);
                tmp->releaseLeft();
                delete tmp;
            }
            else
            {
                auto tmp = parent->releaseRight();
                tmp->releaseLeft();
                parent->setRight(right);
                tmp->releaseRight();
                delete tmp;
            }
        }
    }
    return;
}

template <typename k, typename v, typename c>
template <class... Types>
std::pair<typename bst<k,v,c>::iterator, bool> bst<k,v,c>::emplace(Types&&... args){

    //Francesco: I am now 99.9% convinced that this is what should be done for this function.
    //https://en.cppreference.com/w/cpp/container/map/emplace here is the stl reference for map
    //Which is implemented as a red-black tree (btw, I think we should use exactly this container
    //to benchmark our code).
    //I am 100% convinced after reading stuff on the web that only one element should be inserted
    //The trick is the following: make_pair strictly requires two arguments and builds a pair of that type
    //Invoking the pair_type constructor instead allows us to exploit all the predefined std::pair move
    //constructors! In this way we can actually pass either two arguments, or a pair, etc.. as
    //arguments of the emplace function and get the result.

    return insert(pair_type(std::forward<Types>(args)...)); 
    
}

template <typename k, typename v, typename c>
void bst<k,v,c>::balance() {

    //copying ordered values in a vector 
    std::vector<pair_type> values;
    auto it = begin();
    while(it.getCurrent() != nullptr){
        values.push_back((*it));
        it++;
    }
    clear(); //clear the bst
    balanceRec(values, values.size()); //re-built the balanced bst

    if(isBalanced(head.get()))
        std::cout << "The tree is now balanced" << std::endl;
    else
        std::cout << "The tree is still NOT balanced" << std::endl;
}

template <typename k, typename v, typename c>
void bst<k,v,c>::balanceRec(std::vector<pair_type> values, size_t n) {
    if(n==1) {
        insert({values.at(0).first,values.at(0).second});
    } else if(n==2) {
        insert({values.at(0).first,values.at(0).second});
        insert({values.at(1).first,values.at(1).second});
    } else{
        int middle = (n % 2 == 0) ? (n/2)-1 : floor(n/2);
        insert({values.at(middle).first,values.at(middle).second});

        //create 2 sub-vectors
        auto firstLeft = values.begin();
        auto lastLeft = values.begin() + middle;
        auto firstRight = values.begin() + middle + 1;
        auto lastRight = values.end();
        std::vector<pair_type> leftValues(firstLeft,lastLeft);
        std::vector<pair_type> rightValues(firstRight,lastRight);
        balanceRec(leftValues, leftValues.size());
        balanceRec(rightValues, rightValues.size());
    }
}

template <typename k, typename v, typename c>
bool bst<k,v,c>::isBalanced(node_type* x) {
    if (x == nullptr) 
        return true; 
    
    int lh = height(x->getLeft()); 
    int rh = height(x->getRight()); 
  
    if(abs(lh - rh) <= 1 && isBalanced(x->getLeft()) && isBalanced(x->getRight())) 
        return true;
    return false;
}

template <typename k, typename v, typename c>
int bst<k,v,c>::height(node_type* x) {
    if (x == nullptr) 
        return 0; 
    return 1 + std::max(height(x->getLeft()), height(x->getRight()));
}

template <typename k, typename v, typename c>
void bst<k,v,c>::draw() {
    drawRec("",head.get(),false);
}

template <typename k, typename v, typename c>
void bst<k,v,c>::drawRec(const std::string& prefix, node_type* x, bool isLeft) {
    if(x != nullptr){
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << x->getValue().first << std::endl;

        // enter the next tree level - left and right branch
        drawRec( prefix + (isLeft ? "│   " : "    "), x->getLeft(), true);
        drawRec( prefix + (isLeft ? "│   " : "    "), x->getRight(), false);
    }
}

#endif
