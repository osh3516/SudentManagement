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
링크드리스트 : 자료구조의 한 종류이다. 자료구조란 데이터 관리하는 방법을 말한다.
링크드리스트는 데이터 목록을 연결시켜서 접근할 수 있는 구조를 제공한다.
링크드리스트는 데이터를 저장하기 위한 노드라는 것이 존재한다. 각 노드의 특징은 다음 노드를 알 수 있게된다.(다음 노드의 주소를 저장한다)
리스트는 선형구조로 되어있다. 그렇기 때문에 배열처럼 특정 요소에 바로 접근이 불가능하다.
무조건 앞에서부터 차례대로 타고 들어가야 한다.
노드를 새로 추가할 때는 노드를 생성하고 마지막 노드에 연결만 해주면 되기 때문에 개수의 제한이 없다.(메모리가 되는한)
ex) 학생의 정보를 저장하는 학생기록부를 만들었을 때 배열로 100칸을 설정하게 되면 그 인원이 초과하는 순간 문제가 생긴다.
	하지만 링크드리스트는 무한히 증가할 수 있으므로(데이터 크기가 남는 한) 학생이 1000명이 되어도 문제가 생기지 않는다.
*/

//리스트 노드를 만든다.
typedef struct _tagNode {
	STUDENT tStudent;
	_tagNode* pNext;
}NODE, *PNODE;

//리스트구조체를 만들어준다.
typedef struct _tagList {
	PNODE pBegin;
	PNODE pEnd;
	int iSize;
}LIST, *PLIST;


void InitList(PLIST pList) {
	//포인터는 가급적으로 초기화 해 줄때 초기화 해주는게 좋다.
	//왜냐하면 0은 false 0을 제외한 모든 수는 true이기 때문이다.
	//초기화를 하지 않을 경우 쓰레기 값이 들어가있는데 이 쓰레기값 조차 true이다.
	pList->pBegin = NULL;
	pList->pEnd = NULL;
	pList->iSize = 0;
}

int OutputMenu() {
	system("cls");

	cout << "1. 학생추가" << endl;
	cout << "2. 학생삭제" << endl;
	cout << "3. 학생검색" << endl;
	cout << "4. 학생출력" << endl;
	cout << "5. 종료" << endl;
	cout << "메뉴를 선택하세요 : ";
	int iInput = InputInt();

	if (iInput <= MM_NONE || iInput > MM_EXIT)
		return MM_NONE;
	return iInput;
}

void Insert(PLIST pList) {
	system("cls");
	cout << "---------------------학생입력---------------------" << endl;

	STUDENT tStudent;

	cout << "이름 : ";
	InputStr(tStudent.strName, NAME_SIZE);

	cout << "학번 : ";
	tStudent.iNum = InputInt();

	cout << "국어 : ";
	tStudent.iKor = InputInt();

	cout << "수학 : ";
	tStudent.iMath = InputInt();

	cout << "영어 : ";
	tStudent.iEng = InputInt();

	tStudent.iTotal = tStudent.iKor + tStudent.iMath + tStudent.iEng;
	tStudent.fAvg = tStudent.iTotal / 3.f;

	//동적할당
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
	cout << "이름 : " << pStudent->strName << "\t학번 : " << pStudent->iNum << endl;
	cout << "국어 : " << pStudent->iKor << "\t수학 : " << pStudent->iMath << endl;
	cout << "영어 : " << pStudent->iEng << endl;
	cout << "총점 : " << pStudent->iTotal << "\t평균 : " << pStudent->fAvg << endl;

}

void Output(PLIST pList) {
	system("cls");
	cout << "---------------------학생출력---------------------" << endl;

	PNODE pNode = pList->pBegin;

	while (pNode != NULL) {
		OutputStudent(&pNode->tStudent);
		pNode = pNode->pNext;
		cout << endl;
	}
	cout << "총 학생수 : " << pList->iSize << endl;
	system("pause");
}

void Search(PLIST pList) {
	system("cls");
	cout << "---------------------학생탐색---------------------" << endl;
	cout << "찾으실 학생을 입력해주세요 : ";

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
	cout << "입력하신 학생이 없습니다." << endl;
	system("pause");
}

//학생을 단순히 삭제하는것 뿐만 아니라 삭제 된 리스트의 앞과 뒤를 이어줘야한다
void Delete(PLIST pList) {
	system("cls");
	cout << "---------------------학생삭제---------------------" << endl;
	cout << "삭제하실 학생을 입력해주세요 : ";

	char StrName[NAME_SIZE] = {};
	InputStr(StrName, NAME_SIZE);

	PNODE pNode = pList->pBegin;
	PNODE pPrev = NULL;

	while (pNode != NULL) {
		if (strcmp(StrName, pNode->tStudent.strName) == 0) {
			//지울 노드의 다음 노드를 얻어온다.
			PNODE pNext = pNode->pNext;

			//만약 이전 노드가 NULL이면 제일 첫번째 노드를 지운다는 의미이다.
			if (pPrev == NULL) {
				delete pNode;
				pList->pBegin = pNext;

				//이전노드도 없고 다음노드도 없으면 하나 밖에 없는 노드이다.(즉, 전체삭제)
				if (pNext == NULL) {
					pList->pEnd = NULL;
				}
			}
			//이전 노드가 있을 경우 이전 노드의 다음을 지운 노드의 다음 노드로 연결해준다.
			else {
				delete pNode;
				pPrev->pNext = pNext;

				if (pNext == NULL)
					pList->pEnd = pPrev;
			}
			cout << StrName << "의 기록을 지웠습니다." << endl;
			--pList->iSize;
			system("pause");
			return;
		}
		//해당 학생이 아니라면 다음 학생을 체크
		pPrev = pNode;
		pNode = pNode->pNext;
	}
	cout << "입력하신 학생이 없습니다." << endl;
	system("pause");
}

int main() {
	bool bRun = true;

	LIST tList;

	InitList(&tList);

	while (bRun) {
		switch (OutputMenu()) {
		case MM_INSERT:
			//생성자
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
	//소멸자(메모리릭 방지)
	ClearList(&tList);
	cout << "프로그램을 종료합니다.";
	return 0;
}