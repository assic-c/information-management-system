#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// ���������������ݽṹ
struct Team {
    int teamNumber;   //������
    string projectName;   //��Ŀ����
    string school;   //ѧУ
    string eventCategory;   //�������
    string participant;  //������
    string teacher;  //ָ����ʦ
    int preliminaryScore;  // �����ɼ�
};

// ��������������Ľڵ�ṹ
struct TreeNode {
    Team team;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const Team& t) {   //& t��ʾ���ò��ǿ���
        team = t;       // ��ʼ���ڵ�� team ��Ա
        left = nullptr;  // ��ʼ��������ָ��Ϊ��ָ��
        right = nullptr; // ��ʼ��������ָ��Ϊ��ָ��
    }

};

// ����ڵ㵽����������
TreeNode* insert(TreeNode* root, const Team& team) {
    if (root == nullptr) {
        return new TreeNode(team);
    }

    if (team.teamNumber < root->team.teamNumber) {
        root->left = insert(root->left, team);
    }
    else if (team.teamNumber > root->team.teamNumber) {
        root->right = insert(root->right, team);
    }

    return root;
}

// ���ݲ����ӱ�Ų��ҽڵ�
TreeNode* search(TreeNode* root, int teamNumber, int& asl, int depth = 1) {
    if (root == nullptr) {
        asl += depth;  // ͳ��ƽ�����ҳ���
        return nullptr;
    }

    if (teamNumber == root->team.teamNumber) {
        return root;
    }
    else if (teamNumber < root->team.teamNumber) {
        return search(root->left, teamNumber, asl, depth + 1);
    }
    else {
        return search(root->right, teamNumber, asl, depth + 1);
    }
}

// ��ȡteam.txt�ļ�����������������
TreeNode* buildBSTFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "���ļ�����: " << filename << endl;
        return nullptr;
    }

    TreeNode* root = nullptr;
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        Team team;

        iss >> team.teamNumber;
        getline(iss, team.projectName, '#');
        getline(iss, team.school, '#');
        getline(iss, team.eventCategory, '#');
        getline(iss, team.participant, '#');
        getline(iss, team.teacher, '#');

        // ��������ɼ�
        team.preliminaryScore = rand() % 41 + 60;  // 60~100֮��������

        root = insert(root, team);
    }

    file.close();
    return root;
}

// �������������Ϣ
void printTeamInfo(const Team& team) {
    cout << "�����ӱ��: " << team.teamNumber << endl;
    cout << "������Ʒ����: " << team.projectName << endl;
    cout << "����ѧУ: " << team.school << endl;
    cout << "�������: " << team.eventCategory << endl;
    cout << "������: " << team.participant << endl;
    cout << "ָ����ʦ: " << team.teacher << endl;
    cout << "�����ɼ�: " << team.preliminaryScore << endl;
    cout << "-----------------------------" << endl;
}

//��ѯ��������ɼ�
void queryPreliminaryScore(TreeNode* root)
{
    int teamNumber;
    cout << "����������ӱ�Ž��в�ѯ��";
    cin >> teamNumber;

    int asl = 0;  // ƽ�����ҳ���
    TreeNode* result = search(root, teamNumber, asl);

    if (result != nullptr) {
        cout << "���ҳɹ���" << endl;
        printTeamInfo(result->team);
    }
    else {
        cout << "δ�ҵ���Ӧ�������顣" << endl;
    }

    // ����ƽ�����ҳ���
    int totalNodes = 4;  // ������4��������
    double averageASL = static_cast<double>(asl) / totalNodes;
    cout << "ƽ�����ҳ��� (ASL): " << averageASL << endl;
}

int main() {
    TreeNode* root = buildBSTFromFile("team.txt");

    if (root == nullptr) {
        return 1;
    }
    while (true) {
        cout << "------------������Ϣ����ϵͳ------------" << endl;
        cout << "1.�޸Ĳ���������Ϣ" << endl;
        cout << "2.���Ӳ�������" << endl;
        cout << "3.�����������" << endl;
        cout << "4.��ѯ��������ɼ�" << endl;
        cout << "5.��������ֳ�ģ��" << endl;
        cout << "6.��ͼ����" << endl;
        cout << "<-------���빦��ǰ���֣��س�-------->" << endl;

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            //modifyTeamInfo();
            break;
        case 2:
            //addTeam();
            break;
        case 3:
            //browseTeams();
            break;
        case 4:
            queryPreliminaryScore(root);
            break;
        case 5:
            cout << "��������ֳ�ģ��..." << endl;
            break;
        case 6:
            cout << "��ͼ����..." << endl;
            break;
        default:
            cout << "��Ч��ѡ����������롣" << endl;
        }
    }


    // �ͷŶ������������ڴ�
    // �˴�ʡ���ͷ��ڴ�Ĵ��룬ʵ����Ŀ����Ҫע���ڴ����

    return 0;
}