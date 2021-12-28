#include <iostream>
using namespace std;

struct node {
    int val;
    int height;     //balance factor平衡因子 可用height来计算
    struct node* lchild;
    struct node* rchild;
    struct node* parent;

    node(int x = 0) : val(x), height(0), lchild(nullptr), rchild(nullptr), parent(nullptr) {}
};

class AVLtree {
public:
    AVLtree() : root(nullptr) {}
    ~AVLtree();
    void inOrder();
    void preOrder();
    void insert(int val);
    void remove(int val);   //
    node* search(int val);
    int height(node* p) {   return p ? p->height : 0;   }
private:
    node* root;
private:
    void __inOrder(node* root);
    void __preOrder(node* root);
    void __destroy(node*& root);
    node* __insert(node*& p, int val);   
    node* __remove(node* p, int val);   //

    node* __search(node* p, int val);
    node* __LRotate(node* p);   
    node* __RRotate(node* p);   
    node* __LRRotate(node* p);  
    node* __RLRotate(node* p);  
};

int main() {
    AVLtree t;
    for (int i = 0; i < 10; i++) {
        int k;
        cin >> k;
        t.insert(k);
        t.inOrder();
        cout << endl;
        t.preOrder();
        cout << endl;
    }
    return 0;
}

AVLtree::~AVLtree() {
    __destroy(root);
}

void AVLtree::__inOrder(node* root) {
    if (root == nullptr)
        return;
    __inOrder(root->lchild);
    cout << root->val << ' ';
    __inOrder(root->rchild);
}

void AVLtree::inOrder() {
    __inOrder(root);
}
void AVLtree::__preOrder(node* root) {
    if (root == nullptr)
        return;
    cout << root->val << ' ';
    __preOrder(root->lchild);
    __preOrder(root->rchild);
}

void AVLtree::preOrder() {
    __preOrder(root);
}

void AVLtree::__destroy(node*& root) {
    if (root == nullptr)
        return;
    __destroy(root->lchild);
    __destroy(root->rchild);
    delete root;
    root = nullptr;
}

node* AVLtree::__search(node* p, int val) {
    if (p == nullptr)
        return p;
    if (p->val < val)
        return __search(p->rchild, val);
    else if (p->val > val)
        return __search(p->lchild, val);
    return p;
}

node* AVLtree::search(int val) {
    return __search(root, val);
}

//此处p为最小失衡结点
node* AVLtree::__LRotate(node* p) {
    node* prchild = p->rchild;
    p->rchild = prchild->lchild;
    prchild->lchild = p;

    //更新高度
    p->height = max(height(p->lchild), height(p->rchild)) + 1;
    prchild->height = max(height(prchild->lchild), height(prchild->rchild)) + 1;
    return prchild;
}

node* AVLtree::__RRotate(node* p) {
    node* plchild = p->lchild;
    p->lchild = plchild->rchild;
    plchild->rchild = p;

    //更新高度
    p->height = max(height(p->lchild), height(p->rchild)) + 1;
    plchild->height = max(height(plchild->lchild), height(plchild->rchild)) + 1;
    return plchild;

}

node* AVLtree::__RLRotate(node* p) {
    p->rchild = __RRotate(p->rchild);
    return __LRotate(p);
}

node* AVLtree::__LRRotate(node* p) {
    p->lchild = __LRotate(p->lchild);
    return __RRotate(p);
}

//在根节点为p的子树中插入值为val的结点
//返回这颗子树的根节点(可能不是p)
node* AVLtree::__insert(node*& p, int val) {
    if (p == nullptr) {
        p = new node(val);
    } else if (p->val > val) {
        //在左子树中处理
        p->lchild = __insert(p->lchild, val);
        if (height(p->lchild) - height(p->rchild) == 2) {
            //失衡 因为递归,所以第一次进入这个判断语句的一定为最小失衡节点
            if (val < p->lchild->val) { 
                p = __RRotate(p);   //插入左孩子的左子树
            } else {
                p = __LRRotate(p);
            }
        }
    } else if (p->val < val) {
        p->rchild = __insert(p->rchild, val);
        if (height(p->rchild) - height(p->lchild) == 2) {
            if (val > p->rchild->val) {
                p = __LRotate(p);
            } else {
                p = __RLRotate(p);
            }
        }
    }
    p->height = max(height(p->lchild), height(p->rchild)) + 1;
    return p;
}

void AVLtree::insert(int val) {
    __insert(root, val);
}