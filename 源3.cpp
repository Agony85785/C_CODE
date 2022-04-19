#include<iostream>
using namespace std;

// 合并
void merge(int arr[], int tempArr[], int left, int mid, int right)
{
    // 标记左半区第一个未排序的元素
    int l_pos = left;
    // 标记右半区第一个未排序的元素
    int r_pos = mid + 1;
    // 临时数组元素的下标
    int pos = left;

    // 合并
    while (l_pos <= mid && r_pos <= right)
    {
        if (arr[l_pos] < arr[r_pos])  // 左半区第一个剩余元素更小
            tempArr[pos++] = arr[l_pos++];
        else  // 右半区第一个剩余元素更小
            tempArr[pos++] = arr[r_pos++];
    }

    // 合并左半区剩余的元素
    while (l_pos <= mid)
        tempArr[pos++] = arr[l_pos++];

    // 合并右半区剩余的元素
    while (r_pos <= right)
        tempArr[pos++] = arr[r_pos++];

    // 把临时数组中合并后的元素复制回原来的数组
    while (left <= right)
    {
        arr[left] = tempArr[left];
        left++;
    }
}

// 归并排序
void msort(int arr[], int tempArr[], int left, int right)
{
    // 如果只有一个元素，那么不需要继续划分
    // 只有一个元素的区域，本生就是有序的，只需要被归并即可
    if (left < right)
    {
        // 找中间点
        int mid = (left + right) / 2;
        // 递归划分左半区
        msort(arr, tempArr, left, mid);
        // 递归划分右半区
        msort(arr, tempArr, mid + 1, right);
        // 合并已经排序的部分
        merge(arr, tempArr, left, mid, right);
    }
}
int* tempArr;  // 若声明到下面函数里面，该指针会被释放，再访问该数组时报错
// 归并排序入口
void merge_sort(int arr[], int n)
{
    // 分配一个辅助数组
    tempArr = new int[n];
    // 调用实际的归并排序
    msort(arr, tempArr, 0, n - 1);
}

int main(int argc, char const* argv[])
{
    int arr[50];
    for (int i = 50, j = 0; i > 0 && j < 50; i--, j++)
        arr[j] = i;
    merge_sort(arr, 50);
    for (int i = 0; i < 50; i++)
        cout << tempArr[i] << " ";
    cout << endl;
    return 0;
}