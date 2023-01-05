#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>

#include "cassert"
using namespace std;

/*
    從1開始建構的MaxHeap
    假設已知一個節點索引值為 i
    則此節點的父節點為 i/2
    左節點為 2*i
    右節點為 2*i+1
*/

//模板型MaxHeap
template <class Item>
class MaxHeap {
private:
    //用來儲存資料的動態記憶體
    Item *data;
    //用來紀錄當前已儲存的資料數量
    int count;
    //用來記錄MaxHeap最大能儲存的資料數量
    int capacity;

    /*
        對data[k]做shiftUp--->嘗試向上移動
        規則:
            如果節點k有父節點
            且節點k的值(data[k])>父節點的值(data[k/2])
            就交換子父節點，並繼續往上檢查
            直到抵達適當的位置
    */
    void shiftUp(int k) {
        //當父節點<新加入的節點
        while (1 < k && data[k / 2] < data[k]) {  //需考慮k是否越界--->1<k而不是1<=k的原因是 會檢查data[k/2] 因此k最小應該是2不應該是1
            swap(data[k / 2], data[k]);           //交換父子節點
            k /= 2;                               //繼續往上檢查
        }
    }
    /*
        對data[k]做shiftDown--->嘗試向下移動
        規則:
            如果節點k有子節點(只有左或左右都有)
            則先找出左右節點中較大的節點
            並檢查 當前節點k是否小於子節點
            1.如果小於
            則交換父子節點，且繼續往下檢查，直到適當的位置
            2.如果大於等於
            代表已經到達適當位置，無須再檢查

    */
    void shiftDown(int k) {
        while (2 * k <= count) {  //如果節點k有左孩子
            //比較左右節點誰大
            int j = 2 * k;  //先假設左節點較大
            //如果右節點存在，且右節點大於左節點
            if (j + 1 <= count && data[j + 1] > data[j]) {
                j += 1;  //將j設成 右節點
            }

            if (data[k] >= data[j]) {  //如果當前節點k比k的左或右節點還大
                //data[k]已經到達適當的位置--->不需要再交換
                break;
            } else {  //否則，交換兩個節點
                swap(data[k], data[j]);
                k = j;  //更新要往下shiftDown的節點索引值
            }
        }
    }

public:
    //Constructor
    MaxHeap(int capacity) {             //傳入此MaxHeap最大容量
        data = new Item[capacity + 1];  //因為從1開始存放--->空間需求是(元素量+1)
        this->capacity = capacity;      //紀錄此MaxHeap能容納的最大數量
        count = 0;                      //初始化資料數量
    }
    ~MaxHeap() {
        delete[] data;
    }

    int size() {
        return count;
    }
    bool isEmpty() {
        return count == 0;
    }

    //向MaxHeap插入元素
    void insert(Item item) {
        assert(count + 1 <= capacity);  //保證還有空間
        data[count + 1] = item;         //從最後方插入元素
        count++;                        //更新紀錄元素個素
        //將新加入的元素放到正確的位置(嘗試向上移動)
        shiftUp(count);
    }
    //取出最頂端的元素
    Item extactMax() {
        assert(count > 0);  //保證還有元素
        Item ret = data[1];
        //將最後一個元素放到最頂端的節點
        swap(data[1], data[count]);
        //更新MaxHeap的元素個數(其實就是將原本的data[1]放到data[count] 然後count--)
        count--;
        //將data[1]放到適當的位置
        shiftDown(1);

        return ret;
    }

    //視覺化MaxHeap
    //-------------------------------------------------
    void
    testPrint() {
        // 我们的testPrint只能打印100个元素以内的堆的树状信息
        if (size() >= 100) {
            cout << "This print function can only work for less than 100 int";
            return;
        }

        // 我们的testPrint只能处理整数信息
        if (typeid(Item) != typeid(int)) {
            cout << "This print function can only work for int item";
            return;
        }
        cout << "The max heap capacity is: " << capacity << endl;
        cout << "The max heap size is: " << size() << endl;
        cout << "Data in the max heap: ";
        for (int i = 1; i <= size(); i++) {
            // 我们的testPrint要求堆中的所有整数在[0, 100)的范围内
            assert(data[i] >= 0 && data[i] < 100);
            cout << data[i] << " ";
        }
        cout << endl;
        cout << endl;

        int n = size();
        int max_level = 0;
        int number_per_level = 1;
        while (n > 0) {
            max_level += 1;
            n -= number_per_level;
            number_per_level *= 2;
        }

        int max_level_number = int(pow(2, max_level - 1));
        int cur_tree_max_level_number = max_level_number;
        int index = 1;
        for (int level = 0; level < max_level; level++) {
            string line1 = string(max_level_number * 3 - 1, ' ');

            int cur_level_number = min(count - int(pow(2, level)) + 1, int(pow(2, level)));
            bool isLeft = true;
            for (int index_cur_level = 0; index_cur_level < cur_level_number; index++, index_cur_level++) {
                putNumberInLine(data[index], line1, index_cur_level, cur_tree_max_level_number * 3 - 1, isLeft);
                isLeft = !isLeft;
            }
            cout << line1 << endl;

            if (level == max_level - 1)
                break;

            string line2 = string(max_level_number * 3 - 1, ' ');
            for (int index_cur_level = 0; index_cur_level < cur_level_number; index_cur_level++)
                putBranchInLine(line2, index_cur_level, cur_tree_max_level_number * 3 - 1);
            cout << line2 << endl;

            cur_tree_max_level_number /= 2;
        }
    }

    void putNumberInLine(int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft) {
        int sub_tree_width = (cur_tree_width - 1) / 2;
        int offset = index_cur_level * (cur_tree_width + 1) + sub_tree_width;
        assert(offset + 1 < line.size());
        if (num >= 10) {
            line[offset + 0] = '0' + num / 10;
            line[offset + 1] = '0' + num % 10;
        } else {
            if (isLeft)
                line[offset + 0] = '0' + num;
            else
                line[offset + 1] = '0' + num;
        }
    }

    void putBranchInLine(string &line, int index_cur_level, int cur_tree_width) {
        int sub_tree_width = (cur_tree_width - 1) / 2;
        int sub_sub_tree_width = (sub_tree_width - 1) / 2;
        int offset_left = index_cur_level * (cur_tree_width + 1) + sub_sub_tree_width;
        assert(offset_left + 1 < line.size());
        int offset_right = index_cur_level * (cur_tree_width + 1) + sub_tree_width + 1 + sub_sub_tree_width;
        assert(offset_right < line.size());

        line[offset_left + 1] = '/';
        line[offset_right + 0] = '\\';
    }
    //-------------------------------------------------
};

int main() {
    MaxHeap<int> maxHeap(100);
    cout << maxHeap.size() << endl;

    srand(time(NULL));
    for (int i = 0; i < 15; i++) {
        //隨機插入1~100之間的數值
        maxHeap.insert(rand() % 101 + 1);
    }
    maxHeap.testPrint();

    return 0;
}