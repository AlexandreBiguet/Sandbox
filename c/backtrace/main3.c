#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>

/* Taille maximale du chemin d'un fichier.                               */
#define SLOGL_MAXFILEPATH             1024


/* Nombre maximal de fonctions appelées pour une fonction donnée.        */
#define SLOGL_MAXCALLFUNCTION   16


/* Fichier de journalisation.                                            */
typedef FILE *SLOGL_file;

/* Sauvegarde du descripteur de fichier de journalisation.               */
static SLOGL_file fpSave = NULL;


/* Récupère la date courante.                                            */
static struct tm *getDate(void) {
    time_t t = time(NULL);
    return localtime(&t);
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


/* Niveau d'erreur.                                                      */
typedef enum { 
    SLOGL_LVL_DEBUG,        /* Déboguage du programme.                   */
    SLOGL_LVL_INFO,         /* Informations diverses.                    */
    SLOGL_LVL_NOTICE,       /* Informations remarquables                 */
    SLOGL_LVL_WARNING,      /* Message d'avertissement.                  */
    SLOGL_LVL_ERROR,        /* Erreur d'exécution.                       */
    SLOGL_LVL_FATAL         /* Erreur fatale.                            */
} SLOGL_level;

/* Niveau d'erreur du programme.                                         */
extern SLOGL_level programLevel;




/* Niveau d'erreur du programme.                                         */
#ifdef INFO
    SLOGL_level SLOGL_programLevel = SLOGL_LVL_INFO;
#elif defined NOTICE
    SLOGL_level SLOGL_programLevel = SLOGL_LVL_NOTICE;
#elif defined WARNING
    SLOGL_level SLOGL_programLevel = SLOGL_LVL_WARNING;
#elif defined ERROR
    SLOGL_level SLOGL_programLevel = SLOGL_LVL_ERROR;
#elif defined FATAL
    SLOGL_level SLOGL_programLevel = SLOGL_LVL_FATAL;
#else
    SLOGL_level SLOGL_programLevel = SLOGL_LVL_DEBUG;
#endif




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




/* Ecrit les informations d'en-tête dans le fichier de journalisation.   */
void SLOGL_printHeader(SLOGL_level msgLevel) {
    if (msgLevel >= SLOGL_programLevel) {
        printLevel(msgLevel);
        printDate();
    }
}




/* Ecrit une chaîne dans le fichier de journalisation.                   */
void SLOGL_vprint(SLOGL_level msgLevel, const char *msg, ...) {
    if (fpSave && msg && msgLevel >= programLevel) {
        va_list ap;
        va_start(ap, msg);
        vfprintf(fpSave, msg, ap);
    }
}




/* Affiche un message dans le fichier de journalisation.                 */

#define SLOGL_print(n, ...) \
    do { \
        SLOGL_printHeader(n); \
        SLOGL_vprint(n, __VA_ARGS__); \
    } while (0)




/* Fonction dans la pile d'appel du programme.                           */
typedef struct frame {
    char *name;             /* Nom de la fonction.                       */
    void *addr;             /* Adresse de la fonction.                   */
    char *file;             /* Fichier de la fonction.                   */
    int startLine;          /* Ligne de début de la fonction.            */
    int endLine;            /* Ligne de fin de la fonction.              */
    int depth;              /* Profondeur de la fonction dans la pile.   */
    int iUp;                /* Nombre courants de fonctions appelées.    */
    int iMax;               /* Nombre de fonctions appelées.             */
    struct frame *up        /* Fonctions supérieures.                    */
        [SLOGL_MAXCALLFUNCTION];       
    struct frame *down;     /* Fonction inférieure.                      */
} frame;

/* Structure de la pile d'appel du programme.                            */
typedef struct {
    frame *head;            /* Début de la pile.                         */
    frame *current;         /* Element courant de la pile.               */
    int depth;              /* Profondeur de la pile.                    */
} stack;

/* Pile d'appel du programme.                                            */
static stack currentStack = {NULL, NULL, 0};



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



/* Afficher la pile au fur et à mesure ?                                 */
static int printStackTrace = 0;


/* Détruit la pile d'appel du programme.                                 */
static void deleteStack(void) {
    frame *tmp = currentStack.head;

    while (tmp) {
        if (tmp->up[tmp->iUp]) {
            tmp = tmp->up[tmp->iUp];
            ++tmp->down->iUp;
        }
        else if (tmp->down) {
            frame *buf = tmp->down;
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
static void printFunction(frame *this, int started) {
    SLOGL_vprint(SLOGL_LVL_DEBUG, "\n\t%s:%d : ", this->file, 
                 started ? this->endLine : this->startLine);

    for (int j = 0; j < this->depth; ++j)
        SLOGL_vprint(SLOGL_LVL_DEBUG, "\t");

    SLOGL_vprint(SLOGL_LVL_DEBUG, "%s %s[%p]", started ? 
           "END" : "START", this->name, this->addr);
}

/* Positionne l'affichage ou non de la pile d'appel au fur et à mesure.  */
void SLOGL_setStackTrace(int n) {
    printStackTrace = n;
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




/* Quitte la bibliothèque.                                               */
int SLOGL_quit(void) {
    deleteStack();
    return fpSave && fclose(fpSave) != EOF;
}





/* Affiche la pile d'appel du programme.                                 */
void SLOGL_displayStack(void) {
    frame *tmp = currentStack.head;

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








void foo(unsigned val) 
  START(foo);
    if(val) {
        foo(val / 2);
        putchar((val % 2) ? '1' : '0');
    }
  END();

int main(void) {
    SLOGL_init("mylog");

    SLOGL_setStackTrace(1);

  START(main);

    foo(14);

  END();

    SLOGL_quit();
    return 0;
}



