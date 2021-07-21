#ifndef QUEUES_H
#define QUEUES_H








// ---------------- DEFINITIONS ----------------

//structures
struct QUEUE{
	struct QUEUE* next;
	unsigned int size;
	void* data;
};
typedef struct QUEUE queue;








// ---------------- CREATE / LENGTH / DELETE ----------------
queue* queue_create(void* data, unsigned int size);
unsigned int queue_length(queue* q);
void queue_delete(queue** q);








// ---------------- GET / SET ----------------
queue* queue_get(queue* q, unsigned int index);
void queue_set(queue* q, unsigned int index, void* data, unsigned int size);








// ---------------- ADD / REMOVE ----------------
void queue_addBeforeFirst(queue** q, void* data, unsigned int size);              //
void queue_addAfter(queue* q, unsigned int index, void* data, unsigned int size);
#define queue_append(q,data,size) queue_addAfter(q, queue_length(q)-1, data,size)
void queue_remove(queue** q, unsigned int index);








#endif
