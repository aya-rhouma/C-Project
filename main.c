#include <locale.h>
#include <stdio.h>
#include <string.h>
#include"structure.h"
char loga[] = "admin";
char ma[] = "admin";
//enregister les services
void sauvegarderServices(Service s[], int n) {
    FILE *file;

    file = fopen("services.txt", "w");
    if (file == NULL) {
        printf("Erreur: impossible d'ouvrir le fichier.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\t%s\t%s\t%s\n", s[i].identifiant, s[i].nom, s[i].med, s[i].pat);
    }

    fclose(file);

    printf("\nServices sauveguardees avec succes!\n");
}
//ajouter un service
void ajouterService(Service services[], int *n) {
    Service serv;
    FILE *ser;
    ser=fopen("services.txt","a");
    printf("Entrez l'identifiant du service: ");
    scanf("%d", &serv.identifiant);
    while (getchar() != '\n');

    printf("Entrez le nom du service: ");
    gets(serv.nom);

    printf("Entrez la liste des medecins: ");
    gets(serv.med);

    printf("Entrez la liste des patients: ");
    gets(serv.pat);
    fprintf(ser, "%d\t%s\t%s\t%s\n", serv.identifiant, serv.nom, serv.med, serv.pat);

    fclose(ser);

    //Stocker le service dans le tableau
    services[*n] = serv;
    (*n)++;


    printf("\nService ajoute avec succes!\n");
}
//supprimer un service
void supprimerService(Service s[], int index_a_supprimer, int *n) {
    if (index_a_supprimer < 0 || index_a_supprimer >= *n) {
        printf("Erreur: index de service invalide.\n");
        return;
    }

    for (int i = index_a_supprimer; i < *n - 1; i++) {
        s[i] = s[i + 1];
    }

    (*n)--;

    printf("\nService supprime avec succes!\n");
}
//fonction pour verifier l'autentification
int login(char ch1[], char ch2[]){
    return strcmp(ch1, ch2) == 0 ? 0 : 1;
}
//fonction pour determiner l'indice du patient a partir de l'identifiant
int findident( Patient* p,int taille,int matricule) {
    for (int i = 0; i < taille; ++i) {
        if (p[i].matricule == matricule) {
            // Retourner l'indice du patient trouvé
            return i;
        }
    }
    // Si aucun patient n'est trouvé avec l'identifiant spécifié, retourner -1
    return -1;
}
//fonction qui cherche l'identifiant du service
int findidentserv( Service* s,int taille,int matricule) {
    for (int i = 0; i < taille; ++i) {
        if (s[i].identifiant == matricule) {
            // Retourner l'indice du patient trouvé
            return i;
        }
    }
    // Si aucun patient n'est trouvé avec l'identifiant spécifié, retourner -1
    return -1;
}
// Fonction pour vérifier le format de la date
int verifierFormatDate(char date[11]) {
    int jour, mois, annee;
    char format[4];  // Pour stocker le tiret

    // Utilisez sscanf pour extraire les parties de la date
    if (sscanf(date, "%2d%3[-]%2d%3[-]%4d", &jour, format, &mois, format, &annee) == 3) {
        // Vérifiez si les jours, mois et années sont dans les plages spécifiées
        if ((jour >= 1 && jour <= 31) && (mois >= 1 && mois <= 12)) {
            return 1;  // Le format est correct
        }
    }

    return 0;  // Le format n'est pas correct
}
// Fonction pour comparer les dates (retourne 0 si date1 <= date2, 1 sinon)
int comparerDates(char date1[11], char date2[11]) {
    return strcmp(date1, date2) <= 0 ? 0 : 1;
}
// Fonction pour afficher les 7 premiers rendez-vous supérieurs à la date d'aujourd'hui
void afficherProchainsRendezVous( Patient* patient, char dateAujourdhui[11]) {
    printf("\nProchains rendez-vous pour le patient %s supérieurs à la date du %s :\n", patient->nom, dateAujourdhui);

    // Compteur pour suivre le nombre de rendez-vous affichés
    int rendezVousAffiches = 0;

    // Boucler pour tous les rendez-vous
    for (int i = 0; i < 100 && rendezVousAffiches < 7; ++i) {
        // Si la date du rendez-vous est supérieure à la date d'aujourd'hui, l'afficher
        if (!comparerDates( dateAujourdhui,patient->lrdv[i])) {
            printf("Date : %s\n", patient->lrdv[i]);
            /*for (int j = 0; j < 6; ++j) {
                printf("  Rendez-vous %d : %s\n", j + 1, patient->lrdv[i][j]);
            }
            printf("\n");*/
            // Incrémenter le compteur des rendez-vous affichés
            rendezVousAffiches++;
        }
    }
}
// Fonction pour afficher la description des maladies d'un patient
void afficherDescriptionMaladies(Patient* p, int ind) {
    printf("\nDescription des maladies pour le patient %s :\n", p[ind].nom);
    printf("%s\n", p[ind].description);
}
// Fonction pour afficher la liste des ordonnances et des certificats pris par un patient
void afficherOrdonnancesCertificats(Patient* p, int ind) {
    Certificat cert;
    printf("\nListe des ordonnances et des certificats pour le patient %s :\n", p[ind].nom);
    for (int i = 0; i < 100 && p[ind].lmed[i][0] != '\0'; ++i) {
        printf("Ordonnance %d : %s\n", i + 1, p[ind].lmed[i]);
    }

    for (int i = 0; i < 100 && p[ind].cert[i].identifiant != 0; ++i) {
        printf("Certificat %d : %s\n", i + 1, p[ind].cert[i].cause);
    }
}
// Fonction pour avoir une idée sur tous les rendez-vous d'un patient
void afficherTousRendezVous(Patient* p, int ind) {
    printf("\nTous les rendez-vous pour le patient %s :\n", p[ind].nom);
    for (int i = 0; i < 100 && p[ind].lrdv[i][0] != '\0'; ++i) {
        printf("Rendez-vous %d : %s\n", i + 1, p[ind].lrdv[i]);
    }
}
//fonction pour verifier si un rendez_vous est valide
int verifrdv(char rendezvousp[],char ferie[][11],int n){
    for (int i=0;i<n;i++){
        if (strcmp(ferie[i],rendezvousp)!=0)
            return 1;
        else
            return 0;
    }
}

void main()
{
    setlocale(LC_ALL, "");//pour les accents
    FILE*serv;
    int entree;
    char continuer;
    char ferie[300][11]; //tableau qui contient les jours feriers
//variables de l'aministrateur
    int souhaitadmin,is,nms,js,nps,ks,i; //is:nb de serv||nms:nb de med du serv||nps:nb de pat du serv
    int indm, nmp,j, no, k, nc, l,im,ip; //nmp:nb de pat du med / no:nb d'ord du med / nc:nb cert med / im:nb med / ip:nb pat
    int  npr,  npo, npc; //npr:nb de rdv du pat / npo:nb des ord du pat / npc:nb cert pat
    int inddels,inddelm,inddelp;
    char logina[30],mdpa[15];
    int identservsupp,indservsupp;
//tableau de rendez-vous a verifier pour l'admin
    char rendezvous[20][11];
//variables du medecin
    char addm[30],mdpm[15];
    int identm,souhaitmedecin;
    int indpatmod;
    int indentred,indentpatre;
    char medicaments[1000];
    char cause[50];
    int indmac,indpac,identred;
    int indmao,indpao;
    int indp;
//variables du patient
    char add[30],mdp[15];
    int ind,ident,souhaitpatient;
    char date[11],rendezvousp[11];
    int matricule; //mat du med dans le cert demande
    char datecert[11],causecert[10];
    int identrdv;
    int indms;
//initialisation des strctures
    Patient p[40] = {
    //pat1
    {
        12345,
        "aziz ben amor",
        "01/01/2000",
        'M',
        "L'accident vasculaire cérébral: survient lorsque la circulation sanguine vers une partie du cerveau est interrompue, entraînant une privation d'oxygène. Cela peut être causé par un caillot sanguin ou une rupture d'un vaisseau sanguin.",
        "Cardiologie",
        {
            {"01-02-2023", "03-02-2023", "01-01-2020", "04-02-2023", "05-02-2023", "06-02-2023", "07-02-2023", "08-02-2023", "09-02-2023", "10-02-2023"},
        },
        {
            {1, 5679, "hamza rekik", "rkik ha", 12345, "aziz ben amor", "les somnifères, les tranquillisants, les neuroleptiques"},
        },
        {"dalel marzoug", "hamza rekik"},
        {
            {1, "02/01/2000", "Maladie", 12345, "aziz ben amor", 5678, "dalel marzoug", "dalel mar"},
            {2, "03/01/2000", "Accident", 12345, "aziz ben amor", 5679, "hamza rekik", "rkik ha"}
        },
        "aziz12345",
        "aziz"
    },
    //pat2
    {
        67890,
        "aziza fitouri",
        "12-05-1958",
        'F',
        "La maladie de Parkinson est un problème du cerveau qui affecte le mouvement. Les gens qui en sont atteints peuvent avoir des tremblements, des muscles raides, des mouvements lents et des difficultés d'équilibre.",
        "Neurologie",
        {
            {"01-04-2023", "12-05-2023", "25-09-2023", "10-01-2020", "30-10-2023", "05-12-2023", "27-02-2023", "01-02-2023"},
        },
        {
            {1, 5678, "dalel marzoug", "dalel mar", 67890, "aziza fitouri", "dopilprane,fervexe,artelac"},
        },
        {"dalel marzougi", "rabii mestiri"},
        {
            {1, "02/01/2000", "passage au concours", 67890, "aziza fitouri", 5678, "dalel marzoug", "dalel mar"},
            {2, "03/01/2000", "Accident", 67890, "aziza fitouri", 4100, "rabii mestiri", "mestiri mestiri"}
        },
        "aziza67890",
        "aziza"
    },
    // Add more patients as needed
};
    Medecin m[40] = {
        //med1
        {1, "dalel marzoug", "01/12/1978", 'F', "dalel mar", "Neurologie", "Neurochirurgienne",
        {{"aziz ben amor","aziza fitouri",}},
        {
            {1, 5678, "dalel marzoug","dalel mar", 67890, "aziza fitouri","dopilprane,fervexe,artelac"},
        },
        {"dalel1", "dalel"}},
        //med2
        {2, "hamza rekkik", "22/02/1987", 'H', "rekik ha", "cardiologie", "l'angioplastie",
        {"aziz ben amor"},
        {
            {1,5679, "hamza rkik","rkik ha", 12345, "aziz ben amor","les somnifères, les tranquillisants, les neuroleptiques"}
        },
        {
            {2, "03/01/2000", "Accident", 12345, "aziz ben amor", 5679, "hamza rkik", "rkik ha"},
        },
        "hamza2", "hamza"},
        //med3
        {3, "rabii mestiri", "29/09/1988", 'H', "mestiri mestiri", "cardiologie", "l'angioplastie",
        {"aziza fitouri"},
        {
            {1,5679, "hamza rkik","rkik ha", 12345, "aziz ben amor","les somnifères, les tranquillisants, les neuroleptiques"},
        },
        {
            {2, "03/01/2000", "Accident", 12345, "aziz ben amor", 5679, "hamza rkik", "rkik ha"},
        },
        "hamza3", "hamza"},
    };

    Service s[40] ;/*= {
        //ser1
        {12345, "Cardiologie",
            {"hamza rekik","rabii mestiri"},
            {"aziz ben amor"},
        },
        //ser2
        {6789, "neurologie",
            {"dalel marzoug",},
            {"aziza fitouri",},
        },
    };
*/
    is=2;
    im=3;
    ip=2;
    puts("\t\t\t\t-----Bienvenue dans notre hopital-----");
    puts("Bonjour monsieur l'Administrateur");
//login de l'administrateur
    do {
        printf("entree l'adresse: ");
        gets(logina);
        printf("le mot de passe: ");
        gets(mdpa);
        if (login(logina, loga) != 0 || login(mdpa, ma) != 0){
            system("cls");
            puts("\t\t\t\t-----Bienvenue dans notre hopital-----");
            puts("Bonjour monsieur l'Administrateur");
            puts("Echec,entrer de nouveau votre adesse et mot de passe");}
    } while (login(logina, loga) != 0 || login(mdpa, ma) != 0);
    system("cls");
    puts("\t\t\t\t-----Bienvenue dans notre hopital-----");
    puts("Bonjour monsieur l'Administrateur");
//remplir le tableau de jours feriers
    int nbferie;
    printf("Entrer le nombre des jours ferires: ");
    scanf("%d",&nbferie);
    for (int i=0;i<nbferie;i++){
            while (1) {
            printf("Donner le jour férié numéro %d: ",i+1);
            scanf("%11s",&ferie[i]);
            if (!( verifierFormatDate(ferie[i]) == -1))
                break;
        }
    }
    system("cls");
    puts("\t\t\t\t-----Bienvenue dans notre hopital-----");
    puts("Entrer 1 si vous êtes l'administrateur");
    puts("Entrer 2 si vous êtes un medecin");
    puts("Entrer 3 si vous êtes un patient");
    printf("Entrer 1 ou 2 ou 3: ");
    scanf("%d",&entree);
    while (getchar() != '\n');
//les instructions de l'administrateur
    if (entree==1){

            system("cls");
            puts("\t\t\t\t-----Bienvenue dans notre hopital-----");
            puts("Bonjour monsieur l'Administrateur");
//login de l'administrateur
        do {
            printf("entree l'adresse: ");
            gets(logina);
            printf("le mot de passe: ");
            gets(mdpa);
            if (login(logina, loga) != 0 || login(mdpa, ma) != 0){
                system("cls");
                puts("\t\t\t\t-----Bienvenue dans notre hopital-----");
                puts("Bonjour monsieur l'Administrateur");
                puts("Echec,entrer de nouveau votre adesse et mot de passe");}
        } while (login(logina, loga) != 0 || login(mdpa, ma) != 0);
        do{
        system("cls");
        puts("\t\t\t\t-----Bienvenue dans notre hopital-----");
        puts("Bonjour monsieur l'Administrateur");
//saisir le choix de l'administrateur
        puts("Pour mieux determiner vos choix, entrer ");
        puts("1 Si vous voulez ajouter un service ");
        puts("2 Si vous voulez supprimer un service  ");
        puts("3 Si vous voulez ajouter un medecin ");
        puts("4 Si vous voulez supprimer un medecin ");
        puts("5 Si vous voulez ajouter un patient ");
        puts("6 Si vous voulez supprimer un patient ");
        puts("7 Si vous voulez planifier les rendez-vous ");
        do {
            printf("Entrez 1 ou 2 ou 3 ou 4: ");
            scanf("%d",&souhaitadmin);
            printf("\n %d \n",souhaitadmin);
            if (souhaitadmin!=1 ||souhaitadmin!=2 ||souhaitadmin!=3 ||souhaitadmin!=4)
                puts("Coix invalide, essayez une autre fois");
        }while (!(souhaitadmin!=1 ||souhaitadmin!=2 ||souhaitadmin!=3 ||souhaitadmin!=4 ));
        system("cls"); //supprimer le contenu de la console
        puts("\t\t\t\t-------Bienvenue dans notre hopital!-------");
        puts("Bonsoir Monsieur l'adminisstrateur");
        int nbservaj;
//ajouter un service
        if (souhaitadmin==1){
            do{
                printf("\nDonner le nombre de services à ajouter: ");
                scanf("%d",&nbservaj);
                while (getchar() != '\n');
                is+=nbservaj;
                for (int i=0;i<nbservaj;i++){
                    ajouterService(s, &is);
                    system("cls");
                    puts("\t\t\t\t-----Bienvenue dans notre hopital-----");
                    puts("Bonjour monsieur l'Administrateur");
                }
            }while (continuer=='c');
            system("cls");
            puts("\t\t\t\t-----Bienvenue dans notre hopital-----");
            puts("Bonjour monsieur l'Administrateur");
        }
//supprimer un service
    else if (souhaitadmin==2){
        do{
            printf("\nDonner l'identfiant du service à supprimer: ");
            scanf("%d",&identservsupp);
            indservsupp=findidentserv(s,is,identservsupp);
            printf("\n%d\n",indservsupp);
            while (indservsupp==-1){
                system("cls");
                puts("\t\t\t\t-------Bienvenue dans notre hopital!-------");
                puts("Bonsoir Monsieur l'adminisstrateur");
                puts("L'identifiant saisi n'existe pas");
                printf("\nDonner l'identfiant du service à supprimer: ");
                scanf("%d",&identservsupp);
                indservsupp=findidentserv(s,is,identservsupp);
            }
            puts ("Voulez vous continuer ou quitter (entrer c ou q): ");
            scanf("%c",&continuer);
        }while (continuer=='c');
        system("cls");
        puts("\t\t\t\t-----Bienvenue dans notre hopital-----");
        puts("Bonjour monsieur l'Administrateur");
    }
//ajouter un medecin
       else if (souhaitadmin==3){
            do{
                puts("Pour ajouter un medecin, il suffit de siuivre ces instructions: ");
                im++;
//matricule
                printf("la mat du medecin %d: ", i + 1);
                scanf_s("%d", &m[im].matricule);
                while (getchar() != '\n');
//nom
                printf("le nom du mededecin %d: ", i + 1);
                gets(m[im].nom);
                while (getchar() != '\n');
//date de naissance
                printf("la date de naissance du medecin %d: ", i + 1);
                gets(m[im].date);
//genre
                printf("le genre du medecin %d: ", i + 1);
                scanf("%c",&m[im].genre);
//signature
                printf("la signature du medecin %d: ", i + 1);
                gets(m[im].signature);
//service
                printf("le service du medecin %d: ", i + 1);
                gets(m[im].service);
//specialite
                printf("la specialite du medecin %d: ", i + 1);
                gets(m[im].specialite);
                printf("sepecialite : %s \n", m[im].specialite);
//liste des patients
                printf("le nb des pat du medecin %d: ", i + 1);
                scanf_s("%d", &nmp);
                while (getchar() != '\n');
                for (j = 0; j < nmp; j++)
                {
                    printf("patient %d: ", j + 1);
                    gets(m[im].lpat[j]);
                }
//liste des ordonnances
                printf("le nombre des ordonnances du medecin %d: ", i + 1);
                scanf_s("%d", &no);
                while (getchar() != '\n');
                for (k = 0; k < no; k++)
                {
                    printf("l'identifiant du medecin: ");
                    scanf("%d",&m[im].ord[k].identifiant);
                    printf("le nom du medecin: ");
                    gets(m[im].ord[k].nommed);
                    printf("l'identifiant du patient: ");
                    scanf("%d",&m[im].ord[k].identifiant);
                    printf("le nom du patient ");
                    gets(m[im].ord[k].nompat);
                    printf("les medicaments: ");
                    gets(m[im].ord[k].medicaments);
                }
//liste des certificats
                printf("le nombre des certificats du medecin %d: ", i + 1);
                scanf_s("%d", &nc);
                while (getchar() != '\n');
                for (k = 0; k < no; k++)
                {
                    printf("l'identifiant du medecin: ");
                    scanf("%d",&m[im].cert[k].identifiant);
                    printf("la date de creation du certificat: ");
                    gets(m[im].cert[k].datecreation);
                    printf("la cause du certificat: ");
                    scanf("%d",&m[im].cert[k].cause);
                    printf("l'identifiant du patient: ");
                    scanf("%d",&m[im].cert[k].identpat);
                    printf("le nom du patient ");
                    gets(m[im].cert[k].nompat);
                    printf("l'identifiant du medecin: ");
                    scanf("%d",&m[im].cert[k].identmed);
                    printf("le nom du patient ");
                    gets(m[im].cert[k].nommed);
                    printf("l'identifiant du patient: ");
                    scanf("%d",&m[im].cert[k].identpat);
                    printf("la signature du médecin: ");
                    gets(m[im].cert[k].signature);
                }
            puts ("Voulez vous continuer ou quitter (entrer c ou q): ");
            scanf("%c",&continuer);
        }while (continuer=='c');
        puts("\t\t\t\t-----Bienvenue dans notre hopital-----");
        puts("Bonjour monsieur l'Administrateur");
        }
//supprimer un medecin
        else if (souhaitadmin==4){
            do{
                    im--;

                puts("Pour supprimer un médecin, il suffit de siuivre ces instructions: ");
                do{
                    printf("Enter l'indentifiant du médecin à supprimer: ");
                    scanf("%d",&inddelm);
                }while(findident(m,im,inddelm)==-1);
                im--;
                for (i=inddelm;i<im;i++){
        //matricule
                while (m[i].matricule!=0)
                    m[i].matricule=m[i+1].matricule;
                //nom
                while (m[i].nom!='\0')
                    strcpy(m[i].nom,m[i+1].nom);
                //date de naissance
                while (m[i].date!='\0')
                    strcpy(m[i].date,m[i+1].date);
                //genre
                while (m[i].genre!='\0')
                    strcpy(m[i].genre,m[i+1].genre);
                //signature
                while (m[i].signature!='\0')
                    strcpy(m[i].signature,m[i+1].signature);
                //service
                while (m[i].service!='\0')
                    strcpy(m[i].service,m[i+1].service);
                //specialite
                while (m[i].specialite!='\0')
                    strcpy(m[i].specialite,m[i+1].specialite);
        //liste des patients
                while (m[i].lpat[j]!='\0')
                    strcpy(m[i].lpat[j],m[i+1].lpat[j]);
        //liste des ordonnances
                int k=0;
                while (m[im].ord[k].identifiant!=0)
                    m[im].ord[k].identifiant=m[im].ord[k+1].identifiant;
                while (m[im].ord[k].nommed!='\0')
                    strcpy(m[im].ord[k].nommed,m[im].ord[k+1].nommed);
                while (m[im].ord[k].identifiant!=0)
                    m[im].ord[k].identifiant=m[im].ord[k+1].identifiant;
                while (m[im].ord[k].nompat!='\0')
                    strcpy(m[im].ord[k].nompat,m[im].ord[k+1].nompat);
                while (m[im].ord[k].medicaments!='\0')
                    strcpy(m[im].ord[k].medicaments,m[im].ord[k+1].medicaments);
        //liste des certificats
                int l = 0;
                while (m[im].cert[k].identifiant!=0)
                    m[im].cert[k].identifiant=m[im].cert[k+1].identifiant;
                while (m[im].cert[k].datecreation!='\0')
                    strcpy(m[im].cert[k].datecreation,m[im].cert[k+1].datecreation);
                while (m[im].cert[k].cause!=0)
                    strcpy(m[im].cert[k].cause,m[im].cert[k+1].cause);
                while (m[im].cert[k].identpat!=0)
                    m[im].cert[k].identpat=m[im].cert[k+1].identpat;
                while (m[im].cert[k].nompat!='\0')
                    strcpy(m[im].cert[k].nompat,m[im].cert[k+1].nompat);
                while (m[im].cert[k].identmed!=0)
                    m[im].cert[k].identmed=m[im].cert[k+1].identmed;
                while (m[im].cert[k].nommed!='\0')
                    strcpy(m[im].cert[k].nommed,m[im].cert[k+1].nommed);
                while(m[im].cert[k].identpat=0)
                    m[im].cert[k].identpat=m[im].cert[k+1].identpat;
                while (m[im].cert[k].signature!='\0');
                    strcpy(m[im].cert[k].signature,m[im].cert[k+1].signature);
                }
            puts ("Voulez vous continuer ou quitter (entrer c ou q): ");
                scanf("%c",&continuer);
        }while (continuer=='c');
        puts("\t\t\t\t-----Bienvenue dans notre hopital-----");
        puts("Bonjour monsieur l'Administrateur");
        }
//ajouter un patient
        else if (souhaitadmin==5){
            do{
                puts("Pour ajouter un patient, il suffit de suivre ces instruction: ");
                ip++;
        //matricule
                printf("la mat du pat n %d: ", i + 1);
                scanf_s("%d", &p[ip].matricule);
                while (getchar() != '\n');
        //nom
                printf("le nom du pat %d: ", i + 1);
                gets(p[ip].nom);
                puts(p[ip].nom);
        //adrese pat
                printf("donner l'adresse du patient numero %d: ",i);
                gets(p[ip].adressp);
                puts(p[ip].adressp);
        //mot de passe pat
                printf("donner le mot de passe du patient n %d: ",i);
                gets(p[ip].mdpp);
                puts(p[ip].mdpp);
        //date de naissance
                printf("la date de naissance du pat %d: ", i + 1);
                gets(p[ip].date);
                printf("la date: %s ", p[ip].date);
        //genre
                printf("le genre du pat %d: ", i + 1);
                gets(p[ip].genre);
                printf("le genre: %s", p[ip].genre);
        //Description des maladies
                printf("la description de la maladie du pat %d: ", i + 1);
                gets(p[ip].description);
                printf("des : %s \n", p[ip].description);
        //service
                printf("le service du pat %d: ", i + 1);
                gets(p[ip].service);
                puts(p[ip].service);
        //liste des rendez-vous
                printf("le nb des rdv du pat %d: ", i + 1);
                scanf_s("%d", &npr);
                while (getchar() != '\n');
                for (j = 0; j < npr; j++)
                {
                    printf("rdv n %d: ", j + 1);
                    gets(p[ip].lrdv[j]);
                    puts(p[ip].lrdv[j]);
                }
        //liste des ordonnances
                printf("le nb des ord du pat %d: ", i + 1);
                scanf_s("%d", &npo);
                while (getchar() != '\n');
                for (k = 0; k < npo; k++)
                {
                    printf("l'identifiant du medecin: ");
                    scanf("%d",&p[ip].ord[k].identifiant);
                    printf("le nom du medecin: ");
                    gets(p[ip].ord[k].nommed);
                    printf("l'identifiant du patient: ");
                    scanf("%d",&p[ip].ord[k].identifiant);
                    printf("le nom du patient ");
                    gets(p[ip].ord[k].nompat);
                    printf("les medicaments: ");
                    gets(p[ip].ord[k].medicaments);
                }
        //liste des certificats
                printf("le nb des cert du med %d: ", i + 1);
                scanf_s("%d", &npc);
                while (getchar() != '\n');
                for (l = 0; l < npc; l++)
                {
                    printf("l'identifiant du medecin: ");
                    scanf("%d",&p[ip].cert[l].identifiant);
                    printf("la date de creation du certificat: ");
                    gets(p[ip].cert[l].datecreation);
                    printf("la cause du certificat: ");
                    scanf("%d",&p[ip].cert[l].cause);
                    printf("l'identifiant du patient: ");
                    scanf("%d",&p[ip].cert[l].identpat);
                    printf("le nom du patient ");
                    gets(p[ip].cert[l].nompat);
                    printf("l'identifiant du medecin: ");
                    scanf("%d",&p[ip].cert[l].identmed);
                    printf("le nom du patient ");
                    gets(p[ip].cert[l].nommed);
                    printf("l'identifiant du patient: ");
                    scanf("%d",&p[ip].cert[l].identpat);
                    printf("la signature du médecin: ");
                    gets(p[ip].cert[l].signature);
                }
            puts ("Voulez vous continuer ou quitter (entrer c ou q): ");
            scanf("%c",&continuer);
        }while (continuer=='c');
        system("cls");
        puts("\t\t\t\t-----Bienvenue dans notre hopital-----");
        puts("Bonjour monsieur l'Administrateur");
        }
//supprimer un patient
        else if (souhaitadmin==5){
            do{
                printf("Pour supprimer un patient, il suffit de siuivre ces instructions: ");
                printf("Enter l'indentifiant du patient à supprimer: ");
                scanf("%d",&inddelp);
                 do{
                    printf("Enter l'indentifiant du médecin à supprimer: ");
                    scanf("%d",&inddelp);
                }while(findident(p,im,inddelp)==-1);
                ip--;
                for (i=inddelp;i<im;i++){
        //matricule
                    p[i].matricule=p[i+1].matricule;
        //nom
                    strcpy(p[i].nom,p[i+1].nom);
        //adrese pat
                    strcpy(p[i].adressp,p[i+1].adressp);
        //mot de passe pat
                    strcpy(p[i].mdpp,p[i+1].mdpp);
        //date de naissance
                    strcpy(p[i].date,p[i+1].date);
        //genre
                    strcpy(p[i].genre,p[i+1].genre);
        //Description des maladies
                    strcpy(p[i].description,p[i+1].description);
        //service
                    strcpy(p[i].service,p[i+1].service);
        //liste des rendez-vous
                for (j = 0; j < npr; j++)
                    strcpy(p[i].lrdv[j],p[i+1].lrdv);
        //liste des ordonnances
                int k;
                k=0;
                    while(p[ip].ord[k].identifiant!=0)
                        p[ip].ord[k].identifiant=p[ip].ord[k+1].identifiant;
                    while(p[ip].ord[k].nommed!='\0')
                        strcpy(p[ip].ord[k].nommed,p[ip].ord[k+1].nommed);
                    while (p[ip].ord[k].identifiant!=0)
                        p[ip].ord[k].identifiant=p[ip].ord[k+1].identifiant;
                    while (p[ip].ord[k].nompat!='\0')
                        strcpy(p[ip].ord[k].nompat,p[ip].ord[k+1].nompat);
                    while (p[ip].ord[k].medicaments!='\0')
                        strcpy(p[ip].ord[k].medicaments,p[ip].ord[k+1].medicaments);
        //liste des certificats
                int l = 0;
                while (p[ip].cert[l].identifiant!=0)
                    p[ip].cert[l].identifiant=p[ip].cert[l+1].identifiant;
                while (p[ip].cert[l].datecreation!='\0')
                    strcpy(p[ip].cert[l].datecreation,p[ip].cert[l+1].datecreation);
                while (p[ip].cert[l].cause!='\0')
                    strcpy(p[ip].cert[l].cause,p[ip].cert[l+1].cause);
                while (p[ip].cert[l].identpat!=0)
                    p[ip].cert[l].identpat=p[ip].cert[l+1].identpat;
                while (p[ip].cert[l].nompat!='\0')
                    strcpy(p[ip].cert[l].nompat,p[ip].cert[l+1].nompat);
                while (p[ip].cert[l].identmed!=0)
                    p[ip].cert[l].identmed=p[ip].cert[l+1].identmed;
                while (p[ip].cert[l].nommed!='\0')
                    strcpy(p[ip].cert[l].nommed,p[ip].cert[l+1].nommed);
                while(p[ip].cert[l].identpat=0)
                    p[ip].cert[l].identpat=p[ip].cert[l+1].identpat;
                while (p[ip].cert[l].signature!='\0')
                    strcpy(p[ip].cert[l].signature,p[ip].cert[l+1].signature);
        }
            puts ("Voulez vous continuer ou quitter (entrer c ou q): ");
            scanf("%c",&continuer);
        }while (continuer=='c');
        puts("\t\t\t\t-----Bienvenue dans notre hopital-----");
        puts("Bonjour monsieur l'Administrateur");
        }
    /*//planifier les rendez-vous
        else{
        puts("Pour planifier les rendezvous, il suffit de suivre ces instructions: ");
        }*/

    }while (continuer=='c');
    system("cls");
    puts("\t\t\t\t-----Bienvenue dans notre hopital-----");
    puts("Bonjour monsieur l'Administrateur");
    }
//les instructuents du medecin
    else if (entree==2){
        system("cls");
        puts("\t\t\t\t-------Bienvenue dans notre hopital!-------");
        puts("Bonsoir Docteur");
    //autentification
        printf("Donner votre identifiant: ");
        scanf("%d",&identm);
        while (getchar() != '\n');
        printf("\n");
    //determiner l'indice du medecin
        indm=findident(&m, 6,identm);
        while(indm==-1){
            printf("Lindentificateur n'existe pas, entrer de nouveau: ");
            scanf("%d",&identm);
            while (getchar() != '\n');
            printf("\n");
            indm=findident(&m, 6,identm);
        }
//login
        do{
            printf("Donner votre adresse: ");
            gets(addm);
            printf("\n");
            printf("Donner votre mot de passe: ");
            gets(mdpm);
            if (login(addm,m[indm].adressm) != 0 || login(mdpm, m[indm].mdpm) != 0){
                    system("cls");
                    puts("\t\t\t\t-----Bienvenue dans notre hopital-----");
                    puts("Bonjour monsieur l'Administrateur");
                    puts("Echec,entrer de nouveau votre adesse et mot de passe");}
        }while (login(addm,m[indm].adressm) != 0 || login(mdpm, m[indm].mdpm) != 0);
        do{
        system("cls");
        puts("\t\t\t\t-------Bienvenue dans notre hopital!-------");
        puts("Pour mieux determiner vos choix, entrer ");
        puts("1 Si vous voulez rédiger le dossier du malade  ");
        puts("2 Si vous voulez rédiger des ordonnances  ");
        puts("3 Si vous voulez rédiger des certificats  ");
//saisir le souhait du medecin
        do {
            printf("Entrez 1 ou 2 ou 3: ");
            scanf("%d",&souhaitmedecin);
            printf("\n %d \n",souhaitmedecin);
            if (souhaitmedecin!=1 ||souhaitmedecin!=2 ||souhaitmedecin!=3 )
                puts("Coix invalide, essayez une autre fois");
        }while (!(souhaitmedecin!=1 ||souhaitmedecin!=2 ||souhaitmedecin!=3 ));
        system("cls");
        puts("\t\t\t\t-------Bienvenue dans notre hopital!-------");
        printf("\Bonsoir Docteuur %s \n",m[indm].nom);
//rediger le dossier du malade
       if (souhaitmedecin==1){
            do{
                puts("Pour rédiger le dossier d'un malade, suivez ces instructions: ");
                printf("Entrez l'identifiant de votre patient: ");
                scanf("%d",&indpatmod);
                indp=findident(p,ip,indpatmod);
                while(indpatmod==-1){
                    printf("L'indentificateur n'existe pas, entrer de nouveau: ");
                    scanf("%d",&indpatmod);
                    indp=findident(p,ip,indpatmod);
                }
                puts("Décrivez le patient: ");
                gets(p[indp].description);
                puts ("Voulez vous continuer ou quitter (entrer c ou q): ");
                scanf("%c",&continuer);
            }while (continuer=='c');
            system("cls");
            puts("\t\t\t\t-------Bienvenue dans notre hopital!-------");
            puts("Bonsoir Docteur");
        }
//rediger les ordonnances
    npo=0;
        if (souhaitmedecin==2){
            do{
                puts("Pour rédiger des ordonnances, suivez ces inctructions: ");
                printf("Entrez le nombre des ordonnances à ajouter: ");
                scanf_s("%d", &npo);
                while (getchar() != '\n');
                for (k = 0; k < npo; k++)
                {
                    printf("l'identifiant du medecin: ");
                    scanf("%d",&identred);
                    indmao=findident(&m,im,identred);
                    p[indmao].ord[k].identifiant=identred;
                    printf("le nom du medecin: ");
                    strcpy(m[indmao].ord[k].nommed,m[indmao].nom);
                    printf("l'identifiant du patient: ");
                    scanf("%d",&indentpatre);
                    indpao=findident(&p,ip,indentpatre);
                    p[indpao].ord[k].identifiant=indentpatre;
                    printf("le nom du patient ");
                    strcpy(p[indpao].ord[k].nommed,p[indpao].nom);
                    printf("les medicaments: ");
                    gets(medicaments);
                    strcpy(p[indpao].ord[k].medicaments,medicaments);
                    strcpy(m[indmao].ord[k].medicaments,medicaments);
                }
                puts ("Voulez vous continuer ou quitter (entrer c ou q): ");
                scanf("%c",&continuer);
            }while (continuer=='c');
            system("cls");
            puts("\t\t\t\t-------Bienvenue dans notre hopital!-------");
            puts("Bonsoir Docteur");
        }
//rediger les certificats
        if (souhaitmedecin==3){
            do{
                npc=0;
                printf("Pour rédiger des certificats, suivez ces instructions: ");
                printf("Entrez le nombre des certificats à ajouter: ");
                scanf_s("%d", &npc);
                while (getchar() != '\n');
                for (l = 0; l < npc; l++){
                    printf("l'identifiant du medecin: ");
                    scanf("%d",&identred);
                    indmac=findident(&m,im,identred);
                    p[indmac].ord[k].identifiant=identred;
                    printf("l'identifiant du patient: ");
                    scanf("%d",&indentpatre);
                    indpac=findident(&p,ip,indentpatre);
                    p[indpac].ord[k].identifiant=indentpatre;
                    printf("le nom du patient ");
                    strcpy(p[indpac].ord[k].nommed,p[indpac].nom);
                    printf("la date de creation du certificat: ");
                    gets(p[indpac].cert[l].datecreation);
                    printf("la cause du certificat: ");
                    gets(cause);
                    strcpy(p[indpac].cert[l].cause,cause);
                    strcpy(m[indmac].cert[l].cause,cause);
                    //printf("la signature du médecin: ");
                    strcpy(p[indpac].cert[l].signature,m[indm].signature);
                    strcpy(m[indmac].cert[l].signature,m[indm].signature);}
                puts ("Voulez vous continuer ou quitter (entrer c ou q): ");
                scanf("%c",&continuer);
            }while (continuer=='c');
            system("cls");
            puts("\t\t\t\t-------Bienvenue dans notre hopital!-------");
            puts("Bonsoir Docteur");
        }
    }while (continuer=='c');
    system("cls");
    puts("\t\t\t\t-----Bienvenue dans notre hopital-----");
    puts("Bonjour Docteur");}
//les instruction du patient
else{
        system("cls");
        puts("\t\t\t\t-------Bienvenue dans notre hopital!-------");
        puts("Bienvenue au mode patient");
//autentification
        printf("Donner votre identifiant: ");
        scanf("%d",&ident);
        while (getchar() != '\n');
        printf("\n");
//determiner l'indice du patient
        ind=findident(p, ip,ident);
        while(ind==-1){

            printf("L'indentificateur n'existe pas, entrer de nouveau: ");
            scanf("%d",&ident);
            ind=findident(p,ip,ident);
        }
        system("cls");
        puts("\t\t\t\t-------Bienvenue dans notre hopital!-------");
        printf("Bonsoir Monsieur/Madamme %s , bon rétablissement\n",p[ind].nom);
//login
        do{
            printf("Donner votre adresse: ");
            gets(add);
            printf("\n");
            printf("Donner votre mot de passe: ");
            gets(mdp);
             if (login(add,p[ind].adressp) != 0 || login(mdp, p[ind].mdpp) != 0){
                    system("cls");
                    puts("\t\t\t\t-----Bienvenue dans notre hopital-----");
                    printf("Bonsoir Monsieur/Madamme %s , bon rétablissement\n",p[ind].nom);
                    puts("Echec,entrer de nouveau votre adesse et mot de passe");}
        }while (login(add,p[ind].adressp) != 0 || login(mdp, p[ind].mdpp) != 0);
        do{
        system("cls");
        puts("\t\t\t\t-------Bienvenue dans notre hopital!-------");
        printf("Bonsoir Monseur/Madamme %s , bon rétablissement\n",p[ind].nom);
// Boucle pour saisir la date jusqu'à ce qu'une date valide soit entrée c'est a dire de la forme jj-mm-aaaa
        while (1) {
            printf("Entrez la date d'aujourd'hui (jj-mm-aaaa) : ");
            if (!(scanf("%10s", date) != 1 || verifierFormatDate(date) == -1))
                break;
        }
//afficher la date d'aujourd'huit et les prochain rendez-vous
        printf("La date d'aujourd'hui est : %s\n", date);
        afficherProchainsRendezVous(&p, date);
//saisi du choix du patient
        system("cls");
        printf("La date d'aujourd'hui est : %s\n", date);
        afficherProchainsRendezVous(&p, date);
        puts("Pour mieux determiner vos choix, entrer ");
        puts("1 Si vous voulez demander un certificat ");
        puts("2 Si vous voulez demander un rendez-vous  ");
        puts("3 Si vous voulez consulter votre dossier medical ");
        do {
            printf("Entrez 1 ou 2 ou 3 ou 4: ");
            scanf("%d",&souhaitpatient);
            printf("\n %d \n",souhaitpatient);
            if (souhaitpatient!=1 ||souhaitpatient!=2 ||souhaitpatient!=3 ||souhaitpatient!=4)
                puts("Coix invalide, essayez une autre fois");
        }while (!(souhaitpatient!=1 ||souhaitpatient!=2 ||souhaitpatient!=3 ||souhaitpatient!=4 ));
        system("cls");
        puts("\t\t\t\t-------Bienvenue dans notre hopital!-------");
        printf("\tSalut cher patient %s ,bon rétablissement \n",p[ind].nom);
//demander une certificat
        if (souhaitpatient==1){
            do{
                puts("Pour demander un certificat,suivez ces instructions: ");
                printf("l'identifiant du medecin: ");
                    scanf("%d",&p[ind].cert[l+1].identifiant);
                    printf("la date de creation du certificat: ");
                    gets(p[ind].cert[l+1].datecreation);
                    printf("la cause du certificat: ");
                    scanf("%d",&p[ind].cert[l+1].cause);
                    printf("l'identifiant du patient: ");
                    scanf("%d",&p[ind].cert[l+1].identpat);
                    printf("le nom du patient ");
                    gets(p[ind].cert[l+1].nompat);
                    printf("l'identifiant du medecin: ");
                    scanf("%d",&p[ind].cert[l+1].identmed);
                    printf("le nom du patient ");
                    gets(p[ind].cert[l+1].nommed);
                    printf("l'identifiant du patient: ");
                    scanf("%d",&p[ind].cert[l+1].identpat);
                    printf("la signature du médecin: ");
                    gets(p[ind].cert[l+1].signature);
                // Saisie de la date de création
                printf("Date de création : ");
                gets(p[ind].cert[l+1].datecreation);
                while (1) {
                printf("Entrez la date d'aujourd'hui (jj-mm-aaaa) : ");
                if (! (verifierFormatDate(p[ind].cert[l+1].datecreation) == -1))
                    break;
                }
                // Saisie de la cause
                printf("Cause : ");
                scanf("%s",p[ind].cert[l+1].cause);
                // Saisie de l'identifiant, nom et signature du médecin
                printf("Identifiant du médecin : ");
                scanf("%d", matricule);
                //a rremplr a l'zide le la fonction rechercher de l'ident
                //determiner l'indice du patient
                int indmp;
                indmp=findident(m,im,matricule);
                while(indmp==-1){
                    printf("L'indentificateur n'existe pas, entrer de nouveau: ");
                    scanf("%d",&matricule);
                    ind=findident(m,im,matricule);
                }
                system("cls");
                puts("\t\t\t\t-------Bienvenue dans notre hopital!-------");
                printf("\tSalut cher patient %s ,bon rétablissement \n",p[ind].nom);
                puts("Votre certificat: ");
                printf("Identifiant du medecin: %d\n",matricule);
                printf("Nom du medecin: %s\n",m[ind].nom);
                printf("Identifiant du patient: %d\n",ident);
                printf("La cause de la maladie: %s\n",p[ind].cert[l+1].cause);
                puts ("Voulez vous continuer ou quitter (entrer c ou q): ");
                scanf("%c",&continuer);
            }while (continuer=='c');
            system("cls");
            puts("\t\t\t\t-------Bienvenue dans notre hopital!-------");
            puts("Bienvenue au mode patient");
        }

//demander un rendez-vous
        else if (souhaitpatient==2){
            do{
                printf("Pour demander demandez un rendez vous,suivez ces instructions: ");
                gets(rendezvousp) ;
                printf("Entrez l'identifainat du medecin: ");
                scanf("%d",&identrdv);
                indms=findident(m,im,identrdv);
                while(indms==-1){
                    printf("L'indentificateur n'existe pas, entrer de nouveau: ");
                    scanf("%d",&identrdv);
                    indms=findident(m,im,identrdv);
                }
                while (verifrdv(rendezvousp,ferie[nbferie],nbferie)==0 && nbrend(&m,indms,rendezvousp)<=20) //rendezvous non valide
                {
                    puts("La date saisie est invalide");
                    printf("Saisir une autre date: ");
                    gets(rendezvous) ;
                }
                puts ("Voulez vous continuer ou quitter (entrer c ou q): ");
                scanf("%c",&continuer);
            }while (continuer=='c');
            system("cls");
            puts("\t\t\t\t-------Bienvenue dans notre hopital!-------");
            puts("Bienvenue au mode patient");
        }
//consulter le dossier medical
        else if (souhaitpatient==3){
            puts("Votre dossier medical: ");
            afficherDescriptionMaladies(p, ind);
            afficherOrdonnancesCertificats(p, ind);
            afficherTousRendezVous(p, ind);
        }
        }while (continuer=='c');
            system("cls");
            puts("\t\t\t\t-----Bienvenue dans notre hopital-----");
            puts("Bonjour monsieur l'Administrateur");
    }

    return 0;
}
