#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "3190077-3190280-pizza.h"



//Methodos pou ekteleitai apo kathe paraggelia

void* paraggelia(void* k)
{
    struct timespec stigmiAfixis, stigmiEpikoinwnias, stigmiSyskeuasias, stigmiParadoshs;

    int kwdikos, afixi, plithos_pitswn;
    int lepta_kartas, lepta_syskeuasmou;
    int lepta_nteliveri;


    kwdikos = *((int*)k);          // metatropi tou deikti se int prin tin anathesi 


    afixi = rand_r(&arxikos_sporos) % (Torderhigh - Torderlow + 1) + Torderlow;  //epilogi tyxaiou xronou afixis

    pthread_mutex_lock(&mutexGenikouXronou);                  //Kleidwnei 
    genikos_xronos = genikos_xronos + afixi;                     //auxanei to geniko xrono 
    pthread_mutex_unlock(&mutexGenikouXronou);                // Xekleidwnei 

    if (kwdikos != 1) {                  // Oles oi paraggelies ektos apo tin prwti argoun na ftasoun 
        sleep(genikos_xronos);     // koimatai gia "genikos xronos" deuterolepta oste na min ftanoun oles mazi 
    }


    clock_gettime(CLOCK_REALTIME, &stigmiAfixis);                // Prwth metrisi tou xronou, apo tin wra pou emfanistike h paraggelia 


    // Anazitisi gia thlefwniti 
    pthread_mutex_lock(&mutexThlefwnitwn);                    // kleidwnei 
    while (tilefwnites == 0)                                    // oso den yparxei tilefwnitis, tote perimenei 
    {
        pthread_cond_wait(&conditionalVarThlefwnitwn, &mutexThlefwnitwn);
    }

    tilefwnites--;
    pthread_mutex_unlock(&mutexThlefwnitwn);                 // xekleidwnei 


    plithos_pitswn = rand_r(&arxikos_sporos) % (Norderhigh - Norderlow + 1) + Norderlow;              // Tyxaia plithos apo pitses 
    lepta_kartas = rand_r(&arxikos_sporos) % (Tpaymenthigh - Tpaymentlow + 1) + Tpaymentlow;        // Tyxaios xronos gia na xrewthei h karta toy pelath 

    sleep(lepta_kartas);                                     // koimatai gia tosa deuterolepta 

    if ((rand_r(&arxikos_sporos) % 100 + 1) <= Pfail) {          // pithanotita apotyximenhs xrewsis 


        pthread_mutex_lock(&mutexThlefwnitwn);                // kleidwnei 
        tilefwnites++;                                          // auxanei tous tilefwnites 
        pthread_cond_broadcast(&conditionalVarThlefwnitwn);    // enimerwnei ta ypoloipa nhmata 
        pthread_mutex_unlock(&mutexThlefwnitwn);               // xekleidwnei 


        pthread_mutex_lock(&mutexOthonis);                     // kleidwnei 
        mi_oloklhrwmenes_paraggelies++;                         // auxanei tis mi-oloklirwnemes paraggelies 
        printf("Paraggelia me arithmo (%d) apetixe\n", kwdikos);
        pthread_mutex_unlock(&mutexOthonis);                   // xekleidwnei 

        pthread_exit(NULL);                                      // telos mi-oloklirwmenis paraggelias 
    }

    pthread_mutex_lock(&mutexOthonis);
    oloklhrwmenes_paraggelies++;                               // auxanei tis oloklirwnemes paraggelies 
    printf("Paraggelia me arithmo (%d) kataxorithike\n", kwdikos);
    pthread_mutex_unlock(&mutexOthonis);

    clock_gettime(CLOCK_REALTIME, &stigmiEpikoinwnias);    // metrisi xronou thn wra poy stamataei h epikoinwnia me ton thlefwnith
    wraAnamonis += (stigmiEpikoinwnias.tv_sec - stigmiAfixis.tv_sec);// athroizei thn diafora gia na brei ton meso oro sto telos

    if ((stigmiEpikoinwnias.tv_sec - stigmiAfixis.tv_sec) > MegistiWraAnamonis) { //Krataei thn megisti timi gia tin megisti anamoni
        MegistiWraAnamonis = (stigmiEpikoinwnias.tv_sec - stigmiAfixis.tv_sec);
    }



    pthread_mutex_lock(&mutexEsodwn);                                             // kleidwnei 
    synolo_esodwn = synolo_esodwn + (plithos_pitswn * Cpizza);                        // auxanei ta esoda me vasi to poses pitzes pariggeile 
    pthread_mutex_unlock(&mutexEsodwn);                                          // xekleidwnei 


    pthread_mutex_lock(&mutexThlefwnitwn);                // kleidwnei 
    tilefwnites++;                                          // auxanei tous tilefwnites, oloklirwse tin douleia tou 
    pthread_cond_broadcast(&conditionalVarThlefwnitwn);    //enimerwnei ta ypoloipa nhmata 
    pthread_mutex_unlock(&mutexThlefwnitwn);               // xekleidwnei 


    // Anazitisi gia phsisti 
    pthread_mutex_lock(&mutexPsistwn);                   // kleidwnei 
    while (psistes == 0)                                   // oso den yparxei tilefwnitis, tote perimenei 
    {
        pthread_cond_wait(&conditionalVarPsistwn, &mutexPsistwn);
    }
    psistes--;
    pthread_mutex_unlock(&mutexPsistwn);                 // xekleidwnei 


    sleep(Tprep * plithos_pitswn);                         // xronos anamonis mexri na etoimasei kathe pitsa o phsistis 


    // Anazitisi gia fourno 
    pthread_mutex_lock(&mutexFournwn);                   // kleidwnei 
    while (fournoi < plithos_pitswn)                                   // oso den yparxoun fournooi osoi kai oi pitses, tote perimenei 
    {
        pthread_cond_wait(&conditionalVarFournwn, &mutexFournwn);
    }
    fournoi = fournoi - plithos_pitswn;
    pthread_mutex_unlock(&mutexFournwn);                 // xekleidwnei 


    pthread_mutex_lock(&mutexPsistwn);               // kleidwnei 
    psistes++;                                         // auxanei tous phsites, oloklirwse tin douleia tou 
    pthread_cond_broadcast(&conditionalVarPsistwn);   // enimerwnei ta ypoloipa nhmata 
    pthread_mutex_unlock(&mutexPsistwn);              // xekleidwnei 


    sleep(Tbake);                                     // H paraggelia perimenei mexri na oloklirothei to psisimo 


    // Anazitisi gia ton ypallilo paketarismatos 
    pthread_mutex_lock(&mutexYpallilouPaketarismatos);                   // kleidwnei 
    while (ypallilouPaketarismatos == 0)                                   // oso exei douleia o ypallilos paketarismatos, tote perimenei 
    {
        pthread_cond_wait(&conditionalVarYpallilouPaketarismatos, &mutexYpallilouPaketarismatos);
    }
    ypallilouPaketarismatos = 1;
    pthread_mutex_unlock(&mutexYpallilouPaketarismatos);                 // xekleidwnei 

    sleep(Tpack);

    pthread_mutex_lock(&mutexFournwn);               // kleidwnei 
    fournoi = fournoi + plithos_pitswn;                 // auxanei tous fournouns, oloklirwse tin douleia tou o phsistis 
    pthread_cond_broadcast(&conditionalVarFournwn);   // enimerwnei ta ypoloipa nhmata 
    pthread_mutex_unlock(&mutexFournwn);              // xekleidwnei 


    clock_gettime(CLOCK_REALTIME, &stigmiSyskeuasias);                          // Metrisi tou xronou, tin wra pou syskeuastike h paraggelia 
    lepta_syskeuasmou = stigmiSyskeuasias.tv_sec - stigmiAfixis.tv_sec;        // afairoume tous xronous wste na ypologistoun ta deuterolepta pou perasan 


    pthread_mutex_lock(&mutexYpallilouPaketarismatos);               // kleidwnei 
    ypallilouPaketarismatos = 1;                                        // o ypallilos pou paketarei einai pali diathesimos 
    pthread_cond_broadcast(&conditionalVarYpallilouPaketarismatos);   // enimerwnei ta ypoloipa nhmata 
    pthread_mutex_unlock(&mutexYpallilouPaketarismatos);              // xekleidwnei 


    pthread_mutex_lock(&mutexOthonis);
    printf("Paraggelia me arithmo (%d) etimastike se %d lepta\n", kwdikos, lepta_syskeuasmou);
    pthread_mutex_unlock(&mutexOthonis);


    // Anazitisi gia ton ypallilo delivery 
    pthread_mutex_lock(&mutexNteliveradwn);                    //kleidwnei 
    while (ypallilouPaketarismatos == 0)                                   // oso exei douleia o ypallilos paketarismatos, tote perimenei 
    {
        pthread_cond_wait(&conditionalVarNteliveradwn, &mutexNteliveradwn);
    }
    nteliverades--;
    pthread_mutex_unlock(&mutexNteliveradwn);                 // xekleidwnei 


    lepta_nteliveri = rand_r(&arxikos_sporos) % (Tdelhigh - Tdellow + 1) + Tdellow;        // Tyxaios xronos gia na paradosei tin paraggelia sto spiti 

    sleep(lepta_nteliveri);               // koimatai to nhma mexri na paradothei 


    clock_gettime(CLOCK_REALTIME, &stigmiParadoshs);                           // Metrisi tou xronou, tin wra pou paradothhke h paraggelia 

    sleep(lepta_nteliveri);               // koimatai to nhma mexri na erthei pisw o nteliberas 

    lepta_nteliveri = stigmiParadoshs.tv_sec - stigmiAfixis.tv_sec;             // afairoume tous xronous wste na ypologistoun ta deuterolepta pou perasan     

    wraEksipiretisis += lepta_nteliveri; // athroizei tous xronous eksipiretisis ths kathe paraggelias gia na brei ton meso xrono meta.

    if (MegistiWraEksipiretisis < lepta_nteliveri) { //krataei thn megisti wra eksipiretisis
        MegistiWraEksipiretisis = lepta_nteliveri;
    }

    wraKrywmatos += (lepta_nteliveri - lepta_syskeuasmou); //athroizei tous xronous krywmatos kathe paraggelias gia na brei ton meso xrono meta

    if (MegistiWraKrywmatos < (lepta_nteliveri - lepta_syskeuasmou)) {
        MegistiWraKrywmatos = lepta_nteliveri - lepta_syskeuasmou;
    }

    pthread_mutex_lock(&mutexOthonis);
    printf("Paraggelia me arithmo (%d) paradothike se %d lepta\n", kwdikos, lepta_nteliveri);
    pthread_mutex_unlock(&mutexOthonis);


    pthread_mutex_lock(&mutexNteliveradwn);                // kleidwnei 
    nteliverades++;                                          // o ypallilos pou paradhdei einai pali diathesimos 
    pthread_cond_broadcast(&conditionalVarNteliveradwn);   // enimerwnei ta ypoloipa nhmata 
    pthread_mutex_unlock(&mutexNteliveradwn);               // xekleidwnei 



    pthread_exit(NULL);                                 // termatismos 
}

//  Kyria methodos tou programmatos

int main(int argc, char** argv) {

    int i;

    int Ncust;

    int* id_paraggeliwn;                // pinakas pou diatirei tous arithmous twn paraggeliewn 
    pthread_t* paraggelies;             // pinakas pou diatirei ta nimata (poy einai oi paarggelies) 



    // elegxo an ta orismata pou edose einai oi pelates kai o arxikos sporos 
    if (argc == 3) {

        //metatropi ta orismata se metavlites
        Ncust = atoi(argv[1]);
        arxikos_sporos = atoi(argv[2]);
        srand(arxikos_sporos);            // arxika i timi ths gennitrias tyxaiwn arithmwn 
    }
    else {

        printf("Ta orismata den einai swsta.\n");
        printf("pizzaria <arithmos pelatwn> <arxikos sporos>\n");
        return 0;       //exodos
    }


    // pianei xwro gia tous dyo pinakes sto megethos Ncust 
    id_paraggeliwn = (int*)malloc(Ncust * sizeof(int));
    paraggelies = (pthread_t*)malloc(Ncust * sizeof(pthread_t));


    // dinei tis prwtes times sta mutex 
    pthread_mutex_init(&mutexEsodwn, NULL);
    pthread_mutex_init(&mutexGenikouXronou, NULL);
    pthread_mutex_init(&mutexOthonis, NULL);
    pthread_mutex_init(&mutexThlefwnitwn, NULL);
    pthread_mutex_init(&mutexPsistwn, NULL);
    pthread_mutex_init(&mutexFournwn, NULL);
    pthread_mutex_init(&mutexNteliveradwn, NULL);
    pthread_mutex_init(&mutexYpallilouPaketarismatos, NULL);


    // dinei tis prwtes times  
    wraKrywmatos = 0;
    MegistiWraKrywmatos = 0;
    wraEksipiretisis = 0;
    MegistiWraEksipiretisis = 0;
    wraAnamonis = 0;
    MegistiWraAnamonis = 0;
    oloklhrwmenes_paraggelies = 0;
    mi_oloklhrwmenes_paraggelies = 0;
    synolo_esodwn = 0;
    tilefwnites = Ntel;
    psistes = Ncook;
    fournoi = Noven;
    nteliverades = Ndeliverer;
    ypallilouPaketarismatos = 1;


    // vazei tous kodikous tous kwdikous twn paraggeliwn 
    for (i = 1; i <= Ncust; i++) {
        id_paraggeliwn[i - 1] = i;
    }

    // xekinaei tis paraggelies 
    for (i = 0; i < Ncust; i++)
    {
        pthread_create(&paraggelies[i], NULL, paraggelia, &id_paraggeliwn[i]);
    }


    // perimenei tis paraggelies na oloklirwthoun 
    for (i = 0; i < Ncust; i++)
    {
        pthread_join(paraggelies[i], NULL);
    }


    // katastrefei ta mutex 
    pthread_mutex_destroy(&mutexEsodwn);
    pthread_mutex_destroy(&mutexGenikouXronou);
    pthread_mutex_destroy(&mutexOthonis);
    pthread_mutex_destroy(&mutexThlefwnitwn);
    pthread_mutex_destroy(&mutexPsistwn);
    pthread_mutex_destroy(&mutexFournwn);
    pthread_mutex_destroy(&mutexNteliveradwn);
    pthread_mutex_destroy(&mutexYpallilouPaketarismatos);

    // eleutherwnei tous pinakes apo tin malloc 
    free(paraggelies);
    free(id_paraggeliwn);

    pthread_cond_destroy(&conditionalVarThlefwnitwn);
    pthread_cond_destroy(&conditionalVarPsistwn);
    pthread_cond_destroy(&conditionalVarFournwn);
    pthread_cond_destroy(&conditionalVarNteliveradwn);
    pthread_cond_destroy(&conditionalVarYpallilouPaketarismatos);

    // emfanisi twn apotelesmatwn 
    printf("Oloklhrwmenes paraggelies (%d) kai mh-oloklhrwmenes (%d)\n", oloklhrwmenes_paraggelies, mi_oloklhrwmenes_paraggelies);
    printf("To synolo esodwn tis pizzarias einai %d euro\n", synolo_esodwn);
    printf("O Mesos xronos anamonhs pelatwn einai %.2f lepta\n", wraAnamonis / (float)Ncust);
    printf("Megistos xronos anamonhs pelatwn einai %d lepta\n", MegistiWraAnamonis);
    printf("O Mesos xronos ekspipiretisis pelatwn einai %.2f lepta \n", wraEksipiretisis / (float)Ncust);
    printf("O megistos xronos eksipiretisis pelatwn einai %d lepta \n", MegistiWraEksipiretisis);
    printf("O Mesos xronos krywmatos paraggeliwn einai %.2f lepta \n", wraKrywmatos / (float)Ncust);
    printf("O megistos xronos krywmatos paraggelias einai %d lepta \n", MegistiWraKrywmatos);


    return 0;
}
