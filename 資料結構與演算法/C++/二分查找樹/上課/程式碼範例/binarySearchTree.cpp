#include <algorithm>
#include <ctime>  //計時
#include <iostream>
#include <queue>  //輔助BFS

#include "FileOps.h"     //導入處理bible.txt的自訂義函式庫
#include "SequenceST.h"  //導入以鍊表(Linked-List)實做的順序查找表
using namespace std;

/*
    前中後序問題
    void xxxOrder(Node *node){
        //前序在這裡做事(左邊點點)
        xxxOrder(node->left); //左線
        //中序在這裡做事(中間點點)
        xxxOrder(node->right); //右線
        //後序在這裡做事(右邊點點)
    }

    可以由影片思考左右線與點點的關係
*/

//Binary Search Tree 類--->實現查找表
template <class Key, class Value>
class BST {
private:
    //私有的結構體Node--->用來表示節點
    struct Node {
        Key key;      //節點的key
        Value value;  //節點的value
        Node *left;   //左節點的位置(左孩子)
        Node *right;  //右節點的位置(右孩子)
        //Node的Constructor
        Node(Key key, Value value) {
            //初始化節點的Key-Value
            this->key = key;
            this->value = value;
            //初始化左右節點--->先假設不存在
            this->left = NULL;
            this->right = NULL;
        }
        //以傳入的node節點當作參數 的Constructor
        Node(Node *node) {
            this->key = node->key;
            this->value = node->value;
            this->left = node->left;
            this->right = node->right;
        }
    };
    Node *root;  //代表此BST結構的根結點
    int count;   //代表此BST結構有多少個節點

    /*
        insert的Overloading函數
        傳入要插入的節點位置(Node*)、要插入的節點資訊(Key,Value)
        返回插入完畢後，新的root節點的位置(Node*)

        此過程的實現是透過遞迴來完成的
    */
    Node *insert(Node *node, Key key, Value value) {
        if (node == NULL) {  //如果當前節點為空
            //代表已經到適當位置--->插入新的節點
            count++;                      //將節點數量更新
            return new Node(key, value);  //將新插入的節點往上層回傳
        } else if (key == node->key) {    //如果要插入的節點key就是當前節點key(節點已存在)
            node->value = value;          //將根結點的value更新成 新傳入的節點value
        } else if (key < node->key) {     //如果傳入的節點key小於當前節點的key--->往左子樹去檢查
            //使用遞迴方法:對當前節點的左子樹做insert，並將新的節點位置存回左子樹
            node->left = insert(node->left, key, value);
        } else {  //如果傳入的節點key>當前節點key
            //使用遞迴方法:對當前節點的右子樹做insert，並將新的節點位置存回右子樹
            node->right = insert(node->right, key, value);
        }
        //返回insert後的節點(key==node->key時會到達這裡)
        return node;
    }
    /*
        在以特定節點node為根的二分查找樹中，查找特定的節點Key值
    */
    bool contain(Node *node, Key key) {
        //如果查找到沒有節點了--->沒找到
        if (node == NULL) {
            return false;
        }

        if (key == node->key) {        //如果key等於當前節點的key
            return true;               //return 存在
        } else if (key < node->key) {  //如果key小於當前節點
            //遞迴尋找 以左節點為樹根的BST
            return contain(node->left, key);
        } else {  //如果key大於當前節點
            //遞迴尋找 以右節點為樹根的BST
            return contain(node->right, key);
        }
    }
    /*
        對以node節點為根節點的BST
        做查找key並返回value的指標
    */
    Value *search(Node *node, Key key) {
        if (node == NULL) {  //如果沒有找到Key
            return NULL;     //Value指標就為空
        }

        if (key == node->key) {        //如果key等於當前node的key
            return &(node->value);     //返回value的"地址"
        } else if (key < node->key) {  //如果key小於當前node的key
            //遞迴尋找以左節點的BST
            return search(node->left, key);
        } else {  //如果key大於當前node的key
            //遞迴尋找以右節點的BST
            return search(node->right, key);
        }
    }

    //對以node為根節點的BST進行DFS前序遍歷
    void preOrder(Node *node) {
        if (node != NULL) {
            //因為是左子樹先遞迴到底--->前序--->要做事
            cout << node->key << endl;
            //遞迴左邊到底
            preOrder(node->left);
            //再遞迴右邊到底
            preOrder(node->right);
        }
    }

    //對以node為根節點的BST進行DFS中序遍歷
    void inOrder(Node *node) {
        if (node != NULL) {
            //左邊先遞迴到底--->不做事
            //先遞迴左邊--->想像成左線
            inOrder(node->left);
            //開始中間遞迴到底--->中序--->要做事
            cout << node->key << endl;
            //再遞迴右邊--->想像成右線
            inOrder(node->right);
        }
    }

    //對以node為根節點的BST進行DFS後序遍歷
    void postOrder(Node *node) {
        if (node != NULL) {
            //遞迴左邊
            postOrder(node->left);
            //遞迴右邊
            postOrder(node->right);
            cout << node->key << endl;
        }
    }

    //使用後序方法釋放動態記憶體
    void destory(Node *node) {
        if (node != NULL) {
            destory(node->left);   //先遞迴左邊到底
            destory(node->right);  //再遞迴右邊到底
            delete node;           //釋放節點
            count--;               //更新節點數量
        }
    }

    //查找以node為根節點的BST中key值最小的節點(其實就是一直往左下找)
    Node *minimum(Node *node) {
        //遞迴到底 如果當前節點沒有左孩子(則此節點就是最左下角的節點)
        if (node->left == NULL) {
            return node;
        }
        return minimum(node->left);
    }

    //查找以node為根節點的BST中key值最大的節點(其實就是一直往右下找)
    Node *maximum(Node *node) {
        //遞迴到底 如果當前節點沒有右孩子(則此節點就是最右下角的節點)
        if (node->right == NULL) {
            return node;
        }
        return maximum(node->right);
    }

    //刪除以node的BST中key最小的節點
    Node *removeMin(Node *node) {
        if (node->left == NULL) {  //如果沒有左節點
            //代表此節點是最小節點
            Node *rightNode = node->right;  //檢查以當前節點為根的BST是否有右節點
            /*
                rightNode指標 會有兩種狀況
                1.有右節點--->rightNode存在--->則右節點會取代當前節點當作此層BST的根結點
                2.沒有右節點--->rightNode不存在--->直接刪除--->此層BST就不見了

                所以return rightNode可以同時處理這樣種狀況
                1.原本的右節點會取代當層BST的根節點
                2.沒有右節點--->當層BST直接消失
            */

            //再做取代之前 先釋放動態記憶體
            delete node;
            count--;           //更新節點數量
            return rightNode;  //將右邊節點當作新的BST根節點回傳
        }

        //尚未到達左邊最底部--->繼續遞迴
        node->left = removeMin(node->left);  //將修改完的節點位置傳給左節點
        return node;
    }

    //刪除以node的BST中key最大的節點
    Node *removeMax(Node *node) {
        if (node->right == NULL) {        //沒有右節點--->到達最右下層
            Node *leftNode = node->left;  //此節點的左節點
            delete node;                  //釋放當前節點
            count--;                      //更新節點數量
            return leftNode;              //將左節點取代當前節點 並返回
        }

        node->right = removeMax(node->right);
        return node;
    }

    //刪除掉以node為根的BST中特殊Key值的節點 並返回刪除後的新節點
    Node *remove(Node *node, Key key) {
        if (node == NULL) {  //如果沒有找到節點
            return NULL;     //不操作
        }

        //遞迴查找節點
        if (key < node->key) {  //小於當前節點--->對左子樹操作
            node->left = remove(node->left, key);
            return node;
        } else if (key > node->key) {  //大於當前節點--->對右子樹操作
            node->right = remove(node->right, key);
            return node;
        } else {  //key==node->key--->找到特定節點
            //開始刪除當前節點
            if (node->left == NULL) {  //如果沒有左孩子--->以當前節點的BST的孩子不為2
                Node *rightNode = node->right;
                delete node;                   //釋放當前節點
                count--;                       //更新節點數量
                return rightNode;              //以右邊節點為返回值 取代當前節點
            } else if (node->right == NULL) {  //如果沒有右孩子--->以當前節點的BST的孩子不為2
                Node *leftNode = node->left;
                delete node;      //釋放當前節點
                count--;          //更新節點數量
                return leftNode;  //以左邊節點為返回值 取代當前節點
            } else {              //以當前節點的BST有左右節點
                /*
                    Hibbard Deletion
                    1.先找到要取代當前的節點--->找 右子樹中最小值--->successor
                    2.先刪除successor節點
                    3.將delNode的左右節點資訊 附值給successor
                        因為下面的刪除最小值操作會讓successor指向的位置沒有定義--->因此新增一個Constructor用來複製節點資訊
                        以 找到的最小節點當作參數 再new出一個跟 最小節點完全相同的Node的節點
                    4.刪除原本的節點--->完成取代
                */
                Node *successor = new Node(minimum(node->right));  //找到以當前節點的右子樹中最小的節點
                count++;                                           //更新節點數量(因為多了一個節點)

                //更改successor要放到delNode位置後的左右節點
                successor->right = removeMin(node->right);  //新的successor的右節點就是 當前節點的右子樹刪除操作後的位置
                successor->left = node->left;               //左孩子不需要改變

                //取代完畢--->刪除原本的節點
                delete node;  //釋放當前節點
                count--;      //更新節點數量
                return successor;
            }

            /*
                [思考]如果當前節點 沒有左右孩子?
                其實就是進入(node->left==NULL)的if裡
                並返回NULL給上一層的節點
            */
        }
    }

public:
    //Constructor
    BST() {
        //預設沒有任何節點
        root = NULL;  //根節點為空
        count = 0;
    }
    //Destructor
    ~BST() {
        //使用後序方法來釋放動態記憶體(因為要先釋放左右節點再釋放節點自己)
        destory(root);  //從根節點開始後序釋放記憶體
    }
    //返回此BST結構有多少個節點
    int size() {
        return count;
    }
    //此結構是否為空(是否有節點)
    bool isEmpty() {
        return count == 0;
    }
    //用來插入節點(傳入節點的key-value)
    void insert(Key key, Value value) {
        /*
            [Function Overload]使用多載--->三個參數(Node*,Key,Value)有返回值(Node*)的insert函數
            對此BST結構的根節點(root)插入節點(key-value)
            返回值:返回插入節點後，新產生的節點位置
            將新的位置存回給當前BSF的根結點
        */
        this->root = insert(root, key, value);
    }
    //查詢是否包含特定的Key
    bool contain(Key key) {
        //同insert呼叫兩個參數(要查找的BST樹根位置,要查找的key)的overloading 函數
        return contain(root, key);
    }
    /*
        搜尋特定節點的Value值
        使用指標來防止 查找失敗 沒有Value要處理的狀況
    */
    Value *search(Key key) {
        //呼叫private的overloading函數
        return search(root, key);
    }

    //前序遍歷
    void preOrder() {
        //從BST的根節點開始遞迴遍歷整個BST
        preOrder(root);
    }
    //中序遍歷
    void inOrder() {
        //從BST的根節點開始遞迴遍歷整個BST
        inOrder(root);
    }
    //後序遍歷
    void postOrder() {
        //從BST的根節點開始遞迴遍歷整個BST
        postOrder(root);
    }

    //進行BFS遍歷
    void levelOrder() {
        queue<Node *> q;
        //推入根節點
        q.push(root);
        //當queue裡面還有元素
        while (!q.empty()) {
            //獲取queue中最前面的節點
            Node *node = q.front();
            //推出剛剛取得的最前面節點
            q.pop();
            //輸出當前節點
            cout << node->key << endl;
            //把當前節點的左右節點放入queue(如果有)
            if (node->left != NULL) {
                q.push(node->left);
            }
            if (node->right != NULL) {
                q.push(node->right);
            }
        }
    }

    //尋找key最小值的節點並返回節點的key
    Key minimum() {
        //透過遞迴尋找key最小的節點(從BST的root為BST開始查找)
        Node *minNode = minimum(root);
        return minNode->key;
    }

    //尋找key最大值的節點並返回節點的key
    Key maximum() {
        //透過遞迴尋找key最大的節點(從BST的root為BST開始查找)
        Node *maxNode = maximum(root);
        return maxNode->key;
    }

    //刪除key最小的節點
    void removeMin() {
        if (root != NULL) {
            //遞迴:將修改完的根節點傳回並存回root
            root = removeMin(root);
        }
    }

    //刪除key最大的節點
    void removeMax() {
        if (root != NULL) {
            //遞迴:將修改完的根節點傳回並存回root
            root = removeMax(root);
        }
    }

    //從二叉樹中刪除特定key值的節點
    void remove(Key key) {
        //遞迴操作 操作完再將新的值回傳給root
        root = remove(root, key);
    }
};

int main() {
    string fileName = "bible.txt";  //要處理的txt檔案名稱(聖經的檔名)
    vector<string> words;           //用來儲存聖經內字串的容器
    if (FileOps::readFile(fileName, words)) {
        //容器內有多少元素(字串)
        cout << "There are totally " << words.size() << " words in " << fileName << endl;
        cout << endl;

        //用來測試BST的查找速度
        time_t startTime = clock();
        //宣告空的BST結構--->用來儲存<字串,字串出現頻率>
        BST<string, int> bst;
        //開始存放vector中的字串到BST中
        for (auto w : words) {
            //查詢字串(w)出現的頻率
            int *times = bst.search(w);
            if (times == NULL) {   //如果節點<w,1>不存在於bst中
                bst.insert(w, 1);  //插入節點<w,1>到bst中
            } else {               //如果存在節點key值為w字串
                (*times) += 1;     //將此節點的value增加1
            }
        }

        //輸出字串"god"在聖經內出現的頻率
        if (bst.contain("god")) {  //如果bst中有一個節點key值為"god"字串
            //輸出此節點的value值--->要記得de-reference
            cout << "'god' : " << *(bst.search("god")) << endl;
        } else {
            cout << "No word 'god' in " << fileName << endl;
        }

        //結束計時
        time_t endTime = clock();

        //輸出結果
        cout << "BST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
        cout << endl;

        //---------------------------------------------------------------------------------------------
        // 测试顺序查找表 SST
        startTime = clock();

        // 统计圣经中所有词的词频
        // 注: 这个词频统计法相对简陋, 没有考虑很多文本处理中的特殊问题
        // 在这里只做性能测试用
        SequenceST<string, int> sst = SequenceST<string, int>();
        for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
            int *res = sst.search(*iter);
            if (res == NULL)
                sst.insert(*iter, 1);
            else
                (*res)++;
        }

        // 输出圣经中god一词出现的频率
        if (sst.contain("god"))
            cout << "'god' : " << *sst.search("god") << endl;
        else
            cout << "No word 'god' in " << fileName << endl;

        endTime = clock();

        cout << "SST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
        //---------------------------------------------------------------------------------------------
        bst.levelOrder();

    } else {
        cout << fileName << " open failed." << endl;
    }
    return 0;
}