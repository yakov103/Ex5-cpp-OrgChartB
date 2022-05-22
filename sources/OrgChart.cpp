#include "OrgChart.hpp"
#include <vector>
namespace ariel {


    /* OrgChart Implementation */


    /*
    * @brief constructor
    * @param none
    * @return none
    */

    OrgChart::OrgChart() {
        _root = nullptr;

    }

    /*
    * @brief destructor
    * @param none
    * @return none
    */
   

    OrgChart::~OrgChart() {
       
       while (!_orderedVec.empty()) {
            delete _orderedVec.back();
            _orderedVec.pop_back();
        }
        
}



    OrgChart& OrgChart::operator= (const OrgChart& other) {
        if (this != &other) {
            delete _root;
            _root = other._root;
        }
        return *this;
    }

    /*
    * add root , if the root is not null just change the name
    * else create a new root
    */
    OrgChart& OrgChart::add_root(const string& name) {
        if (_root != nullptr) {
            _root->name = name;
            return *this;
        }
        _root = new Node;
        _root->name = name;
        _root->level = 0 ; 
        return *this;
    }

    bool OrgChart::check_parent(string &parent, string &child, Node *node)
    {
        if (node->name == parent)
        {
            Node *new_sub = new Node;
            new_sub->name = child;
            new_sub->level = node->level +1 ; 
            node->children.push_back(new_sub);
            return true;
        }
        for (unsigned int i = 0; i < node->children.size(); i++)
        {
            //printf("%s\n", node->children[i]->name.c_str());
            if (check_parent(parent, child, node->children.at(i)))
            {
                return true;
            }
        }

        return false;
    }



    OrgChart& OrgChart::add_sub(string parent, string child) {
        if (_root == nullptr) {
            throw "no root";
        }
        if (!check_parent(parent, child, _root))
        {
            throw std::invalid_argument("parent not found");
        }
        return *this;
    }


    OrgChart::Iterator OrgChart::begin_level_order()  {
        if (_root == nullptr) {
            throw "no root";
        }
        if (!_orderedVec.empty()){
            delete _orderedVec.back(); 
        }
        _orderedVec.clear();
        //this->_orderedVec.push_back(_root);
        this->fill_order(_root,LEVEL_ORDER);
        Node *temp = new Node;
        temp->name= "ENDITERATOR";
        this->_orderedVec.push_back(temp);
        Iterator it = Iterator(&this->_orderedVec, LEVEL_ORDER);
        return it;
    }

    /*
  * This function is used the reverse order.
  * using this https://stackoverflow.com/questions/48251254/how-can-i-insert-element-into-beginning-of-vector
  * @return - the end of the reverse order.
  */

    OrgChart::Iterator OrgChart::begin_reverse_order()  {
              if (_root == nullptr) {
            throw "no root";
        }
        if (!_orderedVec.empty()){
            delete _orderedVec.back(); 
        }
        this->_orderedVec.clear();
        Node *temp = new Node;
        temp->name= "ENDITERATOR";
        this->_orderedVec.insert(_orderedVec.begin(),temp);
        //this->_orderedVec.insert(_orderedVec.begin(),_root);
        this->fill_order(_root,REVERSE_ORDER);
        Iterator it = Iterator(&this->_orderedVec, REVERSE_ORDER);
        return it;
    }
   OrgChart::Iterator OrgChart::begin_preorder()  {
        if (_root == nullptr) {
            throw "no root";
        }
        if (!_orderedVec.empty()){
            delete _orderedVec.back(); 
        }
        _orderedVec.clear();
        //this->_orderedVec.push_back(_root);
        this->fill_order(_root,PRE_ORDER);
        Node *temp = new Node;
        temp->name= "ENDITERATOR";
        this->_orderedVec.push_back(temp);
        Iterator it = Iterator(&this->_orderedVec, PRE_ORDER);
        return it;
   }
    OrgChart::Iterator OrgChart::end_level_order() {
              if (_root == nullptr) {
            throw "no root";
        }
        return Iterator(&_orderedVec, END_LEVEL_ORDER);
    }
    OrgChart::Iterator OrgChart::reverse_order() {
              if (_root == nullptr) {
            throw "no root";
        }
        return Iterator(&_orderedVec, END_LEVEL_ORDER);
    }
   OrgChart::Iterator OrgChart::end_preorder(){
             if (_root == nullptr) {
            throw "no root";
        }
          return Iterator(&_orderedVec, END_LEVEL_ORDER);
   }

    OrgChart::Iterator OrgChart::begin(){
        return begin_level_order();
    }
    OrgChart::Iterator OrgChart::end(){
        return end_level_order();
    }

    ostream& operator<<(ostream& os,  OrgChart& org) {
        org.begin();
        unsigned int  i = 0 ;
        unsigned int currLevel = 0 ; 
        for (i = 0 ; i < org._orderedVec.size()-1; i++){ 
            if (currLevel  == org._orderedVec.at(i)->level){
                os << org._orderedVec.at(i)->name << " "; 
            }
            else {
                os << "\n"; 
                currLevel++; 
                os << org._orderedVec.at(i)->name << " "; 
            }
        }
       return os;
    }


        // will fill the vector with order that wanted .
    void OrgChart::fill_order(Node *node, iterator_type type) {
            unsigned int i = 0; // index for loop
            if (type == LEVEL_ORDER) {
                queue <Node *> q;
                q.push(node);
                while (!q.empty()) {
                    Node *temp = q.front();
                    q.pop();
                    for (i = 0; i < temp->children.size(); i++) {
                        q.push(temp->children.at(i));
                    }
                    _orderedVec.push_back(temp);
                }
            }
            else if (type == REVERSE_ORDER){

                queue<Node*> q;
                q.push(node);
                while (!q.empty()) {
                    Node *temp = q.front();
                    q.pop();
                    for (i = temp->children.size()-1 ; i >= 0 && i < VERY_LARGE_LONG ; i--) {
                        q.push(temp->children.at(i));
                    }
                    _orderedVec.insert(_orderedVec.begin(), temp);
                }
         

            }
            else if (type == PRE_ORDER){
                stack<Node*> s;
                s.push(node);
                while (!s.empty()) {
                    Node *temp = s.top();
                    s.pop();
                    for (i = temp->children.size()-1 ; i >= 0 && i < VERY_LARGE_LONG ; i--) {
                        s.push(temp->children.at(i));
                    }
                    _orderedVec.push_back(temp);
                }
            }
        }



    /* implementation of the iterator */


    OrgChart::Iterator::Iterator(vector<Node*> * nodes, iterator_type type) {
        _index = 0;  
        _orderedVecIter = nodes;
        if (type == END_LEVEL_ORDER){
            _index = _orderedVecIter->size()-1;
        }
    }


    OrgChart::Iterator OrgChart::Iterator::operator++() {
        this->_index++;
        return *this;
    }


    OrgChart::Iterator OrgChart::Iterator::operator++(int) {
        this->_index++;
        return *this;
    }

    bool OrgChart::Iterator::operator==(const Iterator& other) {
        return _orderedVecIter->at(_index)->name == other._orderedVecIter->at(other._index)->name;
    }

    bool OrgChart::Iterator::operator!=(const Iterator& other) {
       // printf("%s and %s\n", _orderedVecIter->at(_index)->name.c_str(), other._orderedVecIter->at(_index)->name.c_str());
        return !(_orderedVecIter->at(_index)->name == other._orderedVecIter->at(other._index)->name);
    }

    string & OrgChart::Iterator::operator*() {
        return _orderedVecIter->at(_index)->name;
    }

    string* OrgChart::Iterator::operator->() {
        return &_orderedVecIter->at(_index)->name;
    }










}
