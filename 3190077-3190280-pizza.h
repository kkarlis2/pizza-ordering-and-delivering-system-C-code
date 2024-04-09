#include <pthread.h>

// Dilwseis statherwn 
#define Ntel 3
#define Ncook 2 
#define Noven 10
#define Ndeliverer 7
#define Torderlow 1
#define Torderhigh 5
#define Norderlow 1
#define Norderhigh 5
#define Tpaymentlow 1
#define Tpaymenthigh 2
#define Cpizza 10
#define Pfail 5             //  5/100 (5%)  
#define Tprep 1
#define Tbake 10 
#define Tpack 2 
#define Tdellow 5
#define Tdelhigh 15

// Arxikos sporos tis gennitrias arithmwn 
unsigned int arxikos_sporos;

// Genikos xronos gia na mhn erxontai oi paraggelies oles mazi 
unsigned int genikos_xronos;

// Metavlites gia mesous kai megistous xronous
int wraKrywmatos;
int MegistiWraKrywmatos;
int wraEksipiretisis;
int MegistiWraEksipiretisis;
int wraAnamonis;
int MegistiWraAnamonis;

// Metavlites gia to ypoloipo diathesimo
int oloklhrwmenes_paraggelies;
int mi_oloklhrwmenes_paraggelies;
int synolo_esodwn;
int tilefwnites;
int psistes;
int fournoi;
int nteliverades;
int ypallilouPaketarismatos;

// Mutex gia kathe metavliti 
pthread_mutex_t mutexEsodwn;
pthread_mutex_t mutexGenikouXronou;
pthread_mutex_t mutexOthonis;
pthread_mutex_t mutexThlefwnitwn;
pthread_mutex_t mutexPsistwn;
pthread_mutex_t mutexFournwn;
pthread_mutex_t mutexNteliveradwn;
pthread_mutex_t mutexYpallilouPaketarismatos;


// Metavliti sinthikis gia kathe metavliti kai mutex 
pthread_cond_t conditionalVarThlefwnitwn = PTHREAD_COND_INITIALIZER;
pthread_cond_t conditionalVarPsistwn = PTHREAD_COND_INITIALIZER;
pthread_cond_t conditionalVarFournwn = PTHREAD_COND_INITIALIZER;
pthread_cond_t conditionalVarNteliveradwn = PTHREAD_COND_INITIALIZER;
pthread_cond_t conditionalVarYpallilouPaketarismatos = PTHREAD_COND_INITIALIZER;
