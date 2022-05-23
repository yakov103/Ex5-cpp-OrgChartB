#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <stack>
#include <queue>
#include <stdexcept>

using namespace std;

namespace ariel {

    constexpr long VERY_LARGE_LONG = 4000000000;

    enum iterator_type {
        LEVEL_ORDER,
        REVERSE_ORDER,
        PRE_ORDER,
        END_LEVEL_ORDER
    };

    struct Node {
        string name;
        vector<Node*> children;
        unsigned int level; 
    };

    class OrgChart {
        class Iterator{
        private :

            unsigned int _index;
            vector<Node*> *  _orderedVecIter; // o(1)

            unsigned int _size{};
        public :
            Iterator(vector<Node*> * nodes, iterator_type type);
            Iterator(const Iterator& other);
            Iterator operator++();
            Iterator operator++(int);
            bool operator==(const Iterator& other);
            bool operator!=(const Iterator& other);
            string& operator*();
            string* operator->();

        };



    public :
        Node* _root;// o(n)
        vector<Node*>  _orderedVec;// o(n)

        OrgChart(); // constractor
        ~OrgChart(); // destructor
        OrgChart(const OrgChart& other) ; // copy constractor
        void fill_order(Node *node , iterator_type type); // fill the nodes


        OrgChart& operator= (const OrgChart& other); // assignment operator
        OrgChart& add_root(const string& name); // add root 
        OrgChart& add_sub(string parent,string child); // add sub
        bool check_parent(string &parent, string &child , Node *node);// check if parent exist

        OrgChart::Iterator begin() ; // begin iterator
        OrgChart::Iterator end(); // end iterator
        OrgChart::Iterator begin_level_order() ; // begin iterator level order
        OrgChart::Iterator begin_reverse_order() ; // begin iterator reverse order
        OrgChart::Iterator begin_preorder() ; // begin iterator preorder
        OrgChart::Iterator end_level_order() ;
        OrgChart::Iterator reverse_order()  ;
       OrgChart::Iterator end_preorder() ;




        friend ostream& operator<<(ostream& os,OrgChart& org);



    };
};