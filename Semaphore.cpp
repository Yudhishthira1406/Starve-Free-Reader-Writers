// A process Block.

struct processBlock{
    int* process_blck;
    processBlock* next;
};

struct Queue{
    processBlock *front, *rear;
  
    void* push(int* value){
        processBlock* procBlock = new processBlock();
        procBlock->process_blck = value;
        if(rear != NULL){
            rear->next = procBlock;
            rear = procBlock;
         }
        else{
           front = rear = procBlock;  
        }
   }
    
    int* pop(){
        if(front == NULL){
            cout << "Underflow Error";
            return -1;           
        }
        else{
            int* val = front->process_blck;
            front = front->next;
            if(front == NULL)rear = NULL;
            return val;
        }
    }

    
};



class Semaphore{
    public:
        int val;
        Queue* Que; 
        Semaphore(int value){
            val = value;
            Que = new Queue();
        }
};
    
void wait(Semaphore* Sem,int* pid){
  Sem->val--;
  if(Sem->val < 0){
      Sem->Que->push(pid);
      // this function will will transfer the process to the waiting queue after blocking it.
      // the process will remain in the waiting queue till it is waken up by the wakeup() system calls.
      // this is a type of non busy waiting.
      block();
  }
}
    
void signal(Semaphore* Sem){
  Sem.val++;
  if(Sem.val <= 0){
  int* PID = Sem.Que.pop();
  wakeup(PID);  //Using the System calls,this function will wakeup the process with the specific pid 
  }
};
