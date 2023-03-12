#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan {preorder, inorder, postorder};

template<class T>
class BST {
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp=inorder) const;

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(BSTNode<T> *node, TraversalPlan tp) const;
    void copy_tree(BSTNode<T> *&t1, BSTNode <T> *t2) ;
    void helper_dest(BSTNode<T> *&tree);
    bool helper_cont(BSTNode<T> *tree,BSTNode<T> *node)const;
    BSTNode<T> * help_rem(BSTNode<T>*tree,const T &data);
    void help_rem_all(BSTNode<T> *tree);
    BSTNode<T> *help_post_order(BSTNode<T> *tree,BSTNode<T> *successor) const;
    BSTNode<T> *find_min(BSTNode<T> *tree) const;
    BSTNode<T> *find_parent(BSTNode<T> *tree,BSTNode<T> *node, BSTNode<T> *parent) const;
    BSTNode<T> *help_successor(BSTNode<T> *tree,BSTNode<T> *node,TraversalPlan tp,BSTNode<T> *successor)const;
private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_H
template<class T> 

BSTNode<T> *BST<T>::help_post_order(BSTNode<T> *tree,BSTNode<T> *successor)const{
 
    successor=find_min(tree);
    if(successor->right!=NULL)
        help_post_order(successor->right,NULL);
    else
        return successor;   
     
}   
template<class T>
  BSTNode<T> *BST<T>::find_parent(BSTNode<T> *tree,BSTNode<T> *node,BSTNode<T> *parent)const{

    if (tree==NULL)
        return NULL;
    else if(tree->left==node || tree->right==node)
        {parent= tree;
            return parent;
        }
    else if(node->data>tree->data)
        return find_parent(tree->right,node,parent);
    else if(node->data<tree->data)
        return find_parent(tree->left,node,parent);

 
      return parent;
  }
template<class T>
  BSTNode<T> *BST<T>::help_successor(BSTNode<T> *tree,BSTNode<T> *node,TraversalPlan tp,BSTNode<T> *successor)const{
  
    if (tree == NULL) {
        return successor;
    }

    else if (tp == inorder) {
    if (tree == node)
    {
        if (tree->right != NULL) {
            return find_min(tree->right);
        }
    }
    
    else if (node->data < tree->data)
    {
        successor = tree;
        return help_successor(tree->left,node, tp,successor);
    }
 
    else {
        return help_successor(tree->right,node,tp,successor);
    }
 
    return successor;
  }
  
  else if(tp==preorder){
      
    if(tree==node){
        if(tree->left!=NULL)
            successor=tree->left;
        else if(tree->right!=NULL)
            successor=tree->right;
        else{ 
            BSTNode<T> *current;
            current=root;
            successor=find_parent(current,node,NULL);
            
            for(;successor!=NULL;){
                if(node->data<successor->data && successor->right !=NULL)
                    break;
                successor=find_parent(current,successor,NULL);    
            }
        if (successor!=NULL)
            return successor->right;
        else 
            return NULL;    
        }      
      }
    else if (node->data < tree->data)
    {
        return help_successor(tree->left,node, tp,successor);
    }
 
    else {
        return help_successor(tree->right,node,tp,successor);
    }  

  }
    else if(tp==postorder){
      BSTNode<T> *current;
      current=root;

      if(node==tree){
          return successor;
      }

      successor=find_parent(current,node,NULL);
      
      if (successor!=NULL){
        
      if(successor->right==node || successor->right==NULL){
         return successor;
        }
        
      else if(successor->right!=NULL)    
          successor=help_post_order(successor->right,NULL);
          }
          
      
    return successor;
  }

  }
template<class T>
    void BST<T>::copy_tree(BSTNode <T> *&t1, BSTNode <T> *t2) {
    BSTNode <T> *copy;
    
    if(t2 != NULL) {
        
        copy = new BSTNode<T>();
        copy->data=t2->data;
        t1=copy;
        copy_tree(t1->left, t2->left);
        copy_tree(t1->right, t2->right);
    }

    else
        t1 = NULL;

}

template<class T>
    void BST<T>::helper_dest(BSTNode<T> *&tree){

        if(tree!=NULL){
            helper_dest(tree->left);
            helper_dest(tree->right);
        }

        delete tree;
    }
    

template<class T>
    bool BST<T>::helper_cont(BSTNode<T> *tree,BSTNode<T> *node)const{
        
        if(tree!=NULL){

            if(tree==node)
                return true;

            else{

            helper_cont(tree->left,node);
            helper_cont(tree->right,node);            
            }

        }
    return false;
    }
    

template<class T> 
    
BSTNode<T> *BST<T>::help_rem(BSTNode<T> *tree,const T &data)
    {    
        if (tree==NULL)
            return tree;
            
        else if(data>(tree->data)){
           tree->right=help_rem(tree->right,data);
           
        }
        else if(data<(tree->data)){
            tree->left=help_rem(tree->left,data);
            
        }
        else{
        if (tree->left==NULL &&tree->right==NULL)
        {
        delete tree;
        return NULL;
        }
        
        else if(tree->right==NULL){
            BSTNode<T> *temp;
            temp=tree->left;
            delete tree;
            return temp;
        }
        
        else if (tree->left==NULL){
            BSTNode <T> *temp;
            temp=tree->right;
            delete tree;
            return temp;
        }
        
        
            BSTNode<T> *temp=find_min(tree->right);
            tree->data=temp->data;
            tree->right=help_rem(tree->right,temp->data);
        
        }
        return tree;
        
    }
template<class T>

void BST<T>::help_rem_all(BSTNode<T> *tree) {
    
    if (tree == NULL)
        return;
    else{    
    help_rem_all(tree->left);
    help_rem_all(tree->right);
    }
    
    delete tree;
}
template<class T>
BSTNode<T> *BST<T>::find_min(BSTNode<T> *tree) const {
    BSTNode<T> *current;
    
    for(; tree!=NULL;)
    {   current=tree;
        tree=tree->left;
    }
    /* TODO */
    return current;
}

template<class T>
BST<T>::BST() {
    
    root=NULL;
    /* TODO */
}

template<class T>
BST<T>::BST(const BST<T> &obj) {
    
    if (obj.root==NULL){
        root=NULL;
    }

    else{
        copy_tree(root, obj.root);
    }
    
    /* TODO */
}

template<class T>
BST<T>::~BST() {
    
    helper_dest(root);
    root=NULL;
    
    /* TODO */
}

template<class T>
BSTNode<T> *BST<T>::getRoot() const {
    
    return root;
    
    /* TODO */
}

template<class T>
bool BST<T>::isEmpty() const {
    
    if(root==NULL)
       return true;

    return false;    

    /* TODO */
}

template<class T>
bool BST<T>::contains(BSTNode<T> *node) const {
    
   
    return helper_cont(root,node);
    /* TODO */
}

template<class T>
void BST<T>::insert(const T &data) {
 BSTNode<T> *current,*copy;

   
    if (root==NULL){
        copy=new BSTNode<T> ();
        copy->data=data;
        root=copy;
    }
    
    else{    current=root;
        for (;current!=NULL  ; )
    {   
        if (data>(current->data)&&current->right==NULL)
            {   copy= new BSTNode <T> ();
                copy->data=data;
                current->right=copy;
                break;
            }
        else if(data>(current->data)) 
                current=current->right;
        
        else if (data<(current->data)&& current->left==NULL){
                copy= new BSTNode <T> ();
                copy->data=data;
                current->left=copy;
                break;
        }        
        else if(data<(current->data))
                current=current->left;
            
    }
    
        
    }
    
    /* TODO */
}

template<class T>
void BST<T>::remove(const T &data) {
    BSTNode<T> *current;
    current=root;
    help_rem(current,data);
    /* TODO */
}

template<class T>
void BST<T>::removeAllNodes() {
    BSTNode<T> *current;
    current=root;
    help_rem_all(current);
    root=NULL;
    /* TODO */
}

template<class T>
BSTNode<T> *BST<T>::search(const T &data) const {
    BSTNode<T> *current;
    current=root;
    for (; current!=NULL;){
        
        if(data>(current->data))
            current=current->right;
        else if(data<(current->data))
            current=current->left;
        else{
            return current;
        }    
    }
    
    /* TODO */
    return current;
}

template<class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *node, TraversalPlan tp) const {
    BSTNode<T> *current;
    current=root;
    
    if (tp == inorder) {
        return help_successor(current,node,tp,NULL);
        /* TODO */
    } else if (tp == preorder) {
        return help_successor(current,node,tp,NULL);
        /* TODO */
    } else if (tp == postorder) {
        return help_successor(current,node,tp,NULL);
        /* TODO */
    }
}

template<class T>
void BST<T>::print(TraversalPlan tp) const {

    if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, inorder);
        std::cout << std::endl << "}" << std::endl;
    } 
        else if (tp == preorder) {
        if(isEmpty()){
            std::cout <<"BST_preorder{}" <<std::endl;
            return;
        }
        
        std::cout <<"BST_preorder{"<< std::endl;
        print(root,preorder);
        std::cout << std::endl <<"}" << std::endl;  
        /* TODO */
    }
    else if (tp == postorder) {


        if(isEmpty()){
            std::cout <<"BST_postorder{}" <<std::endl;
            return;
        }
        
        std::cout <<"BST_postorder{"<< std::endl;
        print(root,postorder);
        std::cout << std::endl <<"}" << std::endl;
        /* TODO */
    }
}

template<class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    
   
    if(this != &rhs) {
    removeAllNodes();
    
    if (rhs.root==NULL){
        root=NULL;
    }

    else{
        copy_tree(root, rhs.root);
    }
    
    }
    return *this;
    /* TODO */
}

template<class T>
void BST<T>::print(BSTNode<T> *node, TraversalPlan tp) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    if (tp == inorder) {
        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->data;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } else if (tp == preorder) {
        
  
        /* first print data of node */
    std::cout << "\t" << node->data;    

    /* then recur on left subtree */
      if (node->left){
        std::cout << ","<<std::endl;
      }
      print(node->left,preorder);  
      
    /* now recur on right subtree */
      if (node->right) { 
        std::cout << ","<<std::endl;
      }
      print(node->right,preorder);

    
}
    
    else if (tp == postorder) {
     
     /* then recur on left subtree */
      print(node->left,postorder);  
      if (node->left){
        std::cout << ","<<std::endl;
      }
          /* now recur on right subtree */
      print(node->right,postorder);
      if (node->right) { 
        std::cout << ","<<std::endl;
      }
      

        /* first print data of node */
    std::cout << "\t" << node->data;    

        /* TODO */
    }
}
