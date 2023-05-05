// treemap_funcs.c: Provides a small library of functions that operate on
// binary search trees mapping strings keys to string values.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "treemap.h"

// Initialize the given tree to have a null root and have size 0.
void treemap_init(treemap_t *tree){
    tree->root=NULL; // no elements, size
    tree->size=0;
}

// Inserts given key/value into a binary search tree. Uses an
// ITERATIVE (loopy) approach to insertion which starts a pointer at
// the root of the tree and changes its location until the correct
// insertion point is located. If the key given already exists in the
// tree, no new node is created; the existing value is changed to the
// parameter 'val' and 0 is returned.  If no node with the given key
// is found, a new node is created and with the given key/val, added
// to the tree, and 1 is returned. Makes use of strcpy() to ease
// copying characters between memory locations.
int treemap_add(treemap_t *tree, char key[], char val[]){
    if(tree->root==NULL){ // make the root
        node_t *new_node=malloc(sizeof(node_t)); // if block will allocate, set the root, add size
        strcpy(new_node->key,key);
        strcpy(new_node->val,val);
        tree->root=new_node;
        tree->root->left=NULL;tree->root->right=NULL; // initializes the other node fields
        tree->size+=1;
        return 1; // success
    }
    else{ // find the point of addition
        node_t *ptr=tree->root; // current pointer
        node_t *trl=NULL; // trailing pointer
        while (ptr!=NULL){
            trl=ptr; // this will keep track of the last place visited by ptr
            int compare=strcmp(key,ptr->key); // negative, positive, or zero value comparing node key to argument key
            if(compare<0){ // key smaller, goes left
                ptr=ptr->left;
            }
            else if(compare>0){ // key bigger, goes right
                ptr=ptr->right;
            }
            else{ // equal keys
                strcpy(ptr->val,val); // modify val but thats it. entirely new addition avoided
                return 0; // function terminated
            }
        } // trl is now the node to modify
        int compare=strcmp(key,trl->key); // this will help check to see which side to add to
        if(compare<0){ // new left node
            node_t *new_node=malloc(sizeof(node_t)); // if block will allocate, set the left, add size
            strcpy(new_node->key,key);
            strcpy(new_node->val,val);
            trl->left=new_node;
            trl->left->left=NULL;trl->left->right=NULL; // initializes the other node fields
            tree->size+=1;
        }
        else{ // new right node
            node_t *new_node=malloc(sizeof(node_t)); // else block will allocate, set the right, add size
            strcpy(new_node->key,key);
            strcpy(new_node->val,val);
            trl->right=new_node;
            trl->right->left=NULL;trl->right->right=NULL; // initializes the other node fields
            tree->size+=1;
        }
        return 1; // success
    }
}

// Searches the tree for given 'key' and returns its associated
// value. Uses an ITERATIVE (loopy) search approach which starts a
// pointer at the root of the tree and changes it until the search key
// is found or determined not to be in the tree. If a matching key is
// found, returns a pointer to its value. If no matching key is found,
// returns NULL.
char *treemap_get(treemap_t *tree, char key[]){
    if(tree->root==NULL){ // there is no tree to search
        return NULL;
    }
    else{
        node_t *ptr=tree->root; // start at the root
        while (ptr!=NULL){
            int compare=strcmp(key,ptr->key);
            if(compare<0){ // key smaller, goes left
                ptr=ptr->left;
            }
            else if(compare>0){ // key bigger, goes right
                ptr=ptr->right;
            }
            else{ // equal keys
                return ptr->val; // found
            }
        }
        return NULL; // not found
    }
    
}

// Eliminate all nodes in the tree setting its contents empty. Uses
// recursive node_remove_all() function to free memory for all nodes.
void treemap_clear(treemap_t *tree){
    if(tree->root!=NULL){
        tree->size=0; // reset size
        node_remove_all(tree->root); // pass in the root
        tree->root=NULL; // reset root
    }
}

// Recursive helper function which visits all nodes in a tree and
// frees the memory associated with them. This requires a post-order
// traversal: visit left tree, visit right tree, then free the cur
// node.
void node_remove_all(node_t *cur){
    if(cur->left!=NULL){
        node_remove_all(cur->left); // recursive free the left
    }
    if(cur->right!=NULL){
        node_remove_all(cur->right); // recursive free the right
    }
    free(cur); // free the root
}

// Prints the key/val pairs of the tree in reverse order at differing
// levels of indentation which shows all elements and their structure
// in the tree. Visually the tree can be rotated clockwise to see its
// structure. See the related node_print_revorder() for additional
// detals.
void treemap_print_revorder(treemap_t *tree){
    if(tree->root!=NULL){
        node_print_revorder(tree->root,0); // passes in the root with no indent
    }
}

// Recursive helper function which prints all key/val pairs in the
// tree rooted at node 'cur' in reverse order. Traverses right
// subtree, prints cur node's key/val, then traverses left tree.
// Parameter 'indent' indicates how far to indent (2 spaces per indent
// level).
//
// For example: a if the root node "El" is passed into the function
// and it has the following structure:
// 
//         ___El->strange_____     
//        |                   |   
// Dustin->corny       ___Mike->stoic
//                    |              
//               Lucas->brash     
// 
// the recursive calls will print the following output:
// 
//   Mike -> stoic                 # root->right
//     Lucas -> brash              # root->right->left
// El -> strange                   # root
//   Dustin -> corny               # root->left
void node_print_revorder(node_t *cur, int indent){
    if(cur->right!=NULL){
        node_print_revorder(cur->right,indent+2); // recursive print the right
    }
    for(int i=0;i<indent;i++){ // add the indents
        printf(" ");
    }
    printf("%s -> %s\n",cur->key,cur->val); // print cur node
    if(cur->left!=NULL){
        node_print_revorder(cur->left,indent+2); // recursive print the left
    }
}

// Print all the data in the tree in pre-order with indentation
// corresponding to the depth of the tree. Makes use of
// node_write_preorder() for this.
void treemap_print_preorder(treemap_t *tree){
    if(tree->root!=NULL){
        node_write_preorder(tree->root,NULL,0); // passes in the root with no depth
    }
}

// Saves the tree by opening the named file, writing the tree to it in
// pre-order with node_write_preorder(), then closing the file.
void treemap_save(treemap_t *tree, char *fname){
    FILE *fout=fopen(fname,"w"); // open file for writing
    node_t *cur=tree->root; // point a copy to the root
    node_write_preorder(cur,fout,0); // passes in the copy
    fclose(fout); // close file
}

// Recursive helper function which writes/prints the tree in pre-order
// to the given open file handle. The parameter depth gives how far to
// indent node data, 2 spaces per unit depth. Depth increases by 1 on
// each recursive call. The function prints the cur node data,
// traverses the left tree, then traverses the right tree.
void node_write_preorder(node_t *cur, FILE *out, int depth){
    for(int i=0;i<depth*2;i++){ // add the indentation
        if(out!=NULL){ // write indents or
            fprintf(out," ");
        }
        else{
            printf(" "); // print indents
        }
    }
    if(out!=NULL){
        fprintf(out,"%s %s\n",cur->key,cur->val); // write the node or
    }
    else{
        printf("%s %s\n",cur->key,cur->val); // print the node
    } 
    if(cur->left!=NULL){
        if(out!=NULL){
            node_write_preorder(cur->left,out,depth+1); // recursive write the left or
        }
        else{
            node_write_preorder(cur->left,NULL,depth+1); // recursive print the left
        }
    }
    if(cur->right!=NULL){
        if(out!=NULL){
            node_write_preorder(cur->right,out,depth+1); // recursive write the right or
        }
        else{
            node_write_preorder(cur->right,NULL,depth+1); // recursive print the right
        }
    }
}

// Clears the given tree then loads new elements to it from the
// named. Repeated calls to treemap_add() are used to add strings read
// from the file.  If the tree is stored in pre-order in the file, its
// exact structure will be restored.  Returns 1 if the tree is loaded
// successfully and 0 if opening the named file fails in which case no
// changes are made to the tree.
int treemap_load(treemap_t *tree, char *fname ){
    FILE *fin=fopen(fname,"r");
    if(fin!=NULL){ // file found
        treemap_clear(tree); // clear tree
        int end=0; // to see where the file is at
        while (1){
            if(end==EOF){
                break; // file has reached the end
            }
            char key[128];
            char val[128];
            end=fscanf(fin,"%s %s",key,val); // scan in key and val, update end
            treemap_add(tree,key,val); // calls add
        }
        fclose(fin); // close file
        return 1; // success
    }
    else{
        printf("ERROR: could not open file '%s'\n",fname);
        return 0; // unsuccessful
    }
}
