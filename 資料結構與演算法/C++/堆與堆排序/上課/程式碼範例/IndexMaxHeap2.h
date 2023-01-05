#ifndef INDEXMAXHEAP2
#define INDEXMAXHEAP2
#include <cmath>
#include <ctime>
#include <iostream>

#include "cassert"
using namespace std;

/*
    [假設]更新了data[4]
    為了要重新維護indexes陣列，使其滿足IndexMaxHeap，
    必須先找到4這個索引值 是存放在indexes陣列中的哪個元素呢(即indexes[?]=4)
    透過reverse陣列查找

    查找rev[4]--->rev[4]的值會是9(即rev[4]=9)
    代表data[4]這個資料的索引值是存放在indexes[9]的位置(即indexes[9]=4)

    data陣列、revese陣列、indexes陣列
    關係是
    data[x]=資料
    indexes[y]=x
    rev[x]=y
    有此可推倒
    indexes[rev[x]]=x--->因為將rev[x]替換成y--->則變成indexes[y]=x
    rev[indexes[y]]=y--->因為將indexes[y]替換成x--->則會變成rev[x]=y       
*/

//模板型MaxHeap
template <class Item>
class IndexMaxHeap {
private:
    Item *data;
    int *indexes;  //用來表示 data陣列中元素的索引值的陣列
    int *reverse;  //用來紀錄data索引值在indexes中的位置(即data[x]--->indexes[?]=x)
    int count;
    int capacity;

    /*
        此時的k是indexes陣列中的索引值
        所以資料應該是data[indexes[索引值]]這樣的形式
        而交換的應該是indexes陣列中的索引值
    */
    void shiftUp(int k) {
        //當父節點<新加入的節點
        while (1 < k && data[indexes[k / 2]] < data[indexes[k]]) {  //比較data陣列裡的值--->data[indexes[索引值]]
            swap(indexes[k / 2], indexes[k]);                       //交換indexes陣列中的索引值
            //因為修改indexes--->reverse也要修改
            reverse[indexes[k / 2]] = k / 2;
            reverse[indexes[k]] = k;
            k /= 2;  //繼續往上檢查
        }
    }
    /*
        此時的k是indexes陣列中的索引值
        所以資料應該是data[indexes[索引值]]這樣的形式
        而交換的應該是indexes陣列中的索引值
    */
    void shiftDown(int k) {
        while (2 * k <= count) {
            int j = 2 * k;
            //透過data[indexes[索引值]]取的資料
            if (j + 1 <= count && data[indexes[j + 1]] > data[indexes[j]]) {
                j += 1;
            }

            if (data[indexes[k]] >= data[indexes[j]]) {
                break;
            } else {
                //交換的是indexes陣列裡的資料
                swap(indexes[k], indexes[j]);
                //同步修改reverse
                reverse[indexes[k]] = k;
                reverse[indexes[j]] = j;
                k = j;
            }
        }
    }

public:
    //Constructor
    IndexMaxHeap(int capacity) {          //傳入此MaxHeap最大容量
        data = new Item[capacity + 1];    //因為從1開始存放--->空間需求是(元素量+1)
        this->capacity = capacity;        //紀錄此MaxHeap能容納的最大數量
        count = 0;                        //初始化資料數量
        indexes = new int[capacity + 1];  //用來保存data陣列中元素的索引的陣列
        reverse = new int[capacity + 1];  //用來保存data索引值在indexes中的位置(即data[x]--->indexes[?]=x)
        //處理MaxHeap中沒有任何元素時--->reverse沒有定義
        for (int i = 0; i <= capacity; i++) {
            //將reverse 設定成無定義
            reverse[i] = 0;  //將值設成0(因為此MaxHeap是從1開始編號)
        }
    }

    //用來一次儲存全部元素的Constructor--->一次全部儲存 然後做heapify
    IndexMaxHeap(Item arr[], int n) {
        data = new Item[n + 1];    //因為從1開始儲存--->需要(n+1)個空間
        this->capacity = n;        //容量就是陣列元素個數n
        indexes = new int[n + 1];  //用來保存data陣列中元素的索引的陣列
        reverse = new int[n + 1];  //用來保存data索引值在indexes中的位置(即data[x]--->indexes[?]=x)

        //存放arr陣列中的元素到MaxHeap中
        for (int i = 0; i < n; i++) {
            data[i + 1] = arr[i];
        }
        count = n;  //擁有的元素數量也是n

        /*
            [heapify]
            從第一個非葉子節點開始建構maxHeap
            對每次選中的非葉子做shiftDown(因為當作此狀態的根結點，也就是非葉子節點不在適當的位置)
            逐個檢查到此heap的真正根節點(最上層的非葉子節點)
            當檢查完成，整個heap也就會呈現MaxHeap的特性
        */

        //開始heapify
        for (int i = count / 2; i >= 1; i--) {
            shiftDown(i);  //嘗試shiftDown--->檢查當前型態的heap是否符合MaxHeap的型態(也就是父節點>=子節點)
        }
    }

    ~MaxHeap() {
        delete[] data;
        delete[] indexes;
        delete[] reverse;
    }

    int size() {
        return count;
    }
    bool isEmpty() {
        return count == 0;
    }
    /*
        傳入item在外部陣列中的索引值與item物件
        然後而傳入的索引值i是從0開始索引的
        而內部的data陣列與indexes陣列是從0開始索引的
        所以要修正i的偏移量(i+=1)
    */
    void insert(int i, Item item) {
        assert(count + 1 <= capacity);
        assert(i + 1 >= 1 && (i + 1) <= capacity);  //在陣列範圍內

        i += 1;  //修正索引值的偏移量(參見上面的註解)
        data[i] = item;
        indexes[count + 1] = i;  //將item在data陣列中的索引值加入indexes陣列
        reverse[i] = count + 1;  //根據定義data[i]--->indexes[count+1]=i---->reverse[i]=count+1

        count++;
        shiftUp(count);
    }
    //輸出indexes中最大的索引值(即data[索引值])
    int extactMax() {
        assert(count > 0);
        int ret = indexes[1];              //輸出indexes[1]的值(代表data[ret])
        swap(indexes[1], indexes[count]);  //應該交換的是indexes陣列的值
        //因為修改indexes--->同步修改reverse
        reverse[indexes[1]] = 1;
        reverse[indexes[count]] = 0;
        count--;
        shiftDown(1);

        return ret;
    }

    bool cantain(int i) {
        //確定索引值i存在堆中的範圍
        assert(i + 1 >= 1 && i + 1 <= capacity);
        //i+1是因為外部與內部的差異(外部從0開始內部從1)
        return reverse[i + 1] != 0;  //確定reverse[i+1]有定義
    }

    //取得資料--->對於外部傳入的i是從0開始，而內部data是從1開始
    Item getItem(int i) {
        return data[i + 1];  //外部的i轉換到內部是(i+1)
    }

    //更新已存在的資料--->傳入外部資料索引值與更新的新資料物件
    void change(int i, Item newItem) {
        //此i是外部的i(從0開始的)
        assert(contain(i));  //保證此索引值的元素在堆中

        i += 1;  //修正成內部的索引值
        data[i] = newItem;

        //資料發生改變--->重新維持IndexMaxHeap的性質
        //要先找到data[i]的i在indexes中的索引值
        //直接透過reverse陣列獲取indexes中的索引值
        int j = reverse[i];
    }

    //視覺化MaxHeap
    //-------------------------------------------------
    void testPrint() {
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
#endif