//
// Created by LOKKA on 2020/5/13.
//

#include <bits/stdc++.h>
using namespace std;
const int N = 1e2;

struct Task {
    vector<int> blk_use; // ҳ��
    bool active;        // �Ƿ����

    Task() {
        active = false; // Ĭ��δ����
    }
};

void init_memory(vector<int>& blk, int& busy_blk) {
      //1 ��ʾ�ѷ���  0 ��ʾδ����
//    cout << "������10 * 10�����ʾ�ռ����������:" << endl;
//    for (int i = 0; i < 10; i++) {
//        for (int j = 0; j < 10; j++) {
//            cin >> blk[i * 10 + j];
//        }
//    }

    for (int i = 0; i < 30; i++) { // ��ʼ����
        int tmp = rand() % N;
        if (!blk[tmp]) {
            blk[tmp] = true;
            busy_blk++;
        }
    }
}

void print_status(vector<int>& blk) {
    printf("��ǰ�ڴ����:\n");
    for (int i = 0; i < N; i++) {
        printf("%3d", blk[i]);
        if ((i + 1) % 10 == 0)
            printf("\n");
    }
}

void alloc_blk(vector<Task>& tasks, vector<int>& blk, int& busy_blk) {
    int task_idx, page_size;
    printf("��������ҵ�ź���ҵ��С:");
    cin >> task_idx >> page_size;

    if (tasks[task_idx].active) {
        printf("����ҵ�Ѵ���\n");
        return;
    } else if (page_size > N - busy_blk) {
        printf("�ڴ治�㣬����ʧ��\n");
        return;
    }

    tasks[task_idx].active = true;

    int page_cnt = 0;
    for (int i = 0; i < N, page_cnt < page_size; i++) {
        if (!blk[i]) {     // �жϿ�״̬
            blk[i] = 1;
            tasks[task_idx].blk_use.push_back(i); // �����ڴ�
            page_cnt++;
            busy_blk++;
        }
    }
}

void free_blk(vector<Task>& tasks, vector<int>& blk, int& busy_blk) {
    int task_idx;
    printf("��������ҵ��:");
    cin >> task_idx;

    if (!tasks[task_idx].active) {
        printf("����ҵ������\n");
        return;
    }

    while(!tasks[task_idx].blk_use.empty()) {
        int tmp = tasks[task_idx].blk_use.back();
        tasks[task_idx].blk_use.pop_back();
        blk[tmp] = 0;
        busy_blk--;
    }
    tasks[task_idx].active = false;
}

void print_menu() {
    printf("\n1.�ڴ�״̬ ");
    printf("2.�����ڴ� ");
    printf("3.������ҵ\n");
    printf("������ָ��(0�˳�):");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand((unsigned) time(NULL));

    int busy_blk = 0; //�ѷ����ڴ����
    vector<int> blk(N, 0);  //�ڴ��״̬ȫ����ʼ��Ϊ 0
    init_memory(blk, busy_blk);

    vector<Task> tasks(N);    // ��ҵ��

    print_menu();
    int choice;
    while(cin >> choice, choice) {
        switch (choice) {
            case 1: print_status(blk); break;
            case 2: alloc_blk(tasks, blk, busy_blk); break;
            case 3: free_blk(tasks, blk, busy_blk); break;
            default: break;
        }
        print_menu();
    }
}