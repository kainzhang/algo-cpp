//
// Created by LOKKA on 2020/4/22.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Task {
    int id;
    int arrivetime;  // ����ʱ��
    int servicetime; // ����ʱ��
    int finishtime;  // ���ʱ��
    int priority;    // ���ȼ�
    char state;      // ״̬�� W�ȴ� R���� F���
    Task(){}
    Task(int id, int at, int ct, int pr) :
            id(id), arrivetime(at), servicetime(ct),
            priority(pr), state('W') {}  //��ʼ��Ϊ�ȴ�״̬������ʱ��Ϊ 0
};

bool operator < (const Task &a, const Task &b) {
    return  a.priority < b.priority;        //�������У����ȼ��ߵ���ǰ
}

bool cmp(const Task &a, const Task &b) {
    return a.arrivetime < b.arrivetime;     //���н��̰�����ʱ������
}

void updateTask(vector<Task> &tasks, Task &t) { // ������ҵ״̬
    int len = tasks.size();
    for (int i = 0; i < len; i++) {
        if (tasks[i].id == t.id) {
            tasks[i] = t;
            break;
        }
    }
}

void printState(Task &task, int time) {  // ��ӡ��ҵ������
    printf("ʱ��Ƭ%3d", time);
    printf(" ��ҵID:%3d  ״̬: %c  ���ȼ�:%3d  ����ʱ��:%3d\n",
           task.id, task.state, task.priority, task.servicetime);
}

void priorityScheduling(vector<Task> &tasks, int n) {
    priority_queue<Task> readyque;      //��������
    int len = tasks.size(), pcs = 0, now = 0;  // pcs��¼��ǰ�����ڼ�����ҵ
    for (int i = 0; ; i++) {   // ʱ��Ƭ
        if (readyque.empty() && pcs == len) break;
        for (int j = pcs; j < len; j++) {
            if (tasks[j].arrivetime == i) { // ��ҵ�ڵ�ǰʱ�䵽��
                readyque.push(tasks[j]);   // �����������
                pcs++;
            } else break;
        }
        if (!readyque.empty()) { // ��������������ҵ
            Task tmp = readyque.top();  //����������������ȼ���ߵ���ҵ
            readyque.pop();
            tmp.state = 'R';     // �޸ĵ�ǰ������ҵΪ����״̬
            printState(tmp, i);
            tmp.servicetime--;  // �޸ĵ�ǰ��ҵ����ʱ��
            if (tmp.servicetime == 0) {        // ��ҵ�������
                tmp.finishtime = i + 1;       // ��¼��ɵ�ʱ��
                tmp.state = 'F';             // �޸�״̬Ϊ���
                updateTask(tasks, tmp);     // ������ҵ��Ϣ
                continue;
            } else {
                tmp.priority -= n;
                tmp.state = 'W';
                readyque.push(tmp);
                updateTask(tasks, tmp);

            }
        }
    }
}

int main() {
    int cnt = 0, at, ct, pr, n;
    vector<Task> tasks;
    while(~scanf("%d %d %d", &at, &ct, &pr)) {
        Task t = {cnt++, at, ct, pr};
        tasks.push_back(t);
        if (cnt == 5) break;
    }

    sort(tasks.begin(), tasks.end(), cmp);

    printf("������ÿ����һ��ʱ�䵥λ����Ȩ�仯ֵn��\n");
    scanf("%d", &n);
    priorityScheduling(tasks, n);

    printf("  ID  ����ʱ��  ���ʱ��  ��תʱ��\n");
    for (int i = 0; i < tasks.size(); i++) {
        printf("%4d   %5d    %5d   %5d\n",
               tasks[i].id, tasks[i].arrivetime, tasks[i].finishtime, tasks[i].finishtime - tasks[i].arrivetime);
    }
}