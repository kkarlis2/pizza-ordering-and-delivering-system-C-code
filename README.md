In the project we have implemented a pizza ordering and distribution system with
using the POSIX threads (pthreads) package. Orders are placed in this system
by phone, are paid by card, each order is prepared, packed and finally
distributed to the customer. In these systems we have a large number of orders which
served by a limited number of service points, therefore your schedule
must implement mutual exclusion (with mutexes) and synchronization (with condition variables).
