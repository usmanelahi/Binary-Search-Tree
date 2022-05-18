#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>
using namespace std;

template <typename T>
class bst {
    struct treeNode {
        T data;
        treeNode* lchild, * rchild;

        treeNode(const T& new_data, treeNode* lc = NULL, treeNode* rc = NULL) {
            data = new_data;
            lchild = lc;
            rchild = rc;
        }

    }
    *root;
    int n;//size of the tree
    

    bool getAccess(const T& key, treeNode*& ptr = NULL, treeNode*& pptr = NULL)
    {
        ptr = root;
        pptr = NULL;

        while (ptr != NULL && ptr->data != key) {
            pptr = ptr;//pptr is the parent of next ptr
            if (key < ptr->data)
                ptr = ptr->lchild;
            else
                ptr = ptr->rchild;
        }

        return (ptr != NULL);
    }

    int childCount(treeNode* ptr) {
        if (ptr == NULL || (ptr->lchild == NULL && ptr->rchild == NULL))
            return 0;
        else if (ptr->lchild != NULL && ptr->rchild != NULL)
            return 2;
        else return 1;
    }

    //rotation methods
    bool rr(treeNode* ptr, treeNode* pptr) {
        //right rotate around ptr
        treeNode* cptr = ptr->lchild;
        if (cptr == NULL)
            return false;
        else {
            //what is the node itself is the root
            //promote cptr
            if (pptr == NULL) {
                root = cptr;
            }
            else {
                if (ptr == pptr->lchild)
                    pptr->lchild = cptr;
                else
                    pptr->rchild = cptr;
            }
            //adjust children
            treeNode* rc_cptr = cptr->rchild;
            cptr->rchild = ptr;
            ptr->lchild = rc_cptr;
            return true;
        }
    }


    bool rl(treeNode* ptr, treeNode* pptr) {
        //left rotate around ptr
        treeNode* cptr = ptr->rchild;
        if (cptr == NULL)
            return false;
        else {
            if (pptr == NULL) {
                root = cptr;
            }
            else {
                if (ptr == pptr->lchild)
                    pptr->lchild = cptr;
                else
                    pptr->rchild = cptr;
            }
            treeNode* lc_cptr = cptr->lchild;
            cptr->lchild = ptr;
            ptr->rchild = lc_cptr;
            return true;
        }
    }

    void eraseCase0(treeNode* ptr, treeNode* pptr) {
        delete ptr;
        if (ptr == root) {
            //cout<<"Root updated..."<<endl;
            root = NULL;
        }
        else if (ptr == pptr->lchild) {
            pptr->lchild = NULL;
        }
        else {
            pptr->rchild = NULL;
        }
    }

    void eraseCase1(treeNode* ptr, treeNode* pptr) {
        treeNode* cptr;
        if (ptr->rchild != NULL)
            cptr = ptr->rchild;
        else
            cptr = ptr->lchild;
        //ptr: node, pptr: parent of ptr, cptr: child of ptr
        if (ptr == root) {
            //cout<<"Root updated..."<<endl;
            root = cptr;
            delete ptr;
        }
        else {
            if (ptr == pptr->lchild)//ptr is left child of pptr
                pptr->lchild = cptr;
            else//ptr is right child of pptr
                pptr->rchild = cptr;
            delete ptr;
        }
    }

    void eraseCase2(treeNode* ptr, treeNode* pptr) {
        treeNode* nptr = ptr->rchild, * pnptr = ptr;
        while (nptr->lchild != NULL) {
            pnptr = nptr;
           nptr = nptr->lchild;
        }
        swap(ptr->data, nptr->data);
        if (childCount(nptr) == 0) {
            eraseCase0(nptr, pnptr);
        }
        else {
            eraseCase1(nptr, pnptr);
        }
    }

    void printInOrder(treeNode* ptr) {
        if (ptr != NULL) {
            printInOrder(ptr->lchild);
            cout << ptr->data << " ";
            printInOrder(ptr->rchild);
        }
    }

    // Called in  Destructor
    void PostOrder_Destructor(treeNode* root) {
        if (root != nullptr) {
            PostOrder_Destructor(root->lchild);
            PostOrder_Destructor(root->rchild);
            delete root;
        }
    }

    // height of the tree
    int heightOfBst(treeNode* ptr) {
        if (ptr == NULL)
            return 0;

        else
        {
            int lDepth = heightOfBst(ptr->lchild);
            int rDepth = heightOfBst(ptr->rchild);
            if (lDepth > rDepth)
                return(lDepth + 1);
            else
                return(rDepth + 1);
        }
    }

    //Helper for = Overlaoding
    void PreOrder(treeNode* root) {        
        if (root != nullptr) {
            PreOrder(root->lchild);
            PreOrder(root->rchild);
        }
    }

    // balanced tree constructor
    T sortedbst(T arr[], int s, int e) {
        if (s > e)
            return NULL;

        int mid = (s + e) / 2;
        treeNode* root =new treeNode(arr[mid]);
        root->lchild = sortedbst(arr, s, mid - 1);
        root->rchild = sortedbst(arr, mid + 1, e);
        return root;
    }

    //== operator overloading
    queue<int> InorderOverloading(treeNode* ptr) {
        queue<T>q;
        if (ptr != nullptr) {
            InorderOverloading(ptr->lchild);
            q.push(ptr->data);
            InorderOverloading(ptr->rchild);
        }
        return q;
    }

    //Sub-Tree Method           
    bool Identical(treeNode* ptr,treeNode* ptr1) {
        if (ptr == nullptr && ptr1 == nullptr) {
            return true;
        }
        if (ptr == nullptr || ptr1 == nullptr) {
            return false;
        }
        if ((ptr->data == ptr1->data && Identical(ptr->lchild, ptr1->lchild) && Identical(ptr->rchild, ptr1->rchild))) {
            return true;
        }
    }

    //Helper Function For Sub Tree
    bool SubTree(treeNode* ptr1, treeNode* ptr2) {
        if (ptr1 == nullptr) {
            return true;
        }
        if (ptr2 == nullptr) {
            return false;
        }
        if (Identical(ptr1, ptr2)) {
            return true;
        }
        else {
            bool x = SubTree(ptr1->lchild, ptr2) || SubTree(ptr1->rchild, ptr2);
            
            return x;
        }
    }


    //Helper Function to find the breadth
    int GetBreadth(treeNode* ptr, int k) {
        int lw;
        int rw;
        if (ptr == nullptr) {
            return 0;
        }
        if (k == 1) {
            return 1;
        }
        else {
            lw = GetBreadth(ptr->lchild, k - 1);
            rw = GetBreadth(ptr->rchild, k - 1);
        }
        return lw + rw;
    }

    //SubSet Helper
    vector<int> InOrderSubTree(treeNode* ptr) {
        vector<int>v;
        if (ptr != nullptr) {
            InOrderSubTree(ptr->lchild);
            v.push_back(ptr->data);
            InOrderSubTree(ptr->rchild);
        }
        return v;
    }

    //Helper Function To find Common Ancestor
    bool FindWay(treeNode* ptr, vector<T>& v, T k) {
        if (root == nullptr) {
            return false;
        }
        v.push_back(ptr->data);
        if (ptr->data == k) {
            return true;
        }
        if ((ptr->lchild && FindWay(ptr->lchild, v, k))){
            return true;
        }
        if ((ptr->rchild && FindWay(ptr->rchild, v, k))){
            return true;
        }
        v.pop_back();
        return false;
    }

    // Helper To Find the Path Sum
    void pathSums(vector<int>& v, treeNode* ptr, int sum)
    {
        if (ptr->lchild == 0 && ptr->rchild == 0)
        {
            sum += ptr->data;
            v.push_back(sum);
        }
        else
        {
            sum += ptr->data;
            if (ptr->lchild)
                pathSums(v, ptr->lchild, sum);
            if (ptr->rchild)
                pathSums(v, ptr->rchild, sum);
        }
    }

    //Copy Constructor Helper
    void InOrderTraversing(treeNode* ptr) {
        if (ptr != nullptr) {
            insert(ptr->data);
            InOrderTraversing(ptr->lchild);
            
            InOrderTraversing(ptr->rchild);
        }
    }

    void Trimmer(treeNode* ptr, int k, int i) {
        if (ptr == nullptr) {
            return;
        }
        if (i == k) {
            PostOrder_Destructor(ptr->lchild);
            PostOrder_Destructor(ptr->rchild);
            ptr->lchild = nullptr;
            ptr->rchild = nullptr;
        }
        else {
            Trimmer(ptr->lchild,k,i+1);
            Trimmer(ptr->rchild, k, i + 1);
        }
    }

    public:

        bst() {
            root = NULL;
            n = 0;
        }

        bool insert(const T& key) {
            treeNode* ptr, * pptr;
            if (getAccess(key, ptr, pptr))
                return false;
            else {
                //ptr is null
                if (pptr == NULL) {//empty tree, because pptr==NULL
                    root = new treeNode(key, NULL, NULL);
                }
                else if (key < pptr->data) {//new node is a left child
                    pptr->lchild = new treeNode(key, NULL, NULL);
                }
                else {
                    pptr->rchild = new treeNode(key, NULL, NULL);
                }
                n++;
                return true;
            }
        }

        bool find(const T& key) {
            return getAccess(key);
        }

        bool findAndPromote(const T& key) {
                treeNode* ptr, * pptr, * gptr;
                if (getAccess(key, ptr, pptr, gptr)) {
                    if (pptr != NULL) {  //can't promote root
                        if (pptr->rchild == ptr) {
                            rl(pptr, gptr);
                        }
                        else {
                            rr(pptr, gptr);
                        }
                    }
                    return true;
                }
                else { return false; }
            
        }

        bool erase(const T& key) {
            treeNode* ptr, * pptr;
            if (!getAccess(key, ptr, pptr))
                return false;
            else {
                //case 0: ptr has 0 children
                if (childCount(ptr) == 0) {
                    cout<<"case 0"<<endl;
                    eraseCase0(ptr, pptr);
                    //case 1: ptr has 1 children
                }
                else if (childCount(ptr) == 1) {
                    cout<<"case 1"<<endl;
                    eraseCase1(ptr, pptr);
                    //case 2: ptr has 2 children
                }
                else {
                    cout<<"case 2"<<endl;
                    eraseCase2(ptr, pptr);
                }
                n--;
                return true;
            }
        }

        int size() { 
            return n;
        }

        void print()
        {
            printInOrder(root);
        }

        
        //This will return the height 
        int height()  
        {
           return heightOfBst(root);   //Declared in Private
        }

        //Function to calculate the depth of a leaf
        int Depth( T key) {
            int depth = -1;
            treeNode* ptr = root;
            if (ptr == nullptr) {
                depth = 0;
            }
            while (ptr != nullptr) {
                if (key == ptr->data) {
                    return(depth + 1);
                }
                if (key < ptr->data) {
                    ptr = ptr->lchild;
                    depth += 1;
                    
                }
                if (key > ptr->data) {
                    ptr = ptr->rchild;
                    depth += 1;
                    
                }
            }
            return depth;
        }

        //For the destructor we have to use Post order method declared in private
        ~bst()
        {
            PostOrder_Destructor(root); //Declared in Private
        }

        //Copy Constructor
        bst(bst& obj) {
            root = nullptr;
            n = 0;
            InOrderTraversing(obj.root);
        }

        void operator =(const bst&obj) {
            PreOrder(root);  //Declared in Private
        }

        //Parameterized Constructor
        bst(T SortedData[], int n) { //To make a perfect balanced binary tree
            int s = SortedData[0];
            int e = SortedData[n];
            sortedbst(SortedData, s, e); //Declared in Private
        }

       // Overloading of == operator
        bool operator == (const bst& obj) {
            queue<T>q = InorderOverloading(root);  //Declared in Private
            queue <T>q2 = InorderOverloading(obj.root);  //Declared in Private
            if (root == nullptr && obj.root == nullptr)
                return true;
            if (root != nullptr && obj.root != nullptr) {
                if (q == q2)  //Declared in Private
                    return true;
            }
            else
                return false;
        }

        //To find that a tree is sub-tree or not
        bool Subtree( bst obj) {
            return SubTree(root, obj.root);
        }

        //The Subset Method
        bool IsSubset(const bst& obj) {
            if (root == nullptr && obj.root == nullptr) {
                return false;
            }
            if (InOrderSubTree(obj.root) == InOrderSubTree(root)) {  //Declared in Private
                return true;
            }
        }


        //To Find the breadth of the tree
        int breadth() {
            int width=0;
            int temp;
            int h = height();  //1st func of The Assignment
            int j = 1;
            while (j < h) {
                temp=GetBreadth(root, j);  //Declared in Private
                if (temp > width) {
                    width = temp;
                }
                j++;
            }
            return width;
        }

        //Successor Method
        T Successor(T k) {
            
            treeNode* ptr = root;
            treeNode* gptr = nullptr;
            treeNode* sptr = nullptr;
            if (ptr == nullptr) {
                return -1;
            }
            while (ptr != nullptr && ptr->data != k)
            {
                if (k < ptr->data)
                {
                    sptr = ptr;
                    gptr = ptr;
                    ptr = ptr->lchild;
                }
                else 
                {
                    gptr = ptr;
                    ptr = ptr->rchild;
                }
            }
            if(ptr==nullptr){
               
                return -1;
            }
            else if(ptr->rchild)
            {
               
                ptr = ptr->rchild;
                while (ptr->lchild) {
                    ptr = ptr->lchild;
                }
                return ptr->data;
            }
            else if (gptr->lchild == ptr) {
                return gptr->data;
            }
            else if (sptr) {
                return sptr->data;
            }
            else
            {
                return -1;
            }
        }

        //Lowest Common Ancestor
        int LowestCommonAncestor(T key1, T key2) {
            vector<int>v1, v2;
            if (FindWay(root, v1, key1) == false) {  //Declared in Private
                return -1;
            }
            if (FindWay(root, v2, key2) == false) {  //Declared in Private
                return -1;
            }
            int j = 0;
            while (j < v1.size() && j < v2.size()) {
                if (v1[j] != v2[j]) {
                    break;
                }
                j++;
            }
            return v1[j - 1];
        }

        //Path Sum Method
        vector<int> PathSum() {
            vector<int> v;
            int sum = 0;
            pathSums(v, root, sum);
            return v;
        }


        // To find whether the tree is balanced or,not
        bool isBalanced() {
            int hl = heightOfBst(root->lchild);
            int hr = heightOfBst(root->rchild);
            int p = hr - hl;
            if (-1 >= p <= 1) {
                return true;
            }
        }

        // Iterator class 

        class iterator {

            treeNode* var;
            vector<treeNode*> vec;
            int x;
            friend class bst;

            void Constructor1(treeNode* ptr) {  //Helper Function For Copy Constructor
                if (ptr != nullptr) {
                    Constructor1(ptr->lchild);
                    vec.push_back(ptr);
                    Constructor1(ptr->rchild);
                }

            }
        public:

            bool operator != (const iterator& obj) {

                if (var != obj.var) {
                    return true;
                }
                else {
                    return false;
                }

            }

            iterator& operator ++()
            {
                if (x < vec.size())
                    var = vec[++x];
                return *this;
            }

            iterator() {
                var = root;
                x = 0;
            }

            iterator(treeNode* ptr) {
                
                x = 0;
                Constructor1(ptr);
                vec.push_back(0);
                var = vec[0];
            }

            T& operator*() {
                return var->data;
            }
            
        };
      
            typedef iterator i;

            iterator begin()
            {
                iterator x(root);
                return x;
            }

            iterator end() {
                iterator x(0);
                return x;
            }

            //Function to trim below a level
            void TrimBelowK(int k) {
                if (k < 0) {
                    return ;
                }
                int i = 1;
                Trimmer(root, k, i);
            }
                
};

int main() {
    bst <int>t;
    t.insert(4);
    t.insert(2);
    t.insert(6);
    t.insert(1);
    t.insert(3);
    t.insert(5);
    t.insert(7);
    t.print();
    cout << t.height() << endl;
    cout << t.LowestCommonAncestor(6, 1) << endl;
    vector<int> p;
    p = t.PathSum();
    for (int i = 0; i < p.size(); i++)
        cout << p[i] << " ";
    cout << '\n';
    for (bst<int>::iterator itr = t.begin(); itr != t.end(); ++itr)
    {
        cout << *itr << " ";
    }
    t.TrimBelowK(1);

    t.print();
    cout << t.height() << endl;


    bst<int> tmp;
    tmp.insert(2);
    tmp.insert(3);
    cout << t.IsSubset(tmp) << endl << t.Subtree(tmp);

}

