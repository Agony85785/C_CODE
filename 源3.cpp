#include<iostream>
using namespace std;

// �ϲ�
void merge(int arr[], int tempArr[], int left, int mid, int right)
{
    // ����������һ��δ�����Ԫ��
    int l_pos = left;
    // ����Ұ�����һ��δ�����Ԫ��
    int r_pos = mid + 1;
    // ��ʱ����Ԫ�ص��±�
    int pos = left;

    // �ϲ�
    while (l_pos <= mid && r_pos <= right)
    {
        if (arr[l_pos] < arr[r_pos])  // �������һ��ʣ��Ԫ�ظ�С
            tempArr[pos++] = arr[l_pos++];
        else  // �Ұ�����һ��ʣ��Ԫ�ظ�С
            tempArr[pos++] = arr[r_pos++];
    }

    // �ϲ������ʣ���Ԫ��
    while (l_pos <= mid)
        tempArr[pos++] = arr[l_pos++];

    // �ϲ��Ұ���ʣ���Ԫ��
    while (r_pos <= right)
        tempArr[pos++] = arr[r_pos++];

    // ����ʱ�����кϲ����Ԫ�ظ��ƻ�ԭ��������
    while (left <= right)
    {
        arr[left] = tempArr[left];
        left++;
    }
}

// �鲢����
void msort(int arr[], int tempArr[], int left, int right)
{
    // ���ֻ��һ��Ԫ�أ���ô����Ҫ��������
    // ֻ��һ��Ԫ�ص����򣬱�����������ģ�ֻ��Ҫ���鲢����
    if (left < right)
    {
        // ���м��
        int mid = (left + right) / 2;
        // �ݹ黮�������
        msort(arr, tempArr, left, mid);
        // �ݹ黮���Ұ���
        msort(arr, tempArr, mid + 1, right);
        // �ϲ��Ѿ�����Ĳ���
        merge(arr, tempArr, left, mid, right);
    }
}
int* tempArr;  // �����������溯�����棬��ָ��ᱻ�ͷţ��ٷ��ʸ�����ʱ����
// �鲢�������
void merge_sort(int arr[], int n)
{
    // ����һ����������
    tempArr = new int[n];
    // ����ʵ�ʵĹ鲢����
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