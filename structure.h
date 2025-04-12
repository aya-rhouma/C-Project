typedef struct {
    int identifiant;
    char nommed[10];
    char signature[10];
    int identifiantPatient;
    char nompat[10];
    char medicaments[50];
} Ordonnance;

typedef struct {
    int identifiant;
    char datecreation[11];
    char cause[20];
    int identpat;
    char nompat[10];
    int identmed;
    char nommed[10];
    char signature[10];
} Certificat;

typedef struct {
    char medecin;
    int jour;
    int mois;
    int annee;
    int nombrePatients;
} RendezVous;

typedef struct {
    int identifiant;
    char nom[20];
    char med[100][20];
    char pat[100][20];
} Service;

typedef struct {
    int matricule;
    char nom[10];
    char date[11];
    char genre;
    char signature[10];
    char service[10];
    char specialite[10];
    char lpat[1000];
    Ordonnance ord[100];
    Certificat cert[100];
    char adressm[20];
    char mdpm[10];
} Medecin;

typedef struct {
    int matricule;
    char nom[10];
    char date[12];
    char genre;
    char description[1000];
    int identifiantService;
    char service[10];
    char lrdv[100][100];
    Ordonnance ord[100];
    char lmed[100][10];
    Certificat cert[100];
    char adressp[20];
    char mdpp[10];
} Patient;
