#include <iostream>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));
    long long int n = rand() % 10 + 5;
    long long int m = rand() % 10 + 5;
    long long int q = n + m;
    long long int arr1[n];
    long long int arr2[m];
    long long int arr3[n + m];
    cout << " Array 1: \n";
    for (int i = 0; i < n; i++) {
        arr1[i] = rand() % 9 + 1;
        cout << arr1[i] << " ";
    }
    cout << "\n Array 2: \n";
    for (int i = 0; i < m; i++)
    {
        arr2[i] = rand() % 9 + 1;
        cout << arr2[i] << " ";
    }
    /* for(int i = 0; i < n + m; i++){
     if(i < n)
     arr3[i] = arr1[i];
     else arr3[i] = arr2[i-n];
     }*/

    long long* ptr_array1 = &arr1[0];
    long long* end_array1 = &arr1[q - 1];
    long long* ptr_array2 = &arr2[0];
    long long* ptr_array3 = &arr3[0];
    asm(
        "mov %[ptr_array1], %%rax\n\t"  // �������� ��������� �� ������ ������� � rax
        "mov %[ptr_array2], %%rbx\n\t"  // �������� ��������� �� ������ ������� � rbx
        "mov %[ptr_array3], %%rcx\n\t"  // �������� ��������� �� ������ ������� � rcx
        "mov (%%rax), %%rdx\n\t"        // �������� ��������� �� ������ ������� � rdx
        "cmp %%rdx, (%%rbx)\n\t"        // ������� �������� rdx � rbx

        "push (%%rbx)\n\t"              // ��������� � ���� rbx (����� ���������� ��������)
        "pop (%%rcx)\n\t"               // ����� � rcx �� ����� �������� �� ��������� ������

        "loop_start:\n\t"
        "add $8, %%rax\n\t"         // ��������� ����� � rax �� 8 (����������� �� ���� ������� ������)
        "add $8, %%rbx\n\t"         // ��������� ����� � rbx �� 8 (����������� �� ���� ������� ������)
        "add $8, %%rcx\n\t"         // ��������� ����� � rcx �� 8 (����������� �� ���� ������� ������)
        "mov (%%rax), %%rdx\n\t"    // �������� ��������� �� ������ ������� � rdx
        "cmp %%rdx, (%%rbx)\n\t"    // ������� �������� rdx � rbx


        "push (%%rbx)\n\t"          // ����� �������� ��������� ������� ����� ����
        "pop (%%rcx)\n\t"           // ����� � rcx �� ����� �������� �� ��������� ������
        "cmp %%rax, %[end_array1]\n\t" // �������� ��� ��������� ����� �������
        "je end\n\t"                // ���� ��������� - ����������, ����� �����������
        "jmp loop_start\n\t"            // ������� �� loop_start


        "end:\n\t"
        :
    : [ptr_array1] "m"(ptr_array1), [ptr_array2]"m"(ptr_array2), [ptr_array3]"m"(ptr_array3), [end_array1]"m"(end_array1)
        : "%rax", "%rbx", "%rcx"
        );

    cout << "\nArray asm: " << endl;
    for (int i = 0; i < n + m; i++) {
        cout << arr3[i] << " ";
    }

    return 0;
}