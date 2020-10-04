#include<iostream>

using namespace std;

#define NAME_SIZE 32

enum MAIN_MENU {
	MM_NONE,
	MM_INSERT,
	MM_DELETE,
	MM_SEARCH,
	MM_OUTPUT,
	MM_EXIT
};

typedef struct _tagStudent {
	char strName[NAME_SIZE];
	int iNum;
	int iKor;
	int iMath;
	int iEng;
	int iTotal;
	float fAvg;


}STUDENT, *PSTUDENT;

int InputInt() {
	int iInput;
	cin >> iInput;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX;
	}
	return iInput;
}

void InputStr(char* pString, int iSize) {
	cin.clear();
	cin.ignore(1024, '\n');
	cin.getline(pString, iSize);
}


/*
��ũ�帮��Ʈ : �ڷᱸ���� �� �����̴�. �ڷᱸ���� ������ �����ϴ� ����� ���Ѵ�.
��ũ�帮��Ʈ�� ������ ����� ������Ѽ� ������ �� �ִ� ������ �����Ѵ�.
��ũ�帮��Ʈ�� �����͸� �����ϱ� ���� ����� ���� �����Ѵ�. �� ����� Ư¡�� ���� ��带 �� �� �ְԵȴ�.(���� ����� �ּҸ� �����Ѵ�)
����Ʈ�� ���������� �Ǿ��ִ�. �׷��� ������ �迭ó�� Ư�� ��ҿ� �ٷ� ������ �Ұ����ϴ�.
������ �տ������� ���ʴ�� Ÿ�� ���� �Ѵ�.
��带 ���� �߰��� ���� ��带 �����ϰ� ������ ��忡 ���Ḹ ���ָ� �Ǳ� ������ ������ ������ ����.(�޸𸮰� �Ǵ���)
ex) �л��� ������ �����ϴ� �л���Ϻθ� ������� �� �迭�� 100ĭ�� �����ϰ� �Ǹ� �� �ο��� �ʰ��ϴ� ���� ������ �����.
	������ ��ũ�帮��Ʈ�� ������ ������ �� �����Ƿ�(������ ũ�Ⱑ ���� ��) �л��� 1000���� �Ǿ ������ ������ �ʴ´�.
*/

//����Ʈ ��带 �����.
typedef struct _tagNode {
	STUDENT tStudent;
	_tagNode* pNext;
}NODE, *PNODE;

//����Ʈ����ü�� ������ش�.
typedef struct _tagList {
	PNODE pBegin;
	PNODE pEnd;
	int iSize;
}LIST, *PLIST;


void InitList(PLIST pList) {
	//�����ʹ� ���������� �ʱ�ȭ �� �ٶ� �ʱ�ȭ ���ִ°� ����.
	//�ֳ��ϸ� 0�� false 0�� ������ ��� ���� true�̱� �����̴�.
	//�ʱ�ȭ�� ���� ���� ��� ������ ���� ���ִµ� �� �����Ⱚ ���� true�̴�.
	pList->pBegin = NULL;
	pList->pEnd = NULL;
	pList->iSize = 0;
}

int OutputMenu() {
	system("cls");

	cout << "1. �л��߰�" << endl;
	cout << "2. �л�����" << endl;
	cout << "3. �л��˻�" << endl;
	cout << "4. �л����" << endl;
	cout << "5. ����" << endl;
	cout << "�޴��� �����ϼ��� : ";
	int iInput = InputInt();

	if (iInput <= MM_NONE || iInput > MM_EXIT)
		return MM_NONE;
	return iInput;
}

void Insert(PLIST pList) {
	system("cls");
	cout << "---------------------�л��Է�---------------------" << endl;

	STUDENT tStudent;

	cout << "�̸� : ";
	InputStr(tStudent.strName, NAME_SIZE);

	cout << "�й� : ";
	tStudent.iNum = InputInt();

	cout << "���� : ";
	tStudent.iKor = InputInt();

	cout << "���� : ";
	tStudent.iMath = InputInt();

	cout << "���� : ";
	tStudent.iEng = InputInt();

	tStudent.iTotal = tStudent.iKor + tStudent.iMath + tStudent.iEng;
	tStudent.fAvg = tStudent.iTotal / 3.f;

	//�����Ҵ�
	PNODE pNode = new NODE;

	pNode->pNext = NULL;
	pNode->tStudent = tStudent;

	if (pList->pBegin == NULL)
		pList->pBegin = pNode;
	else
		pList->pEnd->pNext = pNode;
	pList->pEnd = pNode;

	++pList->iSize;
}

void ClearList(PLIST pList) {
	PNODE pNode = pList->pBegin;

	while (pNode != NULL) {
		PNODE pNext = pNode->pNext;
		delete pNode;
		pNode = pNext;
	}

	pList->pBegin = NULL;
	pList->pEnd = NULL;
	pList->iSize = 0;
}

void OutputStudent(const PSTUDENT pStudent) {
	cout << "�̸� : " << pStudent->strName << "\t�й� : " << pStudent->iNum << endl;
	cout << "���� : " << pStudent->iKor << "\t���� : " << pStudent->iMath << endl;
	cout << "���� : " << pStudent->iEng << endl;
	cout << "���� : " << pStudent->iTotal << "\t��� : " << pStudent->fAvg << endl;

}

void Output(PLIST pList) {
	system("cls");
	cout << "---------------------�л����---------------------" << endl;

	PNODE pNode = pList->pBegin;

	while (pNode != NULL) {
		OutputStudent(&pNode->tStudent);
		pNode = pNode->pNext;
		cout << endl;
	}
	cout << "�� �л��� : " << pList->iSize << endl;
	system("pause");
}

void Search(PLIST pList) {
	system("cls");
	cout << "---------------------�л�Ž��---------------------" << endl;
	cout << "ã���� �л��� �Է����ּ��� : ";

	char StrName[NAME_SIZE] = {};
	InputStr(StrName, NAME_SIZE);

	PNODE pNode = pList->pBegin;


	while (pNode != NULL) {
		if (strcmp(StrName, pNode->tStudent.strName) == 0) {
			OutputStudent(&pNode->tStudent);
			system("pause");
			return;
		}
		pNode = pNode->pNext;
	}
	cout << "�Է��Ͻ� �л��� �����ϴ�." << endl;
	system("pause");
}

//�л��� �ܼ��� �����ϴ°� �Ӹ� �ƴ϶� ���� �� ����Ʈ�� �հ� �ڸ� �̾�����Ѵ�
void Delete(PLIST pList) {
	system("cls");
	cout << "---------------------�л�����---------------------" << endl;
	cout << "�����Ͻ� �л��� �Է����ּ��� : ";

	char StrName[NAME_SIZE] = {};
	InputStr(StrName, NAME_SIZE);

	PNODE pNode = pList->pBegin;
	PNODE pPrev = NULL;

	while (pNode != NULL) {
		if (strcmp(StrName, pNode->tStudent.strName) == 0) {
			//���� ����� ���� ��带 ���´�.
			PNODE pNext = pNode->pNext;

			//���� ���� ��尡 NULL�̸� ���� ù��° ��带 ����ٴ� �ǹ��̴�.
			if (pPrev == NULL) {
				delete pNode;
				pList->pBegin = pNext;

				//������嵵 ���� ������嵵 ������ �ϳ� �ۿ� ���� ����̴�.(��, ��ü����)
				if (pNext == NULL) {
					pList->pEnd = NULL;
				}
			}
			//���� ��尡 ���� ��� ���� ����� ������ ���� ����� ���� ���� �������ش�.
			else {
				delete pNode;
				pPrev->pNext = pNext;

				if (pNext == NULL)
					pList->pEnd = pPrev;
			}
			cout << StrName << "�� ����� �������ϴ�." << endl;
			--pList->iSize;
			system("pause");
			return;
		}
		//�ش� �л��� �ƴ϶�� ���� �л��� üũ
		pPrev = pNode;
		pNode = pNode->pNext;
	}
	cout << "�Է��Ͻ� �л��� �����ϴ�." << endl;
	system("pause");
}

int main() {
	bool bRun = true;

	LIST tList;

	InitList(&tList);

	while (bRun) {
		switch (OutputMenu()) {
		case MM_INSERT:
			//������
			Insert(&tList);
			break;
		case MM_DELETE:
			Delete(&tList);
			break;
		case MM_SEARCH:
			Search(&tList);
			break;
		case MM_OUTPUT:
			Output(&tList);
			break;
		case MM_EXIT:
			bRun = false;
			break;
		}
	}
	//�Ҹ���(�޸𸮸� ����)
	ClearList(&tList);
	cout << "���α׷��� �����մϴ�.";
	return 0;
}