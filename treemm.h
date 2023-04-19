#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED
#include <vector>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator
    {
      public:
        Iterator()
        {
        }
        Iterator(std::vector<ValueType>& n) //iterator constructor when passed a vector
        {
            it_vec = n;
            it = n.begin(); //define bounds
            endIT = n.end(); //define bounds
        }


        ValueType& get_value() const //return what value the iterator is pointing to
        {
            return *it;
        }

        bool is_valid() const
        {
            if(it < endIT) //check bounds to see if iterator is valid
            {
                return true;
            }
            return false;
        }

        void advance()
        {
                it++;
        }

      private:
        
        std::vector<ValueType> it_vec;
        typename std::vector<ValueType>::iterator it; //holds position
        typename std::vector<ValueType>::iterator endIT; //holds end bound
    };

    TreeMultimap()
    {
        root = nullptr;
    }

    ~TreeMultimap()
    {
        DeleteTree(root);
        
    }
    

    void insert(const KeyType& key, const ValueType& value)
    {
        if(root == nullptr) //if tree is empty
        {
            root = new Node;
            root->n_key = key;
            root->n_value.push_back(value);
            root->n_left = nullptr;
            root->n_right = nullptr;
            return;
        }
        Node* cur = root;
        for(;;)
        {
            if(cur->n_key == key) //if the key value already exists in tree then push back the data value into the vector
            {
                cur->n_value.push_back(value);
                return;
            }
            if(cur->n_key > key) //search left
            {
                if(cur->n_left != nullptr)
                {
                    cur = cur->n_left; //continue search
                }
                else //position of insertion found
                {
                    cur->n_left = new Node;
                    cur->n_left->n_key = key;
                    cur->n_left->n_value.push_back(value);
                    cur->n_left->n_left = nullptr;
                    cur->n_left->n_right = nullptr;
                    return;
                }
            }
            else if(cur->n_key < key) //search right
            {
                if(cur->n_right != nullptr) //continue search
                {
                    cur = cur->n_right;
                }
                else //position of insertion found
                {
                    cur->n_right = new Node;
                    cur->n_right->n_key = key;
                    cur->n_right->n_value.push_back(value);
                    cur->n_right->n_left = nullptr;
                    cur->n_right->n_right = nullptr;
                    return;
                }
            }
        }
            
    }

    Iterator find(const KeyType& key) const
    {
        Iterator it;
        Node* curr = root; //start at root
        while (curr != nullptr)
        {
            if(curr->n_key == key)
            {
                return Iterator(curr->n_value); //if found return an iterator
            }
            else if (curr->n_key > key)
            {
                curr = curr->n_left;
            }
            else
            {
                curr = curr->n_right;
            }
        }
        return Iterator(); //if not found return void iterator
    }

  private:
    struct Node
    {
        KeyType n_key;
        std::vector<ValueType> n_value;
        Node* n_left;
        Node* n_right;
    };
    Node* root;
    void DeleteTree(Node* n) //destructor helper
    {
        if(n == nullptr)
        {
            return;
        }
        DeleteTree(n->n_left); //recursive destructor deletes all nodes
        DeleteTree(n->n_right);
        delete n;
    };
};

#endif // TREEMULTIMAP_INCLUDED
