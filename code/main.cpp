#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// 定义参赛队伍的数据结构
struct Team {
    int teamNumber;   //队伍编号
    string projectName;   //项目名称
    string school;   //学校
    string eventCategory;   //赛事类别
    string participant;  //参赛者
    string teacher;  //指导老师
    int preliminaryScore;  // 初赛成绩
};

// 定义二叉排序树的节点结构
struct TreeNode {
    Team team;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const Team& t) {   //& t表示引用不是拷贝
        team = t;       // 初始化节点的 team 成员
        left = nullptr;  // 初始化左子树指针为空指针
        right = nullptr; // 初始化右子树指针为空指针
    }

};





// 插入节点到二叉排序树
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

// 根据参赛队编号查找节点
TreeNode* search(TreeNode* root, int teamNumber, int& asl, int depth = 1) {
    if (root == nullptr) {
        asl += depth;  // 统计平均查找长度
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

// 读取team.txt文件，构建二叉排序树
TreeNode* buildBSTFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "打开文件错误: " << filename << endl;
        return nullptr;
    }

    TreeNode* root = nullptr;
    string line;
	string temp;
    while (getline(file, line)) {
        istringstream iss(line);
        Team team;

        iss >> team.teamNumber;
        //cout<< team.teamNumber<<endl;
        getline(iss, temp, '#');    
        getline(iss, team.projectName, '#');
        //cout<< team.projectName<<endl;
        getline(iss, team.school, '#');
        getline(iss, team.eventCategory, '#');
        getline(iss, team.participant, '#');
        getline(iss, team.teacher, '#');

        // 分配初赛成绩
        team.preliminaryScore = rand() % 41 + 60;  // 60~100之间的随机数

        root = insert(root, team);
    }

    file.close();
    return root;
}

// 输出参赛队伍信息
void printTeamInfo(const Team& team) {
	cout << "参赛队伍信息：" <<endl;
    cout << "参赛队编号: " << team.teamNumber << endl;
    cout << "参赛作品名称: " << team.projectName << endl;
    cout << "参赛学校: " << team.school << endl;
    cout << "赛事类别: " << team.eventCategory << endl;
    cout << "参赛者: " << team.participant << endl;
    cout << "指导教师: " << team.teacher << endl;
    cout << "初赛成绩: " << team.preliminaryScore << endl;
    cout << "-----------------------------" << endl;
}

//查询参赛队伍成绩
void queryPreliminaryScore(TreeNode* root)
{
    int teamNumber;
    cout << "请输入参赛队编号进行查询：";
    cin >> teamNumber;

    int asl = 0;  // 平均查找长度
    TreeNode* result = search(root, teamNumber, asl);

    if (result != nullptr) {
        cout << "查找成功！" << endl;
        printTeamInfo(result->team);
    }
    else {
        cout << "未找到对应参赛队伍。" << endl;
    }

    // 计算平均查找长度
    int totalNodes = 4;  // 假设有4个参赛队
    double averageASL = static_cast<double>(asl) / totalNodes;
    cout << "平均查找长度 (ASL): " << averageASL << endl;
}

//二叉排序树的遍历
TreeNode* Traverse(TreeNode* root)
{
	if(root == nullptr)return nullptr;
	//printTeamInfo(root->team);
	if(root->left!=nullptr)
	{
		printTeamInfo(root->left->team);
		Traverse(root->left);
	}
	if(root->right!=nullptr)
	{
		printTeamInfo(root->right->team);
		Traverse(root->right);
	}
 }
 //修改参赛队伍信息
void modifyTeamInfo(TreeNode* root)
{
    int teamNumber;
    cout << "请输入需要修改的参赛队伍编号：";
    cin >> teamNumber;

    int asl = 0;  // 平均查找长度
    TreeNode* result = search(root, teamNumber, asl);

    if (result != nullptr) {
        printTeamInfo(result->team);
    }
    else {
        cout << "未找到对应参赛队伍。" << endl;
    }
    while(true)
    {
    	cout<<"字段序号：   1：参赛队伍编号   2：参赛作品名称   3：参赛学校   4：赛事类别   5：参赛者   6：指导老师    7:退出修改"<<endl; 
    	cout<<"请输入需要修改的字段序号：";
    	int choice;
    	int RTnumber;
    	string RPname;
    	string Rschool;
    	string Rcategory;
    	string Rparticipant;
    	string Rteacher;
    	
		cin >> choice;
		switch(choice)
		{
			case 1:
				//修改参赛队伍编号
				cout<<"请输入修改后内容："; 
				cin>>RTnumber;
				result->team.teamNumber=RTnumber;
				cout<<"修改后的队伍信息："<<endl;
				printTeamInfo(result->team); 
				break; 
			case 2:
				//修改参赛作品名称
				cout<<"请输入修改后内容："; 
				cin>>RPname;
				result->team.projectName=RPname;
				cout<<"修改后的队伍信息："<<endl;
				printTeamInfo(result->team); 
				break;
			case 3:
				//修改参赛学校
				cout<<"请输入修改后内容："; 
				cin>>Rschool;
				result->team.school=Rschool;
				cout<<"修改后的队伍信息："<<endl;
				printTeamInfo(result->team); 
				break;
			case 4:
				//修改赛事类别
				cout<<"请输入修改后内容："; 
				cin>>Rcategory;
				result->team.eventCategory=Rcategory;	
				cout<<"修改后的队伍信息："<<endl;
				printTeamInfo(result->team); 
				break;
			case 5:
				//修改参赛者
				cout<<"请输入修改后内容："; 
				cin>>Rparticipant;
				result->team.participant=Rparticipant;
				cout<<"修改后的队伍信息："<<endl;
				printTeamInfo(result->team); 
				break;
			case 6:
				//修改指导老师
				cout<<"请输入修改后内容："; 
				cin>>Rteacher;
				result->team.teacher=Rteacher;
				cout<<"修改后的队伍信息："<<endl;
				printTeamInfo(result->team); 
				break;
			default:
				//保存修改并退出 
				return ;
				break;	 
		}

	}
}
 
//增加参赛队伍
void addTeam(TreeNode* root)
{
	Team addteam;
    cout << "请输入需要增加的队伍信息：" << std::endl;
    cout << "参赛队编号: ";
    cin >> addteam.teamNumber;
    cout << "参赛作品名称: ";
    cin >> addteam.projectName;
    cout << "参赛学校: ";
    cin >> addteam.school;
    cout << "赛事类别: ";
    cin >> addteam.eventCategory;
    cout << "参赛者: ";
    cin >> addteam.participant;
    cout << "指导教师: ";
    cin >> addteam.teacher;
    addteam.preliminaryScore=rand() % 41 + 60;  // 60~100之间的随机数
    cout<<"增加的"; 
    printTeamInfo(addteam);
    insert(root, addteam);  //插入到二叉排序树
	
	//保存文件
	return ; 
    
 } 
int main() {
    TreeNode* root = buildBSTFromFile("team.txt");

    if (root == nullptr) {
        return 1;
    }
    while (true) {
        cout << "------------赛事信息管理系统------------" << endl;
        cout << "1.修改参赛队伍信息" << endl;
        cout << "2.增加参赛队伍" << endl;
        cout << "3.浏览参赛队伍" << endl;
        cout << "4.查询参赛队伍成绩" << endl;
        cout << "5.进入决赛现场模拟" << endl;
        cout << "6.地图导航" << endl;
        cout << "<-------输入功能前数字，回车-------->" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            modifyTeamInfo(root);
            break;
        case 2:
            addTeam(root);
            break;
        case 3:
            Traverse(root);
            break;
        case 4:
            queryPreliminaryScore(root);
            break;
        case 5:
            cout << "进入决赛现场模拟..." << endl;
            break;
        case 6:
            cout << "地图导航..." << endl;
            break;
        default:
            cout << "无效的选项，请重新输入。" << endl;
        }
    }


    // 释放二叉排序树的内存

    return 0;
}