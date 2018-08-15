#include <ctype.h>
#include <errno.h>
#include <execinfo.h>
#include <getopt.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>  // use of chdir

#include <gsl/gsl_cdf.h>
#include <gsl/gsl_deriv.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_histogram.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_min.h>
#include <gsl/gsl_multimin.h>
#include <gsl/gsl_multiroots.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_roots.h>
#include <gsl/gsl_sort_double.h>
#include <gsl/gsl_statistics_double.h>
#include <gsl/gsl_vector.h>

#define DEBUG(i)      \
  printf("%d \n", i); \
  fflush(stdout)
#define STR_MAXSIZE 1024

// clang-format off
/* Lien : http://paulbourke.net/papers/conrec/ */



/*
 Derivation from the fortran version of CONREC by Paul Bourke
 d               ! matrix of data to contour
 ilb,iub,jlb,jub ! index bounds of data matrix
 x               ! data matrix column coordinates  Attention :::---> x[0 ... iub]
 y               ! data matrix row coordinates
 nc              ! number of contour levels
 z               ! contour levels in increasing order
 */


/*
	char df[STR_MAXSIZE] , ef[STR_MAXSIZE] , gf[STR_MAXSIZE] ;

	sprintf(df , "%s.dat" , namefile );
	sprintf(gf , "%s.gnu" , namefile );
	sprintf(ef , "%s.eps" , namefile );

	FILE *file = fopen (df , "w");
*/



// ConrecLine -> a user defined routine that plot the line
// On essaie d'abord de voir ce que la routine fait.

/*void Surface_Contour(double **d,int ilb,int iub,int jlb,int jub,
			 double *x,double *y,int nc,double *z,
			 void (*ConrecLine)(double,double,double,double,double))*/
// clang-format on

int Surface_Contour(gsl_matrix *d, int ilb, int iub, int jlb, int jub,
                    double *x, double *y, int nc, double *z, double val,
                    gsl_matrix *out, char *namefile, bool write_in_file) {
#define xsect(p1, p2) (h[p2] * xh[p1] - h[p1] * xh[p2]) / (h[p2] - h[p1])
#define ysect(p1, p2) (h[p2] * yh[p1] - h[p1] * yh[p2]) / (h[p2] - h[p1])

  // cherche les 'nc' lignes de niveaux au hauteur données dans 'z' de la
  // matrice d. renvoie la matrice out contenant les points (x_i , y_i) formant
  // le contour à la hauteur 'val'. si write_in_file est vrai alors tout est
  // ecrit dans le fichier dont le nom et 'namefile'

  FILE *file = fopen(namefile, "w");

  // avons nous rempli quelque chose dans la matrice out ?
  int smthg_out = 0;

  // indice matrice out
  int ind_out_i = 0;

  int m1, m2, m3, case_value;
  double dmin, dmax, x1 = 0, x2 = 0, y1 = 0, y2 = 0;
  int i, j, k, m;
  double h[5];
  int sh[5];
  double xh[5], yh[5];
  int im[4] = {0, 1, 1, 0}, jm[4] = {0, 0, 1, 1};
  int castab[3][3][3] = {{{0, 0, 8}, {0, 2, 5}, {7, 6, 9}},
                         {{0, 3, 4}, {1, 3, 1}, {4, 3, 0}},
                         {{9, 6, 7}, {5, 2, 0}, {8, 0, 0}}};

  double temp1, temp2;
  double temp_dij, temp_dij1, temp_di1j, temp_di1j1;
  double temp_diimmm1;

  for (j = (jub - 1); j >= jlb; j--) {
    for (i = ilb; i <= iub - 1; i++) {
      temp_dij = gsl_matrix_get(d, (size_t)i, (size_t)j);
      temp_dij1 = gsl_matrix_get(d, (size_t)i, (size_t)j + 1);
      temp_di1j = gsl_matrix_get(d, (size_t)i + 1, (size_t)j);
      temp_di1j1 = gsl_matrix_get(d, (size_t)i + 1, (size_t)j + 1);

      temp1 = GSL_MIN(temp_dij, temp_dij1);
      temp2 = GSL_MIN(temp_di1j, temp_di1j1);
      dmin = GSL_MIN(temp1, temp2);
      temp1 = GSL_MAX(temp_dij, temp_dij1);
      temp2 = GSL_MAX(temp_di1j, temp_di1j1);

      /*
      temp1 = GSL_MIN(d[i][j],d[i][j+1]);
      temp2 = GSL_MIN(d[i+1][j],d[i+1][j+1]);
      dmin  = GSL_MIN(temp1,temp2);
      temp1 = GSL_MAX(d[i][j],d[i][j+1]);
      temp2 = GSL_MAX(d[i+1][j],d[i+1][j+1]);
      */

      dmax = GSL_MAX(temp1, temp2);

      if (dmax < z[0] || dmin > z[nc - 1]) continue;
      for (k = 0; k < nc; k++) {
        if (z[k] < dmin || z[k] > dmax) continue;
        for (m = 4; m >= 0; m--) {
          if (m > 0) {
            temp_diimmm1 =
                gsl_matrix_get(d, (size_t)i + im[m - 1], (size_t)j + jm[m - 1]);

            h[m] = temp_diimmm1 - z[k];
            xh[m] = x[i + im[m - 1]];
            yh[m] = y[j + jm[m - 1]];

            /*
            h[m]  = d[i+im[m-1]][j+jm[m-1]]-z[k];
            xh[m] = x[i+im[m-1]];
            yh[m] = y[j+jm[m-1]];
            */
          } else {
            h[0] = 0.25 * (h[1] + h[2] + h[3] + h[4]);
            xh[0] = 0.50 * (x[i] + x[i + 1]);
            yh[0] = 0.50 * (y[j] + y[j + 1]);
          }
          if (h[m] > 0.0)
            sh[m] = 1;
          else if (h[m] < 0.0)
            sh[m] = -1;
          else
            sh[m] = 0;
        }

        /*
         Note: at this stage the relative heights of the corners and the
         centre are in the h array, and the corresponding coordinates are
         in the xh and yh arrays. The centre of the box is indexed by 0
         and the 4 corners by 1 to 4 as shown below.
         Each triangle is then indexed by the parameter m, and the 3
         vertices of each triangle are indexed by parameters m1,m2,and m3.
         It is assumed that the centre of the box is always vertex 2
         though this isimportant only when all 3 vertices lie exactly on
         the same contour level, in which case only the side of the box
         is drawn.
         vertex 4 +-------------------+ vertex 3
         | \               / |
         |   \    m-3    /   |
         |     \       /     |
         |       \   /       |
         |  m=2    X   m=2   |       the centre is vertex 0
         |       /   \       |
         |     /       \     |
         |   /    m=1    \   |
         | /               \ |
         vertex 1 +-------------------+ vertex 2
         */
        /* Scan each triangle in the box */
        for (m = 1; m <= 4; m++) {
          m1 = m;
          m2 = 0;
          if (m != 4)
            m3 = m + 1;
          else
            m3 = 1;
          if ((case_value = castab[sh[m1] + 1][sh[m2] + 1][sh[m3] + 1]) == 0)
            continue;
          switch (case_value) {
            case 1: /* Line between vertices 1 and 2 */
              x1 = xh[m1];
              y1 = yh[m1];
              x2 = xh[m2];
              y2 = yh[m2];
              break;
            case 2: /* Line between vertices 2 and 3 */
              x1 = xh[m2];
              y1 = yh[m2];
              x2 = xh[m3];
              y2 = yh[m3];
              break;
            case 3: /* Line between vertices 3 and 1 */
              x1 = xh[m3];
              y1 = yh[m3];
              x2 = xh[m1];
              y2 = yh[m1];
              break;
            case 4: /* Line between vertex 1 and side 2-3 */
              x1 = xh[m1];
              y1 = yh[m1];
              x2 = xsect(m2, m3);
              y2 = ysect(m2, m3);
              break;
            case 5: /* Line between vertex 2 and side 3-1 */
              x1 = xh[m2];
              y1 = yh[m2];
              x2 = xsect(m3, m1);
              y2 = ysect(m3, m1);
              break;
            case 6: /* Line between vertex 3 and side 1-2 */
              x1 = xh[m3];
              y1 = yh[m3];
              x2 = xsect(m1, m2);
              y2 = ysect(m1, m2);
              break;
            case 7: /* Line between sides 1-2 and 2-3 */
              x1 = xsect(m1, m2);
              y1 = ysect(m1, m2);
              x2 = xsect(m2, m3);
              y2 = ysect(m2, m3);
              break;
            case 8: /* Line between sides 2-3 and 3-1 */
              x1 = xsect(m2, m3);
              y1 = ysect(m2, m3);
              x2 = xsect(m3, m1);
              y2 = ysect(m3, m1);
              break;
            case 9: /* Line between sides 3-1 and 1-2 */
              x1 = xsect(m3, m1);
              y1 = ysect(m3, m1);
              x2 = xsect(m1, m2);
              y2 = ysect(m1, m2);
              break;
            default:
              break;
          }

          /* Finally draw the line */

          // ConrecLine(x1,y1,x2,y2,z[k]);

          // printf("%15.6f %15.6f %15.6f %15.6f %15.6f\n",x1,y1,x2,y2,z[k]);

          // if ( z[k] == 0. )
          //{
          //	fprintf(f , "%15.6f %15.6f"
          //}

          if (write_in_file) {
            fprintf(file,
                    _DFMT_
                    " "_DFMT_
                    " "_DFMT_
                    " "_DFMT_
                    "\n",
                    x1, y1, x2, y2, z[k]);
          }

          if (z[k] == val) {
            smthg_out++;
            gsl_matrix_set(out, ind_out_i, (size_t)0, x1);
            gsl_matrix_set(out, ind_out_i, (size_t)1, y1);
            gsl_matrix_set(out, ind_out_i + 1, (size_t)0, x2);
            gsl_matrix_set(out, ind_out_i + 1, (size_t)1, y2);

            ind_out_i += 2;
          }
        } /* m */
      }   /* k - contour */
    }     /* i */
  }       /* j */

  fclose(file);

  return smthg_out;
}

void print_matrice(gsl_matrix *m, int nl, int nc, FILE *f) {
  for (int i = 0; i < nl; i++) {
    for (int j = 0; j < nc; j++) {
      fprintf(f, "%10f ", gsl_matrix_get(m, (size_t)i, (size_t)j));
    }
    fprintf(f, "\n");
  }
}

int main(void) {
  double f(double x, double y) { return x * x + y * y - 1.; }

  int x_nbpts = 50;
  int y_nbpts = 50;

  double xlo = -2.;
  double xhi = +2.;

  double ylo = -2.;
  double yhi = +2.;

  double x_it = (xhi - xlo) / (double)x_nbpts;
  double y_it = (yhi - ylo) / (double)y_nbpts;

  // tableaux des valeurs de x et de y
  double x[x_nbpts];
  double y[y_nbpts];

  // Remplissage des tableaux x et y
  for (int i = 0; i < x_nbpts; i++) {
    x[i] = xlo + i * x_it;
  }

  for (int i = 0; i < y_nbpts; i++) {
    y[i] = ylo + i * y_it;
  }

  // matrice des valeurs de z
  // double m[x_nbpts][y_nbpts] ;

  gsl_matrix *m = gsl_matrix_alloc((size_t)x_nbpts, (size_t)y_nbpts);

  // remplissage de la matrice
  for (int i = 0; i < x_nbpts; i++) {
    for (int j = 0; j < y_nbpts; j++) {
      gsl_matrix_set(m, (size_t)i, (size_t)j, f(x[i], y[j]));
      // m[i][j] = f ( x[i] , y[j] ) ;
    }
  }

  int contour_nb = 2;

  double contour_tab[contour_nb];

  contour_tab[0] = 0.;
  contour_tab[1] = 1.;

  // print_matrice ( m , x_nbpts , y_nbpts , stdout );

  gsl_matrix *m_out = gsl_matrix_alloc(x_nbpts * y_nbpts, 2);

  int nb_mat =
      Surface_Contour(m, 0, x_nbpts - 1, 0, y_nbpts - 1, x, y, contour_nb,
                      contour_tab, 0., m_out, "test_write.dat", true);

  printf("nb_mat = %d \n", nb_mat);

  FILE *file = fopen("test_m_out.dat", "w");

  print_matrice(m_out, nb_mat * 2, 2, file);

  fclose(file);

  gsl_matrix_free(m);
  gsl_matrix_free(m_out);

  return 0;
}
