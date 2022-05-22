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
            vector<Node*> *  _orderedVecIter;

            unsigned int _size{};
        public :
            Iterator(vector<Node*> * nodes, iterator_type type);
            Iterator operator++();
            Iterator operator++(int);
            bool operator==(const Iterator& other);
            bool operator!=(const Iterator& other);
            string& operator*();
            string* operator->();

        };



    public :
        Node* _root;
        vector<Node*>  _orderedVec;

        OrgChart();
        ~OrgChart();
        void fill_order(Node *node , iterator_type type);


        OrgChart& operator= (const OrgChart& other);
        OrgChart& add_root(const string& name);
        OrgChart& add_sub(string parent,string child);
        bool check_parent(string &parent, string &child , Node *node);

        OrgChart::Iterator begin() ;
        OrgChart::Iterator end();
        OrgChart::Iterator begin_level_order() ;
        OrgChart::Iterator begin_reverse_order() ;
        OrgChart::Iterator begin_preorder() ;
        OrgChart::Iterator end_level_order() ;
        OrgChart::Iterator reverse_order()  ;
       OrgChart::Iterator end_preorder() ;




        friend ostream& operator<<(ostream& os,OrgChart& org);



    };
};