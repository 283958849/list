#include "DLinkList.h"

struct StuInfo {
	char name[20];
	char sex;         //'M':male, 'F':female
	int age;
	int score;
	char source[10];  //where is he from
};

void travelInt(void *data)
{
	int tmp = *(int *)data;
	tmp--;
	printf("My own way to show int: %d\n", tmp);
}

void travelStuInfo(void *data)
{
	if (data != NULL) {
		StuInfo *tmp = (StuInfo *)data;
		printf("size = %d, name = %s, sex = %c, age = %d, score = %d, source = %s\n",
			   	(int)sizeof(*tmp), tmp->name, tmp->sex, tmp->age, tmp->score, tmp->source);
	}
}

int main(int argc, char **argv)
{
	printf("============== test start =============\n");

	int val1 = 11;
	float val2 = 2.2;
	int val3 = 33;
	char ch[] = "Hello World!";

	struct StuInfo stuInfo;
	strcpy(stuInfo.name, "lizekun");
	stuInfo.sex = 'M';
	stuInfo.age = 30;
	stuInfo.score = 50;
	strcpy(stuInfo.source, "Hubei");

	DLinkNode *node1 = new DLinkNode();
	node1->setSize(4);
	node1->setType(DLinkNode::DT_INT);
	node1->setData(&val1);
	node1->setCallback(travelInt);

	DLinkNode *node2 = new DLinkNode();
	node2->setSize(4);
	node2->setType(DLinkNode::DT_FLOAT);
	node2->setData(&val2);

	DLinkNode *node3 = new DLinkNode();
	node3->setSize(4);
	node3->setType(DLinkNode::DT_INT);
	node3->setData(&val3);

	DLinkNode *node4 = new DLinkNode();
	node4->setSize(strlen(ch));
	node4->setType(DLinkNode::DT_STRING);
	node4->setData((void *)ch);

	DLinkNode *node5 = new DLinkNode();
	node5->setSize(sizeof(stuInfo));
	node5->setType(DLinkNode::DT_STRUCT);
	node5->setData((void *)&stuInfo);
	node5->setCallback(travelStuInfo);

	DLinkList *list = new DLinkList();
	list->append(node1);
	list->append(node2);
	list->append(node5);
	list->insert(node3);
	list->insert(node4);

	list->travel();
	list->travel(DLinkList::TM_D);

	list->getAllInt();

	delete list;

	printf("============== test end =============\n");
}
