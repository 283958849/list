#include "DLinkList.h"

DLinkList::DLinkList()
{
	head = NULL;
}

DLinkList::DLinkList(DLinkNode *node)
{
	head = node;
}

DLinkList::~DLinkList()
{
	if (NULL == head) {
		return;
	}

	DLinkNode *tmp = head;
	DLinkNode *ttmp = NULL;

	while (tmp->next != head) {
		ttmp = tmp->next;
		tmp->detach();
		tmp = ttmp;
	}

	tmp->detach(); //the last one
	head = NULL;
}

int DLinkList::insert(DLinkNode *node)
{
	if (NULL == node) {
		return OPERATION_FAILED;
	}

	if (head != NULL) {
		node->next = head;
		node->prev = head->prev;
		head->prev->next = node;
		head->prev = node;
	}
	head = node;
	return OPERATION_SUCCESS;
}

int DLinkList::append(DLinkNode *node)
{
	if (NULL == node) {
		return OPERATION_FAILED;
	}

	if (NULL == head) {
		head = node;
	} else {
		node->next = head;
		node->prev = head->prev;
		head->prev->next = node;
		head->prev = node;
	}
	return OPERATION_SUCCESS;
}

void DLinkList::getAllInt(void)
{
	if (NULL == head) {
		return;
	}

	DLinkNode *tmp = head;
	while (tmp->next != head) {
		if (DLinkNode::DT_INT == tmp->getType()) {
			printf("Got one sir: -------\n");
			tmp->print();
		}
		tmp = tmp->next;
	}

	if (DLinkNode::DT_INT == tmp->getType()) {
		printf("Got one sir: -------\n");
		tmp->print();
	}
}

void DLinkList::travel(TravelMode_E mode)
{
	if (NULL == head) {
		return;
	}

	DLinkNode *tmp = NULL;
	if (TM_A == mode) {
		tmp = head;
		while (tmp->next != head) {
			tmp->print();
			tmp = tmp->next;
		}
	} else {
		tmp = head->prev;
		while (tmp != head) {
			tmp->print();
			tmp = tmp->prev;
		}
	}

	if (tmp != NULL) {
		tmp->print(); //the last one or the first one
	}

	printf("\n");
}

