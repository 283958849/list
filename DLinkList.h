#ifndef __DLINKLIST_H__
#define __DLINKLIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define OPERATION_FAILED  -1
#define OPERATION_SUCCESS 0 

class DLinkNode;
typedef void (*Callback_T)(void *);

class DLinkList {
	public:
		typedef enum {
			TM_A = 1,
			TM_D = 2
		} TravelMode_E;

	public:
		DLinkList();
		DLinkList(DLinkNode *node);
		~DLinkList();
		int append(DLinkNode *node);
		int insert(DLinkNode *node);
		void getAllInt(void);
		void travel(TravelMode_E mode = TM_A);

	private:
		DLinkNode *head;	
};

class DLinkNode {
	public:
		typedef enum {
			DT_INT = 1,
			DT_FLOAT = 2,
			DT_STRING = 3,
			DT_STRUCT = 4,
			DT_UNDEF = -1 
		} DataType_E;

		DLinkNode() {
			size = 0;
			data = NULL;
			prev = this;
			next = this;
		}

		DLinkNode(int size, void *data) {
			mallocMemoryForData(size);
			this->size = size;
			prev = this;
			next = this;
		}

		void setSize(int size) {
			this->size = size;
			mallocMemoryForData(size);
		}

		void setType(DataType_E type) {
			this->type = type;
		}

		void setData(void *data) {
			if (data != NULL) {
				memcpy(this->data, data, size);
			}
		}

		void setCallback(Callback_T callback) {
			this->callback = callback;
		}

		int getSize(void) {
			return size;
		}

		DataType_E getType(void) {
			return type;
		}

		void* getData(void) {
			return data;
		}

		Callback_T getCallback(void) {
			return callback;
		}

		void print(void) {
			switch (type) {
			case DT_INT:
				if (callback != NULL) {
					callback(data);
				} else {
					printInt();
				}
				break;
				
			case DT_FLOAT:
				if (callback != NULL) {
					callback(data);
				} else {
					printFloat();
				}
				break;

			case DT_STRING:
				if (callback != NULL) {
					callback(data);
				} else {
					printString();
				}
				break;

			case DT_STRUCT:
				if (callback != NULL) {
					callback(data);
				} else {
					printStruct();
				}
				break;
			}
		}

		void detach(void) {
			if (data != NULL) {
				free(data);
				data = NULL;
			}
		}

		~DLinkNode() {
			detach();
		}

		DLinkNode *prev;
		DLinkNode *next;

	private:
		void mallocMemoryForData(int size) {
			this->data = (void *)malloc(size);
			if (NULL == this->data) {
				perror("malloc failed! operation cancel");
				return;
			}
		}

		void printInt(void) {
			printf("size = %d, data = %d, &data = %p\n", size, *(int *)data, data);
		}

		void printFloat(void) {
			printf("size = %d, data = %f, &data = %p\n", size, *(float *)data, data);
		}

		void printString(void) {
			printf("size = %d, data = %s, &data = %p\n", size, (char *)data, data);
		}

		void printStruct(void) {
			printf("Need to be handled by yourself!\n");
		}

		int size;
		void *data;
		DataType_E type;
		Callback_T callback;
};


#endif //__DLINKLIST_H__
