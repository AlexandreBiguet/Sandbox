



#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Nombre maximal de fonctions appelées pour une fonction donnée.        */
#define SLOGL_MAXCALLFUNCTION   16

/* Taille maximale de la pile d'exceptions.                              */
#define SLOGL_STACKMAXLEN       16


/* Affiche un message dans le fichier de journalisation.                 */
#define SLOGL_print(n, ...) \
    do { \
        SLOGL_printHeader(n); \
        SLOGL_vprint(n, __VA_ARGS__); \
    } while (0)


/* Début d'une fonction.                                                 */
#define START(x) \
    { \
        SLOGL_pushStack(#x, &x, __FILE__, __LINE__)

/* Retour d'une fonction.                                                */
#define RETURN(x) \
    do { \
        SLOGL_popStack(__LINE__); \
        return x; \
    } while (0)

/* Sortie du programme à partir d'une fonction.                          */
#define EXIT(x) \
    do { \
        SLOGL_popStack(__LINE__); \
        exit(x); \
    } while (0)

/* Fin d'une fonction.                                                   */
#define END() \
        SLOGL_popStack(__LINE__); \
    }

/* Essai d'un bloc.                                                      */
#define try \
    if (!((++SLOGL_catch.current)->type = setjmp(SLOGL_catch.current->env)))

/* Bloc de traitement d'erreur.                                          */
#define catch(id) \
    if(!SLOGL_catch.current->type)  \
        --SLOGL_catch.current; \
    else for (int SLOGL_tmp = 1, id = (SLOGL_catch.current--)->type; SLOGL_tmp; \
              SLOGL_tmp = 0)

/* Signalement d'une erreur.                                             */
#define throw(t) \
    longjmp(SLOGL_catch.current->env, t)


/* Fonction dans la pile d'appel du programme.                           */
typedef struct frame {
    char *name;             /* Nom de la fonction.                       */
    void *addr;             /* Adresse de la fonction.                   */
    char *file;             /* Fichier de la fonction.                   */
    int startLine;          /* Ligne de début de la fonction.            */
    int endLine;            /* Ligne de fin de la fonction.              */
    unsigned depth;         /* Profondeur de la fonction dans la pile.   */
    unsigned iUp;           /* Nombre courants de fonctions appelées.    */
    unsigned iMax;          /* Nombre de fonctions appelées.             */
    struct frame *up        /* Fonctions supérieures.                    */
        [SLOGL_MAXCALLFUNCTION];       
    struct frame *down;     /* Fonction inférieure.                      */
} SLOGL_frame;

/* Structure de la pile d'appel du programme.                            */
typedef struct {
    SLOGL_frame *head;      /* Début de la pile.                         */
    SLOGL_frame *current;   /* Element courant de la pile.               */
    unsigned depth;         /* Profondeur de la pile.                    */
} SLOGL_stack;

/* Exception.                                                            */
extern struct SLOGL_exception {
    struct {
        int type;           /* Type de l'exception.                      */
        jmp_buf env;        /* Environnement sauvergardé.                */
    } tab[SLOGL_STACKMAXLEN], *current;
} SLOGL_catch;

/* Niveau d'erreur.                                                      */
typedef enum { 
    SLOGL_LVL_DEBUG,        /* Déboguage du programme.                   */
    SLOGL_LVL_INFO,         /* Informations diverses.                    */
    SLOGL_LVL_NOTICE,       /* Informations remarquables                 */
    SLOGL_LVL_WARNING,      /* Message d'avertissement.                  */
    SLOGL_LVL_ERROR,        /* Erreur d'exécution.                       */
    SLOGL_LVL_FATAL         /* Erreur fatale.                            */
} SLOGL_level;

/* Codes d'erreur.                                                       */
typedef enum {
    SLOGL_ERR_NOERR,        /* Aucune erreur.                            */
    SLOGL_ERR_MEM,          /* Allocation mémoire.                       */
    SLOGL_ERR_FOPEN,        /* Ouverture d'un fichier.                   */
    SLOGL_ERR_FCLOSE,       /* Fermeture d'un fichier.                   */
    SLOGL_ERR_PARAM,        /* Passage en paramètre.                     */
    SLOGL_ERR_DIVNUL,       /* Division par zéro.                        */
    SLOGL_ERR_LAST          /* Nombre d'erreurs.                         */
} SLOGL_err;


/* Erreur courante du programme.                                         */
extern SLOGL_err SLOGL_currentError;

/* Niveau d'erreur du programme.                                         */
extern SLOGL_level SLOGL_programLevel;


/* Positionne l'affichage ou non de la pile d'appel au fur et à mesure.  */
void SLOGL_setStackTrace(int n);

/* Positionne le niveau d'erreur du programme.                           */
void SLOGL_setProgramLevel(SLOGL_level lvl);

/* Récupère une description de l'erreur.                                 */
char *SLOGL_printDesError(SLOGL_err n);

/* Ecrit la description de l'erreur courante.                            */
void SLOGL_printError(const char *msg);

/* Ecrit les informations d'en-tête dans le fichier de journalisation.   */
void SLOGL_printHeader(SLOGL_level msgLevel);

/* Ecrit une chaîne dans le fichier de journalisation.                   */
void SLOGL_vprint(SLOGL_level msgLevel, const char *msg, ...);

/* Empile une fonction.                                                  */
void SLOGL_pushStack(char *name, void *addr, char *file, int line);

/* Dépile une fonction.                                                  */
void SLOGL_popStack(int endLine);

/* Affiche la pile d'appel du programme. (nécessite le niveau DEBUG)     */
void SLOGL_displayStack(void);

/* Initialise la bibliothèque.                                           */
int SLOGL_init(const char *fileName);

/* Quitte la bibliothèque.                                               */
int SLOGL_quit(void);

/* Taille maximale du chemin d'un fichier.                               */
#define SLOGL_MAXFILEPATH             1024


/* Fichier de journalisation.                                            */
typedef FILE *SLOGL_file;


/* Erreur courante du programme.                                         */
SLOGL_err SLOGL_currentError = 0;

/* Exception.                                                            */
struct SLOGL_exception SLOGL_catch = {.current = SLOGL_catch.tab - 1} ;

/* Niveau d'erreur du programme.                                         */
SLOGL_level SLOGL_programLevel = SLOGL_LVL_DEBUG;

/* Pile d'appel du programme.                                            */
static SLOGL_stack currentStack = {NULL, NULL, 0};

/* Sauvegarde du descripteur de fichier de journalisation.               */
static SLOGL_file fpSave = NULL;

/* Afficher la pile au fur et à mesure ?                                 */
static int printStackTrace = 0;


/* Récupère la date courante.                                            */
static struct tm *getDate(void) {
    time_t t = time(NULL);
    return localtime(&t);
}

/* Ecrit le niveau d'erreur dans le fichier de journalisation.           */
static void printLevel(SLOGL_level msgLevel) {
    if (fpSave && msgLevel <= SLOGL_LVL_FATAL) {
        static const char *t[] = 
            {"Debug", "Info", "Notice", "Warning", "Error", "Fatal error"};
        fprintf(fpSave, "\n%s - ", t[msgLevel]);
    }
}

/* Ecrit la date dans le fichier de journalisation.                      */
static void printDate(void) {
    if (fpSave) {
        struct tm *t = getDate();
        fprintf(fpSave, "%dh%dm%d : ", t->tm_hour, t->tm_min, t->tm_sec);
    }
}

/* Détruit la pile d'appel du programme.                                 */
static void deleteStack(void) {
    SLOGL_frame *tmp = currentStack.head;

    while (tmp) {
        if (tmp->up[tmp->iUp]) {
            tmp = tmp->up[tmp->iUp];
            ++tmp->down->iUp;
        }
        else if (tmp->down) {
            SLOGL_frame *buf = tmp->down;
            free(tmp);
            tmp = buf;
        }
        else
            break;
    }

    free(currentStack.head);
}

/* Ecrit une description d'une fonction dans le fichier de               *
 * journalisation.                                                       */
static void printFunction(SLOGL_frame *this, int started) {
    SLOGL_vprint(SLOGL_LVL_DEBUG, "\n\t%s:%d : ", this->file, 
                 started ? this->endLine : this->startLine);

    for (unsigned j = 0; j < this->depth; ++j)
        SLOGL_vprint(SLOGL_LVL_DEBUG, "\t");

    SLOGL_vprint(SLOGL_LVL_DEBUG, "%s %s[%p]", started ? 
           "END" : "START", this->name, this->addr);
}

/* Récupère une description de l'erreur.                                 */
char *SLOGL_printDesError(SLOGL_err n) {
    static const char *t[] = {
        "aucune erreur",
        "allocation mémoire",
        "ouverture d'un fichier",
        "fermeture d'un fichier",
        "paramètre invalide",
        "division par zéro"
    };
    return n < SLOGL_ERR_LAST ? (char *)t[n] : NULL;
}

/* Ecrit la description de l'erreur courante.                            */
void SLOGL_printError(const char *msg) {
    if (msg)
        SLOGL_print(SLOGL_LVL_ERROR, "%s: %s", msg, 
                    SLOGL_printDesError(SLOGL_currentError));
}

/* Positionne l'affichage ou non de la pile d'appel au fur et à mesure.  */
void SLOGL_setStackTrace(int n) {
    printStackTrace = n;
}

/* Positionne le niveau d'erreur du programme.                           */
void SLOGL_setProgramLevel(SLOGL_level lvl) {
    SLOGL_programLevel = lvl;
}

/* Ecrit les informations d'en-tête dans le fichier de journalisation.   */
void SLOGL_printHeader(SLOGL_level msgLevel) {
    if (msgLevel >= SLOGL_programLevel) {
        printLevel(msgLevel);
        printDate();
    }
}

/* Ecrit une chaîne dans le fichier de journalisation.                   */
void SLOGL_vprint(SLOGL_level msgLevel, const char *msg, ...) {
    if (fpSave && msg && msgLevel >= SLOGL_programLevel) {
        va_list ap;
        va_start(ap, msg);
        vfprintf(fpSave, msg, ap);
    }
}

/* Empile une fonction.                                                  */
void SLOGL_pushStack(char *name, void *addr, char *file, int line) {
    SLOGL_frame *tmp = currentStack.current;
    SLOGL_frame *this = malloc(sizeof *this);

    if (this) {
        this->name = name;
        this->addr = addr;
        this->file = file;
        this->startLine = line;
        this->iUp = this->iMax = 0;
        this->endLine = 0;
        this->depth = ++currentStack.depth;
        this->down = tmp;

        for (int i = 0; i < SLOGL_MAXCALLFUNCTION; ++i)
            this->up[i] = NULL;

        if (!currentStack.head) {
            if (printStackTrace)
                SLOGL_printHeader(SLOGL_LVL_DEBUG);
            currentStack.head = this;
        }

        if (tmp)
            tmp->up[tmp->iMax++] = this;

        currentStack.current = this;

        if (printStackTrace)
            printFunction(currentStack.current, 0);
    }
}

/* Dépile une fonction.                                                  */
void SLOGL_popStack(int endLine) {
    if (currentStack.current) {
        currentStack.current->endLine = endLine;

        if (printStackTrace)
            printFunction(currentStack.current, 1);

        currentStack.current = currentStack.current->down;
    }
    
    --currentStack.depth;
}

/* Affiche la pile d'appel du programme. (nécessite le niveau DEBUG)     */
void SLOGL_displayStack(void) {
    SLOGL_frame *tmp = currentStack.head;

    SLOGL_printHeader(SLOGL_LVL_DEBUG);
    printFunction(currentStack.head, 0);

    while (tmp) {
        if (tmp->up[tmp->iUp]) {
            tmp = tmp->up[tmp->iUp];
            printFunction(tmp, 0);
            ++tmp->down->iUp;
        }
        else if (tmp->down) {
            if (tmp->endLine)
                printFunction(tmp, 1);

            tmp->iUp = 0;
            tmp = tmp->down;
        }
        else
            break;
    }

    if (currentStack.head->endLine)
        printFunction(tmp, 1);
    currentStack.head->iUp = 0;
}

/* Initialise la bibliothèque.                                           */
int SLOGL_init(const char *fileName) {
    int ret = 0;

    if (fileName) {
        char fullFileName[SLOGL_MAXFILEPATH];
        struct tm *t = getDate();

        snprintf(fullFileName, sizeof fullFileName, "%s.%d%d%d.log",
                 fileName, t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
        ret = (fpSave = fopen(fullFileName, "a")) != NULL;
    }

    return ret;
}

/* Quitte la bibliothèque.                                               */
int SLOGL_quit(void) {
    deleteStack();
    return fpSave && fclose(fpSave) != EOF;
}




void foo(unsigned val) 
  START(foo);
    if(val) {
        foo(val / 2);
        putchar((val % 2) ? '1' : '0');
    }
  END();



void test () 
START ( test ); 
	printf("bla\n");
END();

void test2 () 
START(test2) ; 
	test();
END();

void test3 () 
START(test3) ; 
	test2();
END();

void test4 () 
START(test4) ; 
	test3();
END();

int main(void) {
    SLOGL_init("mylog");

    SLOGL_setStackTrace(-1);

  START(main);

    //foo(14);
	
	test4();

  END();

    SLOGL_quit();
    return 0;
}
