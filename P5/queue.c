#include "queue.h"


void queue_empty(queue_t *const q){
	(*q).head = 0;
	(*q).tail = 0;
}


bool queue_is_empty(const queue_t *const q){
	if((*q).head ==(*q).tail){
		return true;
	}
	else{
		return false;
	}
	
}

bool queue_is_full(const queue_t *const q){
	if((*q).tail == MAXLEN -1){
		if(((*q).head) == 0)
			return true;
		else
			return false;
	}
	else{ 
		if ((*q).head == ((*q).tail +1))
			return true;
		else
			return false;
	}
}

void queue_enqueue(queue_t *const q, uint8_t v){
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		if(queue_is_full(q) == false){
			(*q).queue[(*q).tail] = v;
			if ((*q).tail == MAXLEN - 1){
				(*q).tail =0; 
			}
			else{
				(*q).tail +=1; 
			}
		}
	}

}

void queue_dequeue(queue_t *const q){
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		if(queue_is_empty(q) == false){
			if((*q).head == MAXLEN -1){
				(*q).head =0;
			}
			else{
				(*q).head +=1;
			}
		}
	}	
}

uint8_t queue_front(const queue_t *const q){
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		return (*q).queue[(*q).head];
	}
}

