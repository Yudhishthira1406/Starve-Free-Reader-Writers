# Starve-Free-Reader-Writers

The Readers-writers problem is one of the most common problem in process synchronization. In this problem, some processes are Readers that read the shared resource and do not modify it, and also various processes, called Writers, that want to modify the same resource. There are three ways to deal with this situation.

### First readers–writers problem 
In this problem, multiple readers are allowed to access the shared resource concurrently. The readers are given preference compared to writers, i.e., each reader locks the source for themselves, and a writer will be given access once the resource becomes free. However, in this case, the writer may lead to starvation as it may not get a chance to access and modify the resource as new readers may continuously read from the resource.

### Second readers–writers problem
In this problem, the writers are given preference compared to readers. The reader must wait until the last writer unlocks the critical section by modifying it and release the lock to allow readers to access the resource.  However, in this solution, the readers may starve as consequent writers will continue to modify the resource. 

### Third readers–writers problem
This solution overcomes the shortcomings of the previous two starvation problems and, therefore, is also known as the **Starve-Free-Readers-Writers-Problem**. It will prioritize the processes, i.e., readers and writers,  in the order of their arrival. For example, if a writer wants to write to the resource, it will wait until the current readers execute their tasks. Meanwhile, other readers accessing the resource would not be allowed to do so.

### Explanation of the Code

The semaphores used in the code are:
- `rd_mutex` -->  It will be used to update the number of readers. Therefore it would only be available to readers method.
- `get_access` -->  This would be either in control of readers or the writer. If a writer tries to modify the critical section while the readers are reading, it will get blocked and vice versa. However, if one reader is reading and another reader tries to access, then there won't be any problem. This semaphore gets updated at 3 instances.
  - When 1st reader arrives.
  - When the last reader left the critical section. 
  - When any writer will write to the resource.
- `order` --> This semaphore is used at the start of the entry section of readers/writers code. This checks if there is any processes already in the waiting queue. If there is a waiting process, it gets blocked; else, it access the semaphore, and no new reader/writer could now execute before this process.  Therefore, it helps in preserving the order of processes.

An integer `rd_count` is used to update the number of readers at a particular time. 

We would first call wait for `order` and `rd_mutex` in case of a read. If any process is already in the queue, `order` would be 1, and thus, the calling process would be blocked. Otherwise, it would make `order` "1". `rd_mutex` would verify that no other process is updating the readers count. If the `rd_count` was 0, then don't allow the writer to access the critical section. After `rd_count` is updated, both the semaphores are unlocked. After reading from the resource, read count is decremented by getting hold of rd_mutex. If `rd_count` is 0, writers can now access the critical section.

We would first check the `order` semaphore for the write method, and then the writer would get access with the `get_access` semaphore. Since the order of processes will be preserved, we could unlock the `order` semaphore. Then writers modify the resource and finally unlock `get_access`.

In this way, the processes will be executed without any starvation.

## Correctness of Solution
### Mutual Exclusion
The `get_access` semaphore guarantees that only a single writer can modify the critical section at any moment, thus ensuring mutual exclusion between various writer processes. Also, when the first reader tries to access the critical section, it has to acquire the `get_access` mutex lock, thus ensuring mutual exclusion between the readers and writers.
### Bounded Waiting
Before accessing the critical section, any reader or writer must acquire the `order` semaphore, which stores the blocked processes in a FIFO queue. As the queue uses a FIFO order, every process has to wait for a finite amount of time before accessing the critical section. Thus, the requirement of bounded waiting is satisfied.
### Progress Requirement
The code is structured so that there are no chances for deadlock. The readers and writers take a finite amount of time to access or modify the critical section. At the end of each reader-writer code, they release the semaphore for other processes to enter the critical section.
